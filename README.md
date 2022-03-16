# Inverter-Communicator
Solar inverter communicator with ESP32

This application based on ESP32, using Serial2 or SoftwareSerial for communicate with MPP Solar inverters, PowMR and another China brands.

code starts with src/main.cpp

files in use (at the moment):
src/main.cpp
include/lib_lcd_helper.h

not all files are in use (yet)!

Used modules:
- ESP32
- MAX232 DB9 Male
- I2C 2004 LCD

Stage: Establsih communication with inverter, show basic info values (QPIGS) on LCD 

Future plans:
- implement menu with rotary switch
- implemant all query commands
- implement configuration commands
- web server

used materials:
https://forum.arduino.cc/t/rs232-read-data-from-mpp-solar-inverter/600960


Contribuitors, Developers are welcome
