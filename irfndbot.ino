#include <IRremote.h>

int IRpin = 11;
int di = 0;
int sp = 0;
int a1 = 44;
int a2 = 47;
int b1 = 48;
int b2 = 51;
int ena = 2;
int enb = 4;
IRrecv irrecv(IRpin);
decode_results results;
byte seven_seg_digits[24][8] = { { 1,1,1,1,1,1,0,0 },  // = 0
                                 { 0,1,1,0,0,0,0,0 },  // = 1
                                 { 1,1,0,1,1,0,1,0 },  // = 2
                                 { 1,1,1,1,0,0,1,0 },  // = 3
                                 { 0,1,1,0,0,1,1,0 },  // = 4
                                 { 1,0,1,1,0,1,1,0 },  // = 5
                                 { 1,0,1,1,1,1,1,0 },  // = 6
                                 { 1,1,1,0,0,0,0,0 },  // = 7
                                 { 1,1,1,1,1,1,1,0 },  // = 8
                                 { 1,1,1,0,0,1,1,0 },  // = 9
                                 { 0,0,0,0,0,0,0,1 },   // = . 
                                 { 1,1,1,0,1,1,1,0 },  // a
                                 { 0,0,1,1,1,1,1,0 }, //b
                                 { 1,0,0,1,1,1,0,0 }, // c
                                 { 1,0,0,1,1,1,1,0 }, // e
                                 { 1,0,0,0,1,1,1,0 }, // f
                                 { 0,1,1,0,1,1,1,0 }, // h
                                 { 0,1,1,1,1,0,0,0 }, // j
                                 { 0,0,0,1,1,1,0,0 }, //l
                                 { 1,1,1,1,1,1,0,0 }, //o
                                 { 1,1,0,0,1,1,1,0 }, //p
                                 { 1,0,1,1,0,1,1,0 }, //s
                                 { 0,1,1,1,1,1,0,0 }, //u
                                 { 0,1,1,0,0,1,1,0 }  //y
                                };

int motion()
{
  switch(sp)
  {
    case 0: analogWrite(ena, 0);
            analogWrite(enb, 0);
            break;
    case 1: analogWrite(ena, 64);
            analogWrite(enb, 64);
            break;
    case 2: analogWrite(ena, 127);
            analogWrite(enb, 127);
            break;
    case 3: analogWrite(ena, 191);
            analogWrite(enb, 191);
            break;
    case 4: analogWrite(ena, 255);
            analogWrite(enb, 255);
            break;
  }
}
void setup() {                
  pinMode(22, OUTPUT);   
  pinMode(25, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

}

    
void sevenSegWrite(byte digit) {
  byte pin = 22;
  for (byte segCount = 0; segCount < 8; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    pin=pin+3;
  }
}

void loop() {
   //sevenSegWrite(count);
   if (irrecv.decode(&results)) 
    {
      Serial.println(results.value, DEC); // Print the Serial 'results.value'
      if (results.value == 615372988 || results.value == 905935834)
      {
        
        di = 15;
        sp = 0;
        sevenSegWrite(di);
        delay(500);
      }
      else if (results.value == 248745739 || results.value == 2610959513)
      {
        
        di = 12;
        sp = 0;
        sevenSegWrite(di);
        delay(500);
      }
      else if (results.value == 182820736 || results.value == 846147286)
      {
        sevenSegWrite(0);
        di = 0;
        sp = 0;
        delay(500);
      }
      else if (results.value == 886442354 || results.value == 697869664)
      {
        
        if (sp <= 3)
        {
          sp++;
          sevenSegWrite(sp);
          delay(500);
        }
      }
      else if (results.value == 903219973 || results.value == 714647283)
      {
        
        if (sp >= 1)
        {
          sp--;
          sevenSegWrite(sp);
          delay(500);
        }
      }
      irrecv.resume();   // Receive the next value
    }
    switch(di)
    {
      case 0: Serial.print("  Break");
              analogWrite(ena, 0);
              analogWrite(enb, 0);
              digitalWrite(a1, LOW);
              digitalWrite(a2, LOW);
              digitalWrite(b1, LOW);
              digitalWrite(b2, LOW);
              break;
      case 12: Serial.print("  Backward");
               digitalWrite(a1, LOW);
               digitalWrite(a2, HIGH);
               digitalWrite(b1, HIGH);
               digitalWrite(b2, LOW);
               motion();
               break;
      case 15: Serial.print("  Forward");
               digitalWrite(a1, HIGH);
               digitalWrite(a2, LOW);
               digitalWrite(b1, LOW);
               digitalWrite(b2, HIGH);
               motion();
               break;
    }
    
   
  
 // writeDot(1);
  //delay(4000);
  
 //writeDot(0);
}
