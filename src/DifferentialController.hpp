#ifndef DIFFERENTIAL_CONTROLLER_H
#define DIFFERENTIAL_CONTROLLER_H
#include "stuPid.hpp"
#include "cuPid.hpp"
class DifferentialController{
  public:
    DifferentialController(double dp,double di,double dd,double ap,double ai,double ad);{distance pid factors},{angular pid factor}
    void update(double x,double y, double z); //has to be run on a fixed time loop and fed precise robot coordinates.
    void setTarget(double x,double y, double z); //no buffer is implemented, a change in target result in an immediate course correction.
    int getLeft(); //return left motor signed PWM
    int getRight(); //return right motor signed PWM
    void setFactors(double dp,double di,double dd,double ap,double ai,double ad); //same parameters as constructor
    double getFactor(int i); //index of the factor
    void reset(); //reset PIDs integral error and derivative memories (this should be called before recovery from an emergency stop)
  private:
    PID *distancePID;
    CuPID *anglePID;
    double din,dtar,dout;
    double ain,atar,aout;
    double tx,ty,ta;
    
};
#endif
