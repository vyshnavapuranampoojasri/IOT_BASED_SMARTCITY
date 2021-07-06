#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

#include <Servo.h>

Servo tap_servo;

int sensor_pin = 4; 
int tap_servo_pin =5;//PWM PIN
int val;
const int IR_Sensor1 = 10;
const int IR_Sensor2 = 11;
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module
  pinMode(sensor_pin,INPUT);
  tap_servo.attach(tap_servo_pin);
  pinMode(IR_Sensor1, INPUT);
  pinMode(IR_Sensor2, INPUT);
    
}
void loop()
{
val = digitalRead(sensor_pin);

  if (val==0)
  {
    tap_servo.write(88);
  }
  if (val==1)
  {
    tap_servo.write(180);
  }
 
  if (digitalRead(IR_Sensor1) == 0)
  {
    SendMessage1();
  }
 
  if (digitalRead(IR_Sensor2) == 0)
  {
    SendMessage2();
  }

}

void SendMessage1()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919346524441\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("DUSTBIN FILLED at SRIT! please take the action IMMEDIATELY!!!");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  
  while(1) 
  {
    if (digitalRead(IR_Sensor1) == 1)  
    {
      return digitalRead(IR_Sensor1);
    }
  }
}
void SendMessage2()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919346524441\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("DUSTBIN FILLED at SRIT! please clean the dustbin!!!");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);

  while(1)
  {
    if (digitalRead(IR_Sensor1) == 1) 
    {
      return digitalRead(IR_Sensor2);
    }
  }
}
