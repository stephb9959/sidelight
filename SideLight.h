// This #include statement was automatically added by the Particle IDE.
#pragma once

#include <Adafruit_MCP23017.h>
#include <functional>
#include <set>
#include <map>

#define bit(b) (1UL << (b))

extern Adafruit_MCP23017    _mcp_X , 
                            _mcp_Y , 
                            _mcp_Z ;

class   SideLightManager;
extern  SideLightManager            SideLight;

typedef std::pair< int ,  Adafruit_MCP23017 *> SideLightPinDef;

constexpr SideLightPinDef X1 = { 0 , &_mcp_X };
constexpr SideLightPinDef X2 = { 1 , &_mcp_X };
constexpr SideLightPinDef X3 = { 2 , &_mcp_X };
constexpr SideLightPinDef X4 = { 3 , &_mcp_X };
constexpr SideLightPinDef X5 = { 4 , &_mcp_X };
constexpr SideLightPinDef X6 = { 5 , &_mcp_X };
constexpr SideLightPinDef X7 = { 6 , &_mcp_X };
constexpr SideLightPinDef X8 = { 7 , &_mcp_X };
constexpr SideLightPinDef X9 = { 8 , &_mcp_X };
constexpr SideLightPinDef X10 = { 9 , &_mcp_X };
constexpr SideLightPinDef X11 = { 10 , &_mcp_X };
constexpr SideLightPinDef X12 = { 11 , &_mcp_X };
constexpr SideLightPinDef X13 = { 12 , &_mcp_X };
constexpr SideLightPinDef X14 = { 13 , &_mcp_X };
constexpr SideLightPinDef X15 = { 14 , &_mcp_X };
constexpr SideLightPinDef X16 = { 15 , &_mcp_X };

constexpr SideLightPinDef Y1 = { 0 , &_mcp_Y };
constexpr SideLightPinDef Y2 = { 1 , &_mcp_Y };
constexpr SideLightPinDef Y3 = { 2 , &_mcp_Y };
constexpr SideLightPinDef Y4 = { 3 , &_mcp_Y };
constexpr SideLightPinDef Y5 = { 4 , &_mcp_Y };
constexpr SideLightPinDef Y6 = { 5 , &_mcp_Y };
constexpr SideLightPinDef Y7 = { 6 , &_mcp_Y };
constexpr SideLightPinDef Y8 = { 7 , &_mcp_Y };
constexpr SideLightPinDef Y9 = { 8 , &_mcp_Y };
constexpr SideLightPinDef Y10 = { 9 , &_mcp_Y };
constexpr SideLightPinDef Y11 = { 10 , &_mcp_Y };
constexpr SideLightPinDef Y12 = { 11 , &_mcp_Y };
constexpr SideLightPinDef Y13 = { 12 , &_mcp_Y };
constexpr SideLightPinDef Y14 = { 13 , &_mcp_Y };
constexpr SideLightPinDef Y15 = { 14 , &_mcp_Y };
constexpr SideLightPinDef Y16 = { 15 , &_mcp_Y };

constexpr SideLightPinDef Z1 = { 0 , &_mcp_Z };
constexpr SideLightPinDef Z2 = { 1 , &_mcp_Z };
constexpr SideLightPinDef Z3 = { 2 , &_mcp_Z };
constexpr SideLightPinDef Z4 = { 3 , &_mcp_Z };
constexpr SideLightPinDef Z5 = { 4 , &_mcp_Z };
constexpr SideLightPinDef Z6 = { 5 , &_mcp_Z };
constexpr SideLightPinDef Z7 = { 6 , &_mcp_Z };
constexpr SideLightPinDef Z8 = { 7 , &_mcp_Z };
constexpr SideLightPinDef Z9 = { 8 , &_mcp_Z };
constexpr SideLightPinDef Z10 = { 9 , &_mcp_Z };
constexpr SideLightPinDef Z11 = { 10 , &_mcp_Z };
constexpr SideLightPinDef Z12 = { 11 , &_mcp_Z };
constexpr SideLightPinDef Z13 = { 12 , &_mcp_Z };
constexpr SideLightPinDef Z14 = { 13 , &_mcp_Z };
constexpr SideLightPinDef Z15 = { 14 , &_mcp_Z };
constexpr SideLightPinDef Z16 = { 15 , &_mcp_Z };

template < uint8_t pin > constexpr uint8_t CheckPin()
{
    static_assert( (pin!=D0 && pin!=D1) , "Invalid PIN" );
    
    return pin;
}

class SideLightPinBasic
{
    public:
        SideLightPinBasic( uint8_t pin , const char * name );
        ~SideLightPinBasic();
        const uint8_t  pin() { return _pin; };
        const String & name() { return _name; };
        
    private:
        uint8_t     _pin;
        String      _name;
};

class OutputPin : public SideLightPinBasic
{
    public:
        OutputPin( uint8_t pin , const char * name , bool initial_value = false , bool reverse = false , bool publish = false );
        OutputPin( const SideLightPinDef pin , const char * name , bool initial_value = false , bool reverse = false , bool publish = false );
        ~OutputPin();
        
        static void pinModeX( uint8_t a , uint8_t b ) ;
//        void pinModeX( uint8_t a , uint8_t b ) ;
        
        void begin();
        void set( bool value = true );
        void unset();
        bool get() { return _value ; } ;

    private:
        Adafruit_MCP23017       * _mcp ;
        uint8_t                 _real_pin ;
        bool                    _value ;
        bool                    _reverse ;
        bool                    _initial_value ;
        bool                    _publish;

        std::function<void(uint8_t , uint8_t)>      __pinMode ;
        std::function<void(uint8_t , uint8_t)>      __digitalWrite ;
        
        std::function<void()>   * set_pin_mode;
};

class InputPin : public SideLightPinBasic
{
    public:
        InputPin( uint8_t pin , const char * name , bool publish = false );
        ~InputPin();
        
        static void pinModeX( uint8_t a , uint8_t b ) ;
        
        void begin() {};
        void set( bool value = true );
        void unset();
        bool get() { return _value ; } ;

    private:
        Adafruit_MCP23017       * _mcp ;
        uint8_t                 _real_pin ;
        bool                    _value ;
        bool                    _reverse ;
        bool                    _initial_value ;
        bool                    _publish;
        
        std::function<void(uint8_t , uint8_t)>      __pinMode ;
        std::function<void(uint8_t , uint8_t)>      __digitalWrite ;
};

class SideLightManager
{
    public:
        SideLightManager();
        ~SideLightManager();
        
        void AddPin( OutputPin * pin );
        void RemovePin( OutputPin * pin );
        void AddPin( InputPin * pin );
        void RemovePin( InputPin * pin );
        
        void begin();
        
        void AllOff();
        void AllOn();

    private:
        std::set< OutputPin * >     _outputs;
        std::set< InputPin * >      _inputs;
};


