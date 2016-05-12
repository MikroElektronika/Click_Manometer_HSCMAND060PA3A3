/****************************************************************************
* Title                 :   Manometer Click
* Filename              :   manometer_hw.h
* Author                :   RBL
* Origin Date           :   09/05/2016
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  09/05/16    		.1           	RBL     Interface Created.
*
*****************************************************************************/
/**
 * @file manometer_hw.h
 * @brief <h3> Manometer Hardware Layer </h3>
 *
 * @par
 * Low level functions for
 * <a href="http://www.mikroe.com">MikroElektronika's Manometer click</a> 
 * board.
 */

/**
 * @page Manometer Library Info
 * @date 09 May 2016
 * @author Richard Lowe
 * @copyright GNU Public License
 * @version 1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 * <h3> Test configuration 1 : </h3>
 * @par
 * <ul>
 * <li><b>MCU</b> :             STM32F107VC</li>
 * <li><b>Dev. Board</b> :      EasyMx Pro v7</li>
 * <li><b>Oscillator</b> :      72 Mhz internal</li>
 * <li><b>Ext. Modules</b> :    Manometer Click</li>
 * <li><b>SW</b> :              MikroC PRO for ARM 4.7.4</li>
 * </ul>
 *
 * <h3> Test configuration 2 : </h3>
 * @par
 * <ul>
 * <li><b>MCU</b> :             PIC32MX795F512L</li>
 * <li><b>Dev. Board</b> :      EasyPic Fusion v7</li>
 * <li><b>Oscillator</b> :      80 Mhz internal</li>
 * <li><b>Ext. Modules</b> :    Manometer Click</li>
 * <li><b>SW</b> :              MikroC PRO for PIC 6.6.2</li>
 * </ul>
 *
 * <h3> Test configuration 3 : </h3>
 * @par
 * <ul>
 * <li><b>MCU</b> :             FT900Q</li>
 * <li><b>Dev. Board</b> :      EasyFT90x v7</li>
 * <li><b>Oscillator</b> :      100 Mhz internal</li>
 * <li><b>Ext. Modules</b> :    Manometer Click</li>
 * <li><b>SW</b> :              MikroC PRO for FT90x 1.2.1</li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> Manometer click </h3>
 * <img src="http://eu.mouser.com/images/microsites/Honeywell%20HSC.jpg" height="200">
 * The pressure is on. No matter the need, Honeywell Sensing and Control (S&C)
 * has the microstructure, pressure sensor solution. Our sensing element design
 * consists of four piezo resistors on a chemically etched silicon diaphragm. A
 * pressure change will cause a strain in the diaphragm and the buried resistors.
 * The resistor values will change in proportion to the stress applied, which
 * produces an electrical output. You will find our components performing in
 * potential applications including dialysis equipment, blood analysis,
 * centrofusion and oxygen and nitrogen gas distribution, HVAC devices, data
 * storage, process controls, industrial machinery, pumps, and robotics.
 *
 * @par
 *
 *
 * <h3> Features </h3>
 * @par
 *
 * <h3> Tutorials </h3>
 * Tutorials and information can be found at our learn pages:
 * <a href="http://learn.mikroe.com/industrial-solution-pressures/"> For All
 * That Pressures You </a>
 *
 * <h3> Examples </h3>
 * @ref Example - ARM
 *
 */
#ifndef MANOMETER_HW_H
#define MANOMETER_HW_H

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/
/**
 * @enum Temperature conversion types
 */
typedef enum
{
    FAHRENHEIT = 0,//!< FAHRENHEIT
    CELSIUS        //!< CELSIUS
} temp_units_t;

/**
 * @enum Status of sensor
 */
typedef enum
{
    NORMAL = 0,     //!< NORMAL
    COMMAND_MODE,   //!< COMMAND_MODE
    STALE_DATA,     //!< STALE_DATA
    DIAGNOSTIC_MODE,//!< DIAGNOSTIC_MODE
} status_t;

/**
 * @enum Sensor types supported
 */
