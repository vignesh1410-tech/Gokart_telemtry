#include  "acc.h"
#include "brakes.h"
#include "temp.h"
#include <arduino.h>

float brake_angle,acc_angle,temp_1;

brakeclass brake1;
tempclass temp1;
accclass acc1;

void setup()
{
  Serial.begin(9600); 
  acc1.setup();
  brake1.setup();
  temp1.setup();
 

}
void loop()
{

  brake_angle=brake1.main();
  acc_angle=acc1.main();
  temp_1=temp1.main();
  Serial.println("#########");

  Serial.print("acc_angle/brake_angle:");Serial.print(acc_angle);Serial.print("/"); Serial.println(brake_angle);

  Serial.println("#########");
  Serial.print("Temprature_1:");Serial.println(temp_1);
  
  delay(1000);
}