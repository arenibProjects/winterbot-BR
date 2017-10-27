/* simple timestamp useful Pid */
#ifndef STUPID_H
#define STUPID_H

class cuPID
{
  public:
    cuPID(double * iinput, double * isetpoint,double * ioutput,double ikp,double iki,double ikd);
    void compute();
  private:
    double *input,*setpoint,*output,kp,ki,kd,integ,prevE;
    long prevT;
};
#endif