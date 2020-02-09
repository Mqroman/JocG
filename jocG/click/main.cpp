#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <ctime>
using namespace std;
void saIncepem();
void desChenar2(int a,int b)
{
 setcolor(CYAN);
 bar(b,a,b+100,a+50);
}

 int a=100,b=200,c=300,d=400,e=500,f=600,V=100,ok=1;
 int culoareblocata1=1;
 int culoareblocata2=2;
 int a0[1000][1000],a2[1000][1000],a3[1000],a4[1000],lib[5];
 int cordX[1001][1001],cordY[1001][1001];
 int n, m;
 char numarpatrat[2]="5" ,mod[111]=" 1vsPC";
 char culoare1=RED;
 char culoare2=GREEN;

typedef unsigned char byte;
typedef unsigned int word;

byte spatiu=0, lat=60, x0=85, y0=45;
byte is, js;
byte Leg[500], Tabla[500][500];

 int modJoc=1;
/*1 incepe om, cheat
2 incepe pc,
3 incepe om pc slab
4  2 oameni
5 pc vs pc
*/
int mouse=0;//mouse sau tastatura
int k=5;

 POINT cursorPosition;
 int mX,mY;

int chenarIN(int x,int y,int loc,int loc2)
{
    if(x>=loc&&x<=loc+100&&y>=loc2&&y<=loc2+50)return 1;
    return 0;
}
void legatura(int n)
{
   int k=1,k2=1,l,i,j;

   for( i=1;i<=n;i++)
   for( j=1;j<=n;j++)
       a0[i][j]=k++,a2[i][j]=0;

   for( k=0;k<=(n*n)/2;k++){
   for( i=1+k;i<=n-k;i++) { l=k+1; if(!a2[l][i]) a3[k2++]=a0[l][i], a2[l][i]=1;}
   for( j=2+k;j<=n-k;j++) { l=n-k; if(!a2[j][l])  a3[k2++]=a0[j][l], a2[j][l]=1;}
   for( i=n-1-k;i>=1+k;i--) { l=n-k; if(!a2[l][i])  a3[k2++]=a0[l][i], a2[l][i]=1;}
   for( j=n-1-k;j>=2+k;j--) { l=k+1; if(!a2[j][l])  a3[k2++]=a0[j][l], a2[j][l]=1;}
 }

k2=1;i=1;
for( k=1;k<=n*n;k++)
   {if(k2==1)a4[i++]=a3[k+1],k2=0;
    else {a4[i++]=a3[k-1],k2=1;}
   }

    for( k=1;k<=n*n;k++)
    Leg[a3[k]]=a4[k];
    Leg[0]=0;
}
void OpenGraph()
{
        DWORD screenWidth=GetSystemMetrics(SM_CXSCREEN);
        DWORD screenHeight=GetSystemMetrics(SM_CYSCREEN);
        initwindow(screenWidth,screenHeight,"Proiect_joc_G");
}
byte CasutaLibera()
{
 return (k*(is-1)+js);
}
void InitTabla()
{
 byte i,j; is=k/2+1; js=k/2+1;

 for (i=1; i<=k; i++)
 for (j=1; j<=k; j++)

 if ((i+j) % 2 != 0) Tabla[i][j]=culoare1;
 else Tabla[i][j]=culoare2;

 Tabla[is][js]=spatiu;
 for (i=0; i<=k+1; i++)
 {
 Tabla[0][i]=culoare2; Tabla[k+1][i]=culoare2;
 Tabla[i][0]=culoare2; Tabla[i][k+1]=culoare2;
 }
}
void DesPiesa(int i, int j)
{

 if ((i!=is) || (j!=js))
 {
 setcolor(WHITE);
 rectangle(x0+lat*i, y0+lat*j, x0+lat*i+lat, y0+lat*j+lat);

 setfillstyle(SOLID_FILL,Tabla[i][j]);
 fillellipse(x0+lat*i+lat/2, y0+lat*j+lat/2,lat/4, lat/4);

 }
 else
 {
 setfillstyle(SOLID_FILL,BLACK);
 bar(x0+lat*i, y0+lat*j, x0+lat*i+lat, y0+lat*j+lat);

 setcolor(WHITE);
 rectangle(x0+lat*i,y0+lat*j, x0+lat*i+lat, y0+lat*j+lat);
 }
}
void DesTabla()
{
 byte i,j; setfillstyle(SOLID_FILL,MAGENTA);
 bar(x0+lat+4,y0+lat+4,x0+lat*6+4,y0+lat*6+4);

 for (i=1; i<=k; i++)
 for (j=1; j<=k; j++)
 {
  setfillstyle(SOLID_FILL,0);
  bar(x0+lat*i,y0+lat*j,x0+lat*i+lat,y0+lat*j+lat);
  cordX[i][j]=x0+lat*i;
  cordY[i][j]=y0+lat*j+lat/2 -5 ;

 DesPiesa(i,j);
 }
}

