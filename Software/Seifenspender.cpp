/*



PinOut:
    - 
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

//Liest ADC Pin und konvertiert Schalterstellung mit Widerstandsnetzwerk in Zeitwert 
void setTime()
{
    ;
}

//ISR
ISR(PCINT0_vect)
{
    ;
}

int main()
{
    // Interrupts deaktivieren & initialisieren
    cli();   

    // Definieren der PB0-PB3 Outputs, PB4 Input, PB5 Input
    DDRB = ((1 << DDB3) | (1 << DDB2) | (1 << DDB1) | (1 << DDB0));

    // Vorrübergehend: Pull-Up auf Reset Pin aktivieren. Eigentlich ist PB5 durch R10 auf High gezogen.
    PORTB |= (1 << PORTB5);

    // Timer auf Normal Mode stellen (ist normalerweise default)
    TCCR0A = 0x00;

    // Setzen aller Register für Pin Change Interrupt PCINT4
    PCMSK = (1 << PCINT4);  // Pin Change Interrupt für Pin 4 demaskieren
    GIMSK |= (1 << PCIE);   // Pin Change Interrupt aktivieren
    
    // Tiefschalfmodus als Schlafmodus setzen. 
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
    
    // Interrupts aktivieren
    sei();          

    // Endlos schlafen gehen sobald er wieder aufwacht.
    do
    {
        sleep_mode();
    } while(1);
}