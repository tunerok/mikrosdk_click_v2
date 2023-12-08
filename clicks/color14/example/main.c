/*!
 * @file main.c
 * @brief Color14 Click example
 *
 * # Description
 * This application showcases ability of click board to read RGB and IR data
 * from device. Also it can be configured to read proximity data and
 * ALS data in lux units.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of host communication modules (UART, I2C) and additonal pin.
 * Read and check device ID, selects example and configures device for it.
 *
 * ## Application Task
 * Depending of selected example in task proximity and als data will be read from
 * device, or it will show ADC value for red, green, blue and ir data from device.
 * 
 * ### Additioal function
 * static void color13_proximity_als_example ( void );
 * static void color13_rgb_example ( void );
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "color14.h"

#define COLOR14_EXAMPLE_PS_LS   3
#define COLOR14_EXAMPLE_RGB     6

static color14_t color14;
static log_t logger;

static uint8_t example_type;

/**
 * @brief Proximity and Als data reading.
 * @details Example function for reading proximity and als data.
 * @return Nothing
 */
static void color14_proximity_als_example ( void );

/**
 * @brief RGB data reading.
 * @details Example function for reading rgb and ir data.
 * @return Nothing
 */
static void color14_rgb_example ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color14_cfg_t color14_cfg;  /**< Click config object. */

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
    color14_cfg_setup( &color14_cfg );
    COLOR14_MAP_MIKROBUS( color14_cfg, MIKROBUS_1 );
    err_t init_flag = color14_init( &color14, &color14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    uint8_t temp_data = 0;
    init_flag = color14_generic_read( &color14, COLOR14_REG_PART_ID, &temp_data, 1 );
    log_printf( &logger, " > ID: 0x%.2X\r\n", ( uint16_t )temp_data );
    
    if ( ( COLOR14_OK != init_flag ) && ( COLOR14_ID != temp_data ) )
    {
        log_error( &logger, " ID" );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    //Select example
    example_type = COLOR14_EXAMPLE_RGB;
    color14_generic_write( &color14, COLOR14_REG_MAIN_CTRL, &example_type, 1 );
    
    if ( COLOR14_EXAMPLE_PS_LS == example_type )
    {
        //Configure proximity data to 11 bit
        color14_generic_read( &color14, COLOR14_REG_PS_MEASRATE, &temp_data, 1 );
        temp_data |= 0x18;
        color14_generic_write( &color14, COLOR14_REG_PS_MEASRATE, &temp_data, 1 );
    }
    
    Delay_ms( 1000 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    switch ( example_type )
    {
        case COLOR14_EXAMPLE_PS_LS:
        {
            color14_proximity_als_example( );
            break;
        }
        case COLOR14_EXAMPLE_RGB:
        {
            color14_rgb_example( );
            break;
        }
        default:
        {
            log_error( &logger, " Select example!" );
            break;
        }
    }
    Delay_ms( 500 );
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

static void color14_proximity_als_example ( void )
{
    //Proximity data
    uint16_t ps_data = 0;
    err_t error_flag = color14_get_proximity( &color14, &ps_data );
    log_printf( &logger, " > PS: %u\r\n", ps_data );
    if ( COLOR14_ERROR_OVF == error_flag )
    {
        log_error( &logger, " Overflow" );
    }
    //ALS data
    float lux = 0;
    color14_get_als( &color14, &lux );
    log_printf( &logger, " > LS[ lux ]: %.2f\r\n", lux );
    log_printf( &logger, "**********************************\r\n" );
}

static void color14_rgb_example ( void )
{
    color14_color_t color_data;

    color14_get_rgb_ir( &color14, &color_data );
    
    log_printf( &logger, " > R: %u\r\n", color_data.red );
    log_printf( &logger, " > G: %u\r\n", color_data.green );
    log_printf( &logger, " > B: %u\r\n", color_data.blue );
    log_printf( &logger, " > IR: %u\r\n", color_data.ir );
    log_printf( &logger, "**********************************\r\n" );
}

// ------------------------------------------------------------------------ END
