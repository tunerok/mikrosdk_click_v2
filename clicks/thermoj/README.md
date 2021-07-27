\mainpage Main Page
 
 

---
# Thermo J click

Thermo J Click is a temperature measurement click board™, which uses a thermocouple type-J probe, connected to a PPC-SMP-J onboard connector.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermoj_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-j-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the ThermoJ Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ThermoJ Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermoj_cfg_setup ( thermoj_cfg_t *cfg ); 
 
- Initialization function.
> THERMOJ_RETVAL thermoj_init ( thermoj_t *ctx, thermoj_cfg_t *cfg );

- Click Default Configuration function.
> void thermoj_default_cfg ( thermoj_t *ctx );


#### Example key functions :

- Check the status of data ready function.
> uint8_t thermoj_check_data_ready ( thermoj_t *ctx );
 
- Set thermocouple type sensor configuration function.
> void thermoj_set_thermocouple_type ( thermoj_t *ctx, uint8_t thermocouple_type );

- Get temperature function.
> float thermoj_get_temperature ( thermoj_t *ctx );

## Examples Description

> This app measured temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermoj_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    thermoj_cfg_setup( &cfg );
    THERMOJ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermoj_init( &thermoj, &cfg );

    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "      Thermo J  Click      \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    
    log_printf( &logger, " Set thermocouple type:  J \r\n" );

    thermoj_set_thermocouple_type( &thermoj, THERMOJ_THERMOCOUPLE_TYPE_J );
    Delay_ms( 1000 );

    log_printf( &logger, "---------------------------\r\n" );
}
  
```

### Application Task

> This is a example which demonstrates the use of Thermo J Click board.
> Measured temperature data from the MCP9600 sensor on Thermo J click board.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    check_data_ready =  thermoj_check_data_ready( &thermoj );

    if ( check_data_ready )
    {
        temperature = thermoj_get_temperature( &thermoj );

        log_printf( &logger, " Temperature : %.2f Celsius\r\n", temperature );
        log_printf( &logger, "---------------------------\r\n" );

        Delay_ms( 1000 );
   }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ThermoJ

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---