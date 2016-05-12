/****************************************************************************
* Title                 :   Manometer click
* Filename              :   Manometer_clickDSPIC.c
* Author                :   RBL
* Origin Date           :   10/05/2016
* Notes                 :   Manometer Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  10/05/16       1.0.0            MSV        Interface Created.
*
*****************************************************************************/
/**
 * @file Manometer.c
 * @brief <h2> Manometer Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * Manometer click board.
 */

/**
 * @page LIB_INFO Library Info
 * @date        28 Jan 2016
 * @author      Richard Lowe
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 * <h3> Test configuration 1 : </h3>
 * @par
 * <ul>
 * <li><b> MCU           </b> :      STM32F107VC                 </li>
 * <li><b> Dev. Board    </b> :      EasyMx Pro v7               </li>
 * <li><b> Oscillator    </b> :      72 Mhz internal             </li>
 * <li><b> Ext. Modules  </b> :      CLICKNAME Click             </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1    </li>
 * </ul>
 *
 * <h3> Test configuration 2 : </h3>
 * @par
 * <ul>
 * <li><b> MCU           </b> :      PIC32MX795F512L             </li>
 * <li><b> Dev. Board    </b> :      EasyPic Fusion v7           </li>
 * <li><b> Oscillator    </b> :      80 Mhz internal             </li>
 * <li><b> Ext. Modules  </b> :      CLICKNAME Click             </li>
 * <li><b> SW            </b> :      MikroC PRO for PIC 6.6.2    </li>
 * </ul>
 *
 * <h3> Test configuration 3 : </h3>
 * @par
 * <ul>
 * <li><b> MCU           </b> :      FT900Q                      </li>
 * <li><b> Dev. Board    </b> :      EasyFT90x v7                </li>
 * <li><b> Oscillator    </b> :      100 Mhz internal            </li>
 * <li><b> Ext. Modules  </b> :      CLICKNAME Click             </li>
 * <li><b> SW            </b> :      MikroC PRO for FT90x 1.2.1  </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> CLICKNAME General Description </h3>
 * @par
 *
 *
 * <h3> CLICKNAME Features </h3>
 * @par
 *
 *
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "manometer_hw.h"
//#include "resources.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define INNER_RADIUS 20.0f
#define OUTER_RADIUS 60.0f
#define X_CENTER     160.0f
#define Y_CENTER     110.0f
#define PI           3.14159265f

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/


/******************************************************************************
* Module Typedefs
*******************************************************************************/
/**
 * @struct Line beginning and end points in X and Y
 */
typedef struct
{
    int x1;
    int y1;
    int x2;
    int y2;
} line_t;


/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
// TFT module connections
char TFT_DataPort at LATE;
sbit TFT_RST at LATC1_bit;
sbit TFT_BLED at LATD2_bit;
sbit TFT_RS at LATB15_bit;
sbit TFT_CS at LATF12_bit;
sbit TFT_RD at LATD5_bit;
sbit TFT_WR at LATD4_bit;
char TFT_DataPort_Direction at TRISE;
sbit TFT_RST_Direction at TRISC1_bit;
sbit TFT_BLED_Direction at TRISD2_bit;
sbit TFT_RS_Direction at TRISB15_bit;
sbit TFT_CS_Direction at TRISF12_bit;
sbit TFT_RD_Direction at TRISD5_bit;
sbit TFT_WR_Direction at TRISD4_bit;
// End TFT module connections

static volatile bool update_flag;
/******************************************************************************
* Function Prototypes
*******************************************************************************/
void display_init( void );
void system_init( void );
void update_display( void );

/******************************************************************************
* Private Function Definitions
*******************************************************************************/


/******************************************************************************
* Public Function Definitions
*******************************************************************************/
//Place/Copy this part in declaration section
void init_timer2()
{
    T2CON                 = 0x0;
    T3CON                 = 0x0;
    TMR2                 = 0;
    TMR3                 = 0;
    T3IE_bit                 = 1;
    T3IF_bit                 = 0;
    T3IP_0_bit                 = 1;
    T3IP_1_bit                 = 1;
    T3IP_2_bit                 = 1;
    PR3                         = 305;
    PR2                         = 11825;
    T2CONbits.TON         = 1;
    T2CONbits.T32         = 1;
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
    //TFT_Image( ( 320 - 220 ) / 2, 1, &pressure3_bmp, 1 );
    TFT_Set_Font( TFT_defaultFont, CL_BLACK, FO_HORIZONTAL );
}


/**
 * @brief <h3> CLICKNAME Initialization </h3>
 *
 * @par
 * Prepares CLICKNAME for usage and sets needed values to default.
 *
 * @note
 * This function must be called first.
 *
 * @param[in]   input   - ...
 * @param[out]  output  - ...
 *
 * @return
 * Function returns ...
 *
 * <h4> Example : </h4>
 * @code
 *
 * @endcode
 */
void system_init()
{
    // UART
    UART3_Init_Advanced( 57600, _UART_8BIT_NOPARITY, _UART_ONE_STOPBIT, _UART_HI_SPEED );
    Delay_ms(100);
    UART_Write_Text( "**** Manometer ****\r\n" );

    I2C2_Init( 100000 );
    Delay_ms(100); // Stabilization time
    if( manometer_init( MANOMETER_ADDRESS_TYPE_3, 0, 60 ) )
        while(1);

    display_init();
    init_timer2();
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

void Timer2_3Interrupt() iv IVT_ADDR_T3INTERRUPT
{
    T3IF_bit                 = 0;
    update_flag = true;
}
/*************** END OF FUNCTIONS *********************************************/