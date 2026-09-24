#include "src/HardwareMap.h"
#include "src/Input/PushButton.h"
#include "src/Output/Led.h"


PushButton buttonPower;
Led ledPower;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);

  buttonPower.begin(DigitalInput::BUTTON_POWER);
  ledPower.begin(DigitalOutput::POWER_LED);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonPower.readState();
  if (buttonPower.isPressed()) {
  ledPower.on();
  } else {
  ledPower.off();
  }
  Serial.print("btnPower:");
  Serial.println(buttonPower.isPressed());
  delay(100);
}
