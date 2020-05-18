#include <SoftwareSerial.h>
#include <stdio.h>

// Port numbers in your arduino: RX | TX
SoftwareSerial BTserial(0, 1);
String cmd = "";
float sensor_val = 0;
bool sendData = false;
char buffer[200];  //buffer used to format a line (+1 is for trailing 0)
int count;

void setup() 
{
    //Serial.begin(19200);
    
    // HC-06 default serial speed is 9600
    BTserial.begin(9600);
    
    //BTserial.write("AT+NAMEphysioBotBT");
    //BTserial.write("AT+VERSION");
    
    sendData = true;
    count = 0;
}

float getValueChannelOne() {
  // Simulate sensor measurement
  sensor_val = (float)random(10); // random number between 0 and 255
    
  return sensor_val;
}

float getValueChannelTwo() {
  // Simulate sensor measurement
  sensor_val = (float)random(10); // random number between 0 and 255
  
  return sensor_val;
}

void loop()
{
/*
  byte data;
  byte receive;
  
    // Keep reading from HC-06 and send to Arduino Serial Monitor
    if (BTserial.available() > 0)
    {
        data = BTserial.read();
        Serial.println(data);
        Serial.write(data);
    }
 
    // Keep reading from Arduino Serial Monitor and send to HC-06
    if (Serial.available())
    {
        receive = Serial.read();
        BTserial.write(receive);
        BTserial.print("abcd");
        BTserial.write(1);
    }
  */
  //Read data from BTserial
  /*
   while(BTserial.available() > 0) {
     cmd += (char)BTserial.read();
     delay(100);
   }
   */
   /*
   while(Serial.available()) {
       cmd += char(Serial.read());
   }
   
   //Select function with cmd
   if(cmd != "") {
      Serial.println(cmd);
     // We expect ON or OFF from bluetooth
     if(cmd == "ON" || cmd == "1") {
         Serial.println("Function is on");
         sendData = true;
     } else if(cmd == "OFF" || cmd == "0") {
         Serial.println("Function is off");
         sendData = false;
     } else {
         Serial.println("Function is OFF by default");
         sendData = false;
     }
     BTserial.print(cmd);
     cmd = ""; //reset cmd
   }
   Serial.println(sendData);
   */
  
  while(sendData) {
    count++;

    float chOne = getValueChannelOne();
    int chOneVal = (int) chOne;   // compute the integer part of the float
    int chOneFra = (int) ((chOne - (float)chOneVal) * 1000);   // compute 3 decimal places (and convert it to int)
    
    float chTwo = getValueChannelTwo();
    int chTwoVal = (int) chTwo;   // compute the integer part of the float
    int chTwoFra = (int) ((chTwo - (float)chTwoVal) * 1000);   // compute 3 decimal places (and convert it to int)
    
    sprintf(buffer,"[%d, %d.%d, %d.%d]", count, chOneVal, chOneFra, chTwoVal, chTwoFra);
    BTserial.println(buffer);

    delay(500);
  }
  delay(200);
}
