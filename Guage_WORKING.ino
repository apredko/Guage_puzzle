#include <Servo.h>

boolean knob1Read; //Analog input read of the different pts
boolean knob2Read;
boolean knob3Read;

bool knob1ReachedTarget = false; //Have we reached the target input for the pot?
bool knob2ReachedTarget = false;
bool knob3ReachedTarget = false;
bool complete = false;

const int knob1 = A0; //The Analog Input puts each pot is connected to
const int knob2 = A1;
const int knob3 = A2;

int knob1LED = 6; //LEDs for feedback on if the pot is in the right range
int knob2LED = 7;
int knob3LED = 8;

int servoPin = 9; //Pin the servo is connected to

int knob1Target = 25; //Arbitrary pot target amounts
int knob2Target = 725;
int knob3Target = 395;

int errorAllowed = 25; //Threshold for error in the reading

int Timer = 0; 
int Max = 600;
int Threshold = 400;

Servo myservo; //Name servo for call

void setup() {
  myservo.attach(servoPin); //Attatch the servo to th designated pin
  
  pinMode(knob1LED, OUTPUT); //Leds set as output
  pinMode(knob2LED, OUTPUT);
  pinMode(knob3LED, OUTPUT);
  
  pinMode(knob1, INPUT_PULLUP); //Pots set as inputs
  pinMode(knob2, INPUT_PULLUP);
  pinMode(knob3, INPUT_PULLUP);
  
  Serial.begin(9600); //Begin serial

}

void loop() {
  
int  knob1Read = analogRead(knob1); //Read analog input and refer to them
int  knob2Read = analogRead(knob2);
int  knob3Read = analogRead(knob3);
    

  if((knob1Read < knob1Target+errorAllowed)&&(knob1Read > knob1Target-errorAllowed) && complete==false){
    knob1ReachedTarget = true;
    digitalWrite(knob1LED, HIGH);
    //If the knob read is within threshold, the target has been reached and LED gives feedback
  }
  else{
    knob1ReachedTarget = false;
    digitalWrite(knob1LED, LOW);
    //Else we have not reach our goal, no LED feedback
  }
  if((knob2Read < knob2Target+errorAllowed)&&(knob2Read > knob2Target-errorAllowed) && complete==false){
    knob2ReachedTarget = true;
    digitalWrite(knob2LED, HIGH);
  }
  else{
    knob2ReachedTarget = false;
    digitalWrite(knob2LED, LOW);
  }
  if((knob3Read < knob3Target+errorAllowed)&&(knob3Read > knob3Target-errorAllowed) && complete==false){
    knob3ReachedTarget = true;
    digitalWrite(knob3LED, HIGH);
  }
  else{
    knob3ReachedTarget = false;
    digitalWrite(knob3LED, LOW);
  }

  if(knob1ReachedTarget == true && knob2ReachedTarget == true && knob3ReachedTarget == true && complete == false){
    Timer++;
    //If all targets are reached and we haven't completed the puzzle, increase timer
  }
  else{
    Timer--;
  }
  Timer = constrain(Timer, 0, Max);
  if(Timer >= Threshold){
    complete == true;
    //digitalWrite(knob1LED, LOW);
    //digitalWrite(knob2LED, LOW);
    //digitalWrite(knob3LED, LOW);
    myservo.write(180);
    Serial.println("COMPLETE");
    //If the timer reaches the threshold, the puzzle is complete and the servo moves
  }
  else{
    myservo.write(90);
    Serial.print("Knob 1: ");
    Serial.print(knob1Read);
    Serial.print("Knob 2: ");
    Serial.print(knob2Read);
    Serial.print("Knob 3: ");
    Serial.println(knob3Read);
  }
  
}
