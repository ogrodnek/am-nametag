#include <avr/io.h>

void setup(void);
void loop(void);

int main(void) {
  setup();
  while (1) {
    loop();
  }

  return 0;
}

void setup() {
  PORTB = 0; // all off
  DDRB = 255; // all output
}

const uint8_t states[] = {
  0b00000001,
  0b00000010,
  0b00000100,
  0b00001000,
  0b00010000
};

void loop() {
  int i;
  for (i=0; i< 5; i++) {
    PORTB = states[i];
  }
}
