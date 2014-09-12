/* Sample Project 2
Updated date: 091214
Description:
This is the sample project connecting 2 Arduino UNO boards via I2C bus
Feature:
Master will count from 0 to 100 then send to even number to slave1
and odd number to slave2
*/
//Slave1_code
#include <Wire.h>

void setup()
{
  Wire.begin(1); //join i2c bus as slave with address #1
  Serial.begin(9600);
  Wire.onReceive(ReceiveGo);
  Wire.onRequest(RequestGo);
}

int flag = 0;

void loop()
{
  delay(10);
}

void ReceiveGo(int i)
{
  if (flag == 0)
  {
    while (Wire.available() > 1)
    {
      char string = Wire.read(); // read the string data received (1st send)
      Serial.print(string); // print it to terminal port
    }
    int x = Wire.read(); //read the received number x (2nd send)
    Serial.println(x);
    if (x >= 100) flag++;
  }
  else
  {
    while (Wire.available()/* > 1 */)
    {
      char phew = Wire.read();
      Serial.print(phew);
    }
    Serial.print("\n");
  }
}

void RequestGo()
{
  Wire.write("Slave1 finishes!");
}
