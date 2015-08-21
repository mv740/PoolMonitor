# PoolMonitor

Basic system that displays your pool's water temperature.

## Parts

- 1 - [Arduino Uno R3](http://store-usa.arduino.cc/products/a000066) 
- 1 - Temperature Sensor - Waterproof [BS18B20](https://www.sparkfun.com/products/11050) <br/>
 <img src="https://github.com/mv740/PoolMonitor/blob/master/BS18B20.jpg" width="250">
- 1 - TFT LCD Saintsmart [ST7735](http://www.sainsmart.com/sainsmart-1-8-spi-lcd-module-with-microsd-led-backlight-for-arduino-mega-atmel-atmega.html) <br/>
 <img src="https://github.com/mv740/PoolMonitor/blob/master/LCD.jpg" width="250">
- 1 - 4.7K resistor 

`These are the one I used for this project. You could use exchange them for similar ones, but I don't guarantee that they will be 100% compatible` 

## Design 

<img src="https://github.com/mv740/PoolMonitor/blob/master/PoolMonitor_bb.png">

### Connections  
| TFT LCD      | Ardruino  |
|:------------:|:---------:|
| VCC          |   3.3V    |
| GND          |   GND     |
| SCL          |   13      |
| SDA          |   11      |
| PS/DC        |   9       |
| RES          |   8       |
| CS           |   10      |

| BS18B20     | Ardruino  |
|:----------:|:---------:|
| Red        | 3.3V      |
| Black      | GND       |
| White      | 2         |
**4.7K resitor between white and red**

`To connect the 4.7K resistor, you could use a breadboard or just strip the cable and connected it directly like I did for a more permanent solution.
` 

## Installation Arduino 

1. Download the [PoolMonitor Sketch](https://github.com/mv740/PoolMonitor/blob/master/PoolMonitor/PoolMonitor.ino)
2. Upload it to your Ardruino and it will start right away 

## LCD OUTPUT 

<img src="https://github.com/mv740/PoolMonitor/blob/master/LCDoutput.PNG" width="320">