void MutaCalc()
{
 byte isv,jsv,cas; isv=is; jsv=js;
 cas=Leg[CasutaLibera()];
 is=(cas-1)/k+1; js=(cas-1)%k+1;
 Tabla[is][js]=spatiu; DesPiesa(is,js);
 Tabla[isv][jsv]=culoare2; DesPiesa(isv,jsv);
}
void MutaCalc1(char culoare1)
{int a,b;
 byte isv,jsv,cas; isv=is; jsv=js;
 cas=CasutaLibera();
 is=(cas-1)/k+1; js=(cas-1)%k+1;

 char t;

 for(int i=1;i<=k;i++)
 {
     Tabla[i][k+1]=t;
     Tabla[i][0]=t;
     Tabla[0][i]=t;
     Tabla[k+1][i]=t;
 }
 if(Tabla[is-1][js]==culoare1)lib[1]=1;
 else
    lib[1]=0;
    if(Tabla[is][js-1]==culoare1)lib[2]=1;
 else
 lib[2]=0;
 if(Tabla[is+1][js]==culoare1)lib[3]=1;
 else lib[3]=0;
 if(Tabla[is][js+1]==culoare1)lib[4]=1;
 else lib[4]=0;

   srand(static_cast<unsigned int>(time(0)));
int o=rand()%5;
while(lib[o]==0)o=rand()%5;

 if(o==1)a=is-1,b=js;
 if(o==2)a=is,b=js-1;
 if(o==3)a=is+1,b=js;
 if(o==4)a=is,b=js+1;

is=a;js=b;
 Tabla[is][js]=spatiu; DesPiesa(is,js);
 Tabla[isv][jsv]=culoare1; DesPiesa(isv,jsv);
}
void MutaOm(char culoare1)
{
 int tasta, mut;
 do {
 tasta=getch(); if (tasta==0) tasta=getch();
 mut=0;
 switch (tasta) {
 case 75: if (is<k)
 if (Tabla[is+1][js]==culoare1)
 {
 is++; mut=1;
 Tabla[is][js]=spatiu; DesPiesa(is,js);
 Tabla[is-1][js]=culoare1; DesPiesa(is-1,js);
 }
 break;
 case 77: if (is>1)
 if (Tabla[is-1][js]==culoare1)
 {
 is--; mut=1;
 Tabla[is][js]=spatiu; DesPiesa(is,js);
 Tabla[is+1][js]=culoare1; DesPiesa(is+1,js);
 }
 break;
 case 80: if (js>1)
 if (Tabla[is][js-1]==culoare1)
 {
 js--; mut=1;
 Tabla[is][js]=spatiu; DesPiesa(is,js);
 Tabla[is][js+1]=culoare1; DesPiesa(is,js+1);
 }
 break;
 case 72: if (js<k)
 if (Tabla[is][js+1]==culoare1)
 {
 js++; mut=1;
 Tabla[is][js]=spatiu; DesPiesa(is,js);
 Tabla[is][js-1]=culoare1; DesPiesa(is,js-1);
 }
 break;
 case 27: {
 closegraph();
 saIncepem();
 }
 }
 if (!mut)
 {  delay(50);
 }
 } while (!mut);
}
void MutaOm3(char culoare1,int directie)
{
 int tasta, mut;
 do {
 tasta=directie;
 mut=0;
 switch (tasta) {
 case 1: if (is<k)
 if (Tabla[is+1][js]==culoare1)//dreapta  -  stanga
 {
 is++; mut=1;
 Tabla[is][js]=spatiu; DesPiesa(is,js);
 Tabla[is-1][js]=culoare1; DesPiesa(is-1,js);
 }
 break;
 case 2: if (is>1)
 if (Tabla[is-1][js]==culoare1) //stanga - dreapta
 {
 is--; mut=1;
 Tabla[is][js]=spatiu; DesPiesa(is,js);
 Tabla[is+1][js]=culoare1; DesPiesa(is+1,js);
 }
 break;
 case 3: if (js>1)
 if (Tabla[is][js-1]==culoare1)    //sus   -   jos
 {
 js--; mut=1;
 Tabla[is][js]=spatiu; DesPiesa(is,js);
 Tabla[is][js+1]=culoare1; DesPiesa(is,js+1);
 }
 break;
 case 4: if (js<k)
 if (Tabla[is][js+1]==culoare1)    //jos -  sus
 {
 js++; mut=1;
 Tabla[is][js]=spatiu; DesPiesa(is,js);
 Tabla[is][js-1]=culoare1; DesPiesa(is,js-1);
 }
 break;
 case 5: {
 closegraph();
 printf("Ati abandonat...");
 exit(1);
 }
 }
 if (!mut)
 {  delay(50);
 }
 } while (!mut);
}
int chenarIN2(int x,int y,int loc,int loc2)
{
    if(x>=loc&&x<=loc+lat&&y>=loc2&&y<=loc2+lat)return 1;
    return 0;
}
int casutalibera2()
{
    for(int i=1;i<=k;i++)
    for(int j=1;j<=k;j++)
         if(Tabla[i][j]==spatiu)return (k*(i-1)+j);
         return 0;
}
void MutaOm2(char culoare1)
{
    int ok=1,cas,a,b;
    cas=CasutaLibera();
    a=(cas-1)/k+1; b=(cas-1)%k+1;

    while(ok){


        GetCursorPos(&cursorPosition);
        mX=cursorPosition.x;
        mY=cursorPosition.y;
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN2(mX,mY,cordX[a][b-1],cordY[a][b-1])&&Tabla[a][b-1]==culoare1){ MutaOm3(culoare1,3);ok=0;}
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN2(mX,mY,cordX[a][b+1],cordY[a][b+1])&&Tabla[a][b+1]==culoare1){ MutaOm3(culoare1,4);ok=0;}
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN2(mX,mY,cordX[a-1][b],cordY[a-1][b])&&Tabla[a-1][b]==culoare1){ MutaOm3(culoare1,2);ok=0;}
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN2(mX,mY,cordX[a+1][b],cordY[a+1][b])&&Tabla[a+1][b]==culoare1){ MutaOm3(culoare1,1);ok=0;}
  }
