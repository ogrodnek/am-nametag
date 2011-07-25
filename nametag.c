#include <avr/io.h>
#include <avr/eeprom.h> 

void setup(void);
void loop(void);
void delay_ms(uint16_t ms);

#define MAX_PROGRAMS 3
uint8_t EEMEM ProgramConfig = 0;
int program = 0;

int main(void) {
  setup();

  program = eeprom_read_byte(&ProgramConfig);
  if (program >= MAX_PROGRAMS) {
    program = 0;
  }

  eeprom_write_byte(&ProgramConfig, program + 1);
  while (1) {
    loop();
  }

  return 0;
}

void setup() {
  DDRB = 255; // all output
  PORTB = 0;
}

const uint8_t states[] = {
  0b00000001,
  0b00000010,
  0b00000100,
  0b00001000,
  0b00010000
};

void loop() {
  switch (program) {
  case 0:
    blink();
    break;
  case 1:
    flash();
    break;
  case 2:
  default:
    allOn();
  }
}

int blinkState = 0;
unsigned long lastBlink = 0;
unsigned long clock = 0;

void blink() {
  if (clock - lastBlink > 15000) {
    blinkState++;
    if (blinkState > 4) {
      blinkState = 0;
    }
    lastBlink = clock;
  }

  PORTB = states[blinkState];

  clock++;
}

void flash() {
  if (clock - lastBlink > 20000) {
    blinkState = 1 - blinkState;
    lastBlink = clock;
  }

  if (blinkState) {
    allOn();
  } else {
    PORTB = 0;
  }

  clock++;
}

void allOn() {
  int i;
  for (i=0; i< 5; i++) {
    PORTB = states[i];
  }
}
