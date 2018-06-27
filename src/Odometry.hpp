#ifndef ODOMETRY_H
#define ODOMETRY_H 1

class Odometry{
  public:
    Odometry(double x0,double y0,double a0,double L,double R,int S); //{base coords},interwheel radius, wheel radius, coder steps per revolution
    void move(int cl,int cr); //left counter delta, right counter delta
    double getX();
    double getY();
    double getA();
    void set(double x0,double y0,double a0);
  private:
    double x_,y_,a_,l_,r_;
    int s_;
};
#endif
