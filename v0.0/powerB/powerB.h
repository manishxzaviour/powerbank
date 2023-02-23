#ifndef powerB_h
#define powerB_h
#endif
#include<FastLED.h>

class Display{
    public:
    int length;
    int shape[2];
    int pin;
    CRGB* frameA;
    CRGB* frameM;
    char maxWI;
    char minI;
    float refT;
    unsigned long dT;
    int filt;
    Display( const int pin,const int length ,const int shape[2],char minI,char maxWI);
    void M2A();
    unsigned long frameShow();
    void solidC(char r,char g, char b);
};
