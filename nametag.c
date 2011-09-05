#include <avr/io.h>
#include <avr/eeprom.h> 

void setup(void);
void loop(void);
void delay_ms(uint16_t ms);

void blink(void);
void flash(void);
void fade(void);
void pwm(void);
void allOn(void);


#define MAX_PROGRAMS 4
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
    allOn();
    break;
  case 1:
    blink();
    break;
  case 2:
    fade();
    break;
  case 3:
    flash();
    break;
  default:
    allOn();
  }
}

uint8_t blinkState = 0;
unsigned long lastBlink = 0;
unsigned long clock = 0;

void blink() {
  if (clock - lastBlink > 25000) {
    blinkState++;
    if (blinkState > 4) {
      blinkState = 0;
    }
    lastBlink = clock;
  }

  PORTB = states[blinkState];

  clock++;
}

uint8_t flashState = 0;

void flash() {
  if (clock - lastBlink > 30000) {
    flashState = 1 - flashState;
    lastBlink = clock;
  }

  if (flashState) {
    blinkState++;
    if (blinkState > 4) {
      blinkState = 0;
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

void fade() {
  if (clock - lastBlink > 1800) {
    lastBlink = clock;

    level += dir;
    if (level == 0 || level >= 200) {
      dir = -1 * dir;
    }
  }

  pwm();

  clock++;
}

unsigned long lastPwm = 0;

void pwm() {
  static uint8_t pwmCnt = 0;
  static uint8_t which = 0;

  pwmCnt++;

  if (level > pwmCnt) {
    PORTB = states[which];
    which++;
    if (which > 4) {
      which = 0;
    }
  } else {
    PORTB = 0;
  }
}

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
