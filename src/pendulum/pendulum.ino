#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;

#include "Wire.h"
#include "AS5600.h"
AS5600 as5600;


void printAngle(uint16_t angle);

void setup() {
  // put your setup code here, to run once:
  matrix.loadSequence(LEDMATRIX_ANIMATION_STARTUP);
  matrix.begin();
  matrix.play(true);

  while(!Serial);

  Serial.begin(115200);
  Serial.println("Starting program...");
  
  Serial.println("Starting wire...");
  Wire.begin();

  Serial.println("Starting encoder...");
  // Serial.println(__FILE__);
  // Serial.print("AS5600_LIB_VERSION: ");
  // Serial.println(AS5600_LIB_VERSION);
  // Serial.println();

  as5600.begin(4);
  int connected = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(connected);

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t angle = as5600.rawAngle() * AS5600_RAW_TO_DEGREES;
  printAngle(angle);
}

void printAngle(uint16_t angle) {
  char text[3];
  sprintf(text, "%d", angle);

  matrix.clear();

  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText();
  matrix.endDraw();

  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.println(" degrees");
}