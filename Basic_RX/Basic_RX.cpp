

/*

 Demonstrates simple RX and TX operation.
 Please read the notes in NRFLite.h for a description of all library features.

 Radio -> Arduino

 CE    -> 7
 CSN   -> 8
 MOSI  -> ISCP MOSI
 MISO  -> ISCP MISO
 SCK   -> ISCP SCK
 IRQ   -> No connection
 VCC   -> No more than 3.6 volts
 GND   -> GND

 */
#include <VarSpeedServo>
#include <SPI.h>
#include <NRFLite.h>

VarSpeedServo pan;
VarSpeedServo tilt;
VarSpeedServo dir;
const static uint8_t RADIO_ID = 0;       // Our radio's id.  The transmitter will send to this id.
const static uint8_t PINradio_CE = 7;
const static uint8_t PINradio_CSN = 8;
const int ptSpeed = 75;
const int dirServSpeed = 255;
#define E1 2  // Enable Pin for motor 1
#define E2 6 // Enable Pin for motor 2

#define I1 2  // Control pin 1 for motor 1
#define I2 3  // Control pin 2 for motor 1
#define I3 4  // Control pin 1 for motor 2
#define I4 5  // Control pin 2 for motor 2
#define lights 24
#define laser 25
boolean flag = true;

struct RadioPacket // Any packet up to 32 bytes can be sent.
{
    uint8_t FromRadioId;
    uint32_t x1Axis;
    uint32_t y1Axis;
    uint32_t x2Axis;
    uint32_t y2Axis;
    uint8_t buttonA;
    uint8_t buttonB;
    uint8_t buttonC;
    uint8_t buttonD;


};

NRFLite radio;
RadioPacket radioData;

void setup() {
    //Initialize Serial
    Serial.begin(115200);

    //Initialize Radio
    radio.init(RADIO_ID, PINradio_CE, PINradio_CSN, NRFLite::BITRATE1MBPS, 75);
    if (!radio.init(RADIO_ID, PINradio_CE, PINradio_CSN)) {
        Serial.println("Cannot communicate with radio");
        while (1) {
        } // Wait here forever.
    }

    //Initialize Servos.

    pan.attach(8);
    tilt.attach(9);
    dir.attach(10);

    pan.write(90, ptSpeed, true);
    tilt.write(60, ptSpeed, true);
    dir.write(90, dirServSpeed, true);

    //Initialize motor pins (L293 module);
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);

    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);
    
    // initialize flip flop buttons
    pinMode(lights,OUTPUT);
    pinMode(laser,OUTPUT);
}

void loop() {
    while (radio.hasData()) {
        radio.readData(&radioData); // Note how '&' must be placed in front of the variable name.
        moveRover(radioData.y1Axis, radioData.x1Axis);
        panTilt(radioData.x2Axis, radioData.y2Axis);
        lightButton();
    }
    delay(10);
    if (radio.buttonB == LOW)
    {
    delay(5);
    flipflop(lights, radio.buttonB);
    }
    if (radio.buttonB == LOW)
    {
    delay(5);
 flipflop(laser, radio.buttonC);
    }
   

/*      Debug Radio Connection  
        
         String msg = "Radio ";
        msg += radioData.FromRadioId;
        msg += ", ";
        msg += radioData.x1Axis;
        msg += " x1Axis, ";
        msg += radioData.y1Axis;
        msg += " y1Axis";
        msg += radioData.x2Axis;
        msg += " x2Axis";
        msg += radioData.y2Axis;
        msg += " y2Axis";
        msg += radioData.buttonA;
        msg += " buttonA";
        msg += radioData.buttonB;
        msg += " buttonB";
        msg += radioData.buttonC;
        msg += " buttonC";
        msg += radioData.buttonD;
        msg += " buttonD";
        Serial.println(msg);
*/


}

void moveRover(uint32_t direct, uint32_t spd) {
    uint32_t dirPos = map(direct, 0, 1023, 15, 165);
    dir.write(dirPos);

    uint32_t speed = map(spd, 0, 1023, 0, 255);
    if (spd <= 450) {
        backward(450 - speed);
    }
    if (spd >= 550) {
        forward(speed);
    } else {
        stop();
    }
}

void forward(uint32_t spdValue) {
    analogWrite(E1, spdValue); // Run in half speed
    analogWrite(E2, spdValue); // Run in full speed

    digitalWrite(I1, HIGH);
    digitalWrite(I2, HIGH);
    digitalWrite(I3, LOW);
    digitalWrite(I4, HIGH);
}

void backward(uint32_t spdValue) {
    analogWrite(E1, spdValue);  // Run in full speed
    analogWrite(E2, spdValue);  // Run in half speed

    digitalWrite(I1, LOW);
    digitalWrite(I2, HIGH);
    digitalWrite(I3, HIGH);
    digitalWrite(I4, LOW);
}

void stop() {
    digitalWrite(I1, LOW);
    digitalWrite(I2, LOW);
    digitalWrite(I3, LOW);
    digitalWrite(I4, LOW);
}

void panTilt(uint32_t panTiltVal, uint32_t tiltPanVal) {
    uint32_t panTiltVal2 = 900 - panTiltVal;
    uint32_t panPos = map(panTiltVal2, 150, 900, 0, 180);
    uint32_t tiltPos = map(tiltPanVal, 150, 900, 15, 120);
    pan.write(panPos, ptSpeed);
    tilt.write(tiltPos, ptSpeed);

}

void flipflop(int action, uint32_t signal)
{   
bool flag = true;
    flag = !flag;Serial.print("flag =   " );   Serial.println(flag);
  if (flag == HIGH){
    digitalWrite(action ,HIGH); }
  if (flag == LOW) {
    digitalWrite(action,LOW); 
    }
  while(signal == LOW); 
  delay(50);
  }
}


