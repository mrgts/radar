/*
radar de ultrasonido para arduino 
Autor: MrGTS
Fecha: 15/04/2013
 Arduino SRF05 Radar Sketch
*/
#include <Servo.h>   
Servo leftRightServo;   
int leftRightPos = 0;    
int index = 0;  
long total = 0;    
int average = 0;    
long duration = 0;  
int distance = 0; 
// CONFIGURACIÓN
int echoPin = 11;   
int trigPin = 10;    
int servoPin = 12;    
int servoMin = 700;    
int servoMax = 2400;    
const int numReadings = 2;    
void setup() {
leftRightServo.attach(servoPin,700,2400);    
Serial.begin(9600);   
pinMode(trigPin, OUTPUT);    
pinMode(echoPin, INPUT);   
digitalWrite(trigPin, LOW);   
} 
  
void loop() {  
    for(leftRightPos = 0; leftRightPos < 180; leftRightPos++) {  
    leftRightServo.write(leftRightPos);
        for (index = 0; index<numReadings; index++) {   
        digitalWrite(trigPin, HIGH); 
        delayMicroseconds(10); 
        digitalWrite(trigPin, LOW);
     
        duration = pulseIn(echoPin, HIGH, 17400);    
            if (!duration){    
            duration = 17400;    
            }
        distance = duration/58;    
        total = total + distance;    
        delay(50);   
     
    average = total/numReadings;    
    total = 0;    
   
    
    Serial.print("X");   
    Serial.print(leftRightPos);   
    Serial.print("V");    
    Serial.println(average);    
    }
    for(leftRightPos = 180; leftRightPos > 0; leftRightPos--) {    
    leftRightServo.write(leftRightPos);
        for (index = 0; index<numReadings; index++) {           
        
        digitalWrite(trigPin, HIGH); 
        delayMicroseconds(10); 
        digitalWrite(trigPin, LOW);
     
        duration = pulseIn(echoPin, HIGH, 17400); 
            if (!duration){
            duration = 17400;
            }
        distance = duration/58;                               
        total = total + distance;                              
        delay(50);  
        }
     
    average = total/numReadings;                               
    total = 0;
   
    Serial.print("X");                                         
    Serial.print(leftRightPos);                                
    Serial.print("V");                                         
    Serial.println(average);                                   
    }
}
