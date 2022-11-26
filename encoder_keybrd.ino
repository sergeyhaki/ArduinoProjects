#include <LiquidCrystal.h>
//LiquidCrystal lcd(33, 32, 31, 30, 29, 28);  //rs, en, d4, d5, d6, d7  m128L version
LiquidCrystal lcd(26, 27, 28, 29, 30, 31);  //rs, en, d4, d5, d6, d7  m64 version
//LiquidCrystal lcd(23, 22, 21, 20, 19, 18);  //rs, en, d4, d5, d6, d7 m16 version

//map for m64 version
#define ENC_A PE2
#define ENC_B PE3
#define BTN_MENU PE6
#define BTN_SELECT PE5
#define BTN_OK PE4
#define BTN_SUM ((1 << BTN_MENU) | (1 << BTN_SELECT) | (1 << BTN_OK))

void setup() {
  Serial.begin(57600);  
  DDRB |= (1 << PB7); //Pin 17 / OC2  
  DDRA |= (1 << PA0) | (1 << PA1);//test port  
  PORTE |= (1 << BTN_OK) | (1 << BTN_SELECT) | (1 << BTN_MENU) | (1 << ENC_B) | (1 << ENC_A); //pull-up
  lcd.begin(16, 2);  
  
  //timer2 setup
  TCCR2 = (1 << WGM20) | (1 << WGM21) | (2 << COM20) | 4;
  TIMSK |= (1 << OCIE2);
  OCR2 = 124;  
}

void loop() {  
}

ISR(TIMER2_COMP_vect) {
  uint8_t kbrdState, eventState;
  kbrdState = BTN_SUM - (PINE & ((1 << BTN_MENU) | (1 << BTN_SELECT) | (1 << BTN_OK)));
  
  encoderState = PINE & ((1 << ENC_A) | (1 << ENC_B));
  if ((encoderState == (1 << ENC_A)) and (lastEncoderState == (1 << ENC_B))) {
    if (!eventMode) {
      freq -= step;
      changeFreq = 1;     
    }  
  eventState = ENC_EVENT_LEFT;
  } 
  else if ((encoderState == (1 << ENC_B)) and (lastEncoderState == (1 << ENC_A))) {
    if (!eventMode) {
      freq += step;
      changeFreq = 1;      
    }
    eventState = ENC_EVENT_RIGHT;
  }
  if (encoderState) {
    lastEncoderState = encoderState;
  }  
  if (kbrdState) {
    switch (kbrdState) {
      case (1 << BTN_MENU):
        eventState = KBD_EVENT_MENU;
        break;
      case (1 << BTN_SELECT):
        eventState = KBD_EVENT_SELECT;
        break;
      case (1 << BTN_OK):
        eventState = KBD_EVENT_OK;
        break;
    }
  }  
}
