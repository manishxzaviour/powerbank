#include "powerB.h"
#include<FastLED.h>

Display::Display(const int pin,const int l,const int shape[2],char minI,char maxI)
{
    this->length=l;
    this->shape[0]=shape[0];this->shape[1]=shape[1];
    this->maxWI=maxI;
    this->minI=minI;
    this->frameA= new CRGB[l];
    this->frameM=new CRGB[shape[0],shape[1]];
}

void Display::M2A(){
    int count=0;
    for (int m = 0; m < this->shape[0]; m++)
    {
        for (int n = 0; n < this->shape[1]; n++)
        {
            this->frameA[count]=this->frameM[m][n];
            count++;
        }
    }
}
void Display::solidC(char r,char g,char b){
        int count=0;
    for (int m = 0; m < this->shape[0]; m++)
    {
        for (int n = 0; n < this->shape[1]; n++)
        {
            this->frameM[m][n]=CRGB(r,g,b);
        }
    }
}

unsigned long Display::frameShow(){
    unsigned long t0=millis();
    this->M2A();
    FastLED.show();
    this->dT=millis()-t0;
    return dT;
}
