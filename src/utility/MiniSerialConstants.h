/******************************************************************

 ******************************************************************/
 #ifndef MiniSerialConstants_h
 #define MiniSerialConstants_h


 /* Version numbers for the Firmata library.
  * The firmware version will not always equal the protocol version going forward.
  * Query using the REPORT_FIRMWARE message.
  */
 static const int FIRMWARE_MAJOR_VERSION =  2;
 static const int FIRMWARE_MINOR_VERSION =  5;
 static const int FIRMWARE_BUGFIX_VERSION = 6;

 /* Version numbers for the protocol.  The protocol is still changing, so these
  * version numbers are important.
  * Query using the REPORT_VERSION message.
  */
 static const int PROTOCOL_MAJOR_VERSION =  2; // for non-compatible changes
 static const int PROTOCOL_MINOR_VERSION =  5; // for backwards compatible changes
 static const int PROTOCOL_BUGFIX_VERSION = 1; // for bugfix releases

 // message command bytes
 // system command bytes (0x00-0x0F) (0xF0-0xFF)
 static const byte SYSTEM_RST                   = 0x00; // reset all the data fields
 static const byte UPDATE_I2C                   = 0x01; // update connected I2C sensors
 static const byte START_SYSEX                  = 0xF0; // message start byte
 static const byte END_SYSEX                    = 0xF7; // message end byte

 // motor command bytes (0x10-0x1F)
 static const byte M1_CONFIG                = 0x10; //
 static const byte M2_CONFIG                = 0x11; //

 // servo motor command bytes (0x20-0x2F)
 static const byte RC1_ANGLE                    = 0x20; //
 static const byte RC2_ANGLE                    = 0x21; //
 static const byte RC3_ANGLE                    = 0x22; //
 static const byte RC4_ANGLE                    = 0x23; //

 // LED (RGB) command bytes (0x30-0x3F)
 static const byte LED1_HSV                    = 0x30; //
 static const byte LED2_HSV                    = 0x31; //

 // button command bytes (0x40-0x47)
 static const byte BTN1                     = 0x40; //
 static const byte BTN2                     = 0x41; //

 // digital command bytes (0x50-0x7F)
 static const byte D1_STATUS                   = 0x50; // read digital input status
 static const byte D1_CONFIG                   = 0x51; // set digital output status
 static const byte D2_STATUS                   = 0x52; //
 static const byte D2_CONFIG                   = 0x53; //
 static const byte D3_STATUS                   = 0x54; //
 static const byte D3_CONFIG                   = 0x55; //
 static const byte D4_STATUS                   = 0x56; //
 static const byte D4_CONFIG                   = 0x57; //

 // analog command bytes (0x80-0x9F)
 static const byte A1_STATUS                   = 0x80; // read analog input
 static const byte A2_STATUS                   = 0x81; //
 static const byte A3_STATUS                   = 0x82; //
 static const byte A4_STATUS                   = 0x83; //

 // Core I2C command bytes (0xA0-0xBF)
 // Core Inturrupt Color sensor
 static const byte CORE_COLOR_RGB               = 0xA0; //
 static const byte CORE_COLOR_IDX               = 0xA1; //
 static const byte CORE_COLOR_MOD               = 0xA2; //
 static const byte CORE_COLOR_WBL               = 0xA3; //

 // Core Gyro sensor
 static const byte CORE_GYRO_DEG                = 0xA8; //

 //Core Compass sensor
 static const byte CORE_COMPASS_HEADING         = 0xAA; //
 static const byte CORE_COMPASS_ACC             = 0xAB; // read accelerometer value (3 axises)
 static const byte CORE_COMPASS_MAG             = 0xAC; // read magnetometer value  (3 axises)
 static const byte CORE_COMPASS_CAL_TILT        = 0xAD; // calibrate tiltUp and tiltDown
 static const byte CORE_COMPASS_CAL_ACC         = 0xAE; // calibrate accelerometer

 // Core IR Seeker sensor
 static const byte CORE_SEEKER_DIR              = 0xB0; // read IR seeker direction value
 static const byte CORE_SEEKER_SIG              = 0xB1; // read IR seeker signal strength value


#endif
