#include <PM01_PowerModule.h>

#define newPowerModuleAddress 0x18
#define PowerModuleAddress 0x08

PM01_PowerModule PM01(PowerModuleAddress); 

void setup() {
  Wire.begin();
  Serial.begin(115200);

  delay(1000);



  // connect to PM01_ power module
  if(PM01.begin()) {
    Serial.println("Ready to power controll.");
    // set new i2c address
    PM01.changeAddress(newPowerModuleAddress);
  } else {
    Serial.println("Check connections to Power module.");
  }
}

void loop() {

}
