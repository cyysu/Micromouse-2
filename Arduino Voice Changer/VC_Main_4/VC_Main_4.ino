#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <TimerOne.h>

Adafruit_MCP4725 dac;

// set both equal to 1 for unchanged voice.
#define CHUNK 512 // max ~ 850 from dynamic memory, max = 1023 from uint16_t voiceIn/voiceOut.
#define FSEL_INCON (16 / 1023 / 2) // used to convert analogRead input into one of the levels in fSelCase.
#define FSEL_PIN 1 // input fSelPin = A1
#define FREF_PIN 13 // output 5v reference, to be voltaged divided with 10 kOhm resistor and POT.
#define FSEL_TIME (unsigned long)1024 // used in if statement to modulate millis(), to regulate analogRead for fSelCase.

boolean fSelReady = true;
uint8_t fSelCase = 0; // percent speed to play back voice (  15 |  14 |  13 |  12 |  11 |  10 |   9 |   8 |   0 |  1   |  2   |  3  |  4   |  5   |  6   |  7
                      //                                 =  xxx | 400 | 300 | 250 | 200 | 175 | 150 | 125 | 100 | 87.5 | 75.0 |67.5 | 50.0 | 37.5 | 25.0 | 12.5).

uint16_t voiceIn = 1; //ahead by 1 to prevent permanent simultaneous read/write when modSlow = 1.
uint16_t voiceOut = 0;
int speakerOut = 11;
uint16_t voiceVec[CHUNK];

void setup()
{
  // http://www.robotplatform.com/knowledge/ADC/adc_tutorial_3.html
  ADMUX |= (0 & 0x07);    // set A0 analog input pin?
  ADMUX |= (1 << REFS0);  // set reference voltage

  // http://www.robotplatform.com/knowledge/ADC/adc_tutorial_2.html
  // sampling rate is [ADC clock] / [prescaler] / [conversion clock cycles]
  // for Arduino Uno ADC clock is 16 MHz and a conversion takes 13 clock cycles
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescaler for 9.615 kHz
  //ADCSRA |= (1 << ADPS2) | (1 << ADPS1);    // 64 prescaler for 19.231 kHz
  //ADCSRA |= (1 << ADPS2) | (1 << ADPS0);    // 32 prescaler for 38.462 KHz
  //ADCSRA |= (1 << ADPS2);                   // 16 prescaler for 76.923 KHz
  //ADCSRA |= (1 << ADPS1) | (1 << ADPS0);    // 8 prescaler for 153.846 KHz
  // must remain between 3.846 and 15.385 kHz (50 and 200 kHz before /13 clock cycles), kHzaccording to datasheet?

  ADCSRA |= (1 << ADATE); // enable auto trigger
  ADCSRA |= (1 << ADEN);  // enable ADC
  ADCSRA |= (1 << ADSC);  // start ADC conversion

  Timer1.initialize(100); // timer period (in microseconds)
  Timer1.attachInterrupt(callback); // blinkLED to run at 9000 Hz

  dac.begin(0x62);

//  pinMode(A1, INPUT);
//  
  pinMode(FREF_PIN, OUTPUT);
  digitalWrite(FREF_PIN, HIGH); // to be used in voltage divider circuit for fSelCase.

  Serial.begin(115200);
}

void callback()
{
  uint8_t low, high;

  ADMUX = (ADMUX & 0xF0) | 0x00;    // set A0 analog input pin
  ADCSRA |= (1 << ADSC);  // start ADC conversion
//  ADMUX |= (0 & 0x07);    // set A0 analog input pin?
//  ADMUX |= (1 << REFS0);  // set reference voltage
  low = ADCL;
  high = ADCH;
  voiceVec[voiceIn] = (high << 8) | low;
  
  voiceIn = (voiceIn + 1) % CHUNK;
  
  switch (fSelCase){
    case 0: // 100%
      voiceOut = (voiceOut + 1) % CHUNK; // 8/8
    break;
    case 1: // 87.5%
      if (voiceIn % 8){ voiceOut = (voiceOut + 1) % CHUNK; } // 7/8
    break;
    case 2: // 75.0%
      if (voiceIn % 4){ voiceOut = (voiceOut + 1) % CHUNK; } // 6/8
    break;
    case 3: // 67.5%
      if (voiceIn % 3){ voiceOut = (voiceOut + 1) % CHUNK; } // 5/8
    break;
    case 4: // 50.0%
      if (voiceIn % 2){ voiceOut = (voiceOut + 1) % CHUNK; } // 4/8
    break;
    case 5: // 37.5%
      if (!(voiceIn % 3)){ voiceOut = (voiceOut + 1) % CHUNK; } // 3/8
    break;
    case 6: // 25.0%
      if (!(voiceIn % 4)){ voiceOut = (voiceOut + 1) % CHUNK; } // 2/8
    break;
    case 7: // 12.5%
      if (!(voiceIn % 8)){ voiceOut = (voiceOut + 1) % CHUNK; } // 1/8
    break;
    case 8: // 125%
      if (voiceIn % 4){ voiceOut = (voiceOut + 2) % CHUNK; } // 10/8
      else { voiceOut = (voiceOut + 1) % CHUNK; }
    break;
    case 9: // 150%
      if (voiceIn % 2){ voiceOut = (voiceOut + 2) % CHUNK; } // 12/8
      else { voiceOut = (voiceOut + 1) % CHUNK; }
    break;
    case 10: // 175%
      if (!(voiceIn % 4)){ voiceOut = (voiceOut + 2) % CHUNK; } // 14/8
      else { voiceOut = (voiceOut + 1) % CHUNK; }
    break;
    case 11: // 200%
      voiceOut = (voiceOut + 2) % CHUNK; // 16/8
    break;
    case 12: // 250%
      if (!(voiceIn % 3)){ voiceOut = (voiceOut + 2) % CHUNK; } // 20/8
      else { voiceOut = (voiceOut + 1) % CHUNK; }
    break;
    case 13: // 300%
      voiceOut = (voiceOut + 3) % CHUNK; // 24/8
    break;
    case 14: // 400%
      voiceOut = (voiceOut + 4) % CHUNK; // 32/8
    break;
    default: break; // do nothing, includes case 15 (analogRead from fSelPin = 1023).
  }
}

void loop(void)
{
  dac.setVoltage(voiceVec[voiceOut], false);
  
  if(!(millis() % FSEL_TIME) && fSelReady) // triggers when millis is evenly divisible by FSEL_TIME, used to limit analogRead frequency.
  {
    ADMUX = (ADMUX & 0xF0) | 0x01;    // set A1 analog input pin.
    ADCSRA |= (1 << ADSC);  // start ADC conversion
//    ADMUX |= (0 & 0x07);    // set A0 analog input pin?
//    ADMUX |= (1 << REFS0);  // set reference voltage
    uint8_t low, high;
    
    low = ADCL;
    high = ADCH;
    fSelCase = (high << 8) | low;
    
    //fSelCase = floor(fSelCase * FSEL_INCON); // fSelCase = input * 16 / 1023, rounded down.
    
    Serial.println(fSelCase);

    fSelReady = false;
  } 
  else if(millis() % FSEL_TIME) 
  {
    fSelReady = true;
  }
  
}
