#ifndef __PM01_POWER_MODULE__
#define __PM01_POWER_MODULE__

#include <Wire.h>
#include <Arduino.h>

enum ST_PM01_POWER_MODULE_STATE {
  PM01_POWER_STATE_FIRST_POWER_ON     = 0x00,
  PM01_POWER_STATE_POWER_ON           = 0x01,
  PM01_POWER_STATE_POWER_OFF          = 0x02,
  PM01_POWER_STATE_SLEEP              = 0x03,
  PM01_POWER_STATE_WAKEUP             = 0x04,
  PM01_POWER_STATE_DEEP_SLEEP_DELAY   = 0x05,
  PM01_POWER_STATE_DEEP_SLEEP         = 0x06,
  PM01_POWER_STATE_DEEP_WAKEUP        = 0x07,
  PM01_POWER_STATE_OFFLINE            = 0xff
};

enum ST_COMMANDS {
  PM01_POWER_COMMAND_POWER_OFF                    = 0x00,
  PM01_POWER_COMMAND_POWER_ON                     = 0x01,
  PM01_POWER_COMMAND_SLEEP                        = 0x02,
  PM01_POWER_COMMAND_WAKEUP                       = 0x03,
  PM01_POWER_COMMAND_DEEP_SLEEP                   = 0x04,
  PM01_POWER_COMMAND_DEEP_SLEEP_CANCEL            = 0x05,
  PM01_POWER_COMMAND_SET_STARTUP_CHARGE_SETTING   = 0x06,
  PM01_POWER_COMMAND_SET_CHARGE_SETTING           = 0x07,
  PM01_POWER_COMMAND_SET_DELAY_TIME               = 0x08,
  PM01_POWER_COMMAND_SET_VIN_THRESHOLD            = 0x09,
  PM01_POWER_COMMAND_SET_VIN_MODE                 = 0x0a,
  PM01_POWER_COMMAND_SET_BATTERY_DETECT_THRESHOLD = 0x0c,
  PM01_POWER_COMMAND_CHANGE_ADDRESS               = 0x0f,
  PM01_POWER_REQUEST_STATE                        = 0x10,
  PM01_POWER_REQUEST_BATTERY_VOLTAGE              = 0x11,
  PM01_POWER_REQUEST_BATTERY_CHARGE_STATE         = 0x12,
  PM01_POWER_REQUEST_BATTERY_STATE                = 0x13,
  PM01_POWER_REQUEST_VIN_VOLTAGE                  = 0x14,
  PM01_POWER_REQUEST_STARTUP_CHARGE_SETTTING      = 0x16,
  PM01_POWER_REQUEST_CHARGE_SETTING               = 0x17,
  PM01_POWER_REQUEST_DELAY_TIME                   = 0x18,
  PM01_POWER_REQUEST_VIN_THRESHOLD                = 0x19,
  PM01_POWER_REQUEST_VIN_MODE                     = 0x1a,
  PM01_POWER_REQUEST_VIN_STATE                    = 0x1b,
  PM01_POWER_REQUEST_BATTERY_DETECT_THRESHOLD     = 0x1c,
  PM01_POWER_REQUEST_ADDRESS                      = 0x1f
};

enum ST_BATTERY_CHARGE_STATE {
  PM01_POWER_BATTERY_STATE_CHARGE     = 0x00,
  PM01_POWER_BATTERY_STATE_DISCHARGE  = 0x01
};

enum ST_BATTERY_STATE {
  PM01_POWER_BATTERY_DISCONNECTED    = 0x00,
  PM01_POWER_BATTERY_CHARGING        = 0x01,
  PM01_POWER_BATTERY_DISCHARGING     = 0x02
};

enum ST_BATTERY_CHARGE_SETTING {
  PM01_POWER_BATTERY_CHARGE_DISABLE   = 0x00,
  PM01_POWER_BATTERY_CHARGE_ENABLE    = 0x01
};

enum ST_VIN_MODE {
  PM01_POWER_VIN_MODE_DISABLE = 0x00,
  PM01_POWER_VIN_MODE_AUTO = 0x01,
  PM01_POWER_VIN_MODE_ENABLE = 0x02
};

enum ST_VIN_STATE {
  PM01_POWER_VIN_STATE_OFF   = 0x00,
  PM01_POWER_VIN_STATE_ON    = 0x01
};

#define DEFAULT_ADDRESS 0x08

#define INCORR_PARAM 0xFF

#define KVBAT 6.6
#define KVIN 26.11

class PM01_PowerModule {
public:

  PM01_PowerModule(uint8_t address);
  bool begin(TwoWire &wirePort = Wire);  // begin I2C process
  //
  // command
  //
  void power_off();                                     // power off // DO NOT POWER OFF if I2C Master Processor power supplied by this module.
  void power_on();                                      // power on
  void sleep();                                         // power sleep
  void deep_sleep();                                    // power off and sleep after delay  // wakeup by external interrupt
  void deep_sleep_cancel();                             // sleep cancel between power off delay
  bool setStartupChargeSetting(uint8_t setting);        // set startup charge setting
  bool setChargeSetting(uint8_t setting);               // set charge setting
  bool setDelayTime(uint8_t dt);                        // set delay time. 0 to 255 [ms] (default 255ms)
  bool setVinThreshold(float vinThreshold);             // set vin threshold voltage
  bool setVinMode(uint8_t mode);                        // set vin mode
  bool setBatteryDetectThreshold(float vbatThreshold);  // set battery detect threshold voltage
  bool changeAddress(uint8_t newAddress);               // change I2C address
  //
  // request
  //
  uint8_t getState();                         // get power module state
  float getBatteryVoltage();                  // get battery voltageAC
  bool getBatteryChargeState();               // get battery charging state
  uint8_t getBatteryState();                  // get battery state
  uint8_t getStartupChargeSetting();          // get startup charge setting
  uint8_t getChargeSetting();                 // getr charge setting
  float getVinVoltage();                      // get VIN voltage
  uint8_t getDelayTime();                     // get delay time
  float getVinThreshold();                    // get VIN threshold voltage
  uint8_t getVinMode();                       // get VIN mode
  uint8_t getVinState();                      // get VIN state
  float getBatteryDetectThreshold();          // get battery detect threshold voltage

private:

  int _address;
  uint8_t state;
  bool _writeByte(uint8_t _command, uint8_t value);
  bool _writeWord(uint8_t _command, uint16_t value);
  bool _writeCommand(uint8_t _command);
  uint8_t _readByte(uint8_t _command);
  uint16_t _readWord(uint8_t _command);
  TwoWire *_i2cPort;
};

#endif
