/****************************************************************************
* Title                 :   Manometer clink
* Filename              :   manometer_hw.h
* Author                :   RBL
* Origin Date           :   10/05/2016
* Notes                 :   Hardware layer
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  10/05/16     .1                  RBL     Interface Created.
*
*****************************************************************************/
/**
 * @file manometer_hw.c
 * @brief <h3> Hardware Layer </h3>
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "manometer_hw.h"
#include "manometer_hal.h"
#include <math.h>

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define MS5803_CMD_RESET      (0x1E)   // ADC reset command
#define MS5803_CMD_ADC_READ   (0x00)   // ADC read command
#define MS5803_CMD_ADC_CONV   (0x40)   // ADC conversion command
#define MS5803_CMD_ADC_D1     (0x00)   // ADC D1 conversion
#define MS5803_CMD_ADC_D2     (0x10)   // ADC D2 conversion
#define MS5803_CMD_ADC_256    (0x00)   // ADC OSR=256
#define MS5803_CMD_ADC_512    (0x02)   // ADC OSR=512
#define MS5803_CMD_ADC_1024   (0x04)   // ADC OSR=1024
#define MS5803_CMD_ADC_2048   (0x06)   // ADC OSR=2056
#define MS5803_CMD_ADC_4096   (0x08)   // ADC OSR=4096
#define MS5803_CMD_PROM_RD    (0xA0)   // Prom read command

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/
/**
 * @struct Sensor metadata
 */
typedef struct
{
    sensor_type_t type;
    status_t status;         /**< Current status of sensor */
    uint16_t OUTPUT_MAX;     /**< Output at max ( counts ) */
    uint16_t OUTPUT_MIN;     /**< Output at min ( counts ) */
    int16_t PRESSURE_MAX;    /**< Max value of PRESSURE range */
    int16_t PRESSURE_MIN;    /**< Min value of PRESSURE range */
} measurements_t;

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static measurements_t cur_measure;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Private Function Definitions
*******************************************************************************/

/******************************************************************************
* Public Function Definitions
*******************************************************************************/
int manometer_init( sensor_type_t type, int16_t min, int16_t max )
{
    uint8_t read_val[2];

    if( manometer_hal_init( type ) )
        return -1;

    manometer_hal_read( type, read_val, 2 );
    cur_measure.status = ( read_val[0] & 0xC0 );
    
    if( cur_measure.status != NORMAL )
        return -1;
    
    cur_measure.type = type;
    cur_measure.PRESSURE_MIN = min;
    cur_measure.PRESSURE_MAX = max;
    cur_measure.OUTPUT_MAX = 0x3999;
    cur_measure.OUTPUT_MIN = 0x0666;
    
    return 0;
}

status_t manometer_get_status()
{
   return cur_measure.status;
}

void manometer_reset()
{
    manometer_hal_write( MS5803_CMD_RESET );
    manometer_hal_delay( 3 );
}

float manometer_get_pressure()
{
    float ret_pressure = 0.0f;
    uint8_t read_val[2];
    uint16_t output;

    manometer_hal_read( cur_measure.type, read_val, 2 );
    cur_measure.status = ( read_val[0] & 0xC0 );
    output = ( (uint16_t)( read_val[0] & 0x1F ) << 8 ) + read_val[1];
    
    ret_pressure = ( (float)( output - cur_measure.OUTPUT_MIN ) *
                 (float)( cur_measure.PRESSURE_MAX - cur_measure.PRESSURE_MIN ) ) /
                 (float)( cur_measure.OUTPUT_MAX - cur_measure.OUTPUT_MIN ) +
                 (float)cur_measure.PRESSURE_MIN;
    manometer_hal_delay( 3 );
    return ret_pressure;
}

float manometer_get_temp( temp_units_t unit )
{
    float ret_temp;
    uint8_t read_val[4];
    uint16_t output;
    
    manometer_hal_read( cur_measure.type, read_val, 4 );
    cur_measure.status = ( read_val[0] & 0xC0 );
    output = ( ( (uint16_t)read_val[2] << 8 ) | (uint16_t)read_val[3] ) >> 5;
    
    ret_temp = (float)( (float)( output / 2047.0f ) * 200.0f ) - 50.0f;

    if( unit == FAHRENHEIT )
    {
        ret_temp = ( ( ret_temp * 9.0f ) / 5.0f ) + 32.0f;
    }
    
    manometer_hal_delay( 3 );
    return ret_temp;
}


/*************** END OF FUNCTIONS *********************************************/
