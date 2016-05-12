/*******************************************************************************
* Title                 :   Manometer click
* Filename              :   manometer_hal.c
* Author                :   RBL
* Origin Date           :   10/05/2016
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description
*  10/05/16                    .1                  RBL      Interface Created.
*
*******************************************************************************/
/**
 * @file manometer_hal.c
 * @brief <h2> Manometer HAL layer </h2>
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "manometer_hal.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define READ_BIT                1
#define WRITE_BIT               0
#define NACK_BIT                1
#define ACK_BIT                 0

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static uint8_t _i2c_hw_address;

#if defined( __MIKROC_PRO_FOR_ARM__ )
#define STM32
    #if defined( STM32 )
static unsigned int ( *start_i2c_p )( void );
static unsigned int ( *write_i2c_p )( unsigned char slave_address,
                                      unsigned char *buffer,
                                      unsigned long count,
                                      unsigned long end_mode );
static void ( *read_i2c_p )( unsigned char slave_address,
                             unsigned char *buffer,
                             unsigned long count,
                             unsigned long end_mode );
    #elif defined( TI )
static void ( *enable_i2c_p )( void );
static void ( *disable_i2c_p )( void );
static void ( *set_slave_address_i2c_p )( unsigned char slave_address,
                                          unsigned char dir );
static void ( *write_i2c_p )( unsigned char data_out,
                              unsigned char mode );
static void ( *read_i2c_p )( unsigned char *data,
                             unsigned char mode );
    #endif

#elif  defined( __MIKROC_PRO_FOR_AVR__ )
static unsigned char( *is_idle_i2c_p )( void );
static unsigned char( *status_i2c_p )( void );
static unsigned char( *start_i2c_p )( void );
static void         ( *stop_i2c_p )( void );
static void         ( *close_i2c_p )( void );
static void         ( *write_i2c_p )( unsigned char data_out );
static unsigned char( *read_i2c_p )( unsigned char ack );

#elif  defined( __MIKROC_PRO_FOR_PIC__ )
static unsigned char( *is_idle_i2c_p )( void );
static unsigned char( *start_i2c_p )( void );
static void         ( *stop_i2c_p )( void );
static void         ( *restart_i2c_p )( void );
static unsigned char( *write_i2c_p )( unsigned char data_out );
static unsigned char( *read_i2c_p )( unsigned char ack );

#elif defined( __MIKROC_PRO_FOR_PIC32__ )
static unsigned int ( *is_idle_i2c_p )( void );
static unsigned int ( *start_i2c_p )( void );
static void         ( *stop_i2c_p )( void );
static unsigned int ( *restart_i2c_p )( void );
static unsigned int ( *write_i2c_p )( unsigned char data_out );
static unsigned char( *read_i2c_p )( unsigned int ack );

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )
static unsigned int ( *is_idle_i2c_p )( void );
static unsigned int ( *start_i2c_p )( void );
static void         ( *stop_i2c_p )( void );
static void         ( *restart_i2c_p )( void );
static unsigned int ( *write_i2c_p )( unsigned char data_out );
static unsigned char( *read_i2c_p )( unsigned int ack );

#elif defined( __MIKROC_PRO_FOR_8051__ )
static unsigned char( *status_i2c_p )( void );
static unsigned char( *start_i2c_p )( void );
static void         ( *stop_i2c_p )( void );
static void         ( *close_i2c_p )( void );
static void         ( *write_i2c_p )( unsigned char data_out );
static unsigned char( *read_i2c_p )( unsigned char ack );

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
static void         ( *soft_reset_i2c_p )( void );
static void         ( *set_slave_address_i2c_p )( unsigned char slave_address );
static unsigned char( *write_i2c_p )( unsigned char data_out );
static unsigned char( *read_i2c_p )( unsigned char *data_in );
static unsigned char( *write_bytes_i2c_p )( unsigned char *buffer,
                                            unsigned int count );
static unsigned char( *read_bytes_i2c_p )( unsigned char *buffer,
                                           unsigned int count );
static unsigned char( *write_10bit_i2c_p )( unsigned char data_out,
                                            unsigned int address_10bit );
static unsigned char( *read_10bit_i2c_p )( unsigned char *data_in,
                                           unsigned int address_10bit );
#endif


/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
int manometer_hal_init( uint8_t address_id )
{
#if defined( __MIKROC_PRO_FOR_ARM__ )
    #if defined( STM32 )
    start_i2c_p                 = I2C_Start_Ptr;
    write_i2c_p                 = I2C_Write_Ptr;
    read_i2c_p                  = I2C_Read_Ptr;

    #elif defined( TI )
    enable_i2c_p                = I2C_Enable_Ptr;
    disable_i2c_p               = I2C_Disable_Ptr;
    set_slave_address_i2c_p     = I2C_Master_Slave_Addr_Set_Ptr;
    write_i2c_p                 = I2C_Write_Ptr;
    read_i2c_p                  = I2C_Read_Ptr;

    #endif

#elif defined( __MIKROC_PRO_FOR_AVR__ )
    #if defined( LT64 )
    is_idle_i2c_p               = TWI_Busy;
    status_i2c_p                = TWI_Status;
    close_i2c_p                 = TWI_Close;
    start_i2c_p                 = TWI_Start;
    stop_i2c_p                  = TWI_Stop;
    write_i2c_p                 = TWI_Write;
    read_i2c_p                  = TWI_Read;

    #elif defined( GT64 )
    is_idle_i2c_p               = TWIC_Busy;
    status_i2c_p                = TWIC_Status;
    close_i2c_p                 = TWIC_Close;
    start_i2c_p                 = TWIC_Start;
    stop_i2c_p                  = TWIC_Stop;
    write_i2c_p                 = TWIC_Write;
    read_i2c_p                  = TWIC_Read;
    #endif

#elif defined( __MIKROC_PRO_FOR_PIC__ )
    is_idle_i2c_p               = I2C1_Is_Idle;
    start_i2c_p                 = I2C1_Start;
    stop_i2c_p                  = I2C1_Stop;
    restart_i2c_p               = I2C1_Repeated_Start;
    write_i2c_p                 = I2C1_Wr;
    read_i2c_p                  = I2C1_Rd;

#elif defined( __MIKROC_PRO_FOR_PIC32__ )
    is_idle_i2c_p               = I2C_Is_Idle_Ptr;
    start_i2c_p                 = I2C_Start_Ptr;
    stop_i2c_p                  = I2C_Stop_Ptr;
    restart_i2c_p               = I2C_Restart_Ptr;
    write_i2c_p                 = I2C_Write_Ptr;
    read_i2c_p                  = I2C_Read_Ptr;

#elif defined( __MIKROC_PRO_FOR_DSPIC__ )
    is_idle_i2c_p               = I2C2_Is_Idle;
    start_i2c_p                 = I2C2_Start;
    stop_i2c_p                  = I2C2_Stop;
    restart_i2c_p               = I2C2_Restart;
    write_i2c_p                 = I2C2_Write;
    read_i2c_p                  = I2C2_Read;

#elif defined( __MIKROC_PRO_FOR_8051__ )
    status_i2c_p                = TWI_Status;
    close_i2c_p                 = TWI_Close;
    start_i2c_p                 = TWI_Start;
    stop_i2c_p                  = TWI_Stop;
    write_i2c_p                 = TWI_Write;
    read_i2c_p                  = TWI_Read;

#elif defined( __MIKROC_PRO_FOR_FT90x__ )
    soft_reset_i2c_p            = I2CM_Soft_Reset_Ptr;
    set_slave_address_i2c_p     = I2CM_Set_Slave_Address_Ptr;
    write_i2c_p                 = I2CM_Write_Ptr;
    read_i2c_p                  = I2CM_Read_Ptr;
    write_bytes_i2c_p           = I2CM_Write_Bytes_Ptr;
    read_bytes_i2c_p            = I2CM_Read_Bytes_Ptr;
    write_10bit_i2c_p           = I2CM_Write_10Bit_Ptr;
    read_10bit_i2c_p            = I2CM_Read_10Bit_Ptr;
#endif

#if defined( __MIKROC_PRO_FOR_ARM__ )   ||  \
    defined( __MIKROC_PRO_FOR_FT90x__ )
    _i2c_hw_address             = address_id;
#else
    _i2c_hw_address             = ( address_id << 1 );
#endif

    return 0;
}


void manometer_hal_delay(uint16_t ms)
{
#if defined( __GNUC__)

#else
    while(ms--)
        Delay_1ms();
#endif
}


void manometer_hal_write( uint8_t command )
{
    uint8_t temp[ BUFF_SIZE ];

    /* Fill the temp buffer with data*/
    temp[0] = command;

