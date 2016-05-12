![mikroe_logo] [MikroElektronika]

## Manometer click
![click_image] [click]

---



---

### General Description
The pressure is on. No matter the need, Honeywell Sensing and Control (S&C) has the microstructure, pressure sensor solution. Our sensing element design consists of four piezoresistors on a chemically etched silicon diaphragm. A pressure change will cause a strain in the diaphragm and the buried resistors. The resistor values will change in proportion to the stress applied, which produces an electrical output. You will find our components performing in potential applications including dialysis equipment, blood analysis, centrofusion and oxygen and nitrogen gas distribution, HVAC devices, data storage, process controls, industrial machinery, pumps, and robotics.


### Example
```

I2C1_Init_Advanced( 400000, &_GPIO_MODULE_I2C1_PB67 );
    Delay_ms(100); // Stabilization time
    if( manometer_init( MANOMETER_ADDRESS_TYPE_3, 0, 60 ) )
        while(1); // Error happened, loop forever
        
temp = manometer_get_temp( CELSIUS );
pressure = manometer_get_pressure();

```

[MikroElektronika]: <http://www.mikroe.com/>
[mikroe_logo]: <http://www.mikroe.com/img/designs/beta/logo_small.png>
[click]: <http://www.mikroe.com/click/nrf-c/>
[click_image]: <http://www.mikroe.com/img/development-tools/accessory-boards/click/nrf-c/nrf_c_click_main.png>
[learn_article]: <http://learn.mikroe.com/>
[package_manager]: <http://www.mikroe.com/package-manager/>