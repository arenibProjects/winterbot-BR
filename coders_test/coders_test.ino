#include "coders.hpp"
#include "Motor.hpp"
#include "Odometry.hpp"
#include "DifferentialController.hpp"
#include "SerialCommand.h"
IntervalTimer controlTimer;
Coders coders(33,34,35,36);
Odometry odometry(0,0,0,170,65,20000);
SerialCommand sCmd;
long t=millis();
bool sendPos=false;
//DifferentialController controller(10,0,0,100,0,0);
void setup() {
  Serial.begin(250000);
  delay(10000);
  Serial.println("GO!!");
  controlTimer.begin(controlLoop,4166);
  controlTimer.priority(129);
  //controller.setTarget(-2000,0,0);
  // Setup callbacks for SerialCommand commands
  sCmd.addCommand("GOTO",    goto_command);     // goto
  sCmd.addCommand("SPOS",   spos_command);     // setpos
  sCmd.addCommand("+POS",   startpos_command);     // setpos
  sCmd.addCommand("-POS",   stoppos_command);     // setpos
  sCmd.addCommand("WHOIS", whois_command);       // who are you?
  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
  Serial.println("READY");
}

void loop() {
  sCmd.readSerial();
  if(millis()-t>100){
    if(sendPos)Serial.print("POS ");Serial.print(odometry.getX());Serial.print(" ");Serial.print(odometry.getY());Serial.print(" ");Serial.println(odometry.getA());
    t=millis();
  }
}

void controlLoop(){
  int cl=coders.left();
  int cr=coders.right();
  odometry.move(cl,cr);
  //controller.update(odometry.getX(),odometry.getY(),odometry.getA());
  //odometry.move(controller.getLeft(),controller.getRight());
  //odometry.move(1000,1000);
}


void goto_command() {
  delay(2000);
  Serial.println("ONSPOT");
}
void spos_command() {
  odometry.set(String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat());
}
void startpos_command(){
  sendPos=true;
}
void stoppos_command(){
  sendPos=false;
}
void whois_command() {
  Serial.println("IAM motionbase");
}

// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println("SCRAMBLED");
}