typedef enum
{
    MANOMETER_ADDRESS_TYPE_2 = 0x28,//!< MANOMETER_ADDRESS_TYPE_2
    MANOMETER_ADDRESS_TYPE_3 = 0x38,//!< MANOMETER_ADDRESS_TYPE_3
    MANOMETER_ADDRESS_TYPE_4 = 0x48,//!< MANOMETER_ADDRESS_TYPE_4
    MANOMETER_ADDRESS_TYPE_5 = 0x58,//!< MANOMETER_ADDRESS_TYPE_5
    MANOMETER_ADDRESS_TYPE_6 = 0x68,//!< MANOMETER_ADDRESS_TYPE_6
    MANOMETER_ADDRESS_TYPE_7 = 0x78 //!< MANOMETER_ADDRESS_TYPE_7
} sensor_type_t;

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
 * @brief <h3> HW Layer Initialization </h3>
 *
 * @par
 * Prepares library for usage and sets needed values to default.
 *
 * @note
 * This function must be called first.
 *
 * Example :
 * @code
 *	I2CM1_Init(_I2CM_SPEED_MODE_STANDARD, _I2CM_SWAP_DISABLE);
 *  manometer_init( MANOMETER_ADDRESS_TYPE_3, 0, 60 );
 * @endcode
 */
int manometer_init( sensor_type_t type, int16_t min, int16_t max );

/**
 * @brief Manometer get status
 *
 * @retval Returns the current status of the sensor
 *
 */
status_t manometer_get_status( void );

/**
 * @brief Manomter reset
 *
 * Resets the sensor and returns to Normal status
 */
void manomter_reset( void );

/**
 * @brief Manometer get pressure
 *
 * @return float - returns the pressure in psi
 */
float manometer_get_pressure( void );

/**
 * @brief manometer_get_temp
 * @param unit - @see temp_units_t
 *
 * @return float - returns the measured temp in selected units.
 */
float manometer_get_temp( temp_units_t unit );





#ifdef __cplusplus
} // extern "C"
#endif

#endif /* MANOMETER_HW_H */
/*** End of File **************************************************************/

