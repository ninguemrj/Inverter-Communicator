#ifndef INVERTER_H
  #define INVERTER_H

#ifndef byte
  #define uint8_t byte
#endif 

#include <string.h>
#include <HardwareSerial.h>
#include <lib_lcd_helper.h>

String NAK = "\x28\x4E\x41\x4B\x73\x73";   // "(NAKss"  this message receiving on not accepted command from inverter.

// commands in hex without CRC and CR (don't add CRC and CR, it will be calculated and added before send) // crc "\xB7\xA9" // CR "\x0D"
String QPI = "\x51\x50\x49";              // Device Protocol ID Inquiry
String QPIGS = "\x51\x50\x49\x47\x53";    // Device general status parameters inquiry
String QPIWS = "\x51\x50\x49\x57\x53";
String QDI = "\x51\x44\x49";              // The default setting value information
String QMOD = "\x51\x4D\x4F\x44";
String QVFW =  "\x51\x56\x46\x57";
String QVFW2 = "\x51\x56\x46\x57\x32";
String QFLAG = "\x51\x46\x4C\x41\x47";
String QMCHGCR = "\x51\x4D\x43\x48\x47\x43\x52";
String QMUCHGCR = "\x51\x4D\x55\x43\x48\x47\x43\x52";
String QBOOT = "\x51\x42\x4F\x4F\x54";
String QOPM = "\x51\x4F\x50\x4D";
String QPIRI = "\x51\x50\x49\x52\x49";
String QPGS0 = "\x51\x50\x47\x53\x30";
String QBV = "\x51\x42\x56";
String PF = "\x50\x46";
String POP02 = "\x50\x4F\x50\x30\x32";
String POP01 = "\x50\x4F\x50\x30\x31";
String POP00 = "\x50\x4F\x50\x30\x30";
String PCP00 = "\x50\x43\x50\x30\x30";
String PCP01 = "\x50\x43\x50\x30\x31";
String PCP02 = "\x50\x43\x50\x30\x32";
String MUCHGC002 = "\x4D\x55\x43\x48\x47\x43\x30\x30\x32";
String MUCHGC010 = "\x4D\x55\x43\x48\x47\x43\x30\x31\x30";
String MUCHGC020 = "\x4D\x55\x43\x48\x47\x43\x30\x32\x30";
String MUCHGC030 = "\x4D\x55\x43\x48\x47\x43\x30\x33\x30";
String PPCP000 = "\x50\x50\x43\x50\x30\x30\x30";
String PPCP001 = "\x50\x50\x43\x50\x30\x30\x31";
String PPCP002 = "\x50\x50\x43\x50\x30\x30\x32";
String QPIGS2 = "\x51\x50\x49\x47\x53\x32";
String POP03 = "\x50\x4F\x50\x30\x33";


String inverterData;
byte incomingdata;
bool nocommunication=false;
bool LCDbase = false;

// Structure to store the data for QPIGS
struct pipVals_t {
  uint32_t gridVoltage;             // xxx V
  uint32_t gridFrequency;           // xx.xx Hz  *100
  uint32_t acOutput;                // xxx V
  uint32_t acFrequency;             // xx.xx Hz  *100
  uint32_t acApparentPower;         // xxxx VA
  uint32_t acActivePower;           // xxxx W
  uint32_t loadPercent;             // xxx %
  uint64_t busVoltage;              // xxxx V    *100
  uint32_t batteryVoltage;          // xx.xx V   *100
  uint32_t batteryChargeCurrent;    // xxx A
  uint32_t batteryCharge;           // %
  uint32_t inverterTemperature;     // xxxx      /100
  uint32_t PVCurrent;               // xx A
  uint32_t PVVoltage;               // xx V
  uint32_t PVPower;                 // xxxx W
  uint32_t batterySCC;              // xx.xx V   *100
  uint32_t batteryDischargeCurrent; // xxxx A
  char deviceStatus[8];             // 8 bit binary
} pipVals;

struct QpiMessage
{
  byte protocolId;
};


struct QmodMessage
{
  char mode;
};

struct QpiwsMessage
{
  bool reserved0;
  bool inverterFault;
  bool busOver;
  bool busUnder;
  bool busSoftFail;
  bool lineFail;
  bool opvShort;
  bool overTemperature;
  bool fanLocked;
  bool batteryVoltageHigh;
  bool batteryLowAlarm;
  bool reserved13;
  bool batteryUnderShutdown;
  bool reserved15;
  bool overload;
  bool eepromFault;
  bool inverterOverCurrent;
  bool inverterSoftFail;
  bool selfTestFail;
  bool opDcVoltageOver;
  bool batOpen;
  bool currentSensorFail;
  bool batteryShort;
  bool powerLimit;
  bool pvVoltageHigh;
  bool mpptOverloadFault;
  bool mpptOverloadWarning;
  bool batteryTooLowToCharge;
  bool reserved30;
  bool reserved31;
};

struct QflagMessage
{
  bool disableBuzzer;
  bool enableOverloadBypass;
  bool enablePowerSaving;
  bool enableLcdEscape;
  bool enableOverloadRestart;
  bool enableOvertempRestart;
  bool enableBacklight;
  bool enablePrimarySourceInterruptedAlarm;
  bool enableFaultCodeRecording;
};

struct QidMessage
{
  char id[16];
};

void store_val( String cmd = "" );
void QPIGS_print();
void inverter_LCD_data( String cmd = "" );
void inverter_LCD_base( String cmd = "" );



// ******************************************  CRC Functions  ******************************************
uint16_t crc_xmodem_update (uint16_t crc, uint8_t data);
uint16_t calc_crc(char *msg, int n);
// ******************************************  inverter communication  *********************************
String inverter_send ( String inv_command );
void invereter_receive( String cmd = "" );

#endif