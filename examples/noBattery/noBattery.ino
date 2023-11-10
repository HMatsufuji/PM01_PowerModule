#include <PM01_PowerModule.h>

#define PowerModuleAddress 0x08

PM01_PowerModule PM01(PowerModuleAddress); 

void setup() {
  Wire.begin();

  // connect to PM01 power module
  if(PM01.begin()) {

    // set VIN mode to enable (default)
    PM01.setVinMode(PM01_POWER_VIN_MODE_ENABLE);

    // put your code here:




    // into the sleep 
    PM01.deep_sleep();
  }
}

void loop() {

}
