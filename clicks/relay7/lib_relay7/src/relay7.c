/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file relay7.c
 * @brief Relay 7 Click Driver.
 */

#include "relay7.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                    0x00

void relay7_cfg_setup ( relay7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RELAY7_DEVICE_ADDRESS_0;
}

err_t relay7_init ( relay7_t *ctx, relay7_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t relay7_default_cfg ( relay7_t *ctx ) 
{
    relay7_reset_device( ctx );
    err_t err_flag = relay7_generic_write( ctx, RELAY7_REG_CONFIGURATION, RELAY7_DEFAULT_CONFIG );
    err_flag |= relay7_set_relay( ctx, RELAY7_SEL_REL1, RELAY7_STATE_OPEN );
    err_flag |= relay7_set_relay( ctx, RELAY7_SEL_REL2, RELAY7_STATE_OPEN );
    err_flag |= relay7_set_relay( ctx, RELAY7_SEL_REL3, RELAY7_STATE_OPEN );
    err_flag |= relay7_set_relay( ctx, RELAY7_SEL_REL4, RELAY7_STATE_OPEN );
    return err_flag;
}

void relay7_reset_device ( relay7_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

err_t relay7_generic_write ( relay7_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { reg, data_in };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t relay7_generic_read ( relay7_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t relay7_set_port_expander ( relay7_t *ctx, uint8_t set_mask, uint8_t clr_mask )
{
    uint8_t data_in, data_out;
    err_t err_flag = relay7_generic_read( ctx, RELAY7_REG_OUTPUT_PORT, &data_out );
    data_in = ( data_out & ~clr_mask ) | set_mask;
    if ( data_out != data_in )
    {
        err_flag |= relay7_generic_write( ctx, RELAY7_REG_OUTPUT_PORT, data_in );
    }
    return err_flag;
}

err_t relay7_set_relay ( relay7_t *ctx, uint8_t relay_sel, relay7_relay_state_t state )
{
    err_t err_flag = RELAY7_ERROR;
    uint8_t data_buf = DUMMY;
    if ( ( RELAY7_SEL_REL1 <= relay_sel ) && ( RELAY7_SEL_REL4 >= relay_sel ) )
    {
        err_flag = relay7_generic_read( ctx, RELAY7_REG_OUTPUT_PORT, &data_buf );
        relay_sel--;
        data_buf &= ~( RELAY7_PIN_MASK_P0 << relay_sel );
        data_buf |= state << relay_sel ;
        err_flag |= relay7_generic_write( ctx, RELAY7_REG_OUTPUT_PORT, data_buf );
    }
    return err_flag;
}

uint8_t relay7_get_interrupt ( relay7_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
