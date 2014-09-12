/* Sample Project 2
Updated date: 091214
Description:
This is the sample project connecting 2 Arduino UNO boards via I2C bus
Feature:
Master will count from 0 to 100 then send to even number to slave1
and odd number to slave2
*/
//Master_code
#include <Wire.h>

void setup()
{
  Wire.begin(); //join i2c as master
  Serial.begin(9600);
}

byte x = 0;

void loop()
{
  if (x<=100)
  {
    if(x % 2 == 0)
    {
      Wire.beginTransmission(1); //begin transmission with slave at address #1
      Wire.write("x = "); //send 4 bytes of data
      Wire.write(x); //send value x (1 byte)
      Wire.endTransmission();
    }
    else
    {
      Wire.beginTransmission(2); //begin transmission with slave at address #2
      Wire.write("x = "); //send 4 bytes of data
      Wire.write(x); //send value x (1 byte)
      Wire.endTransmission();
    }
    x++;
    delay(500); //give a pause for .5 sec
  }
  else
  {
    Wire.beginTransmission(1);
    Wire.write("The End"); //send bytes of string
    Wire.endTransmission(); //finish sending ending data to slave1
    delay(500);
    Wire.beginTransmission(2);
    Wire.write("The End");
    Wire.endTransmission(); //finish sending ending data to slave2
    delay(1000);
    Wire.requestFrom(1,16);
    while (Wire.available())
    {
      char slave1_mess = Wire.read();
      Serial.print(slave1_mess);
    }
    Serial.println();
    delay(500);
    Wire.requestFrom(2,16);
    while (Wire.available())
    {
      char slave2_mess=Wire.read();
      Serial.print(slave2_mess);
    }
    Serial.println();
    while (true)
    {
      delay (5000);
    }
  }
}
