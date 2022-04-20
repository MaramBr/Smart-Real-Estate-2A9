#include <Keypad.h>
#include <Servo.h>

Servo servo_1;

const byte ROWS = 4; 
const byte COLS = 3; 

int servo_pin=10;

int pos=180;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

String mot;
char data='0';

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(115200);
  mot="";
  servo_1.attach(servo_pin);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
 if (customKey){
    mot=mot+customKey;
  }
  if(mot.length()==8){ //longeur max id CIN
    Serial.println(mot);
    mot="";
  }
  delay(100);
  if (Serial.available()){     
    //Si un message a été reçu  faire ceci
     data=Serial.read();  
     if(data=='1') //si le caractère lu est égale à 1
    {
     servo_1.write(180);
     delay(5000);
     servo_1.write(90);
     delay(500);
     
     }  
     /*else if(data=='0') //si le caractère lu est égale à 0

     {
     pos=0;
     servo_1.write(pos);
     } */ 
    }
}
