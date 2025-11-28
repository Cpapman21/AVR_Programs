
#define F_CPU 1000000UL      // ATtiny45 internal 8 MHz oscillator
#include <avr/io.h>
#include <util/delay.h>
#include <xc.h>

#define MAX_PINS 6                              // up to PB0?PB5
#define MAX_LEDS (MAX_PINS * (MAX_PINS - 1))    // N*(N-1)

// Global config
static uint8_t charlie_pins[MAX_PINS];   // bitmasks for each pin (e.g. (1<<PB0))
static uint8_t num_pins = 0;

// For each LED index, store which pin is VCC and which is GND (bitmask on PORTB/DDRB)
static uint8_t led_map[MAX_LEDS][2];     // [led][0]=vccMask, [led][1]=gndMask
static uint8_t num_leds = 0;

void charlie_init(const uint8_t *pins, uint8_t n)
{
    if (n < 2) return;           // need at least two pins
    if (n > MAX_PINS) n = MAX_PINS;

    num_pins = n;
    for (uint8_t i = 0; i < n; i++) {
        charlie_pins[i] = pins[i];
    }

    // Build LED map: ordered pairs (i, j) with i != j
    uint8_t k = 0;
    for (uint8_t i = 0; i < n; i++) {
        for (uint8_t j = 0; j < n; j++) {
            if (i == j) continue;
            led_map[k][0] = charlie_pins[i];   // VCC pin mask
            led_map[k][1] = charlie_pins[j];   // GND pin mask
            k++;
        }
    }
    num_leds = k;
}

// Optional helper to know how many LEDs you have
uint8_t charlie_get_led_count(void)
{
    return num_leds;   // = num_pins * (num_pins - 1)
}

static void charlie_all_off(void)
{
    uint8_t mask = 0;
    for (uint8_t i = 0; i < num_pins; i++) {
        mask |= charlie_pins[i];
    }

    DDRB  &= ~mask;   // inputs
    PORTB &= ~mask;   // no pull-ups
}

// Turn one LED on by index (0 .. num_leds-1)
void charlie_led_on(uint8_t led)
{
    if (led >= num_leds) return;

    uint8_t vccMask = led_map[led][0];
    uint8_t gndMask = led_map[led][1];

    // First tri-state everything
    charlie_all_off();

    // Configure the two pins:
    // VCC pin: output, high
    // GND pin: output, low
    DDRB  |= (vccMask | gndMask);
    PORTB &= ~gndMask;        // ensure GND pin is low
    PORTB |= vccMask;         // VCC pin high
}

// For multiplexing: briefly light LED, then turn off again
void charlie_led_pulse(uint8_t led)
{
    charlie_led_on(led);
    // insert a small delay here if desired
    _delay_ms(200);  // example
    charlie_all_off();
}

int main(void)
{
    uint8_t pins[] = {
        (1<<PB0),
        (1<<PB1),
        (1<<PB2)
    };

    charlie_init(pins, 3);  // works for 2,3,4,5,6 pins too

    while (1) {
        for (uint8_t i = 0; i < charlie_get_led_count(); i++) {
            charlie_led_pulse(i);    // light LED i for a moment
            // add delay between LEDs:  
        }
    }
}
