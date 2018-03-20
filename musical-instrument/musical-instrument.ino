#include <Adafruit_CircuitPlayground.h>

long C = 261.63;
long D = 293.665;
long E = 329.628;
long F = 349.228;
long G = 391.995;
long A = 440;
long B = 466.164;

int value;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {

  CircuitPlayground.clearPixels();
  
  value = CircuitPlayground.lightSensor();
  
  Serial.print("Light Sensor: ");
  Serial.println(value);

  if(CircuitPlayground.slideSwitch()){
    play(value);
  }

  delay(1); 
}

void play(int value){

  if(value < 146){
    CircuitPlayground.playTone(C, 100);
  } else if(value > 146 && value <= 292) {
    CircuitPlayground.playTone(D, 100);
  } else if(value > 292 && value <= 438) {
    CircuitPlayground.playTone(E, 100);
  } else if(value > 438 && value <= 584) {
    CircuitPlayground.playTone(F, 100);
  } else if(value > 584 && value <= 730) {
    CircuitPlayground.playTone(G, 100);
  } else if(value > 730 && value <= 876) {
    CircuitPlayground.playTone(A, 100);
  } else if(value > 876 && value <= 1022) {
    CircuitPlayground.playTone(B, 100);
  } 
  
  
}

