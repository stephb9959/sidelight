// This #include statement was automatically added by the Particle IDE.
#include "SideLight.h"

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_MCP23017.h>

OutputPin   // GreenLED( X1 , "green_led" , false , false , true ) ,
            // PinkLED(  CheckPin<D2>() , "pink_led" , false , false , true ) ,
            BlueLED(  D7 , "blue_led" );

void setup()
{
    uint8_t c;

    Serial.begin(115200);

    //  This initializes every single programmed pin
    Serial.println("----------  STARTING  --------------");
    
    SideLight.begin();
    
    delay(5000);
    
    Serial.println("Snooping I@c");
    
    snoop_I2C();
}

void snoop_I2C()
{
    for (uint8_t i = 1; i < 120; i++)
    {
        Wire.beginTransmission (i);
        if (Wire.endTransmission () == 0)
        {
            Serial.print ("Found address: ");
            Serial.println (i, HEX);
        }
    }
}

void loop() 
{
    delay(1000);
    Serial.println("ON");
    BlueLED.set();
    
    delay(1000);
    Serial.println("OFF");
    BlueLED.unset();
}

