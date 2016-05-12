#include "manometer_hw.h"

void main()
{
    float pressure, temp;
    int count = 0;
    I2C1_Init(100000);
    manometer_init( MANOMETER_ADDRESS_TYPE_3, 0, 60 );
    pressure = manometer_get_pressure();
    temp = manometer_get_temp( CELSIUS );

    if( pressure > 45 && temp > 35 )
        count++;
}