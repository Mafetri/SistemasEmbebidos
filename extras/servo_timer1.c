#include <avr/io.h>
#include <util/delay.h>
#include "myutils.h"
#include "adc.h"

typedef struct {
    uint8_t tccr1a;
    uint8_t tccr1b;
    uint8_t tccr1c;
    uint8_t reserved;
    uint16_t tcnt1;
    uint16_t icr1;
    uint16_t ocr1a;
    uint16_t ocr1b;
} volatile timer1_t;

volatile timer1_t *timer1 = (timer1_t *)(0x80);
volatile uint8_t *timer1_timsk = (uint8_t *)(0x6F);

// Bits for Compare Output Mode
#define COM1A1 7

// Bits for Waveform Generation Mode
#define WGM10 0
#define WGM11 1
#define WGM12 3
#define WGM13 4

// Bits for Prescaler
#define CS10 0
#define CS11 1
#define CS12 2

void init_timer1() {
  // D9 as PWM output (OC1A)
  DDRB |= (1 << 1);
  
  // Clear OC1A1 on Compare Match (set output low level)
  timer1->tccr1a |= (1 << COM1A1);
  // Fast PWM with top ICR1
  timer1->tccr1a |= (1 << WGM11);
  timer1->tccr1b |= (1 << WGM13) | (1 << WGM12);
  // 8 prescaler (0.5 tick per us)
  timer1->tccr1b |= (1 << CS11);
  // ICR1 (when the counter register must be cleared, or length in ticks of the period)
  timer1->icr1 = 9900; // 20ms = 50hz -> 4MHz / (8 * 10000) = 50Hz

  // 0deg = 200 ticks
  // 90deg = 700 ticks
  // 180deg = 1200 ticks
  timer1->ocr1a = 700;
  delay_ms(500);
}

set_servo_width(int width) {
  int val = width / 3.4125;
  if(val < 200) {
    val = 200;
  } else if (val > 1200) {
    val = 1200;
  }

  timer1->ocr1a = val;
  delay_ms(20);
}

int main() {
  init_timer1();
  adc_init();
  int val;
  while(1) {
    set_servo_width(adc_get(2));
    delay_ms(500);
  }
  return 0;
}
