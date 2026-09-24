#include "src/HardwareMap.h"
#include "src/Input/PushButton.h"


PushButton buttonPower;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  buttonPower.begin(DigitalInput::BUTTON_POWER);
  buttonPower.readState();
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonPower.readState();
  Serial.println(buttonPower.isPressed());
  delay(500);

}
