/* simple timestamp useful Pid */
#ifndef CUPID_H
#define CUPID_H

class CuPID
{
  public:
    CuPID(double * iinput, double * isetpoint,double * ioutput,double ikp,double iki,double ikd);
    void compute();
  private:
    double *input,*setpoint,*output,kp,ki,kd,integ,prevE;
    long prevT;
};
#endif
