// This #include statement was automatically added by the Particle IDE.
#include "SideLight.h"

Adafruit_MCP23017           _mcp_X , 
                            _mcp_Y , 
                            _mcp_Z ;

// SideLightManager            SideLight ;

SideLightPinBasic::SideLightPinBasic( uint8_t pin , const char * name )
            : _pin( pin ) , _name( name )
{
    
}

SideLightPinBasic::~SideLightPinBasic()
{
    
}
        
OutputPin::OutputPin( SideLightManager & SL , const SideLightPinDef pin, const char * name , bool initial_value , bool reverse , bool publish )
    :
        SideLightPinBasic( 0 , name ) , 
        _sl(SL),
        _mcp(pin.second),
        _real_pin(pin.first),
        _value(initial_value),
        _reverse(reverse) ,
        _initial_value(initial_value),
        _publish(publish)
{
    do_pinMode = [this]() { _mcp->pinMode( _real_pin , OUTPUT ); } ;
    do_digitalWrite = [this](bool Value) { _mcp->digitalWrite( _real_pin , Value ); };

    _sl.AddPin( this );
} 

OutputPin::OutputPin( SideLightManager & SL ,uint8_t pin_name , const char * name , bool initial_value , bool reverse , bool publish )
    :   
        SideLightPinBasic( pin_name , name ) , 
        _sl(SL),
        _mcp(nullptr),
        _real_pin(pin_name),
        _value(initial_value),
        _reverse(reverse) ,
        _initial_value(initial_value),
        _publish(publish)
{
    do_pinMode = [this]() { pinMode( _real_pin , OUTPUT ); } ;
    do_digitalWrite = [this](bool Value) { /* Serial.printf("OUTPUT: Pin=%d Value=%d\r\n", _real_pin , Value ); */ digitalWrite( _real_pin , Value ); };

    _sl.AddPin( this );
}
        
OutputPin::~OutputPin()
{
    _sl.RemovePin( this );
}

void OutputPin::begin()
{
    do_pinMode();
    do_digitalWrite( _value = _reverse ? !_initial_value : _initial_value );

    if(_publish)
    {
        Particle.variable( this->name() , _value );
    }
}

void OutputPin::set( bool value )
{
    do_digitalWrite( _value = _reverse ? !value : value );
}

void OutputPin::unset()
{
    set(false);
}
  
//
//
//

InputPin::InputPin( SideLightManager & SL , const SideLightPinDef pin , const char * name , PinMode mode , bool publish )
    :   
        SideLightPinBasic( 0 , name ) , 
        _sl(SL),
        _mcp(pin.second),
        _real_pin(pin.first),
        _mode(mode),
        _publish(publish)
{
    do_pinMode = [this]() 
            { 
                _mcp->pinMode( _real_pin , INPUT );
                _mcp->pullUp( _real_pin , _mode == INPUT_PULLUP ? 1 : 0 );
            } ;
    do_digitalRead = [this] () -> int { _value = _mcp->digitalRead( _real_pin ); /* Serial.printf("INPUT pin=%d value=%d\r\n" , _real_pin , _value ); */ return _value; };

    _sl.AddPin( this );
}



InputPin::InputPin( SideLightManager & SL , uint8_t pin_name , const char * name , PinMode mode, bool publish )
    :   
        SideLightPinBasic( pin_name , name ) , 
        _sl(SL),
        _mcp(nullptr),
        _real_pin(pin_name),
        _mode(mode),
        _publish(publish)
{
    do_pinMode = [this]() { pinMode( _real_pin , _mode ); } ;
    do_digitalRead = [this]  () -> int { _value = digitalRead( _real_pin ); /* Serial.printf("INPUT pin=%d value=%d\r\n" , _real_pin , _value ); */ digitalRead( _real_pin ); return _value; };

    _sl.AddPin( this );
}

InputPin::~InputPin()
{
    _sl.RemovePin( this );
}

void InputPin::begin() 
{
//    Serial.println("INPUT pins");
    do_pinMode();
    _value = do_digitalRead();

    if(_publish)
    {
        Particle.variable( this->name() , _value );
    }
    
};

int InputPin::get() 
{ 
    return do_digitalRead() ;
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