/*dreapta stanga =1
stanga dreapta=2
 sus jos=3
 jos sus=4*/
}
int EsteGata(char culoare)
{
    int cas;
    cas=casutalibera2();
    is=(cas-1)/k+1; js=(cas-1)%k+1;

 char t=culoare;

 for(int i=1;i<=k;i++)
{ Tabla[i][k+1]=t;
  Tabla[i][0]=t;
  Tabla[0][i]=t;
  Tabla[k+1][i]=t;
}


return ((Tabla[is-1][js]==culoare) && (Tabla[is+1][js]==culoare)&&(Tabla[is][js-1]==culoare) && (Tabla[is][js+1]==culoare));
 }

 void who(char culoare,int nr)
{
     setbkcolor(CYAN);
     setcolor(culoare);
     char py[25];

     if(nr==1)strcpy(py,"player 1");
     else   if(nr==2) strcpy(py,"player 2");
 else   if(nr==3) strcpy(py,"player 1 won");
  else    strcpy(py,"player 2 won");
     outtextxy(800,35,py);


}
void incepejoc()
{
    if(k>10)lat=40;
    legatura(k);

 OpenGraph(); setbkcolor(BLUE); setfillstyle(9,LIGHTGREEN);
 bar(30,65,getmaxx()-30,getmaxy()-65);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
 settextjustify(CENTER_TEXT,CENTER_TEXT);
 setcolor(CYAN); outtextxy(320,35,"ALUNECATOARELE");
 InitTabla(); DesTabla();
 setfillstyle(SOLID_FILL,CYAN);

 int yu=0;
  do {
        //incepi primul
        if(modJoc==1)
            {
        who(culoare1,1);     if(mouse) MutaOm2(culoare1); else MutaOm(culoare1);  who(culoare2,2);  delay(300);  MutaCalc();
            }
        else
           //incepe calc meciul
            if(modJoc==2)
            {
       if(yu==0)delay(300),yu=4;  who(culoare1,1);    delay(300);    MutaCalc1(culoare1);   who(culoare2,2);   if(!EsteGata(culoare1))if(mouse) MutaOm2(culoare2); else MutaOm(culoare2);
            }

        else
            if(modJoc==3)
            {
          who(culoare1,1);     if(mouse) MutaOm2(culoare1); else MutaOm(culoare1); who(culoare2,2);delay(300); if(!EsteGata(culoare1))  MutaCalc1(culoare2);
        }
        //om vs om
        else if(modJoc==4)
        {
         who(culoare1,1);  if(mouse) MutaOm2(culoare1); else MutaOm(culoare1);   who(culoare2,2); delay(300); if(!EsteGata(culoare1))  if(mouse) MutaOm2(culoare2); else MutaOm(culoare2);
        }
         else if(modJoc==5)
        {
         who(culoare1,1); delay(500);    MutaCalc1(culoare1);     who(culoare2,2); delay(500); if(!EsteGata(culoare1))   MutaCalc1(culoare2);
        }
 } while (!EsteGata(culoare1)&&!EsteGata(culoare2));

 if(EsteGata(culoare1))
 who(culoare1,3);
 else  who(culoare2,4);
 getch();
 closegraph();
saIncepem();

}