#if defined(__MIKROC_PRO_FOR_ARM__)
    #if defined( STM32 )
    start_i2c_p();
    write_i2c_p( _i2c_hw_address, temp, 1, END_MODE_STOP );

    #elif defined( TI )
    set_slave_address_i2c_p( _i2c_hw_address, _I2C_DIR_MASTER_TRANSMIT );
    write_i2c_p( temp[0], _I2C_MASTER_MODE_SINGLE_SEND );
    #endif

#elif defined(__MIKROC_PRO_FOR_FT90x__)
    set_slave_address_i2c_p( _i2c_hw_address );
    write_i2c_p( temp[0] );

#elif defined(__MIKROC_PRO_FOR_AVR__)   || \
      defined(__MIKROC_PRO_FOR_8051__)  || \
      defined(__MIKROC_PRO_FOR_DSPIC__) || \
      defined(__MIKROC_PRO_FOR_PIC32__) || \
      defined(__MIKROC_PRO_FOR_PIC__)
    start_i2c_p();
    write_i2c_p( _i2c_hw_address | WRITE_BIT );
    write_i2c_p( temp[0] );
    stop_i2c_p();
#endif
}

void manometer_hal_read( uint8_t command, uint8_t *buffer, uint8_t count )
{
    uint8_t *buffer_ptr = buffer;
    uint8_t cmd[1];
    
    cmd[0] = command;
#if defined(__MIKROC_PRO_FOR_ARM__)
    #if defined( STM32 )
    start_i2c_p();
    write_i2c_p( _i2c_hw_address, cmd, 1, END_MODE_RESTART );
    read_i2c_p( _i2c_hw_address, buffer_ptr, count, END_MODE_STOP );

    #elif defined( TI )
    set_slave_address_i2c_p( _i2c_hw_address, _I2C_DIR_MASTER_TRANSMIT );
    write_i2c_p( command, _I2C_MASTER_MODE_SINGLE_SEND );
    set_slave_address_i2c_p( _i2c_hw_address, _I2C_DIR_MASTER_RECEIVE );

    if( count == 1 )
    {
        read_i2c_p( buffer_ptr, _I2C_MASTER_MODE_BURST_SINGLE_RECEIVE );

    } else {

        read_i2c_p( buffer_ptr++ , _I2C_MASTER_MODE_BURST_RECEIVE_START ) )
        count--;

        while( count-- > 1 )
            read_i2c_p( buffer_ptr++ , _I2C_MASTER_MODE_BURST_SEND_CONT );

        read_i2c_p( buffer_ptr, _I2C_MASTER_MODE_BURST_SEND_FINISH );
    }

    #endif

#elif defined(__MIKROC_PRO_FOR_FT90x__)
    set_slave_address_i2c_p( _i2c_hw_address );
    write_i2c_p( command );
    read_bytes_i2c_p( buffer_ptr, count );

#elif defined( __MIKROC_PRO_FOR_AVR__ )    || \
      defined( __MIKROC_PRO_FOR_PIC32__ )  || \
      defined( __MIKROC_PRO_FOR_8051__ )   || \
      defined( __MIKROC_PRO_FOR_PIC__ )    || \
      defined( __MIKROC_PRO_FOR_DSPIC__ )
    start_i2c_p();
    write_i2c_p( _i2c_hw_address | WRITE_BIT );
    write_i2c_p( command );
    stop_i2c_p();

    while( !is_idle_i2c_p() )
        asm nop;

    start_i2c_p();
    write_i2c_p( _i2c_hw_address | READ_BIT );

    while( !is_idle_i2c_p() )
        asm nop;

    while( count-- > 1 )
    {
        *( buffer_ptr++ ) = read_i2c_p( ACK_BIT );
    }

    *buffer_ptr = read_i2c_p( NACK_BIT );

    stop_i2c_p();
#endif
}

/*************** END OF FUNCTIONS *********************************************/