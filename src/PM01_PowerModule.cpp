/**
 * @file PM01_PowerModule.cpp
 * @author HMatsufuji (h-matsufuji@hi-corp.jp)
 * @brief 
 * @version 1.0.0
 * @date 2023-03-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <PM01_PowerModule.h>

PM01_PowerModule::PM01_PowerModule(uint8_t address) {
  _address = address;
}  //Constructor for I-squared-C

bool PM01_PowerModule::begin(TwoWire &wirePort) {
  _i2cPort = &wirePort;

  _i2cPort->beginTransmission(_address);
  uint8_t _ret = _i2cPort->endTransmission();
  if (!_ret)
    return true;
  else
    return false;
}

//
// command
//

// Into the power-off delay state.
void PM01_PowerModule::power_off() {
  _writeCommand(PM01_POWER_COMMAND_POWER_OFF);
}

// Into the power-on state.
void PM01_PowerModule::power_on() {
  _writeCommand(PM01_POWER_COMMAND_POWER_ON);
}

// Into the sleep state.
void PM01_PowerModule::sleep() {
  _writeCommand(PM01_POWER_COMMAND_SLEEP);
}

// Into the deep sleep state.
void PM01_PowerModule::deep_sleep() {
  _writeCommand(PM01_POWER_COMMAND_DEEP_SLEEP);
}

// Cancel to cancel deep sleep state.
void PM01_PowerModule::deep_sleep_cancel() {
  _writeCommand(PM01_POWER_COMMAND_DEEP_SLEEP_CANCEL);
}

// set startup charge setting
// No need to call setChargeSetting function next boot
// usage:
//   setStartupChargeSetting(PM01_POWER_BATTERY_CHARGE_ENABLE); ... enable battery charge
//   setStartupChargeSetting(PM01_POWER_BATTERY_CHARGE_DISABLE); ... disable battery charge
//
bool PM01_PowerModule::setStartupChargeSetting(uint8_t setting) {
  return _writeByte(PM01_POWER_COMMAND_SET_STARTUP_CHARGE_SETTING, setting);
}

// set charge setting
// usage:
//   setChargeSetting(PM01_POWER_BATTERY_CHARGE_ENABLE); ... enable battery charge
//   setChargeSetting(PM01_POWER_BATTERY_CHARGE_DISABLE); ... disable battery charge
// 
bool PM01_PowerModule::setChargeSetting(uint8_t setting) {
  return _writeByte(PM01_POWER_COMMAND_SET_CHARGE_SETTING, setting);
}

// Set the delay time to deep sleep.
bool PM01_PowerModule::setDelayTime(uint8_t dt) {
  return _writeByte(PM01_POWER_COMMAND_SET_DELAY_TIME, dt);
}

// Set the VIN threshold voltage.
bool PM01_PowerModule::setVinThreshold(float vinThreshold) {
  uint16_t VT;
  VT = (uint16_t)((vinThreshold / KVIN) * 1024.0);
  return _writeWord(PM01_POWER_COMMAND_SET_VIN_THRESHOLD, VT);
}

// Set the battery detect threshold voltage.
bool PM01_PowerModule::setBatteryDetectThreshold(float batThreshold) {
  uint16_t VT;
  VT = (uint16_t)((batThreshold / KVBAT) * 1024.0);
  return _writeWord(PM01_POWER_COMMAND_SET_BATTERY_DETECT_THRESHOLD, VT);
}

// Set the Vin mode.
// usage:
//  setVinMode(PM01_POWER_VIN_MODE_ENABLE);  ... VIN is always enabled.
//  setVinMode(PM01_POWER_VIN_MODE_AUTO);    ... Automatic detection of enable/disable by VIN threshold voltage. Entering deep sleep mode, the state is fixed.
//  setVinMode(PM01_POWER_VIN_MODE_DISABLE); ... If you use battery only, you can disable VIN to reduce current consumption.
//
bool PM01_PowerModule::setVinMode(uint8_t mode) {
  return _writeByte(PM01_POWER_COMMAND_SET_VIN_MODE, mode);
}

// Changes the I2C address.
bool PM01_PowerModule::changeAddress(uint8_t newAddress) {
  if (newAddress < 0x07 || newAddress > 0x78)  // Range of legal addresses
    return false;

  _i2cPort->beginTransmission(_address);
  _i2cPort->write(PM01_POWER_COMMAND_CHANGE_ADDRESS);
  _i2cPort->write(newAddress);

  if (!_i2cPort->endTransmission())
    return true;
  else
    return false;
}

//
// request
//

// Get the power module state.
uint8_t PM01_PowerModule::getState() {
  uint8_t state = _readByte(PM01_POWER_REQUEST_STATE);
  return state;
}

// Get the battery voltage.
float PM01_PowerModule::getBatteryVoltage() {
  return (float)_readWord(PM01_POWER_REQUEST_BATTERY_VOLTAGE) / 1024 * KVBAT;
}

// Gget the battery charging state.
bool PM01_PowerModule::getBatteryChargeState() {
  return _readByte(PM01_POWER_REQUEST_BATTERY_CHARGE_STATE);
}

// Get the battery state.
uint8_t PM01_PowerModule::getBatteryState() {
  return _readByte(PM01_POWER_REQUEST_BATTERY_STATE);
}

// Get the battery voltage.
float PM01_PowerModule::getVinVoltage() {
  return (float)_readWord(PM01_POWER_REQUEST_VIN_VOLTAGE) / 1024 * KVIN;
}

// Get the startup charge setting
uint8_t PM01_PowerModule::getStartupChargeSetting() {
  return _readByte(PM01_POWER_REQUEST_STARTUP_CHARGE_SETTTING);
}

// Get the charge setting
uint8_t PM01_PowerModule::getChargeSetting() {
  return _readByte(PM01_POWER_REQUEST_CHARGE_SETTING);
}

// Get the delay time to deep sleep.
uint8_t PM01_PowerModule::getDelayTime() {
  return _readByte(PM01_POWER_REQUEST_DELAY_TIME);
}

// Get the VIN threshold voltage.
float PM01_PowerModule::getVinThreshold() {
  return (float)_readWord(PM01_POWER_REQUEST_VIN_THRESHOLD) / 1024 * KVIN;
}

// Get the battery detect threshold voltage.
float PM01_PowerModule::getBatteryDetectThreshold() {
  return (float)_readWord(PM01_POWER_REQUEST_BATTERY_DETECT_THRESHOLD) / 1024 * KVBAT;
}

// Get the VIN mode.
uint8_t PM01_PowerModule::getVinMode() {
  return _readWord(PM01_POWER_REQUEST_VIN_MODE);
}

// Get th VIN state.
uint8_t PM01_PowerModule::getVinState() {
  return _readByte(PM01_POWER_REQUEST_VIN_STATE);
}

// Set command
bool PM01_PowerModule::_writeCommand(uint8_t _command) {
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(_command);

  if (!_i2cPort->endTransmission())
    return true;
  else
    return false;
}

// Set a byte
bool PM01_PowerModule::_writeByte(uint8_t _command, uint8_t value) {
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(_command);
  _i2cPort->write(value);
  
  if (!_i2cPort->endTransmission())
    return true;
  else
    return false;
}

// Set 2 bytes word
bool PM01_PowerModule::_writeWord(uint8_t _command, uint16_t value) {
  union {
    uint16_t value;
    struct {
      byte H;
      byte L;
    };
  } V;
  V.value = value;
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(_command);
  _i2cPort->write(V.H);
  _i2cPort->write(V.L);
  
  if (!_i2cPort->endTransmission())
    return true;
  else
    return false;
}

// Request a byte
uint8_t PM01_PowerModule::_readByte(uint8_t _command) {
  _i2cPort->beginTransmission(_address);
  _i2cPort->write(_command);
  _i2cPort->endTransmission();

  _i2cPort->requestFrom(_address, 1);
  uint8_t status = _i2cPort->read();
  return (status);
}

// Request 2 bytes word
uint16_t PM01_PowerModule::_readWord(uint8_t _command) {
  union {
    uint16_t value;
    struct {
      byte voltage_H;
      byte voltage_L;
    };
  } V;

  _i2cPort->beginTransmission(_address);
  _i2cPort->write(_command);
  _i2cPort->endTransmission();

  _i2cPort->requestFrom(_address, 2);
  V.voltage_H = _i2cPort->read();
  V.voltage_L = _i2cPort->read();

  return (V.value);
}


