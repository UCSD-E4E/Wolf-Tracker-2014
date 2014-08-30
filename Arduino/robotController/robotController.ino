#include <SoftwareSerial.h>

//PREPROCCESSOR DIRECTIVES

#define THRESHOLD        0.15
#define MAX_INPUT_LENGTH 16
//uncomment for debug statements
#define DEBUG

//pin defines
#define LEFT_MOTOR_PWM_PIN    6
#define LEFT_MOTOR_DIR_PIN    8
#define RIGHT_MOTOR_PWM_PIN   5
#define RIGHT_MOTOR_DIR_PIN   7
//STRUCT DEFINITIONS

struct MotorPower{
  float leftMotor;
  float rightMotor;
};

//global values
struct MotorPower motorPower;
unsigned long lastUpdateTime; //to keep track of time of last input

//function prototypes
bool isValidChar(char c);
bool isValidInput(String input);
void parseData(String data);
void updateMotors(String lpower, String rpower);
void driveMotors();
void updateTime();
void stopMotors();

SoftwareSerial mySerial(2,3);//RX, TX

void setup() {
  //Setting up serial
  Serial.begin(115200);
  mySerial.begin(57600);
  #ifdef DEBUG
  Serial.print("Started Serial\n");
  #endif  
  
  //Setting up motors
  pinMode(LEFT_MOTOR_PWM_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_DIR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR_PIN, OUTPUT);  
  
  //setting last update time
  lastUpdateTime = millis();
}

void loop() {
  String str;
  if(mySerial.available()){
    str = mySerial.readStringUntil('\n');
    updateTime();
    if(isValidInput(str) == true){
      parseData(str); //updates teh global motorPower struct
      driveMotors();      
    }
  } else {
    //if last update sent was longer than 1 second, reset the motors to 0
    if((millis() - lastUpdateTime) >  500){
      stopMotors();      
    }
  }
}

void updateTime(){
  lastUpdateTime = millis();
}

String validCharacters = "LR:|1234567890.-;";

//returns false if char not found in string
bool isValidChar(char c){
  for(int i =0; i < validCharacters.length(); i++){
    if(c == validCharacters.charAt(i)){
      return true;
    }
  }
  return false;
}

bool isValidInput(String input){  
   //go through each character in the data string
  if(input.length() > MAX_INPUT_LENGTH){
    #ifdef DEBUG
    Serial.print("TOO long of input!\n");
    #endif
    return false;
  }
  for(int i = 0; i < input.length(); i++){
    if(isValidChar(input.charAt(i)) == false){
      //char not valid!
      #ifdef DEBUG
      Serial.print("char not valid!\n");
      #endif
      return false;
    }
  } //end of i for
  return true;
}

void parseData(String data){
  String leftMotorString = "";
  String rightMotorString = "";
  int state = 0;
  for(int i = 0; i < data.length(); i++){
    char c = data.charAt(i);
    if(c == 'L'){
      state = 0;
      continue;
    }
    if(c == 'R'){
      state = 1;
      continue;
    }
    if(c == ':' || c =='|' || c == ';'){
      continue;
    }
    
    switch(state) {
      case 0:
        // parsing leftMotorString data
        leftMotorString.concat(data.charAt(i));
        break;
      case 1:
        //parsing rightMotorString data
        rightMotorString.concat(data.charAt(i));        
        break;
      default:
        //don't do anything
        break;
    }
  } //end of for loop
  updateMotors(leftMotorString, rightMotorString);
}

void stopMotors(){
  motorPower.leftMotor = 0;
  motorPower.rightMotor = 0;
  
  //stop motors with pwm signal of 0
  analogWrite(LEFT_MOTOR_PWM_PIN, 0);  
  analogWrite(RIGHT_MOTOR_PWM_PIN, 0);     
}

void updateMotors(String lpower, String rpower){
  //creating char arrays since .toCharArray needs an array to write to
  int sizeOfArray = 8;
  char leftPowerCharArray[sizeOfArray];
  char rightPowerCharArray[sizeOfArray];
  lpower.toCharArray(leftPowerCharArray, sizeOfArray);
  rpower.toCharArray(rightPowerCharArray, sizeOfArray);
  
  motorPower.leftMotor = atof(leftPowerCharArray);  
  motorPower.rightMotor = atof(rightPowerCharArray);
}

void driveMotors(){
  #ifdef DEBUG
  Serial.print("Left Power: ");
  Serial.print(motorPower.leftMotor);
  Serial.print("\t\tRightPower: ");
  Serial.print(motorPower.rightMotor);
  Serial.print("\n");
  #endif
  
  //Left Drive
   if(abs(motorPower.leftMotor) > THRESHOLD){
     int LeftMotorPWM = map(abs(motorPower.leftMotor * 100), 0, 100, 0, 255);
     analogWrite(LEFT_MOTOR_PWM_PIN, LeftMotorPWM);
   
     if(motorPower.leftMotor < 0){ //move forward if stick pushed forward
       
       digitalWrite(LEFT_MOTOR_DIR_PIN, HIGH);
     } else {
       digitalWrite(LEFT_MOTOR_DIR_PIN, LOW);   
     }   
   } else {
     analogWrite(LEFT_MOTOR_PWM_PIN, 0);  
   }

   
  //Right Drive
  
   if(abs(motorPower.rightMotor) > THRESHOLD){
     int RightMotorPWM = map(abs(motorPower.rightMotor * 100), 0, 100, 0, 255);
     analogWrite(RIGHT_MOTOR_PWM_PIN, RightMotorPWM);    
   
     if(motorPower.rightMotor < 0){ //move forward if stick pushed forward
       digitalWrite(RIGHT_MOTOR_DIR_PIN, LOW);
     } else {
       digitalWrite(RIGHT_MOTOR_DIR_PIN, HIGH);   
     }      
   } else {
     analogWrite(RIGHT_MOTOR_PWM_PIN, 0);  
   }
}
