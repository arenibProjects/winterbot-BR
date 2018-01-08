#include "coders.hpp"
#include "Motor.hpp"
#include "Odometry.hpp"
#include "DifferentialController.hpp"
#include "SerialCommand.h"
IntervalTimer controlTimer;
Coders coders(33,34,35,36);
Odometry odometry(0,0,0,265.0,16.0,20000);
DifferentialController controller(10,0,0,100,0,0);
Motor leftMotor(2,3,4);
Motor rightMotor(5,6,7);
SerialCommand sCmd;
long t=millis();
bool sendPos=false;
bool on=false;

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
  sCmd.addCommand("RPID",   rpid_command);     //reset pid

  sCmd.addCommand("STAR",   star_command);     //setTarget

  sCmd.addCommand("STILL",   still_command);     //still pid
  sCmd.addCommand("ON",   on_command);     //on pid
  sCmd.addCommand("OFF",   off_command);     //off pid
  
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
  controller.update(odometry.getX(),odometry.getY(),odometry.getA());
  if(on){
    leftMotor.setSpeed(controller.getLeft());
    rightMotor.setSpeed(controller.getRight());
  }else{
    leftMotor.setSpeed(0);
    rightMotor.setSpeed(0);
  }
}


void goto_command() {
  delay(2000);
  Serial.println("ONSPOT");
}
void spos_command() {
  odometry.set(String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat());
}
void spid_command() {
  controller.setFactors(String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat());
}
void gpid_command() {
  Serial.print("PID ");
  Serial.print(controller.getFactor(0));
  Serial.print(" ");
  Serial.print(controller.getFactor(1));
  Serial.print(" ");
  Serial.print(controller.getFactor(2));
  Serial.print(" ");
  Serial.print(controller.getFactor(3));
  Serial.print(" ");
  Serial.print(controller.getFactor(4));
  Serial.print(" ");
  Serial.println(controller.getFactor(5));
}
void rpid_command() {
  controller.reset();
}
void star_command() {
  controller.setTarget(String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat(),String(sCmd.next()).toFloat());
}
void still_command() {
  controller.setTarget(odometry.getX(),odometry.getY(),odometry.getA());
}
void on_command() {
  rpid_command();
  on=true;
}
void off_command() {
  on=false;
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
