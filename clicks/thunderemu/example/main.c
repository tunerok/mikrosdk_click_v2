/*!
 * @file main.c
 * @brief Thunder EMU Click example
 *
 * # Description
 * This example demonstrates the use of Thunder EMU click board by generating
 * CLOSE, MID, or FAR range thunder signal depending on the click push-buttons state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Checks if any of the click board buttons are pressed and then generates a thunder
 * signal related to the pressed button and displays an appropriate message on the USB UART.
 * 
 * @note
 * Thunder EMU click should be used in combination with a Thunder click which detects
 * a lightning presence. The emulator is calibrated for ranges of up to 15cm from the sensor board.
 * It's recommended to distant both click boards from their development boards using a Shuttle click
 * to reduce the board noise that can affect the sensor and emulator performance.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thunderemu.h"

static thunderemu_t thunderemu;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thunderemu_cfg_t thunderemu_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    thunderemu_cfg_setup( &thunderemu_cfg );
    THUNDEREMU_MAP_MIKROBUS( thunderemu_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thunderemu_init( &thunderemu, &thunderemu_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THUNDEREMU_ERROR == thunderemu_default_cfg ( &thunderemu ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( !thunderemu_get_close_pin ( &thunderemu ) )
    {
        if ( THUNDEREMU_OK == thunderemu_generate_thunder ( &thunderemu, THUNDEREMU_MODE_CLOSE ) )
        {
            log_printf( &logger, " Close range thunder signal generated!\r\n\n" );
            Delay_ms ( 500 );
        }
    }
    else if ( !thunderemu_get_mid_pin ( &thunderemu ) )
    {
        if ( THUNDEREMU_OK == thunderemu_generate_thunder ( &thunderemu, THUNDEREMU_MODE_MID ) )
        {
            log_printf( &logger, " Mid range thunder signal generated!\r\n\n" );
            Delay_ms ( 500 );
        }
    }
    else if ( !thunderemu_get_far_pin ( &thunderemu ) )
    {
        if ( THUNDEREMU_OK == thunderemu_generate_thunder ( &thunderemu, THUNDEREMU_MODE_FAR ) )
        {
            log_printf( &logger, " Far range thunder signal generated!\r\n\n" );
            Delay_ms ( 500 );
        }
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
