![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Manometer Click

- **CIC Prefix**  : MANOMETER
- **Author**      : Nenad Filipovic
- **Verison**     : 1.0.0
- **Date**        : Sep 2018.

---

### Software Support

We provide a library for the Manometer Click on our [LibStock](https://libstock.mikroe.com/projects/view/1781/manometer-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library covers all the necessary functions to control Manometer Click board. 
Library performs the communication with the device via I2C driver by reading from registers of HSCMAND060PA3A3 sensor.
Library get Pressure and Temperature data from HSCMAND060PA3A3 sensor, convert pressure data to mbar and temperature data to degrees Celsius.

Key functions :

- ``` uint32_t manometer_readData() ``` - Generic read data function
- ``` float manometer_getPressure() ``` - Function read pressure data
- ``` float manometer_getTemperature() ``` - Function read temperature data

**Examples Description**

The application is composed of three sections :

- System Initialization -  Initializes I2C structures.
- Application Initialization - Initialization driver enable's - I2C and start write log to Usart Terminal.
- Application Task - (code snippet) This is a example which demonstrates the use of Manometer Click board.
     Measured pressure ( mbar ) and temperature ( degrees Celsius ) from sensor,
     results are being sent to the Usart Terminal where you can track their changes.
     All data logs on usb uart for aproximetly every 2 sec.


```.c

void applicationTask()
{
    readData = manometer_getPressure();
    Delay_10ms();

    mikrobus_logWrite( " Pressure:    ", _LOG_TEXT );
    IntToStr( readData, textLog );
    mikrobus_logWrite( textLog, _LOG_TEXT );
    mikrobus_logWrite( " mbar", _LOG_LINE );

    readData = manometer_getTemperature();
    Delay_10ms();

    mikrobus_logWrite( " Temperature: ", _LOG_TEXT );
    IntToStr( readData, textLog );
    mikrobus_logWrite( textLog, _LOG_TEXT );
    mikrobus_logWrite( " °C", _LOG_LINE );
    mikrobus_logWrite( "--------------------------", _LOG_LINE );

    Delay_1sec();
    Delay_1sec();
}

```



The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/1781/manometer-click) page.

Other mikroE Libraries used in the example:

- I2C
- UART
- Conversions

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
### Architectures Supported

#### mikroC

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

#### mikroBasic

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

#### mikroPascal

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

---
---
