#include "powerB.h"
#include<FastLED.h>

//const int shape[]={9,24};

Display::Display(const int pin,const int l,const int shape[2],char minI,char maxI)
{
    this->length=l;
    this->shape[0]=shape[0];this->shape[1]=shape[1];
    this->center[0]=shape[0]/2;this->center[1]=this->shape[1]/2;
    this->maxWI=maxI;
    this->minI=minI;
//    this->frameA=new CRGB[l];//
//    this->frameM=new CRGB[9][24];
    int count=0;
    for (int m = 0; m <this->shape[0]; m++)
    {
        for (int n = 0; n < this->shape[1]; n++)
        {
            this->frameM[m][n]=CRGB(0,0,0);
            this->frameA[count]=CRGB(0,0,0);
            count++;
        }
    }
}

void Display::M2A(){
    int count=0;
    for (int m = 0; m < this->shape[0]; m++)
    {
        for (int n = 0; n < this->shape[1]; n++)
        {
            if(m&2!=0){
              this->frameA[count]=this->frameM[m][shape[1]-1-n];
              }
              else{
                this->frameA[count]=this->frameM[m][n];
                }
            count++;
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

void Display::solidC(byte r,byte g,byte b){
        int count=0;
    for (int m = 0; m < this->shape[0]; m++)
    {
        for (int n = 0; n < this->shape[1]; n++)
        {
            this->frameM[m][n]=CRGB(r,g,b);
            count++;
        }
    }
}

void Display::solidC(byte r,byte g,byte b,int n, bool row){
      if(row){
        for (int m = 0; m < this->shape[0]; m++)
          {
              this->frameM[m][n]=CRGB(r,g,b);//
          }
        }
        else{
          for (int m = 0; m < this->shape[1]; m++)
            {
                this->frameM[n][m]=CRGB(r,g,b);
            }
         }
}
void Display::solidCr(byte r,byte g,byte b,int ox,int oy,int fx,int fy){
    for (int m = min(ox,fx); m <= max(ox,fx); m++)
    {
        for (int n = min(oy,fy); n <= max(oy,fy); n++)
        {
            this->frameM[m][n]=CRGB(r,g,b);
        }
    }
}
void Display::solidCd(byte r,byte g,byte b,int ox,int oy,int l,int d){
  switch(d){
      case 0:
        for (int m = 0; m <= l; m++)
        {
          if((ox+m)<this->shape[0]&&(oy+m)<this->shape[1]){
          this->frameM[ox+m][oy+m]=CRGB(r,g,b);}
        }
        break;
      case 1:
        for (int m = 0; m <= l; m++)
        {
          if((ox-m)>-1&&(oy+m)<this->shape[1]){
          this->frameM[ox-m][oy+m]=CRGB(r,g,b);}
        }
      break;
      case 2:
        for (int m = 0; m <= l; m++)
        {
          if((ox-m)>-1&&(oy-m)>-1){
          this->frameM[ox-m][oy-m]=CRGB(r,g,b);}
        }
      break;
      case 3:
        for (int m = 0; m <= l; m++)
        {
          if((ox+m)<this->shape[0]&&(oy-m)>-1){
          this->frameM[ox+m][oy-m]=CRGB(r,g,b);}
        }
      break;
    }
}
void Display::solidCl(byte r,byte g,byte b,int ox,int oy,int l,int d){
  switch(d){
    case 0:
      for(int i=0;i<l;i++){
        this->frameM[ox][oy+i]=CRGB(r,g,b);
        }
    break;
    case 1:
      for(int i=0;i<l;i++){
        this->frameM[ox-i][oy]=CRGB(r,g,b);
        }
    break;
    case 2:
      for(int i=0;i<l;i++){
        this->frameM[ox][oy-i]=CRGB(r,g,b);
        }
    break;
    case 3:
      for(int i=0;i<l;i++){
        this->frameM[ox+i][oy]=CRGB(r,g,b);
        }
    break;
    }
}
void Display::solidCt(byte r,byte g,byte b,int ox,int oy,int l,int d){
  l=l-1;
  switch(d){
    case 0:
        this->solidCd(r,g,b,ox,oy,l,0);
        this->solidCd(r,g,b,ox,oy,l,1);
        if(ox-l>-1&&oy+l<this->shape[1]&&ox+l<this->shape[0]){
        this->solidCr(r,g,b,ox-l,oy+l,ox+l,oy+l);
        }
    break;
    case 1:
        this->solidCd(r,g,b,ox,oy,l,1);
        this->solidCd(r,g,b,ox,oy,l,2);
        if(oy+l<this->shape[1]&&ox-l>-1&&oy-l>-1){
        this->solidCr(r,g,b,ox-l,oy+l,ox-l,oy-l);
        }
    break; 
    case 2:
      this->solidCd(r,g,b,ox,oy,l,2);
      this->solidCd(r,g,b,ox,oy,l,3);
      if(ox-l>-1&&oy-l>-1&&ox+l-1<this->shape[0]){
      this->solidCr(r,g,b,ox-l,oy-l,ox+l,oy-l);
      }
    break; 
    case 3:
      this->solidCd(r,g,b,ox,oy,l,3);
      this->solidCd(r,g,b,ox,oy,l,0);
      if(ox+l<this->shape[0]&&oy+l<this->shape[1]&&oy-l>-1){
      this->solidCr(r,g,b,ox+l,oy+l,ox+l,oy-l);
      }
    break;  
    }    
}
void Display::solidCx(byte r,byte g,byte b,int ox,int oy,int l,int w, bool d){
    if(d&& ox-w-1>-1&&oy-w-1>-1){
      for(int i=0;i<w;i++){
        this->solidCd(r,g,b,ox-i,oy,l-i,0);
        this->solidCd(r,g,b,ox-i,oy,l-i,1);
        this->solidCd(r,g,b,ox-i,oy,l-i,2);
        this->solidCd(r,g,b,ox-i,oy,l-i,3);

        this->solidCd(r,g,b,ox+i,oy,l-i,0);
        this->solidCd(r,g,b,ox+i,oy,l-i,1);
        this->solidCd(r,g,b,ox+i,oy,l-i,2);
        this->solidCd(r,g,b,ox+i,oy,l-i,3);

        this->solidCd(r,g,b,ox,oy-i,l-i,0);
        this->solidCd(r,g,b,ox,oy-i,l-i,1);
        this->solidCd(r,g,b,ox,oy-i,l-i,2);
        this->solidCd(r,g,b,ox,oy-i,l-i,3);

        this->solidCd(r,g,b,ox,oy+i,l-i,0);
        this->solidCd(r,g,b,ox,oy+i,l-i,1);
        this->solidCd(r,g,b,ox,oy+i,l-i,2);
        this->solidCd(r,g,b,ox,oy+i,l-i,3);
      
      }
    }
  }
