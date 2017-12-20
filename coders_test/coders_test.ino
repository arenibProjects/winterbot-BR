#include "coders.hpp"
#include "Motor.hpp"
#include "Odometry.hpp"
#include "DifferentialController.hpp"
#include "SerialCommand.h"
IntervalTimer controlTimer;
Coders coders(33,34,35,36);
Odometry odometry(0,0,0,265.0,16.0,20000);
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
  sCmd.addCommand("+POS",   startpos_command);     // startpos
  sCmd.addCommand("-POS",   stoppos_command);     // stoppos
  sCmd.addCommand("SPID",   spid_command);     // setpid
  sCmd.addCommand("GPID",   gpid_command);     // getpid
  sCmd.addCommand("WHOIS", whois_command);       // who are you?
  sCmd.addCommand("AYR", ready_command);       // are you ready?
  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
  ready_command();
}

void loop() {
  sCmd.readSerial();
  if(millis()-t>100){
    if(sendPos){
      Serial.print("POS ");Serial.print(odometry.getX());Serial.print(" ");Serial.print(odometry.getY());Serial.print(" ");Serial.println(odometry.getA());
    }
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
void spid_command() {// === NOT IMPLEMENTED ===
  sCmd.next();
  sCmd.next();
  sCmd.next();
  sCmd.next();
  sCmd.next();
  sCmd.next();
}
void gpid_command() {// === NOT IMPLEMENTED ===
  Serial.println("PID 0 0 0 0 0 0");
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
void ready_command() {
  Serial.println("READY");
  stoppos_command();
}
// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println("SCRAMBLED");
}
