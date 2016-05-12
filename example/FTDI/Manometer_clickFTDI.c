#include "manometer_hw.h"

void main() 
{
    float pressure, temp;
    int count = 0;
    
    I2CM1_Init(_I2CM_SPEED_MODE_STANDARD, _I2CM_SWAP_DISABLE);
    manometer_init( MANOMETER_ADDRESS_TYPE_3, 0, 60 );
    pressure = manometer_get_pressure();
    temp = manometer_get_temp( CELSIUS );
    
    if( pressure > 40.0f && temp > 35.0f )
        count++;
}