//////
//meniu//

void stergechenar(int a,int b)
{
     setfillstyle(SOLID_FILL,BLACK);
     bar(b-10,a-10,b+280,a+800);
     setfillstyle(SOLID_FILL,GREEN);
}
void desChenar(int a,int b,char text[])
{
 stergechenar(a,b);

 setcolor(CYAN);
 bar(b,a,b+100,a+50);
 settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
 setcolor(CYAN); outtextxy(b+b/5,a+18,text);
}
void linie(int a,int b,int c,int d)
{
    setcolor(BLACK);
    line(a,b,c,d);
}
void colorJ2(int meniu3)
{
    desChenar(a,V+300,"RED");
    desChenar(b,V+300,"GREEN");
    desChenar(c,V+300,"BLUE");
    desChenar(d,V+300,"YELLOW");
    desChenar(e,V+300,"WHITE");
    if(culoareblocata1==1&&meniu3==2) linie(V+300,a,V+400,a+50);
    if(culoareblocata1==2&&meniu3==2)linie(V+300,b,V+400,b+50);
    if(culoareblocata1==3&&meniu3==2)linie(V+300,c,V+400,c+50);
    if(culoareblocata1==4&&meniu3==2)linie(V+300,d,V+400,d+50);
    if(culoareblocata1==5&&meniu3==2)linie(V+300,e,V+400,e+50);

    if(culoareblocata2==1&&meniu3==1) linie(V+300,a,V+400,a+50);
    if(culoareblocata2==2&&meniu3==1)linie(V+300,b,V+400,b+50);
    if(culoareblocata2==3&&meniu3==1)linie(V+300,c,V+400,c+50);
    if(culoareblocata2==4&&meniu3==1)linie(V+300,d,V+400,d+50);
    if(culoareblocata2==5&&meniu3==1)linie(V+300,e,V+400,e+50);
}
void sizeJ()
{
    desChenar(a,V+150,"5");
    desChenar(b,V+150,"7");
    desChenar(c,V+150,"9");
    desChenar(d,V+150,"11");
    desChenar(e,V+150,"13");
}
void colorJ()
{
    desChenar(a,V+150,"FIRST");
    desChenar(b,V+150,"SECOND");

}
void mode()
{
    desChenar(a,V+150,"1vsPC");
    desChenar(b,V+150,"1vsPC2");
    desChenar(c,V+150,"PCvs1");
    desChenar(d,V+150,"1vs1");
    desChenar(e,V+150,"PCvsPC");
}
void start()
{
    desChenar(a,V,"MODE");
    desChenar(b,V,"COLORS");
    desChenar(c,V,"SIZE");
    desChenar(d,V,"START");
    desChenar(e,V,"MOUSE");
    desChenar(f,V,"EXIT");

}
void modtext()
{settextstyle(DEFAULT_FONT,HORIZ_DIR,3);

     outtextxy(750,470,"MOD:");
     outtextxy(910,470,mod);
}

void textsize()
{
 settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
 outtextxy(760,405,"SIZE:");
 outtextxy(880,405,numarpatrat);
}
void desChenar3(int a,int b,char culoare)
{
 setfillstyle(SOLID_FILL,culoare);
 bar(b,a,b+50,a+50);
}
void culoare()
{

  desChenar3(500,940,culoare1);
  desChenar3(560,940,culoare2);

}


