#include <SoftwareSerial.h>

SoftwareSerial BTserial(0, 1); // Port numbers in your arduino: RX | TX

void setup() 
{
    Serial.begin(9600);
 
    // HC-06 default serial speed is 9600
    BTserial.begin(9600);
    
    BTserial.write("AT+NAMEphysioBotBT");
    BTserial.write("AT+VERSION");

    Serial.println("AT+VERSION");
    Serial.println("Enter AT commands:");

    Serial.println(BTserial.available());
}

void loop()
{
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
    }
}
