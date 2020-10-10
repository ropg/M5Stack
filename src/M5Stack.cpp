// Copyright (c) M5Stack. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "M5Stack.h"

M5Stack::M5Stack() : isInited(0) {
}

void M5Stack::begin(bool LCDEnable, bool SDEnable, bool SerialEnable, bool I2CEnable) {
  // Correct init once
  if (isInited == true) {
    return;
  } else {
    isInited = true;
  }

  // UART
  if (SerialEnable == true) {
    Serial.begin(115200);
    Serial.flush();
    delay(50);
    Serial.print("M5Stack initializing...");
  }

  // TF Card
  if (SDEnable == true) {
    SD.begin(TFCARD_CS_PIN, SPI, 40000000);
  }

  // LCD INIT
  if (LCDEnable == true) {
    Lcd.begin();

    // draw global buttons, set up before the display was ready
    Buttons.draw();
  }

  // TONE
  // Speaker.begin();

  // Set wakeup button
  Power.setWakeupButton(BUTTON_A_PIN);

  // I2C init
  if (I2CEnable == true) {
    Wire.begin(21, 22);
  }

  if (SerialEnable == true) {
    Serial.println("OK");
  }

  // if use M5GO button, need set gpio15 OD or PP mode to avoid affecting the wifi signal
  pinMode(15, OUTPUT_OPEN_DRAIN);
}

void M5Stack::update() {
  //Button update
  Buttons.update();

  //Speaker update
  Speaker.update();
}

/**
  * Function has been move to Power class.(for compatibility)
  * This name will be removed in a future release.
  */
void M5Stack::setPowerBoostKeepOn(bool en) {
  M5.Power.setPowerBoostKeepOn(en);
}
/**
  * Function has been move to Power class.(for compatibility)
  * This name will be removed in a future release.
  */
void M5Stack::setWakeupButton(uint8_t button) {
  M5.Power.setWakeupButton(button);
}
/**
  * Function has been move to Power class.(for compatibility)
  * This name will be removed in a future release.
  */
void M5Stack::powerOFF() {
  M5.Power.deepSleep();
}

M5Stack M5;