void  saIncepem()
{
    DWORD screenWidth=GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight=GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenWidth,screenHeight,"",-3,-3);

 POINT cursorPosition;
 int mX,mY;

 start();
lat=60;
 settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
 settextjustify(CENTER_TEXT,CENTER_TEXT);
 setcolor(CYAN); outtextxy(320,35,"ALUNECATOARELE");

 settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
 outtextxy(780,535,"color 1");
 outtextxy(780,600,"color 2");

 if(mouse!=1)outtextxy(800,340,"KEYBOARD");
 else outtextxy(800,340,"   MOUSE   ");

 culoare();
 textsize();
 modtext();

 setfillstyle(SOLID_FILL,GREEN);
 int meniu2=0,meniu3=0,stop=1;

    while(stop)
    {
        GetCursorPos(&cursorPosition);
        mX=cursorPosition.x;
        mY=cursorPosition.y;
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V,a))mode(),meniu2=1,meniu3=0;//V=y,a=x
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V,b))colorJ(),meniu2=2,meniu3=0;
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V,c))sizeJ(),meniu2=3,meniu3=0;
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V,d))incepejoc(),meniu3=0,stop=0;//start
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V,e)){setcolor(CYAN); settextstyle(DEFAULT_FONT,HORIZ_DIR,3);if(mouse==1)mouse=0,outtextxy(800,340,"KEYBOARD");else mouse=1,outtextxy(800,340,"   MOUSE   ");}
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V,f)) closegraph(),stop=0 , exit(1);//end
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+150,a)&&meniu2==2)colorJ2(1),meniu3=1;
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+150,b)&&meniu2==2)colorJ2(2),meniu3=2;

        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+150,a)&&meniu2==1)strcpy(mod," 1vsPC "),modtext(),meniu3=0,modJoc=1;
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+150,b)&&meniu2==1)strcpy(mod," 1vsPC2 "),modtext(),meniu3=0,modJoc=3;
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+150,c)&&meniu2==1)strcpy(mod," PCvs1 "),modtext(),meniu3=0,modJoc=2;
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+150,d)&&meniu2==1)strcpy(mod,"  1vs1   "),modtext(),meniu3=0,modJoc=4;
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+150,e)&&meniu2==1)strcpy(mod,"  PCvsPC  "),modtext(),meniu3=0,modJoc=5;

        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+150,a)&&meniu2==3) k=5,strcpy(numarpatrat," 5 "),textsize();
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+150,b)&&meniu2==3)k=7,strcpy(numarpatrat," 7 "),textsize();
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+150,c)&&meniu2==3) k=9,strcpy(numarpatrat," 9 "),textsize();
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+150,d)&&meniu2==3) k=11,strcpy(numarpatrat," 11 "),textsize();
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+150,e)&&meniu2==3) k=13,strcpy(numarpatrat," 13 "),textsize();

        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+300,a)&&meniu3==1&&culoareblocata2!=1)culoareblocata1=1,culoare1=RED,culoare();
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+300,b)&&meniu3==1&&culoareblocata2!=2)culoareblocata1=2,culoare1=GREEN,culoare();
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+300,c)&&meniu3==1&&culoareblocata2!=3)culoareblocata1=3,culoare1=BLUE,culoare();
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+300,d)&&meniu3==1&&culoareblocata2!=4)culoareblocata1=4,culoare1=YELLOW,culoare();
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+300,e)&&meniu3==1&&culoareblocata2!=5)culoareblocata1=5,culoare1=WHITE,culoare();

        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+300,a)&&meniu3==2&&culoareblocata1!=1)culoareblocata2=1,culoare2=RED,culoare();
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+300,b)&&meniu3==2&&culoareblocata1!=2)culoareblocata2=2,culoare2=GREEN,culoare();
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+300,c)&&meniu3==2&&culoareblocata1!=3)culoareblocata2=3,culoare2=BLUE,culoare();
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+300,d)&&meniu3==2&&culoareblocata1!=4)culoareblocata2=4,culoare2=YELLOW,culoare();
        if(GetAsyncKeyState(VK_LBUTTON)&&chenarIN(mX,mY,V+300,e)&&meniu3==2&&culoareblocata1!=5)culoareblocata2=5,culoare2=WHITE,culoare();


        delay(100);

    }


}
int main()
{
saIncepem();
 return 0;
 }
