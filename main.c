/*
  sample code for MSP430 UART
  transmit serial data at 9600,N,8,1

  code for msp430-gcc
  MSP430G2553 at 1 MHz
*/

#include <msp430.h>
#include <legacymsp430.h>
#include <stdio.h>

/* some prototypes */

/* some vars */
unsigned int count;

/*
 * main routines
 */
int main(void)
{
  // Stop Watchdog
  WDTCTL = WDTPW + WDTHOLD;
  // MCLK:LFXT1CLK/8
  // SMCLK:LFXT1CLK
  BCSCTL2 = 0xF8;
  // IO setup (launchpad : bit 0 -> red led, bit 6 -> green led)
  P1DIR  |= BIT0;
  P1OUT  &= ~BIT0;
  // Timer A0 setup
  CCTL0 = CCIE;
  CCR0 = 0;
  TACCR0 = 0x3FF; // Period of 1023 + 1 cnts, which is 32Hz
  TACTL = 0x0211; // Timer_A: SMCLK, UP MODE, TAIE
  // Sleep
  while(1) 
    _BIS_SR(LPM1_bits + GIE);
}

/*
 * Timer A0 interrupt routine
 * 
 */
interrupt(TIMER0_A0_VECTOR) timer_a0_isr(void) {
  count++;
  if(count >= 250) {    // 10 * 32 ms = 320 ms, ≈.3 s
    P1OUT |= BIT0;   // P1.0 red LED on
    count = 0;
  } else {
    P1OUT &= ~BIT0;   // P1.0 red LED off
  }
}
