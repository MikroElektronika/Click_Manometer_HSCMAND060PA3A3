/****************************************************************************
* Title                 :   Manometer click
* Filename              :   Manometer_hal.h
* Author                :   Richard Lowe
* Origin Date           :   09/05/2016
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  09/05/16    		.1         		RBL     Interface Created.
*
*****************************************************************************/
/**
 * @file Manometer_hal.h
 * @brief <h2> HAL layer </h2>
 *
 * @par
 * HAL layer for <a href="http://www.mikroe.com">MikroElektronika's Manometer click board</a>
 * 
 */
#ifndef MANOMETER_HAL_H_
#define MANOMETER_HAL_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define BUFF_SIZE               3                // BUFFER SIZE

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
        
/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief <h3>HAL Initialization</h3>
 *
 * @par
 * Initialization of HAL layer used to initialize I2C bus and pins needed
 * for proper usage of click board.
 *
 * @param[in] address_id - hardware address
 */
int manometer_hal_init( uint8_t address_id );

/**
 * @brief HAL delay for accessing platform delay function
 * @param ms
 */
void manometer_hal_delay( uint16_t ms );


/**
 * @brief <h3>HAL Write</h3>
 *
 * @par Generic write function adapted for I2C bus.
 *
 * @param[in] command - register address
 */
void manometer_hal_write( uint8_t command );

/**
 * @brief <h3>HAL Read</h3>
 *
 * @par Generic read function adapted for SHT click.
 *
 * @param[in] command - register address
 * @param[out] buffer - data buffer
 * @param[in] count - data size in bytes
 */
void manometer_hal_read( uint8_t command, uint8_t *buffer, uint8_t count );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* Manometer_HAL_H_ */

/*** End of File **************************************************************/