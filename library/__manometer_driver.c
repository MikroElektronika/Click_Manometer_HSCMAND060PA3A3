/*
    __manometer_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__manometer_driver.h"
#include "__manometer_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __MANOMETER_DRV_I2C__
static uint8_t _slaveAddress;
#endif

// ADC reset command
const uint8_t _MANOMETER_CMD_RESET       = 0x1E;
// ADC read command
const uint8_t _MANOMETER_CMD_ADC_READ    = 0x00;
// ADC conversion command
const uint8_t _MANOMETER_CMD_ADC_CONV    = 0x40;
// ADC D1 conversion
const uint8_t _MANOMETER_CMD_ADC_D1      = 0x00;
// ADC D2 conversion
const uint8_t _MANOMETER_CMD_ADC_D2      = 0x10;
// ADC OSR=256
const uint8_t _MANOMETER_CMD_ADC_256     = 0x00;
// ADC OSR=512
const uint8_t _MANOMETER_CMD_ADC_512     = 0x02;
// ADC OSR=1024
const uint8_t _MANOMETER_CMD_ADC_1024    = 0x04;
// ADC OSR=2056
const uint8_t _MANOMETER_CMD_ADC_2048    = 0x06;
// ADC OSR=4096
const uint8_t _MANOMETER_CMD_ADC_4096    = 0x08;
// Prom read command
const uint8_t _MANOMETER_CMD_PROM_RD     = 0xA0;

// Output register address
const uint8_t _MANOMETER_OUTPUT_ADDRESS  = 0x38;

// I2C register address
const uint8_t _MANOMETER_I2C_ADDRESS     = 0x38;


/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __MANOMETER_DRV_SPI__

void manometer_spiDriverInit(T_MANOMETER_P gpioObj, T_MANOMETER_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __MANOMETER_DRV_I2C__

void manometer_i2cDriverInit(T_MANOMETER_P gpioObj, T_MANOMETER_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __MANOMETER_DRV_UART__

void manometer_uartDriverInit(T_MANOMETER_P gpioObj, T_MANOMETER_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif


/* ----------------------------------------------------------- IMPLEMENTATION */

/* Generic write data function */
void manometer_writeData( uint8_t regAddress, uint32_t writeCommand )
{
    uint8_t buffer[ 5 ];
    buffer[ 0 ]= regAddress;
    buffer[ 1 ] = ( uint8_t ) ( writeCommand &  0x000000FF );
    buffer[ 2 ] = ( uint8_t ) ( ( writeCommand &  0x0000FF00 ) >> 8 );
    buffer[ 3 ] = ( uint8_t ) ( ( writeCommand &  0x00FF0000 ) >> 16 );
    buffer[ 4 ] = ( uint8_t ) ( ( writeCommand &  0xFF000000 ) >> 24 );

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, buffer, 5, END_MODE_STOP );
}

/* Generic read data function */
uint32_t manometer_readData( uint8_t regAddress )
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 4 ];
    uint32_t result;
        
    writeReg[ 0 ] = regAddress;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readReg, 4, END_MODE_STOP );
    
    result = readReg[ 0 ];
    result <<= 8;
    result |= readReg[ 1 ];
    result <<= 8;
    result |= readReg[ 2 ];
    result <<= 8;
    result |= readReg[ 3 ];
    
    return result;
}

/* Function read pressure data */
float manometer_getPressure()
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 4 ];
    uint16_t result = 0x0000;
    float pressure;

    writeReg[ 0 ] = _MANOMETER_OUTPUT_ADDRESS;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readReg, 4, END_MODE_STOP );

    result = readReg[ 0 ];
    result <<= 8;
    result |= readReg[ 1 ];

    pressure = ( float ) result;
    pressure = ( pressure - 1638.00 ) * ( ( 4.177 / 13107.00 ) * 1000.00 );
    
    return pressure;
}

/* Function read temperature data */
float manometer_getTemperature()
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 4 ];
    uint16_t result = 0x0000;
    float temperature;
        
    writeReg[ 0 ] = _MANOMETER_OUTPUT_ADDRESS;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readReg, 4, END_MODE_STOP );

    result = readReg[ 2 ] ;
    result <<= 8;
    result |= readReg[ 3 ];
    result >>= 5;
    result = result & 0x03E0;
     
    temperature = ( float ) result * 200.00;
    temperature = ( temperature / 2047.00 ) - 50.00;

    return temperature;
}



/* -------------------------------------------------------------------------- */
/*
  __manometer_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */