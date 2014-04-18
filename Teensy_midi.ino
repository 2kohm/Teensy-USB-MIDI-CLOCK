// Teensy2.0 MIDI CLOCK INTERFACE //
//            by 2kohm            //
//        18. Aprill 2014         //
//     http://stromakustik.de     //
//                                //
//    Teensyduino MIDI Beat Clock //
//       by Sebastian Tomczak     //
//         29 August 2011         //
//   http://www.goo.gl/Xh2skw     //



// Bytes
byte counter; 
byte CLOCK = 1; 
byte START = 1; 
byte CONTINUE = 5; 
byte STOP = 20;
byte divider;

// Var
int pot1 = 0;
int clockdivider = clockdivider; // MIDI Clock Divider

// Setup
  void setup() 
{ 
  Serial.begin(31250); 
  pinMode(10, OUTPUT);
  pinMode(1, INPUT); 
  pinMode(11, OUTPUT); 

  digitalWrite(10, HIGH);
  
// MIDI RealTime System
  usbMIDI.setHandleRealTimeSystem(RealTimeSystem); 
} 
  void loop() 
{
  
// Midi Clock Divider
  divider = (analogRead(0)/250); // Read Pot 1 (scale 0 - 4)
  
  if(divider == 0) { clockdivider = 24;} // 1/4
  if(divider == 1) { clockdivider = 12;} // 1/8
  if(divider == 2) { clockdivider = 6;}  // 1/16
  if(divider == 3) { clockdivider = 3;}  // 1/32
  if(divider == 4) { clockdivider = 2;}  // 1/64
  Serial.println(divider); // Display the Pot value ( 0 - 4)
  
  usbMIDI.read();
}

  void RealTimeSystem(byte realtimebyte) 
{ 
  if(realtimebyte == 248) 
{ 
  counter++; 
  if(counter == clockdivider) 
{ 
  counter = 0; 
  digitalWrite(10, HIGH); 
} 
  if(counter == 1) 
{ 
  digitalWrite(10, LOW);  
}

} 
  if(realtimebyte == START || realtimebyte == CONTINUE) 
{ 
  counter = 0; 
  digitalWrite(10, HIGH) ; 
} 
  if(realtimebyte == STOP) 
{ 
  digitalWrite(10, LOW); 
} 

}
