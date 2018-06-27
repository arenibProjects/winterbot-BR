#ifndef CODERS_H
#define CODERS_H 1
#include <Encoder.h>
class Coders{
  public:
    Coders(int p11,int p12,int p21,int p22);//{coder 1 pins},{coder 2 pins}
    ~Coders();
    int left();//read an reset the left coder
    int right();//read an reset the right coder
    void reset();//reset both coders
    
  private:
    Encoder *lc_;
    Encoder *rc_;
};
#endif
