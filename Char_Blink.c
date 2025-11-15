
#define F_CPU 1000000UL      // ATtiny45 internal 8 MHz oscillator
#include <avr/io.h>
#include <util/delay.h>
#include <xc.h>

int main(void)
{
    // Use PB0 (pin 5) as output
    char List[] = {'0','1','2','3','4','5','A','B','C','D'};
    DDRB |= 0xFF;      
    
    for(int z = 0 ; z < 10 ; z++ ) {
       PORTB = List[z];
       _delay_ms(500);
    };
  
}
