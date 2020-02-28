#include <atmel_start.h>
// EVF_Changes start
#include <avr/io.h>
#include <avr/sleep.h>
#include "touch_example.h"

// FUSES and LOCKBITS configuration here allows you to build them into the ELF (Executable and Linkable Format) production programming file
// From Atmel Studio menu Tools / Device Programming, then go to Production File. Select the .elf file, enable Flash, Fuses and  Lock bits, the click Program.

FUSES = {
	PERIOD_OFF_gc,		// WDTCFG;  /* Watchdog Configuration */ /* Off */
	LVL_BODLEVEL0_gc,	// BODCFG;  /* BOD Configuration */ /* 1.8 V */
	FREQSEL_20MHZ_gc, // OSCCFG;  /* Oscillator Configuration */
	0xff, // reserved
	0x00, // TCD0CFG;  /* TCD0 Configuration */
	0xf7, // SYSCFG0;  /* System Configuration 0 */ */ No CRC of Boot nor Application code, Enable UPDI, EEPROM not erased */
	SUT_64MS_gc, // SYSCFG1;  /* System Configuration 1 */ /* 64ms start up time */
	0x00, // APPEND;  /* Application Code Section End */
	0x00, // BOOTEND;  /* Boot Section End */
};

LOCKBITS = LB_NOLOCK_gc;	/* No locks */
// LOCKBITS = LB_RWLOCK_gc;	/* Read and write lock */


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	set_sleep_mode(SLEEP_MODE_IDLE);

	/* Replace with your application code */
	while (1) {
		
		touch_example();
				
		sleep_mode();
	}
}
// EVF_Changes end