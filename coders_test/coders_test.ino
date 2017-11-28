#include "coders.hpp"
#include "Motor.hpp"
#include "Odometry.hpp"
#include "DifferentialController.hpp"
IntervalTimer controlTimer;
Coders coders(33,34,35,36);
Odometry odometry(0,0,0,170,65,20000);
//DifferentialController controller(10,0,0,100,0,0);
void setup() {
  Serial.begin(250000);
  delay(10000);
  Serial.println("GO!!");
  controlTimer.begin(controlLoop,4166);
  controlTimer.priority(129);
  //controller.setTarget(-2000,0,0);
}

void loop() {
  
}

void controlLoop(){
  int cl=coders.left();
  int cr=coders.right();
  odometry.move(cl,cr);
  //controller.update(odometry.getX(),odometry.getY(),odometry.getA());
  //odometry.move(controller.getLeft(),controller.getRight());
  //odometry.move(1000,1000);
  Serial.print("Left:");Serial.print(cl);Serial.print(" Right:");Serial.print(cr);Serial.print(" X:");Serial.print(odometry.getX());Serial.print(" Y:");Serial.print(odometry.getY());Serial.print(" A:");Serial.println(odometry.getA());
}

