#include <msp430g2553.h>

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR = 0x01;   // make P1.0 as output
	P1OUT = 0x00;   // make outputs low

	// set up clocks
	BCSCTL1 = CALBC1_1MHZ;  // set range
	DCOCTL = CALDCO_1MHZ;   // set step

	// set up timer
	TACCR0 = 62499; // count up to 62499
	TACCTL0 = CCIE; // enable the interrupt in control register
	TACTL = TASSEL_2 + ID_3 + MC_1 + TACLR;

	_enable_interrupt();
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void CCR0_ISR(void)
{
    P1OUT ^= 0x01;
}
