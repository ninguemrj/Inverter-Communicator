#include <Arduino.h>
// #define USE_SOFTWARESERIAL     //uncomment this line if you want use softwareserial instead of hw
#ifdef USE_SOFTWARESERIAL
  #include <SoftwareSerial.h>
  // 16 RX, 17 TX for ESP-32 doit v1 using physical Serial2 with software.
  #define RX_pin 16
  #define TX_pin 17
  SoftwareSerial Serial3(RX_pin, TX_pin);
#endif

#define heartbeat_led 2     // hearbeat led pin for ESP32-CAM  4 flashlight / internal led 33   esp32 led 2
#define I2C_SDA 21          // ESP32 I2c pin        ESP32-CAM 2
#define I2C_SCL 22          // ESP32 I2c pin        ESP32-CAM 14
#define LCDADDR 0x27                           // address of LCD on I2C bus
#define LCDLINES 4
#define LCDROWS 20
bool lcdok = false;                            // LCD not present by default (don't change it)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <lib_lcd_helper.h>
#include <menu.h>
#include <inverter.h>

String swversion="0.1b";

// ******************************************  Setup  ******************************************
void setup()
{
  Serial.begin(115200); //Serial Monitor Console Baud Setting
  while (!Serial)
    {
    ; // wait for serial port to connect. Needed for native USB port only
    }
  Serial.println("");
  #ifdef USE_SOFTWARESERIAL
  Serial.println("Setup serial3 for sodtwareserial");
  Serial3.begin(2400); //MPP-Solar inverter Baud Setting(http://www.offgrid.casa/wp-content/uploads/2017/10/HS_MS_MSX_RS232_Protocol_20140822_after_current_upgrade.pdf)
  Serial3.setTimeout(10000);
    while (!Serial3)
    {
    ; // wait for serial port to connect.
    }
  Serial3.flush();
  #else
  Serial.println("Setup physical Serial2");
  Serial2.begin(2400, SERIAL_8N1); //MPP-Solar inverter Baud Setting(http://www.offgrid.casa/wp-content/uploads/2017/10/HS_MS_MSX_RS232_Protocol_20140822_after_current_upgrade.pdf)
  Serial2.setTimeout(10000);
    while (!Serial2)
    {
    ; // wait for Serial2 port to connect.
    }
  #endif
  
  lcdinit();
  if ( lcdok == true ) {
      lcdclear();
      lcdsetCursor(3,0);
      lcdprint("Solar Inverter");
      lcdsetCursor(4,1);
      lcdprint("Communicator");
      lcdsetCursor(7,2);
      lcdprint("V"+String(swversion));
  }
  delay(2000);
 //setup_rotary();
 QPIGS_lcd_base();
}

// ******************************************  Loop  ******************************************
void loop() {
  yield();
  
  inverter_send("QPIGS");

  //#endif

    #ifdef USE_SOFTWARESERIAL
    //if (Serial3.available())
    //  {
    stringOne = Serial3.readStringUntil('\r');
    #else
    //if (Serial2.available())
    //  {
    stringOne = Serial2.readStringUntil('\r');
    #endif

  // (NAK handle ???    // not accepted command message from inverter
  if (stringOne.substring(0,3) != "(NAK" )
    {
    Serial.println (stringOne.substring(0,stringOne.length()-2));
    QPIGS_val();
    QPIGS_print();
    QPIGS_lcd();
    delay(1000);
    }
  #ifdef USE_SOFTWARESERIAL
  #else
  //}
  #endif
  stringOne = "";
  // loop_menu();
}

