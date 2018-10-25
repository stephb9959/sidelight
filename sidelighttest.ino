// This #include statement was automatically added by the Particle IDE.
#include "SideLight.h"

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_MCP23017.h>

SideLightManager            SL ;

OutputPin   OutputTest( SL , X1 , "green_led" , false , false , true ) ,
            BlueLED(  SL , D7 , "BlueLED" , false , false , true);
            
InputPin    InputTest( SL , Y1 , "input_test" , INPUT , true );

void setup()
{
    uint8_t c;

    Serial.begin(115200);

    //  This initializes every single programmed pin
    Serial.println("----------  STARTING  --------------");
    
    SL.begin();
     
    Serial.println("Snooping I2C");
    
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
    Serial.println("LED ON");
    BlueLED.set();
    
    OutputTest.set();
    Serial.printf("OUTPUT=%d INPUT=%d\r\n",OutputTest.get(),InputTest.get());
    
    OutputTest.unset();
    Serial.printf("OUTPUT=%d INPUT=%d\r\n",OutputTest.get(),InputTest.get());
    
    
    delay(1000);
    Serial.println("LED OFF");
    BlueLED.unset();
}

