# Georgia Institute of Technology
ECE 4180 Embedded Systems Final Project
<br>Team Members : Hyeonjae Park, John Bowzard

## Description
The Laser Lidar Turret is a bluetooth controllable laser detection system.


![](https://github.com/jaep99/ECE4180_FinalProject/blob/022344b8617959c0f7ce8497d1d4ffe523004245/Turret%20Img.png)

Featuring:
* Horizontal & vertical detecting movement
* Lidar motion detect with laser confirmation
* LCD status display
* LED & audio alert
* Auto reset

## List of Components

* [Mbed LPC1768](https://os.mbed.com/platforms/mbed-LPC1768/)
* [uLCD-144-G2 128 by 128 Smart Color LCD](https://os.mbed.com/users/4180_1/notebook/ulcd-144-g2-128-by-128-color-lcd/)
* [VL53L0X Time of Flight Distance Sensor](https://www.adafruit.com/product/3317)
* [RC Servos](https://os.mbed.com/users/4180_1/notebook/an-introduction-to-servos/)
* [Bluefruit LE UART Friend](https://os.mbed.com/users/4180_1/notebook/adafruit-bluefruit-le-uart-friend---bluetooth-low-/)
* [Speaker 8ohm .1W](https://os.mbed.com/users/4180_1/notebook/using-a-speaker-for-audio-output/)
* [TPA2005D1 Class D Audio Amp](https://os.mbed.com/users/4180_1/notebook/tpa2005d1-class-d-audio-amp/)
* [SD Card File System](https://os.mbed.com/cookbook/SD-Card-File-System)
* [RGB LED](https://os.mbed.com/users/4180_1/notebook/rgb-leds/)
* [Laser](https://www.amazon.com/Tactical-Flashlight-rechargeableUSB-Adjustable-Teaching/dp/B0B7D4K7HV/ref=sr_1_5?crid=2BMFAQFGVXDAY&keywords=laser&qid=1700187578&sprefix=laser%2Caps%2C110&sr=8-5&th=1)

## Block Diagram
![](https://github.com/jaep99/ECE4180_FinalProject/blob/933866a23e75bfc0fce2925000369933cdb858df/Block%20Diagram.png)

## Hardware Components Pinouts
### uLCD-144-G2 128 by 128 Smart Color LCD
| Mbed | uLCD |
|------|------|
| VU   | +5V  |
| P10  | TX   |
| P9   | RX   |
| GND  | GND  |
| P30  | RES  |

### VL53L0X Time of Flight Distance Sensor
| Mbed | VL42L0X |
|------|---------|
| 3.3V | VIN     |
| GND  | GND     |
| P28  | SDA     |
| P27  | SCL     |
| P22  | SHDN    |

### RC Servo 1
| Mbed | Servo       | External Power |
|------|-------------|----------------|
| GND  | - (BLACK)   | GND            |
| +5V  | + (RED)     | 5V             |
| P23  | PWM (YELLOW)|                |

### RC Servo 2
| Mbed | Servo       | External Power |
|------|-------------|----------------|
| GND  | - (BLACK)   | GND            |
| +5V  | + (RED)     | 5V             |
| P21  | PWM (YELLOW)|                |

### Bluefruit LE UART Friend
| Mbed | Adafruit BLE |
|------|--------------|
| GND  | GND          |
| VU   | VIN          |
| nc   | RTS          |
| GND  | CTS          |
| P14  | TXO          |
| P13  | RXI          |

### Speaker 8ohm .1W & TPA2005D1 Class D Audio Amp
| Mbed | Class D Audio Amp | Speaker       | External Power |
|------|-------------------|---------------|----------------|
| GND  | PWR, IN-          |               |                |
| PWR+ |                   | +             | 5V or 3.3V     |
| P18  | IN+               |               |                |
| OUT+ |                   |               |                |
| OUT- |                   | -             |                |

### SD Card File System
| Mbed | MicroSD Breakout Board |
|------|------------------------|
| P8   | CS                     |
| P5   | DI                     |
| VOUT | VCC                    |
| P7   | SCK                    |
| GND  | GND                    |
| P6   | DO                     |

### RGB LED
| Mbed | RGB   |
|------|-------|
| P20  | RED   |
| GND  | GND   |
| P19  | GREEN |
| P17  | BLUE  |

## Schematic
![](https://github.com/jaep99/ECE4180_FinalProject/blob/089e6f7881c6d4ccfa1e20060b0a3173d2330bf4/Schematic.png)

## Libraries
* [Mbed LPC1768](http://mbed.org/users/mbed_official/code/mbed/builds/031413cf7a89)
* [uLCD-144-G2 128 by 128 Smart Color LCD](https://os.mbed.com/users/4180_1/code/4DGL-uLCD-SE/)
* [VL53L0X Time of Flight Distance Sensor](https://developer.mbed.org/teams/ST/code/X_NUCLEO_53L0A1/)
* [RC Servos](https://os.mbed.com/users/simon/code/Servo/)
* [Wave Player](https://os.mbed.com/users/sravet/code/wave_player/)
* [SD Card File System](https://developer.mbed.org/users/4180_1/code/SDFileSystem_OldbutworkswithRTOS/)
* [RTOS](http://developer.mbed.org/users/mbed_official/code/mbed-rtos/)

## Video
[https://www.youtube.com/watch?v=Zwwxa-yJVOc&ab_channel=HyeonjaePark](https://www.youtube.com/watch?v=Zwwxa-yJVOc&ab_channel=HyeonjaePark)
