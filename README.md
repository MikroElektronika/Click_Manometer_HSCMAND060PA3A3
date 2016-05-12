![mikroe logo](http://www.mikroe.com/img/designs/beta/logo_small.png)

## Manometer click
![mano meter](http://cdn.mikroe.com/img/click/manometer/gallery/manometer-click-02.png)


---
[Product Page](http://www.mikroe.com/click/manometer)
[Documentation](http://docs.mikroe.com/Manometer_click)
[Tutorial](http://learn.mikroe.com/industrial-solution-pressures/)
---

### General Description
Manometer click is an add-on board with a piezoresistive silicon pressure sensor. The onboard Honeywell HSCMAND060PA3A3 module has an industry-leading, extremely high accuracy of ±0.25%FSS BFSL. An absolute pressure range from 0 to 60 PSI makes it suitable for a variety applications. Beyond the measurement range, the sensor has a high burst pressure threshold, resulting in increased reliability. The barbed port accepts 4.93 mm (0.19”) tubing. Manometer click communicates with the target board MCU through the mikroBUS™ I2C interface (SCL, SDA). Manometer click uses a 3.3V power supply. 


### Example

#### Configuration
* MCU:             STM32F107VC
* Dev.Board:       EasyMx Pro v7
* Oscillator:      72 Mhz internal
* Ext. Modules:    Manometer Click
* SW:              MikroC PRO for ARM 4.7.4


```

I2C1_Init_Advanced( 400000, &_GPIO_MODULE_I2C1_PB67 );
    Delay_ms(100); // Stabilization time
    if( manometer_init( MANOMETER_ADDRESS_TYPE_3, 0, 60 ) )
        while(1); // Error happened, loop forever

temp = manometer_get_temp( CELSIUS );
pressure = manometer_get_pressure();

```
