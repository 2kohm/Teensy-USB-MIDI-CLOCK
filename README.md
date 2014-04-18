Teensy-USB-MIDI-CLOCK-SEQUENER-INTERFACE
========================================

USB MIDI CLOCK SYNC FOR ANALOG CV/GATE SEQUENCERS!

Original Source! http://www.goo.gl/Xh2skw

// Teensyduino MIDI Beat Clock Example 
// by Sebastian Tomczak 
// 29 August 2011 


How To Deal With Real Time MIDI Beat Clock Data in Teensyduino

The Teensy is an affordable, compact and easy-to-use microcontroller development board. Part of the attraction of Teensy is theTeensyduino add-on for the Arduino software environment, which adds support for the Teensy board. One of the strengths of Teensy and Teensyduino is the ability to have the Teensy board appear as a USB HID MIDI device. This allows for the creation of interfaces and projects that register as native USB MIDI devices on the major operating systems. 

Currently, the usbMIDI.read() function in Teensyduino reads a range of standard MIDI commands (sent from the computer host to the Teensy board), such as note on, note off, continuous controllers etc. However, there is no support for detecting and dealing with MIDI sync signals (also known as MIDI beat clock and real time system bytes). 

I've edited the Teensyduino package to include a function made for dealing with real time system bytes. Thanks to Paul Stoffregen for his fantastic work with the Teensy board, and for his help in pushing me in the right direction with this. My edited files can be found here:http://milkcrate.com.au/_other/downloads/other/TeensyduinoRealTimeClockUpdate_20110829/ 

To add the functions to the Teensyduino code, simply right-click on the Arduino application and select "Show Package Contents". Copy and replace the files from the link above to Contents > Resources > Java > hardware > teensy > cores > usb_midi. 

This will add a new handle (setHandleRealTimeSystem()) and a new function (RealTimeSystem()) that can be used in conjunction with usbMIDI.read() to receive MIDI beat clock data. To use the new code, set up a MIDI input sketch as you would normally with Teensyduino. Then: 

1) add: 
usbMIDI.setHandleRealTimeSystem(RealTimeSystem); 
to void setup() 

2) add a new function to the sketch: 
void RealTimeSystem(byte realtimebyte) { 
} 

In the new function in (2) above, the byte realtimebyte is used for the MIDI beat clock data. The following bytes indicate which MIDI beat clock bytes have been received. 

clock tick byte (at 24 pulses per quarter note) = 248; 
start byte = 250; 
continue byte = 251; 
stop byte = 252; 

Below is a working example, with code and a demo video. The LED that is part of the Teensy board lights up for every quarter note of sync data that is received via the USB cable. 





// Teensyduino MIDI Beat Clock Example 
// by Sebastian Tomczak 
// 29 August 2011 

byte counter; 
byte CLOCK = 248; 
byte START = 250; 
byte CONTINUE = 251; 
byte STOP = 252; 

void setup() { 
Serial.begin(31250); 
pinMode(11, OUTPUT); 
digitalWrite(11, HIGH); 
usbMIDI.setHandleRealTimeSystem(RealTimeSystem); 
} 

void loop() { 
usbMIDI.read(); 

} 

void RealTimeSystem(byte realtimebyte) { 
if(realtimebyte == 248) { 
counter++; 
if(counter == 24) { 
counter = 0; 
digitalWrite(11, HIGH); 
} 

if(counter == 12) { 
digitalWrite(11, LOW); 
} 
} 

if(realtimebyte == START || realtimebyte == CONTINUE) { 
counter = 0; 
digitalWrite(11, HIGH); 
} 

if(realtimebyte == STOP) { 
digitalWrite(11, LOW); 
} 

}

