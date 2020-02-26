
/* 
 * File:   app.c
 *
 * SAML10 + QT4 Proximity & Touch Buttons with simple on/off LEDs
 */

/*----------------------------------------------------------------------------
 *     include files
 *----------------------------------------------------------------------------*/
#include "definitions.h"                // SYS function prototypes
#include "app.h"

/*----------------------------------------------------------------------------
 *   Extern variables
 *----------------------------------------------------------------------------*/
extern volatile uint8_t measurement_done_touch;

/*----------------------------------------------------------------------------
 *   Global variables
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *   prototypes
 *----------------------------------------------------------------------------*/
void touch_status_display(void);

/*----------------------------------------------------------------------------
 *   function definitions
 *----------------------------------------------------------------------------*/

/*============================================================================
void app(void)
------------------------------------------------------------------------------
Purpose: This function provides sample code snippet to process and check the
         status of touch library
Input  : none
Output : none
Notes  : 
============================================================================*/

void app(void)
{
	touch_process();
    if (measurement_done_touch == 1) {
        measurement_done_touch = 0; // reset flag
        touch_status_display();
    }
}

///*============================================================================
//void touch_status_display(void)
//------------------------------------------------------------------------------
//Purpose: Sample code snippet to demonstrate how to check the status of the
//         sensors
//Input  : none
//Output : none
//Notes  : none
//============================================================================*/
void touch_status_display(void)
{
    uint8_t key_status = 0;

    for (uint8_t i = 0; i < DEF_NUM_SENSORS; i++)
    {
        if (0u != (get_sensor_state(i) & KEY_TOUCHED_MASK)) {
            key_status |= 1 << i;
        } 
    }
    
    // Note if any key is pressed
    if (0u != key_status) {
        USER_LED_Clear();   // LED on
	} else {
        USER_LED_Set();     // LED off    
    }

	if (0u != (key_status & (1<<0))) {
        LED0_Clear();   // LED on
	} else {
        LED0_Set();     // LED off    
    }
	
    if (0u != (key_status & (1<<1))) {
        LED3_Clear();   // LED on
    } else {
        LED3_Set();     // LED off
    }
    
	if (0u != (key_status & (1<<2))) {
        LED1_Clear();   // LED on
	} else {
        LED1_Set();     // LED off    
    }
	
    if (0u != (key_status & (1<<3))) {
        LED2_Clear();   // LED on
    } else {
        LED2_Set();     // LED off
    }
}

