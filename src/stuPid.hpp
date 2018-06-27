/* simple timestamp useful Pid */
/* is to be used for linear or constrained angular PID control*/
#ifndef STUPID_H
#define STUPID_H

class PID
{
  public:
    PID(double * iinput, double * isetpoint,double * ioutput,double ikp,double iki,double ikd);
    void compute();
    void set(double kp,double ki,double kd);
    double getP();
    double getI();
    double getD();
    void reset();
  private:
    double *input,*setpoint,*output,kp,ki,kd,integ,prevE;
    long prevT;
};
#endif
