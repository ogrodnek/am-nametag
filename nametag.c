#include <avr/io.h>
#include <avr/eeprom.h> 

void setup(void);
void loop(void);
void delay_ms(uint16_t ms);

uint8_t EEMEM ProgramConfig = 0;
int program = 0;

int main(void) {
  setup();

  program = eeprom_read_byte(&ProgramConfig);
  if (program > 1) {
    program = 0;
  }

  eeprom_write_byte(&ProgramConfig, 1 - program);
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
  if (program) {
    blink();
  } else {
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

void allOn() {
  int i;
  for (i=0; i< 5; i++) {
    PORTB = states[i];
  }
}
