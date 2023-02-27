#include "powerB.h"
#include<FastLED.h>

//const int shape[]={9,24};


Display::Display(const int pin,const int l,const int shape[2],char minI,char maxI)
{
    this->length=l;
    this->shape[0]=shape[0];this->shape[1]=shape[1];
    this->center[0]=(shape[0]-1)/2;this->center[1]=this->shape[1]/2;
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
void Display::solidCl(byte r,byte g,byte b,int ox,int oy,int fx,int fy,bool a){//
  //Bresenhams Line algo
  int x1,y1,x2,y2;//,m_new,slope_error_new;
  // float slope=(y2-y1)/(x2-x1);
  // if(!a){
  //    x1=min(ox,fx);
  //    x2=max(ox,fx);
  //    y1=min(oy,fy);
  //    y2=max(oy,fy);
  // }
  // else{
     x1=ox;
     x2=fx;
     y1=oy;
     y2=fy;
  // }
  int m_new = 2 * abs(y2 - y1);
    int slope_error_new = m_new - abs(x2 - x1);
    for (int x = x1, y = y1; x <= x2; x++) {
      if(x<24&&y<9&&x>-1&&y>-1)
        this->frameM[x][y]=CRGB(r,g,b);
         slope_error_new += m_new;
        if (slope_error_new >= 0) {
            y++;
            slope_error_new -= 2 * abs(x2 - x1);
        }
    }
}
void Display::solidCc(byte r,byte g,byte b,int ox,int oy,int rad){
  //midpoint circle algo
    int x = rad, y = 0;
    if(ox<24&&oy<9&&ox>-1&&oy>-1){
      this->frameM[x + ox][y + oy]=CRGB(r,g,b);
      if (rad > 0)
      {
          this->frameM[x + ox][-y + oy]=CRGB(r,g,b);
          this->frameM[y + ox][-x + oy]=CRGB(r,g,b);
          this->frameM[-x + ox][y + oy]=CRGB(r,g,b);
          this->frameM[-y + ox][x + oy]=CRGB(r,g,b);
      }
      int P = 1 - rad;
      while (x > y)
      {
          y++;
          if (P <= 0)
            P = P + 2*y + 1;
          else
          {
              x--;
              P = P + 2*y - 2*x + 1;
          }
          if (x < y){break;}
          this->frameM[x + ox][y + oy]=CRGB(r,g,b);
          this->frameM[-x + ox][y + oy]=CRGB(r,g,b);
          this->frameM[x + ox][-y + oy]=CRGB(r,g,b);
          this->frameM[-x + ox][-y + oy]=CRGB(r,g,b);
          if (x != y)
          {
              this->frameM[y + ox][x + oy]=CRGB(r,g,b);
              this->frameM[-y + ox][x + oy]=CRGB(r,g,b);
              this->frameM[y + ox][-x + oy]=CRGB(r,g,b);
              this->frameM[-y + ox][-x + oy]=CRGB(r,g,b);
          }
      }
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
    if(d){
      if(ox-w-1>-1&&oy-w-1>-1){
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
    else{
      for(int i=0;i<w;i++){
        this->solidCl(r,g,b,ox-i,oy,l-i,0);
        this->solidCl(r,g,b,ox-i,oy,l-i,1);
        this->solidCl(r,g,b,ox-i,oy,l-i,2);
        this->solidCl(r,g,b,ox-i,oy,l-i,3);

        this->solidCl(r,g,b,ox+i,oy,l-i,0);
        this->solidCl(r,g,b,ox+i,oy,l-i,1);
        this->solidCl(r,g,b,ox+i,oy,l-i,2);
        this->solidCl(r,g,b,ox+i,oy,l-i,3);

        this->solidCl(r,g,b,ox,oy-i,l-i,0);
        this->solidCl(r,g,b,ox,oy-i,l-i,1);
        this->solidCl(r,g,b,ox,oy-i,l-i,2);
        this->solidCl(r,g,b,ox,oy-i,l-i,3);

        this->solidCl(r,g,b,ox,oy+i,l-i,0);
        this->solidCl(r,g,b,ox,oy+i,l-i,1);
        this->solidCl(r,g,b,ox,oy+i,l-i,2);
        this->solidCl(r,g,b,ox,oy+i,l-i,3);
      }
    }
  }

Menu::Menu(Display* display,Button* button){
  this->display=display;
  this->button=button;
}

void Menu::pong(){//
  int posP1=this->display->center[1];
  int posP2=this->display->center[1];
  bool startF=1;
  this->display->solidC(1,1,1);
  this->display->solidCl(50,50,50,0,0,this->display->shape[1],0);
  this->display->solidCl(50,50,50,this->display->shape[0]-1,0,this->display->shape[1],0);
  this->display->solidCl(50,5,5,1,posP1-1,3,0);
  this->display->solidCl(50,5,5,this->display->shape[0]-2,posP2-1,3,0);
  this->display->solidCl(0,10,10,2,0,8,3);
  this->display->solidCl(0,10,10,this->display->shape[0]-3,this->display->shape[1]-1,8,1);
  for(int i=0;i<this->display->shape[1];i++){
      this->display->frameM[this->display->center[0]][i]=CRGB(5,5,20);
      this->display->frameM[this->display->center[0]+1][i]=CRGB(5,5,20);
  }
  this->display->frameM[this->display->center[0]][this->display->center[1]]=CRGB(50,32,0);
  this->display->frameM[this->display->center[0]+1][this->display->center[1]]=CRGB(50,32,0);
  this->display->frameShow();
  for(int i=0;i<this->display->center[0]-2;i++){
    this->display->solidCl(5,50,10,this->display->shape[0]-3,this->display->center[1],i+1,1);
    this->display->solidCl(5,50,10,2,this->display->center[1],i+1,3);
    this->display->frameShow();
    delay(250);
    this->display->solidCl(1,1,1,this->display->shape[0]-3,this->display->center[1],i,1);
    this->display->solidCl(1,1,1,2,this->display->center[1],i,3);
    this->display->frameShow();
    delay(400);
  }
  this->display->solidCl(1,1,1,2,this->display->center[1],this->display->center[0]-2,3);
  this->display->solidCl(1,1,1,this->display->shape[0]-3,this->display->center[1],this->display->center[0]-2,1);
  this->display->solidCl(50,5,5,1,posP1-1,3,0);
  this->display->solidCl(50,5,5,this->display->shape[0]-2,posP2-1,3,0);
  this->display->solidCl(50,50,50,0,0,this->display->shape[1],0);
  this->display->solidCl(50,50,50,this->display->shape[0]-1,0,this->display->shape[1],0);
  this->display->frameShow();
  while(1){  
    if(startF){
      startF=0;
      this->display->solidCl(50,32,0,this->display->center[0],this->display->center[1],2,int(random(0,this->display->shape[1]-1)),1);
    }
    if(digitalRead(this->button->lb)&&digitalRead(this->button->rb)&&!digitalRead(this->button->dpad[0])){break;}

    if(digitalRead(this->button->rb)){
      this->display->solidCl(1,1,1,1,0,this->display->shape[1],0);
      if(posP2<this->display->shape[1]-3){
        posP2+=1;
        this->display->solidCl(50,5,5,1,posP2,3,0);
      }
      else if(posP2<this->display->shape[1]-2){
        posP2+=1;
        this->display->solidCl(50,5,5,1,posP2,2,0);
      }
      else if(posP2<this->display->shape[1]-1){
        posP2+=1;
        this->display->solidCl(50,5,5,1,posP2,1,0);
      }
      else{
        posP2=0;
        this->display->solidCl(50,5,5,1,posP2,2,0);
      }
    }
    if(digitalRead(this->button->lb)){
      this->display->solidCl(1,1,1,this->display->shape[0]-2,0,this->display->shape[1],0);
      if(posP1>0){
        posP1-=1;
        this->display->solidCl(50,5,5,this->display->shape[0]-2,posP1,3,0);
      }
      else{
        posP1=this->display->shape[1]-2;
        this->display->solidCl(50,5,5,this->display->shape[0]-2,posP1,2,0);
      }
    }
    this->display->frameShow();
  }
}

void Menu::dieThrow(){
  int prevThrow=random(1,7);
  while(1){
    if(digitalRead(this->button->lb)&&digitalRead(this->button->rb)&&!digitalRead(this->button->dpad[0])){break;}
    int lb=digitalRead(this->button->lb);
    int rb=digitalRead(this->button->rb);
    if((lb&&!rb)||(!lb&&rb)){
      if(lb){
        this->display->solidCl(20,50,10,this->display->shape[0]-1,this->display->shape[1]-1,5,2);
        this->display->solidCl(1,1,1,0,0,5,0);
        this->display->frameShow();
      }
      else{
        this->display->solidCl(1,1,1,this->display->shape[0]-1,this->display->shape[1]-1,5,2);
        this->display->solidCl(20,50,10,0,0,5,0);
        this->display->frameShow();
      }
      this->display->solidCr(0,0,0,this->display->center[0]-4,this->display->center[1]-4,this->display->center[0]+4,this->display->center[1]+4);
      this->display->solidCc(30,50,50,this->display->center[0],this->display->center[1],2);
      this->display->frameShow();
      delay(150);
      this->display->solidCr(0,0,0,this->display->center[0]-4,this->display->center[1]-4,this->display->center[0]+4,this->display->center[1]+4);
      this->display->solidCc(30,50,50,this->display->center[0],this->display->center[1],5);
      this->display->frameShow();
      while(1){
        int thisThrow=random(1,7);
        if(prevThrow!=thisThrow){  prevThrow=thisThrow; break;}
      }
      switch (prevThrow)
      {
        case 1:
          this->display->solidCr(70,10,10,this->display->center[0]-1,this->display->center[1]-1,this->display->center[0]+1,this->display->center[1]+1);
        break;
        case 2:
          this->display->solidCr(70,10,10,this->display->center[0]-3,this->display->center[1]-3,this->display->center[0]-1,this->display->center[1]-1);
          this->display->solidCr(70,10,10,this->display->center[0]+3,this->display->center[1]+3,this->display->center[0]+1,this->display->center[1]+1);
        break;
        case 3:
          this->display->solidCr(70,10,10,this->display->center[0]-3,this->display->center[1]-3,this->display->center[0]-2,this->display->center[1]-2);
          this->display->solidCr(70,10,10,this->display->center[0]-1,this->display->center[1]-1,this->display->center[0]+1,this->display->center[1]+1);
          this->display->solidCr(70,10,10,this->display->center[0]+3,this->display->center[1]+3,this->display->center[0]+2,this->display->center[1]+2);
        break;
        case 4:
          this->display->solidCr(70,10,10,this->display->center[0]-2,this->display->center[1]-2,this->display->center[0]-1,this->display->center[1]-1);
          this->display->solidCr(70,10,10,this->display->center[0]+2,this->display->center[1]+2,this->display->center[0]+1,this->display->center[1]+1);
          this->display->solidCr(70,10,10,this->display->center[0]-2,this->display->center[1]+2,this->display->center[0]-1,this->display->center[1]+1);
          this->display->solidCr(70,10,10,this->display->center[0]+2,this->display->center[1]-2,this->display->center[0]+1,this->display->center[1]-1);
        break;
        case 5:
          this->display->solidCr(70,10,10,this->display->center[0]-3,this->display->center[1]-3,this->display->center[0]-2,this->display->center[1]-2);
          this->display->solidCr(70,10,10,this->display->center[0]-3,this->display->center[1]+3,this->display->center[0]-2,this->display->center[1]+2);
          this->display->solidCr(70,10,10,this->display->center[0]-1,this->display->center[1]-1,this->display->center[0]+1,this->display->center[1]+1);
          this->display->solidCr(70,10,10,this->display->center[0]+3,this->display->center[1]+3,this->display->center[0]+2,this->display->center[1]+2);
          this->display->solidCr(70,10,10,this->display->center[0]+3,this->display->center[1]-3,this->display->center[0]+2,this->display->center[1]-2);
        break;
        case 6:
          this->display->solidCr(70,10,10,this->display->center[0]-3,this->display->center[1]-3,this->display->center[0]-2,this->display->center[1]-2);
          this->display->solidCr(70,10,10,this->display->center[0]-3,this->display->center[1]+3,this->display->center[0]-2,this->display->center[1]+2);
          this->display->solidCr(70,10,10,this->display->center[0]+3,this->display->center[1]+3,this->display->center[0]+2,this->display->center[1]+2);
          this->display->solidCr(70,10,10,this->display->center[0]+3,this->display->center[1]-3,this->display->center[0]+2,this->display->center[1]-2);
          this->display->solidCl(70,10,10,this->display->center[0]-2,this->display->center[1],4,1);
          this->display->solidCl(70,10,10,this->display->center[0]+2,this->display->center[1],4,3);
        break;
      }
      this->display->frameShow();
      delay(1000);
    }
    this->display->frameShow();
  }
}