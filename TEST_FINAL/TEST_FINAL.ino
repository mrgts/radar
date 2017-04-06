/*
Arduino Ultrasonic Radar 
Autor: oscar palacios
Fecha: 15/04/2013
 Arduino SRF05 Radar Sketch
*/
#include <Servo.h>    // Añade la libreria Servo
Servo leftRightServo;    // Crea una variable servo
int leftRightPos = 0;    // Variable para la posición del servo (grados)
int index = 0;    // Contador para el número de lectura
long total = 0;    // Variable para calcular el pormedio
int average = 0;    // Variable para calcular el promedio
long duration = 0;    // Variable para calcular el tiempo de llegada de la señal
int distance = 0; // Variable para calcular la distancia
// CONFIGURACIÓN:
int echoPin = 11;    // SRF05's Echo pin
int trigPin = 10;    // SRF05's Trig pin
int servoPin = 12;    // Pin para el cable de señal del servo
int servoMin = 700;    // Anchura del pulso, en microsegundos, correspondiente al mínimo (0 grados) ángulo en del servo (por defecto 544)
int servoMax = 2400;    // Anchura del pulso, en microsegundos, correspondiente al máximo (180 grados) ángulo en del servo (por defecto 2400)
const int numReadings = 2;    // Número de lecturas en cada posición
void setup() {
leftRightServo.attach(servoPin,700,2400);    // Pin de salida para el servo, recorrido minimo, recorrido maximo
Serial.begin(9600);    // Establece la velocidad de datos del puerto serie
pinMode(trigPin, OUTPUT);    // Establece pin como salida
pinMode(echoPin, INPUT);    // Establece pin como entrada
digitalWrite(trigPin, LOW);    // Pone el pin a un estado logico bajo
} 
  
void loop() {  
    for(leftRightPos = 0; leftRightPos < 180; leftRightPos++) {    // De izquierda a derecha.
    leftRightServo.write(leftRightPos);
        for (index = 0; index<numReadings; index++) {    // Repite tantas veces como número de lecturas en cada posicion           
        // Pulso de 10us para inicial el modulo
        digitalWrite(trigPin, HIGH); 
        delayMicroseconds(10); 
        digitalWrite(trigPin, LOW);
     
        duration = pulseIn(echoPin, HIGH, 17400);    // Devuelve la longitud del pulso del pin Echo en us (3metros maximo)
            if (!duration){    // Si la duracción es 0
            duration = 17400;    // La señal se a perdido. Se establece distancia maxima
            }
        distance = duration/58;    // Calculamos distancia en centrimetros
        total = total + distance;    // Almacenamos la distancia para calcular promedio
        delay(50);    // Esperamos hasta la siguiente medida
        }
     
    average = total/numReadings;    // Calcula el promedio
    total = 0;    // Resetea variable
   
    // Envia datos por el puerto serie
    Serial.print("X");    // Identificador X para la posicion del servo
    Serial.print(leftRightPos);    // Posición del servo
    Serial.print("V");    // Identificador V para el promedio de distancia
    Serial.println(average);    // Promedio de distancia
    }
    for(leftRightPos = 180; leftRightPos > 0; leftRightPos--) {    // De derechas a izquierda
    leftRightServo.write(leftRightPos);
        for (index = 0; index<numReadings; index++) {           
        // Pulso de 10us para inicial el modulo
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
