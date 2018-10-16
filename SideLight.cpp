// This #include statement was automatically added by the Particle IDE.
#include "SideLight.h"

Adafruit_MCP23017           _mcp_X , 
                            _mcp_Y , 
                            _mcp_Z ;

SideLightManager            SideLight ;

SideLightPinBasic::SideLightPinBasic( uint8_t pin , const char * name )
            : _pin( pin ) , _name( name )
{
    
}

SideLightPinBasic::~SideLightPinBasic()
{
    
}
        
OutputPin::OutputPin( const SideLightPinDef pin, const char * name , bool initial_value , bool reverse , bool publish )
    :   SideLightPinBasic( 0 , name ) , 
        _initial_value(initial_value),
        _reverse(reverse) ,
        _publish(publish)
{
    _real_pin = pin.first ; 
    _mcp = pin.second ;
    
    __pinMode = std::bind(&Adafruit_MCP23017::pinMode,_mcp,std::placeholders::_1,std::placeholders::_2) ;
    __digitalWrite = std::bind(&Adafruit_MCP23017::digitalWrite,_mcp,std::placeholders::_1,std::placeholders::_2) ;

    SideLight.AddPin( this );
}

template<typename T> constexpr bool ValidPin(T pin)
{
    return pin != D0;
}

void pinMode2( uint8_t a , uint8_t b ) 
{ 
    Serial.println("pinMode2");
    pinMode( (uint16_t) a , (PinMode) b ); 
};

OutputPin::OutputPin( uint8_t pin_name , const char * name , bool initial_value , bool reverse , bool publish )
    :   SideLightPinBasic( pin_name , name ) , 
        _initial_value(initial_value),
        _reverse(reverse) ,
        _publish(publish)
{

//   static_assert( ValidPin<uint8_t>(pin_name)  ,"bit position out of range");

    _real_pin = pin_name ;
    __pinMode = pinMode2 ;
    __digitalWrite = digitalWrite ;

    *set_pin_mode = [this]() { Serial.println("Lambda") ; pinMode( _real_pin , OUTPUT ); } ;

    SideLight.AddPin( this );
}
        
OutputPin::~OutputPin()
{
    SideLight.RemovePin( this );
}

void OutputPin::pinModeX( uint8_t a , uint8_t b ) 
{ 
    Serial.println("pinModeX");
    pinMode( (uint16_t) a , (PinMode) b ); 
};

void OutputPin::begin()
{
    // __pinMode( _real_pin , OUTPUT );
    (*set_pin_mode)();
    __digitalWrite( _real_pin , _value = _reverse ? !_initial_value : _initial_value );
    
    if(_publish)
        Particle.variable( this->name() , _value );
}

void OutputPin::set( bool value )
{
    Serial.printf( "PINMODE=%0x" , set_pin_mode );
    Serial.println("__digitalWrite");
    __digitalWrite( _real_pin , _value = _reverse ? !value : value );
}

void OutputPin::unset()
{
    set(false);
}
        

SideLightManager::SideLightManager()
{
    
}

SideLightManager::~SideLightManager()
{
    
}

void SideLightManager::AddPin( OutputPin * pin )
{
    _outputs.insert( pin );
}

void SideLightManager::RemovePin( OutputPin * pin )
{
    _outputs.erase( pin );
}

void SideLightManager::AddPin( InputPin * pin )
{
    _inputs.insert( pin );
}

void SideLightManager::RemovePin( InputPin * pin )
{
    _inputs.erase( pin );
}

void SideLightManager::begin()
{
    Wire.begin();
    
    _mcp_X.begin(0);
    _mcp_Y.begin(1);
    _mcp_Z.begin(2);
    
    for( auto & x : _outputs )
    {
        x->begin();
    }
    
    for( auto & x : _inputs )
    {
        x->begin();
    }
}

void SideLightManager::AllOn()
{
    for( auto & x : _outputs )
    {
        x->set();
    }
}

void SideLightManager::AllOff()
{
    for( auto & x : _outputs )
    {
        x->unset();
    }
}

