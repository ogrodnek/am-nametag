#include <avr/io.h>
#include <avr/eeprom.h> 
#include <util/delay.h>

void setup(void);
void loop(void);
void delay_ms(uint16_t ms);

void blink(void);
void flash(void);
void fade(void);
void pwm(void);
void allOn(void);

void delay_ms(uint16_t ms) {
  while (ms) {
    _delay_ms(1);
    ms--;
  }
}

#define MAX_PROGRAMS 4
uint8_t EEMEM ProgramConfig = 0;
int program = 0;

int main(void) {
  setup();

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

uint8_t blinkState = 0;
unsigned long totalBlinks = 0;

void loop() {

  unsigned long blinks = totalBlinks;

  blinkState = 0;
  while (totalBlinks - blinks < 2) {
    blink();
  }

  delay_ms(1000);

  blinks = totalBlinks;

  PORTB=0;
  blinkState = 3;
  while (totalBlinks - blinks < 8) {
    flash();
  }

  blinkState = 0;
  PORTB=0;

  delay_ms(1000);
}

unsigned long lastBlink = 0;
unsigned long clock = 0;

void blink() {
  if (clock - lastBlink > 70000) {
    blinkState++;
    if (blinkState > 2) {
      blinkState = 0;
    }
    lastBlink = clock;
    totalBlinks++;
  }

  PORTB = states[blinkState];

  clock++;
}

uint8_t flashState = 0;
void flash() {
  if (clock - lastBlink > 30000) {
    flashState = 1 - flashState;
    lastBlink = clock;
    totalBlinks++;
  }

  if (flashState) {
    blinkState++;
    if (blinkState > 4) {
      blinkState = 3;
    }

    PORTB=states[blinkState];
  } else {
    PORTB = 0;
  }

  clock++;
}

uint8_t level = 0;
uint8_t pwmCount = 0;
uint8_t dir = 1;

void allOn() {
  if (clock - lastBlink > 2) {
    blinkState++;
    if (blinkState > 4) {
      blinkState = 0;
    }
    lastBlink = clock;
  }

  PORTB = states[blinkState];

  clock++;
}
