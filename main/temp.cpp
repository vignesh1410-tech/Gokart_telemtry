#include <Arduino.h>
#include "temp.h"
#define ADC_VREF_mV    5000.0 // in millivolt
#define ADC_RESOLUTION 1024.0
#define PIN_LM35       A0

tempclass::tempclass(){

}

void tempclass::setup()  {
  Serial.begin(9600);
}

float tempclass::main(){
  // get the ADC value from the temperature sensor
  int adcVal = analogRead(PIN_LM35);
  // convert the ADC value to voltage in millivolt
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convert the voltage to the temperature in Celsius
  float tempC = milliVolt / 10;
  // convert the Celsius to Fahrenheit
  //float tempF = tempC * 9 / 5 + 32;

  // print the temperature in the Serial Monitor:
 /* Serial.print("Temperature: ");
  Serial.println(tempC);   // print the temperature in Celsius
   Serial.print("millivolts: ");
  Serial.println(milliVolt);
  Serial.print("°C");
  Serial.print("  ~  "); // separator between Celsius and Fahrenheit
  Serial.print(tempF);   // print the temperature in Fahrenheit
  Serial.println("°F");
*/
return tempC;
  delay(500);
}
