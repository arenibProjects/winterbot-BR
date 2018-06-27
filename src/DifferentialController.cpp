#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "DifferentialController.hpp"

#define MAX_PWM 255

double cap(double in,double c){//capping fuction that constrain output to [-c,c]
  if(abs(in)>c)return in/abs(in)*c;
  else return in;
}

DifferentialController::DifferentialController(double dp,double di,double dd,double ap,double ai,double ad){
  distancePID = new PID(&din,&dtar,&dout,dp,di,dd);
  anglePID = new CuPID(&ain,&atar,&aout,ap,ai,ad);
}
void DifferentialController::update(double x,double y, double a){
  double cd=sqrt(pow(tx-x,2)+pow(ty-y,2)); //distance to travel
  double ca=atan2(ty-y,tx-x); //angle to rotate to be toward objectives
  //angle
  if(cd>1) atar=ca;//if there is distance to travel, then turn toward the target point (by feeding ca to the pid as target)
  else atar=ta; //else turn to target angle (by feeding ta to the pid as target)
  ain=a;//feeding current angle to pid as input
  anglePID->compute();//updating the angle pid
  //distance
  dtar=0; //we want to minimize distance
  din=cd;
  distancePID->compute();//updating the distance pid
}
void DifferentialController::setTarget(double x,double y, double a){
  tx=x;
  ty=y;
  ta=a;
}
int DifferentialController::getLeft(){
  return min(abs(dout),MAX_PWM-min(abs(aout),MAX_PWM))-cap(aout,MAX_PWM);
  //the basic idea is dist pid - angle pid
}
int DifferentialController::getRight(){
  return min(abs(dout),MAX_PWM-min(abs(aout),MAX_PWM))+cap(aout,MAX_PWM);
  //the basic idea is dist pid + angle pid
}
void DifferentialController::setFactors(double dp,double di,double dd,double ap,double ai,double ad){
  distancePID->set(dp,di,dd);
  anglePID->set(ap,ai,ad);
}
double DifferentialController::getFactor(int i){
  if(i==0) return distancePID->getP();
  if(i==1) return distancePID->getI();
  if(i==2) return distancePID->getD();
  if(i==3) return anglePID->getP();
  if(i==4) return anglePID->getI();
  if(i==5) return anglePID->getD();
  return 0;
}
void DifferentialController::reset(){
  distancePID->reset();
  anglePID->reset();
}

