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
 * @file optoencoder5.c
 * @brief Opto Encoder 5 Click Driver.
 */

#include "optoencoder5.h"

void optoencoder5_cfg_setup ( optoencoder5_cfg_t *cfg ) 
{
    cfg->on  = HAL_PIN_NC;
    cfg->out = HAL_PIN_NC;
}

err_t optoencoder5_init ( optoencoder5_t *ctx, optoencoder5_cfg_t *cfg ) 
{
    err_t err_flag = digital_out_init( &ctx->on, cfg->on );
    err_flag |= digital_in_init( &ctx->out, cfg->out );
    return err_flag;
}

void optoencoder5_enable ( optoencoder5_t *ctx ) 
{
    digital_out_high( &ctx->on );
}

void optoencoder5_disable ( optoencoder5_t *ctx ) 
{
    digital_out_low( &ctx->on );
}

uint8_t optoencoder5_get_out_state ( optoencoder5_t *ctx ) 
{
    return digital_in_read( &ctx->out );
}

// ------------------------------------------------------------------------- END
