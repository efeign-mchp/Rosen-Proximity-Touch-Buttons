/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "app.h"                        // EVF_Changes Touch example


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    // Enable and set LED PWMs
    TC0_CompareStart();
    TC2_CompareStart();
    TC2_Compare8bitMatch0Set(0); // PROXIMITY - UNSHIELDED LED0 PWM
    TC0_Compare8bitMatch1Set(0); // PROXIMITY - DRIVEN SHIELD LED3 PWM
    TC2_Compare8bitMatch1Set(0); // BUTTON 1 LED1 PWM
    TC0_Compare8bitMatch0Set(0); // BUTTON 2 LED2 PWM

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        app();  // EVF_Changes
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

