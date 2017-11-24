#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "DifferentialController.hpp"

#define MAX_PWM 255

double cap(double in,double c){
  if(abs(in)>c)return in/abs(in)*c;
  else return in;
}

DifferentialController::DifferentialController(double dp,double di,double dd,double ap,double ai,double ad){
  distancePID = new PID(&din,&dtar,&dout,dp,di,dd);
  anglePID = new CuPID(&ain,&atar,&aout,ap,ai,ad);
}
void DifferentialController::update(double x,double y, double a){
  double cd=sqrt(pow(tx-x,2)+pow(ty-y,2));
  double ca=atan2(ty-y,tx-x);
  //angle
  if(cd>1) atar=ca;
  else atar=ta;
  ain=a;
  anglePID->compute();
  //distance
  dtar=0;
  din=cd;
  distancePID->compute();
}
void DifferentialController::setTarget(double x,double y, double a){
  tx=x;
  ty=y;
  ta=a;
}
int DifferentialController::getLeft(){
  return min(abs(dout),MAX_PWM-min(abs(aout),MAX_PWM))-cap(aout,MAX_PWM);
}
int DifferentialController::getRight(){
  return min(abs(dout),MAX_PWM-min(abs(aout),MAX_PWM))+cap(aout,MAX_PWM);
}
