#include <PM01_PowerModule.h>

#define PowerModuleAddress 0x08

PM01_PowerModule PM01(PowerModuleAddress); 

void setup() {
  Wire.begin();

  // connect to PM01_ power module
  if(PM01.begin()) {

    // set VIN mode auto
    PM01.setVinMode(PM01_POWER_VIN_MODE_AUTO);

    // set Battery charge enable (default disabled)
    PM01.setChargeSetting(PM01_POWER_CHARGE_ENABLE);

    // put your code here:




    // If the battery is charging, stop it to reduce charging noise.
    if (PM01.getBatteryState() == PM01_POWER_BATTERY_CHARGING) {
      PM01.setChargeSetting(PM01_POWER_CHARGE_DISABLE);
    }

    // put your analog measurement code here:




    // set Battery charge enable
    PM01.setChargeSetting(PM01_POWER_CHARGE_ENABLE);

    // into the sleep 
    //PM01.sleep();
    PM01.deep_sleep();
  }
}

void loop() {

}
