#ifndef powerB_h
#define powerB_h
#endif
#include<FastLED.h>

class Display{
    public:
    int length;
    int shape[2];
    int center[2];
    int origin[2];
    int pin;
//    CRGB* frameA;
//    CRGB* frameM;
    CRGB frameA[216];
    CRGB frameM[24][9];
    char maxWI;
    char minI;
    float refT;
    unsigned long dT;
    int filt;
    Display( const int pin,const int length ,const int shape[2],char minI,char maxWI);
    void M2A();
    unsigned long frameShow();
    void solidC(byte r,byte g, byte b);
    void solidC(byte r,byte g, byte b,int n,bool row);
    void solidCr(byte r,byte g,byte b,int ox,int oy,int fx,int fy);
    void solidCd(byte r,byte g,byte b,int ox,int oy,int l,int d);
    void solidCl(byte r,byte g,byte b,int ox,int oy,int l,int d);
    void solidCa(byte r,byte g,byte b,int ox,int oy,int l,float a);
    void solidCt(byte r,byte g,byte b,int ox,int oy,int l,int d);
    void solidCx(byte r,byte g,byte b,int ox,int oy,int l,int w,bool d);
};
