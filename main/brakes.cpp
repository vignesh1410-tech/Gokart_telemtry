
#include <Wire.h>  // Wire library - used for I2C communication
#include <arduino.h>
#include "brakes.h"
//#include inRange

int ADXL345_1 = 0x53;  // The ADXL345 sensor I2C address

float X_out_1, Y_out_1, Z_out_1;  // Outputs
float roll_1, pitch_1, rollF_1, pitchF_1 = 0, rollfc_1, correction_1 = 0;

brakeclass::brakeclass(){

}

void brakeclass::setup() 
{
  Serial.begin(9600);  // Initiate serial communication for printing the results on the Serial monitor

  Wire.begin();  // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345_1);  // Start communicating with the device
  Wire.write(0x2D);                 // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8);  // Bit D3 High for measuring enable (8dec -> 0000 1000 binary)
  Wire.endTransmission();
  delay(10);

  //Off-set Calibration
  //X-axis
  Wire.beginTransmission(ADXL345_1);
  Wire.write(0x1E);
  Wire.write(1);
  Wire.endTransmission();
  delay(10);
  //Y-axis
  Wire.beginTransmission(ADXL345_1);
  Wire.write(0x1F);
  Wire.write(-2);
  Wire.endTransmission();
  delay(10);

  //Z-axis
  Wire.beginTransmission(ADXL345_1);
  Wire.write(0x20);
  Wire.write(-9);
  Wire.endTransmission();
  delay(10);
}

float brakeclass::main() {
  // === Read acceleromter data === //
  Wire.beginTransmission(ADXL345_1);
  Wire.write(0x32);  // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345_1, 6, true);        // Read 6 registers total, each axis value is stored in 2 registers
  X_out_1 = (Wire.read() | Wire.read() << 8);  // X-axis value
  X_out_1 = X_out_1 / 256;                       //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  Y_out_1 = (Wire.read() | Wire.read() << 8);  // Y-axis value
  Y_out_1 = Y_out_1 / 256;
  Z_out_1 = (Wire.read() | Wire.read() << 8);  // Z-axis value
  Z_out_1 = Z_out_1 / 256;

  // Calculate Roll and Pitch (rotation around X-axis, rotation around Y-axis)
  roll_1 = atan(Y_out_1 / sqrt(pow(X_out_1, 2) + pow(Z_out_1, 2))) * 180 / PI;
  pitch_1 = atan(-1 * X_out_1 / sqrt(pow(Y_out_1, 2) + pow(Z_out_1, 2))) * 180 / PI;

  // Low-pass filter
  rollF_1 = 0.94 * rollF_1 + 0.06 * roll_1;
  pitchF_1 = 0.94 * pitchF_1 + 0.06 * pitch_1;

  //Serial.print(rollF);
  //Serial.print("/");
  //Serial.println(pitchF);

  rollfc_1 = (roll_1 - correction_1)*-1;

  //Serial.println(rollfc_1);
  return(rollfc_1);
}