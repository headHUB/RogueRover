/*

Demonstrates simple RX and TX operation.
Please read the notes in NRFLite.h for a description of all library features.

Radio -> Arduino

CE    -> 9
CSN   -> 10 (Hardware SPI SS)
MOSI  -> 11 (Hardware SPI MOSI)
MISO  -> 12 (Hardware SPI MISO)
SCK   -> 13 (Hardware SPI SCK)
IRQ   -> No connection in this example
VCC   -> No more than 3.6 volts
GND   -> GND

*/

#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 1;             // Our radio's id.
const static uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio we will transmit to.
const static uint8_t PIN_RADIO_CE = 8;
const static uint8_t PIN_RADIO_CSN = 7;

struct RadioPacket // Any packet up to 32 bytes can be sent.
{
      uint8_t FromRadioId;
    uint32_t x1Axis;
    uint32_t y1Axis;
    uint32_t x2Axis;
    uint32_t y2Axis;
     uint8_t  buttonA;
         uint8_t  buttonB;
     uint8_t  buttonC;
     uint8_t  buttonD;
};

NRFLite _radio;
RadioPacket _radioData;

void setup()
{
    Serial.begin(115200);
        _radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE1MBPS, 75);
    if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
    {
        Serial.println("Cannot communicate with radio");
        while (1) {} // Wait here forever.
    }
    
    _radioData.FromRadioId = RADIO_ID;

}

void loop()
{
    _radioData.x1Axis = analogRead(A0);
_radioData.y1Axis = analogRead(A1);
_radioData.x2Axis = analogRead(A8);
 _radioData.y2Axis = analogRead(A15);
 _radioData.buttonA= digitalRead(5);
_radioData.buttonB = digitalRead(6);
 _radioData.buttonC = digitalRead(4);
_radioData.buttonD = digitalRead(3);
    
    String msg = "Radio ";
        msg += _radioData.FromRadioId;
        msg += ", ";
        msg += _radioData.x1Axis;
        msg += " x1Axis, ";
        msg += _radioData.y1Axis;
        msg += " y1Axis";
        msg += _radioData.x2Axis;
        msg += " x2Axis";
   msg +=  _radioData.y2Axis;
   msg += " y2Axis";
   msg +=  _radioData.buttonA;
   msg += " buttonA";
   msg +=      _radioData.buttonB;
   msg += " buttonB";
   msg +=  _radioData.buttonC;
   msg += " buttonC";
   msg +=  _radioData.buttonD;
   msg += " buttonD";

    if (_radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData))) // Note how '&' must be placed in front of the variable name.
    {
        Serial.println("...Success");
    }
    else
    {
        Serial.println("...Failed");
        
    }

    delay(50);
     Serial.println(msg);
    /*
    By default, 'send' transmits data and waits for an acknowledgement.
    You can also send without requesting an acknowledgement as shown below.
    _radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData), NRFLite::NO_ACK)
    _radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData), NRFLite::REQUIRE_ACK) // THE DEFAULT
    */
}
