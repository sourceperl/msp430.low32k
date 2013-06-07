#include <msp430.h>

#define RED_LED BIT0

unsigned int wdtCounter = 0;

int main(void)
{
    /* Set watchdog timer interval to 1000ms (requires external crystal to work) */
    WDTCTL = WDT_ADLY_1000;

    /* "Interrupt enable 1" for the Watchdog Timer interrupt */
    IE1 |= WDTIE;

    /* Set the LED pin as an output pin */
    P1DIR |= RED_LED;

    /* Turn on LED pin */
    P1OUT |= RED_LED;

    /* Go into low power mode 3, general interrupts enabled */
    __bis_SR_register( LPM3_bits + GIE );

    /* Do nothing...forever */
    for( ; ; ) { }
}

/* Watchdog Timer interrupt service routine.  The function prototype
 *  * tells the compiler that this will service the Watchdog Timer, and
 *   * then the function follows.
 *    */
interrupt(WDT_VECTOR) watchdog_timer(void)
{
    wdtCounter++;

    /* Count 1 interrupts x 1000ms = 1000ms, or one second */
    if(wdtCounter == 1) {
        /* Blink the LED pin */
        P1OUT ^= RED_LED;

        /* Reset the counter for the next blink */
        wdtCounter = 0;
    }
}
