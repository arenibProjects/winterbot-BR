#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
  public:
    Motor();
    Motor(int,int,int); //PWM pin, polarity pin 1, polarity pin 2
    void setSpeed(int); //take the speed of the motor in signed PWM value ([-256,256] by default but can be increased by changing the number of pwm bits
    int getSpeed();
    void ARU(); //shutdown the motor, not resetable
  private:
    int pins [3];
    int speed=0;
    bool disabled=false;
};

#endif
