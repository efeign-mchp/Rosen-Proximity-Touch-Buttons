
/* 
 * File:   app.c
 *
 * SAML10 + QT4 Proximity & Touch Buttons with basic 8bit PWM controlling LEDs
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
uint8_t LED0_pwm_val = 0;
uint8_t LED1_pwm_val = 0;
uint8_t LED2_pwm_val = 0;
uint8_t LED3_pwm_val = 0;

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
    touch_delta_t delta0, delta1;
    uint8_t pwm0, pwm1;

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

/*  Replaced with PWM control of LED
    // PROXIMITY - UNSHIELDED
	if (0u != (key_status & (1<<0))) {
        LED0_Clear();   // LED on
	} else {
        LED0_Set();     // LED off    
    }
*/

/*  Replaced with PWM control of LED
    // PROXIMITY - DRIVEN SHIELD    
    if (0u != (key_status & (1<<1))) {
        LED3_Clear();   // LED on
     } else {
        LED3_Set();     // LED off
    }
*/
    
    // BUTTON1
	if (0u != (key_status & (1<<2))) {
        LED1_pwm_val += 2;
        TC2_Compare8bitMatch1Set(LED1_pwm_val);
	} else {
        TC2_Compare8bitMatch1Set(0); // LED off
    }
	
    // BUTTON2
    if (0u != (key_status & (1<<3))) {
        LED2_pwm_val += 2;
        TC0_Compare8bitMatch0Set(LED2_pwm_val);
    } else {
        TC0_Compare8bitMatch0Set(0); // LED off
    }


    // PROXIMITY - UNSHIELDED
    // Touch delta
	delta0 = get_sensor_node_signal(0) - get_sensor_node_reference(0);
    if (delta0 <= 0) {
        pwm0 = 0;
    }
    else if (delta0 > 255) {
        pwm0 = 255;
    }
    else {
        pwm0 = (uint8_t) delta0;
    }
    TC2_Compare8bitMatch0Set(pwm0);
    
    // PROXIMITY - DRIVEN SHIELD
    // Touch delta
	delta1 = get_sensor_node_signal(1) - get_sensor_node_reference(1);
    if (delta1 <= 0) {
        pwm1 = 0;
    }
    else if (delta1 > 255) {
        pwm1 = 255;
    }
    else {
        pwm1 = (uint8_t) delta1;
    }
    TC0_Compare8bitMatch1Set(pwm1);
}

