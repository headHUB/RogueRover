cmake_minimum_required(VERSION 3.9)
project(Basic_RX)

set(CMAKE_CXX_STANDARD 11)

add_executable(Basic_RX
        NRFLite/examples/Basic_RX/Basic_RX.ino
        NRFLite/examples/Basic_RX_2Pin/Basic_RX_2Pin.ino
        NRFLite/examples/Basic_TX/Basic_TX.ino
        NRFLite/examples/Basic_TX_2Pin/Basic_TX_2Pin.ino
        NRFLite/examples/Basic_TX_ATtiny84/Basic_TX_ATtiny84.ino
        NRFLite/examples/Basic_TX_ATtiny85/Basic_TX_ATtiny85.ino
        NRFLite/examples/Dynamic_RX/Dynamic_RX.ino
        NRFLite/examples/Dynamic_TX/Dynamic_TX.ino
        NRFLite/examples/IRQ_ACK_RX/IRQ_ACK_RX.ino
        NRFLite/examples/IRQ_ACK_TX/IRQ_ACK_TX.ino
        NRFLite/examples/IRQ_RX/IRQ_RX.ino
        NRFLite/examples/IRQ_TX/IRQ_TX.ino
        NRFLite/examples/RX_Tests/RX_Tests.ino
        NRFLite/examples/RX_Tests/Serial_Output_RX_Separate_CE_CSN.txt
        NRFLite/examples/RX_Tests/Serial_Output_RX_Shared_CE_CSN.txt
        NRFLite/examples/Sensor_RX_2Pin/Sensor_RX_2Pin.ino
        NRFLite/examples/Sensor_TX_ATtiny85_2Pin/Sensor_TX_ATtiny85_2Pin.ino
        NRFLite/examples/TX_Tests/Serial_Output_TX_Separate_CE_CSN.txt
        NRFLite/examples/TX_Tests/Serial_Output_TX_Shared_CE_CSN.txt
        NRFLite/examples/TX_Tests/TX_Tests.ino
        NRFLite/extras/ATmega328_pinout_small.jpg
        NRFLite/extras/ATtiny84_pinout_small.png
        NRFLite/extras/ATtiny85_pinout_small.png
        NRFLite/extras/ATtiny_pinout.png
        NRFLite/extras/nRF24L01_pinout_small.jpg
        NRFLite/extras/Two_pin_schematic.png
        NRFLite/src/nRF24L01.h
        NRFLite/src/NRFLite.cpp
        NRFLite/src/NRFLite.h
        NRFLite/library.properties
        NRFLite/LICENSE.md
        NRFLite/README.md
        Basic_RX.hex
        Basic_RX.cpp
        nRF24L01.h
        NRFLite.cpp
        NRFLite.h)
