#ifndef powerB_h
#define powerB_h
#endif
#include <FastLED.h>
#include "Arduino.h"

class Display
{
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
    Display(const int pin, const int length, const int shape[2], char minI, char maxWI);
    void M2A();
    unsigned long frameShow();
    void solidC(byte r, byte g, byte b);
    void solidC(byte r, byte g, byte b, int n, bool row);
    void solidCr(byte r, byte g, byte b, int ox, int oy, int fx, int fy);
    void solidCd(byte r, byte g, byte b, int ox, int oy, int l, int d);
    void solidCl(byte r, byte g, byte b, int ox, int oy, int l, int d);
    void solidCl(byte r, byte g, byte b, int ox, int oy, int fx, int fy, bool a);
    void solidCc(byte r, byte g, byte b, int ox, int oy, int rad);
    void solidCt(byte r, byte g, byte b, int ox, int oy, int l, int d);
    void solidCx(byte r, byte g, byte b, int ox, int oy, int l, int w, bool d);
};

typedef struct
{
    int lb;
    int rb;
    int dpad[5];
} Button;

class Pong
{
public:
    Pong(Display *display, Button *button, int fps);
    Display *display;
    Button *button;
    int posP1;
    int posP2;
    bool startF;
    int fps;
    int Delay;
    bool breakChk();
    void set();
    void run();
};
class DieThrow
{
public:
    DieThrow(Display *display, Button *button, int fps);
    Display *display;
    Button *button;
    int fps;
    int Delay;
    void set();
    int prevThrow;
    bool breakChk();
    void run();
    int numGen();
};

class Snake
{
public:
    Snake(Display *display, Button *button, int fps);
    int apple[2];
    int head[2];
    int length;
    Display *display;
    Button *button;
    int fps;
    int Delay;
    void set();
    bool breakChk();
    void run();
    bool col;
};
class Menu
{
public:
    int option;
    int lastopt;
    Display *display;
    Button *button;
    Pong *pong;
    DieThrow *dieThrow;
    Snake *snake;
    Menu(Display *display, Button *button);
};
