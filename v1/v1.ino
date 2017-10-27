#include "coders.hpp"
#include "Motor.hpp"
#include "stuPid.hpp"
IntervalTimer ControlTimer;
Coders *coders;
void setup() {
  coders = new Coders(2,3,4,5);
  ControlTimer.begin(controlLoop,4166);
  ControlTimer.priority(129);
}

void loop() {
}
void controlLoop(){
  
}