/**
 * @page Example
 *
 * @code
	#include <stdbool.h>
	#include "manometer_hw.h"
	#include "resources.h"

	#define INNER_RADIUS 20.0f
	#define OUTER_RADIUS 60.0f
	#define X_CENTER     160.0f
	#define Y_CENTER     110.0f
	#define PI           3.14159265f

	typedef struct
	{
    	int x1;
    	int y1;
    	int x2;
    	int y2;
	} line_t;

	unsigned int TFT_DataPort at GPIOE_ODR;
	sbit TFT_RST at GPIOE_ODR.B8;
	sbit TFT_RS at GPIOE_ODR.B12;
	sbit TFT_CS at GPIOE_ODR.B15;
	sbit TFT_RD at GPIOE_ODR.B10;
	sbit TFT_WR at GPIOE_ODR.B11;
	sbit TFT_BLED at GPIOE_ODR.B9;

	static volatile bool update_flag;

	void display_init( void );
	void system_init( void );
	void update_display( void );

	void init_timer2()
	{
    	RCC_APB1ENR.TIM2EN = 1;
    	TIM2_CR1.CEN = 0;
    	TIM2_PSC = 575;
    	TIM2_ARR = 62499;
    	NVIC_IntEnable(IVT_INT_TIM2);
    	TIM2_DIER.UIE = 1;
    	TIM2_CR1.CEN = 1;
	}

	void display_init()
	{
    	TFT_Init_ILI9341_8bit( 320, 280 );
    	TFT_BLED = 1;
    	TFT_Set_Default_Mode();
    	TFT_Set_Pen( CL_WHITE, 1 );
    	TFT_Set_Brush( 1, CL_WHITE, 0, 0, 0, 0 );
    	TFT_Set_Font( TFT_defaultFont, CL_BLACK, FO_HORIZONTAL );

    	TFT_Fill_Screen( CL_WHITE );
    	TFT_Set_Pen( CL_BLACK, 1 );
    	TFT_Line( 20, 222, 300, 222 );
    	TFT_Write_Text( "EasyMx PRO v7 for STM32", 19, 223 );
    	TFT_Write_Text( "www.mikroe.com", 200, 223 );
    	TFT_Image( ( 320 - 220 ) / 2, 1, &pressure3_bmp, 1 );
    	TFT_Set_Font( TFT_defaultFont, CL_BLACK, FO_HORIZONTAL );
	}


	void system_init()
	{
    	UART1_Init_Advanced( 115200,
                         _UART_8_BIT_DATA,
                         _UART_NOPARITY,
                         _UART_ONE_STOPBIT,
                         &_GPIO_MODULE_USART1_PA9_10 );
    	Delay_ms(100);
    	UART_Write_Text( "**** Manometer ****\r\n" );

    	I2C1_Init_Advanced( 400000, &_GPIO_MODULE_I2C1_PB67 );
    	Delay_ms(100); // Stabilization time
    	if( manometer_init( MANOMETER_ADDRESS_TYPE_3, 0, 60 ) )
        	while(1);

    	display_init();
    	init_timer2();
    	EnableInterrupts();
	}

	void update_display()
	{
    	float temp, pressure;
    	static float old_temp, old_pressure;
    	static line_t last_line;
    	char txt[80];
    	line_t current_line;

    	temp = manometer_get_temp( CELSIUS );
		pressure = manometer_get_pressure();

		sprintf( txt, "Temp: %f\r\n", temp );
		UART_Write_Text( txt );
		sprintf( txt, "Pressure: %f\r\n", pressure );
		UART_Write_Text( txt );

		TFT_Set_Font( TFT_defaultFont, CL_WHITE, FO_HORIZONTAL );
		sprintf( txt, "%3.1f PSI", old_pressure );
		TFT_Write_Text( txt, 160, 138 );
		sprintf( txt, "%3.1f C", old_temp );
		TFT_Write_Text( txt, 160, 160 );
		TFT_Set_Font( TFT_defaultFont, CL_BLACK, FO_HORIZONTAL );
		sprintf( txt, "%3.1f PSI", pressure );
		TFT_Write_Text( txt, 160, 138 );
		sprintf( txt, "%3.1f C", temp );
		TFT_Write_Text( txt, 160, 160 );

		old_pressure = pressure;
		old_temp = temp;

		TFT_Set_Pen( CL_WHITE, 4 );
		TFT_Line( last_line.x1, last_line.y1, last_line.x2, last_line.y2 );
		TFT_Set_Pen( CL_RED, 4 );

		if( old_pressure <= 15.0f )
		{
			current_line.x1 = ( int )( X_CENTER + ( INNER_RADIUS * sin( 270.0f *
													( PI / 180.0f ) ) ) );
			current_line.y1 = ( int )( Y_CENTER + ( INNER_RADIUS * -cos( 270.0f *
													( PI  / 180.0f ) ) ) );
			current_line.x2 = ( int )( X_CENTER + ( OUTER_RADIUS * sin( 270.0f *
													( PI / 180.0f ) ) ) );
			current_line.y2 = ( int )( Y_CENTER + ( OUTER_RADIUS * -cos( 270.0f *
													( PI  / 180.0f ) ) ) );
		}
		else if( old_pressure >= 42.0f )
		{
			current_line.x1 = ( int )( X_CENTER + ( INNER_RADIUS * sin( 90.0f *
													( PI / 180.0f ) ) ) );
			current_line.y1 = ( int )( Y_CENTER + ( INNER_RADIUS * -cos( 90.0f *
													( PI  / 180.0f ) ) ) );
			current_line.x2 = ( int )( X_CENTER + ( OUTER_RADIUS * sin( 90.0f *
													( PI / 180.0f ) ) ) );
			current_line.y2 = ( int )( Y_CENTER + ( OUTER_RADIUS * -cos( 90.0f *
													( PI  / 180.0f ) ) ) );
		}
		else
		{
			current_line.x1 = ( int )( X_CENTER + ( INNER_RADIUS * sin( old_pressure *
													( PI / 180.0f ) ) ) );
			current_line.y1 = ( int )( Y_CENTER + ( INNER_RADIUS * -cos( old_pressure *
													( PI  / 180.0f ) ) ) );
			current_line.x2 = ( int )( X_CENTER + ( OUTER_RADIUS * sin( old_pressure *
													( PI / 180.0f ) ) ) );
			current_line.y2 = ( int )( Y_CENTER + ( OUTER_RADIUS * -cos( old_pressure *
													( PI  / 180.0f ) ) ) );
		}

		TFT_Line( current_line.x1, current_line.y1, current_line.x2,
				  current_line.y2 );
		memcpy( &last_line, &current_line, sizeof( line_t ) );

	}

	void main()
	{
		system_init();

		while(1)
		{
			if( update_flag )
			{
				update_display();
				update_flag = false;
			}
		}
	}


	void Timer2_interrupt() iv IVT_INT_TIM2
	{
		TIM2_SR.UIF = 0;
		update_flag = true;
	}

	@endcode
 */
