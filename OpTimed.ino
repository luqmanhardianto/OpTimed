#include "src/HardwareMap.h"
#include "src/Input/PushButton.h"
#include "src/Output/Led.h"


PushButton buttonPower;
Led ledPower;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);

  buttonPower.begin(DigitalInput::BUTTON_POWER);
  ledPower.begin(DigitalOutput::POWER_LED);

  Serial.println("optimed button event test");
}

void loop() {
  // put your main code here, to run repeatedly:
  // read button state
  buttonPower.readState();

  // update button event depent button state
  ButtonEvent event = buttonPower.update();

  // check event Button
  switch (event) {
    case BTN_LONG_PRESS:
      Serial.println("BTN_LONG_PRESS ");
      break;

    case BTN_REPEAT:
      Serial.println("BTN_REPEAT");
      break;

    case BTN_SHORT_PRESS:
      Serial.println("BTN_SHORT_PRESS");
      break;

    case BTN_NONE:
      // do nothing
      break;
  }
}
