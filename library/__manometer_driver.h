/*
    __manometer_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __manometer_driver.h
@brief    Manometer Driver
@mainpage Manometer Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   MANOMETER
@brief      Manometer Click Driver
@{

| Global Library Prefix | **MANOMETER** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Sep 2018.**      |
| Developer             | **Nenad Filipovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _MANOMETER_H_
#define _MANOMETER_H_

/** 
 * @macro T_MANOMETER_P
 * @brief Driver Abstract type 
 */
#define T_MANOMETER_P    const uint8_t*

/** @defgroup MANOMETER_COMPILE Compilation Config */              /** @{ */

//  #define   __MANOMETER_DRV_SPI__                            /**<     @macro __MANOMETER_DRV_SPI__  @brief SPI driver selector */
   #define   __MANOMETER_DRV_I2C__                            /**<     @macro __MANOMETER_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __MANOMETER_DRV_UART__                           /**<     @macro __MANOMETER_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup MANOMETER_VAR Variables */                           /** @{ */

extern const uint8_t _MANOMETER_CMD_RESET;
extern const uint8_t _MANOMETER_CMD_ADC_READ;
extern const uint8_t _MANOMETER_CMD_ADC_CONV;
extern const uint8_t _MANOMETER_CMD_ADC_D1;
extern const uint8_t _MANOMETER_CMD_ADC_D2;
extern const uint8_t _MANOMETER_CMD_ADC_256;
extern const uint8_t _MANOMETER_CMD_ADC_512;
extern const uint8_t _MANOMETER_CMD_ADC_1024;
extern const uint8_t _MANOMETER_CMD_ADC_2048;
extern const uint8_t _MANOMETER_CMD_ADC_4096;
extern const uint8_t _MANOMETER_CMD_PROM_RD;

extern const uint8_t _MANOMETER_OUTPUT_ADDRESS;

extern const uint8_t _MANOMETER_I2C_ADDRESS;

                                                                       /** @} */
/** @defgroup MANOMETER_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup MANOMETER_INIT Driver Initialization */              /** @{ */

#ifdef   __MANOMETER_DRV_SPI__
void manometer_spiDriverInit(T_MANOMETER_P gpioObj, T_MANOMETER_P spiObj);
#endif
#ifdef   __MANOMETER_DRV_I2C__
void manometer_i2cDriverInit(T_MANOMETER_P gpioObj, T_MANOMETER_P i2cObj, uint8_t slave);
#endif
#ifdef   __MANOMETER_DRV_UART__
void manometer_uartDriverInit(T_MANOMETER_P gpioObj, T_MANOMETER_P uartObj);
#endif


/** @defgroup MANOMETER_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Generic write data function
 *
 * @param[in] regAddress    8-bit register address
 *
 * @param[in] dataToWrite    32-bit data to write
 *
 * Function write data from register
 */
void manometer_writeData( uint8_t regAddress, uint32_t writeCommand );

/**
 * @brief Generic read data function
 *
 * @param[in] regAddress    8-bit register address
 *
 * @return    32-bit data from HSCMAND060PA3A3 sensor
 *
 * Function read byte of data from HSCMAND060PA3A3 sensor
 */
uint32_t manometer_readData( uint8_t regAddress );

/**
 * @brief Function read 16-bit data and convert to pressure in mbar
 *
 * @return         pressure value [ mbar ]
 *
 * Function read pressure value
 */
float manometer_getPressure();

/**
 * @brief Function read 11-bit data and convert to temperature in degrees Celsius [ °C ]
 *
 * @return         temperature value in degrees Celsius [ °C ]
 *
 * Function read temperature value
 */
float manometer_getTemperature();




                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Manometer_STM.c
    @example Click_Manometer_TIVA.c
    @example Click_Manometer_CEC.c
    @example Click_Manometer_KINETIS.c
    @example Click_Manometer_MSP.c
    @example Click_Manometer_PIC.c
    @example Click_Manometer_PIC32.c
    @example Click_Manometer_DSPIC.c
    @example Click_Manometer_AVR.c
    @example Click_Manometer_FT90x.c
    @example Click_Manometer_STM.mbas
    @example Click_Manometer_TIVA.mbas
    @example Click_Manometer_CEC.mbas
    @example Click_Manometer_KINETIS.mbas
    @example Click_Manometer_MSP.mbas
    @example Click_Manometer_PIC.mbas
    @example Click_Manometer_PIC32.mbas
    @example Click_Manometer_DSPIC.mbas
    @example Click_Manometer_AVR.mbas
    @example Click_Manometer_FT90x.mbas
    @example Click_Manometer_STM.mpas
    @example Click_Manometer_TIVA.mpas
    @example Click_Manometer_CEC.mpas
    @example Click_Manometer_KINETIS.mpas
    @example Click_Manometer_MSP.mpas
    @example Click_Manometer_PIC.mpas
    @example Click_Manometer_PIC32.mpas
    @example Click_Manometer_DSPIC.mpas
    @example Click_Manometer_AVR.mpas
    @example Click_Manometer_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __manometer_driver.h

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