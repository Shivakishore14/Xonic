#include<stdlib.h>
#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
int X,Y,n=5,whex=-10,points=0,gtime=0,whey=-10,ek=0,whxx=-10,whxy=-10,ran,gx=-25,gy=-25,t,z=0,gmode=0;
float T=0,hsc=0;
void reset()
{
n=5,whex=-10,points=0,gtime=0,whey=-10,ek=0,whxx=-10,whxy=-10,ran,gx=-25,gy=-25,z=0,gmode=0,T=0,hsc=0;
}
struct hscore
{
 char name[20];
 float pt;
}cscore,nscore;
char* getcurrent(float *a)
{
 FILE *f;
 f=fopen("score.dat","rb");
 if(f==NULL)
 {
  *a=0;
  fclose(f);
  return NULL;
 }
 fread(&cscore,sizeof(struct hscore),1,f);
 *a=cscore.pt;
 fclose(f);
 return cscore.name;
}

int getnew()
{
 FILE *f;
 char ch,*p1,l=0;
 int pt[]={X/2-150,Y/2-60,X/2+150,Y/2-60,X/2+150,Y/2+60,X/2-150,Y/2+60},i=10,p[] = { X/2-50,Y/2, X/2+50,Y/2, X/2+50,Y/2+30, X/2-50,Y/2+30};
 setcolor(RED);
 setfillstyle(9,RED);
 fillpoly(4,pt);
 setcolor(WHITE);
 outtextxy(260,200,"enter your name");
 setcolor(GREEN);
 setfillstyle(1,BLACK);
 fillpoly(4,p);
 while((int)(ch=getch())!=13)
 {
  if(l<12)
  {
   *p1=ch;
   cscore.name[l++]=ch;
   *(p1+1)='\0';
   outtextxy(X/2-55+i,Y/2+10,p1);
   i+=8;
  }
 }
 cscore.name[l]='\0';
 cscore.pt=points;
 f=fopen("score.dat","wb");
 if(f==NULL)
 {
   fclose(f);
   cscore.pt=0;
   strcpy(cscore.name,"none");
   return 0;
 }
 fwrite(&cscore,sizeof(struct hscore),1,f);
 fclose(f);
 return 1;
 }
void disp()
{
 char c[4];
 moveto(400,100);
 settextstyle(0,0,1);
 setcolor(GREEN);
 outtext(getcurrent(&hsc));
 sprintf(c,"%d",(int)hsc);
 outtext(" : ");
 outtext(c);
}



void killed()
{
 if(points>(int)hsc)
  getnew();
 getch();
 exit(0);
}
int outerbox(a)
{
 line(a,a+10,X-a,a+10);
 line(X-a,a+10,X-a,Y-a);
 line(a,Y-a,a,a+10);
 line(X-a,Y-a,a,Y-a);
 return 1;
}

int pixelbox(int x, int y,int c)
{
 int a,b;
 for(a=x-2;a<x+3;a++)
  for(b=y-2;b<y+3;b++)
   if(a!=0 && b!=0)
    putpixel(a,b,c);
 return 1;
}
int deletepixel(int x, int y)
{ int a,b;
 for(a=x-2;a<x+3;a++)
  for(b=y-2;b<y+3;b++)
   putpixel(a,b,0);
   return 1;
}
void box(int x, int y,int r,int c)
{  int i,j;
  for(i=x-r;i<=x+r;i++)
  {
   for(j=y-r;j<=y+r;j++)
    putpixel(i,j,c);
  }
}
void gbox(int n)
{ int i,j,c=5,x=X-60;
 for(i=x;i<x+41;i++)
 {
  for(j=3;j<=13;j++)
  { if((i==x||i==x+40)||(j==3||j==13))
     c=RED;
    else if(i<x+41-4*n)
     c=GREEN;
    else
    c=0;
   putpixel(i,j,c);
  }
 }
}
int godmode(int x,int y)
{
   int k=4,pt[]={10,10,100,100};
   moveto(X-90,4);
   setcolor(GREEN);
   outtext("GOD:");

  if(gmode==1 && gtime+10>=T)
  {
   gbox((int)T-gtime);
   return 1;
  }
   if((int)T==ran)
     { gmode=0;
       box(gx,gy,k,BLACK);
       gx=rand()%600+20,gy=rand()%390+30;
       box(gx,gy,k,BLACK);
       t=T;
       ran=T+rand()%30;
       box(gx,gy,k,RED);
     }
   if((int)T>t+11)
    {
     gmode=0;
     return 0;
    }
   if((int)T<t+10)
    {
     if(gmode==0)
     {
      moveto(gx-3,gy-3);
      box(gx,gy,k,RED);
      outtext("G");
     }
     else
      return 1;
    }
   if((int)T==t+10)
   {
     box(gx,gy,k,BLACK);
   }
   if(abs(gx-x)<k+2 && abs(gy-y)<k+2)
   {
     gmode=1;
     gtime=T;
     box(gx,gy,k,BLACK);
   }
}
void hm()
{
union REGS i,o;
i.x.ax=2;
int86(0x33,&i,&o);
}
void sm()
{
union REGS i,o;
i.x.ax=1;
int86(0x33,&i,&o);
}
void gmb(int *b,int *x,int *y)
{
union REGS i,o;
i.x.ax=3;
int86(0x33,&i,&o);
*b=o.x.bx;
*x=o.x.cx;
*y=o.x.dx;
}
void menu1()
{
  int exit[]={20,Y-90,200,Y-90,200,Y-40,20,Y-40},start[]={380,Y-90,560,Y-90,560,Y-40,380,Y-40};
  setcolor(RED);
  fillpoly(4,exit);
  fillpoly(4,start);
  settextstyle(0,0,3);
  outtextxy(45,Y-70,"EXIT");
  outtextxy(405,Y-70,"START");
}
void menu2()
{
 int p,q,p1[]={50,50,560,50,560,200,50,200,50,50},p2[]={50,250,560,250,560,400,50,400,50,250};
  setcolor(GREEN);
  drawpoly(5,p1);
  drawpoly(5,p2);
  settextstyle(0,0,2);
//  floodfill(100,100,RED);
  setcolor(RED);
  outtextxy(100,100,"Control one player");
  outtextxy(100,300,"Control two player");
   //Ip
   p=480,q=100;
   setcolor(BLUE);
   moveto(p,q);
   outtext("w");
   moveto(p-30,q+30);
   outtext("a");
   moveto(p,q+30);
   outtext("s");
   moveto(p+30,q+30);
   outtext("d");
   pixelbox(X/2-50,Y/2-10,GREEN);
   pixelbox(X/2+50,Y/2-10,GREEN);
   line(p,q+50,X/2-50,Y/2-10);
   //2p
    p=480,q=300;
   line(p,q-33,X/2+50,Y/2-10);
   setcolor(BLUE);
   moveto(p,q);
   outtext("i");
   moveto(p-30,q+30);
   outtext("j");
   moveto(p,q+30);
   outtext("k");
   moveto(p+30,q+30);
   outtext("l");
   settextstyle(0,0,1);
   outtextxy(p-100,q-30,"control of 2nd player " );
   outtextxy(380,70,"control of 1st player " );
}
int animate()
{
 int l=0,i,p=10,q=180,a=10,b=210,gx=10,gy=240,ex=10,ey=265,yx=10,yy=290,mb,mx,my;

 char *x="Xonic";
 setcolor(RED);
 settextstyle(0,0,9);
 moveto(100,5);
 outtext(x);
 box(p,q,9,WHITE);
 for(i=0;i<13;i++)
  {

   if(i<10)
     {
       setcolor(i);
       circle(p,q,i);
     }
  else
    {
      setcolor(BLACK);
      circle(p,q,i);
    }
  }
   for(int j=0;j<10;j++)
  {
   setcolor(j);
   circle(a,b,10-j);
  }
   settextstyle(0,0,0);
   setcolor(GREEN);
   moveto(gx-3,gy-3);
   box(gx,gy,4,RED);
   outtext("G");

   pixelbox(yx,yy,GREEN);
   pixelbox(ex,ey,1);
  //text
   moveto(p+20,q-4);
   outtext(":  wormhole enterance");
   moveto(a+20,b-4);
   outtext(":  wormhole exit");
   moveto(gx+20,gy-4);
   outtext(":  god mode");
   moveto(yx+20,yy-4);
   outtext(":  your player");
   moveto(ex+20,ey-4);
   outtext(":  enemy player");
   settextstyle(0,0,2);
   moveto(p+400,q-30);
   setcolor(RED);
   outtext("tips");
   setcolor(BLUE);
   settextstyle(0,0,0);
   moveto(p+300,q);
   outtext("you die if enemy touches you");
   moveto(p+300,q+15);
   outtext("survive as long as possible");
   moveto(p+300,q+30);
   outtext("Take godemode and destroy your enemy");
   moveto(p+300,q+45);
   outtext("use wormhole to take shortcuts");
   moveto(p+300,q+60);
   outtext("dont touch outerwall at normal mode");
   setcolor(RED);
   settextstyle(0,0,2);
   moveto(p+350,q+100);
   outtext("controls");
   setcolor(BLUE);
   moveto(p+400,q+130);
   outtext("w");
   moveto(p+370,q+160);
   outtext("a");
   moveto(p+400,q+160);
   outtext("s");
   moveto(p+430,q+160);
   outtext("d");
   disp();
   settextstyle(0,0,0);
   sm();
   gmb(&mb,&mx,&my);
   menu1();
   while(1)
   {
     gmb(&mb,&mx,&my);
     if(l==0)
     {
      l=1;
      menu1();
     }
     if(mb==1||mb==2)
     {
      if(my>390 && my<440)
       if(mx>382 && mx<560)
	break;
      if( mx>21 && mx<198)
      {
	hm();
	return 0;
      }

     }
   }
   delay(60);
   cleardevice();
   l=0;
   i=mx;
   menu2();
   while(1)
   {
     gmb(&mb,&mx,&my);
      if(l==0&&i-mx>15)
     {
      l=1;
      cleardevice();
      menu2();
     }
     if(mb==1||mb==2)
     {
      if(mx>50 && mx<560)
       if(my>50 && my<200)
       {
	hm();
	return 1;
       }
      if( my>250 && my<400)
       {
	hm();
	return 2;
       }
     }
   }

   getch();

   return 1;
}

int outside(int x,int y,int a)
{  a+=3;
 if(x<a||x>X-a||y<a+10||y>Y-a)
 {
  return 1;
 }

 return 0;
}
int follow1(int *a,int *b,int x,int y,int x1,int y1,int k)
{
 int c,c1,w=x-*a,v=y-*b,px=*a,py=*b,sx,sy,hx[]={20,X-20,20,X-20},hy[]={30,30,Y-20,Y-20};
 int max=3600,min=-3600,mx=*a,my=*b,i,j,p=*a,o,q=*b,g=x,h=y;
 //float m=(float)v/w;
 //c=10-m*(10);
 //q=m*(++p)+c;
 //*a=p,*b=q;
 if(godmode(x,y)==1)
 {
  for(i=0;i<4;i++)
  {
      c=abs(hx[i]-p)+abs(hy[i]-q);
      if(c<max)
      {
	max=c;
	sx=hx[i];
	sy=hy[i];
      }
  }
  max=3600;
  x=sx,y=sy;
 }
 for(i=-k;i<=k;i++)
 {
  for(j=-k;j<=k && (abs(j)==k || abs(i)==k) ;j++)
  {
    p=*a+i;o=*b+j;
    c=abs(x-p)+abs(y-o);
    c1=abs(x1-p)+abs(y1-o);
    if(c1<c)
     c=c1;
     if(max>c)
     {
      max=c;
      mx=*a+i;
      my=*b+j;
     }
   }
  }
 *a=mx;
 *b=my;

  if((abs(*a-g)<4 && abs(*b-h)<4)||(abs(*a-x1)<4 && abs(*b-y1)<4))
  {
   if(gmode==0 )
    return -1;
   else
    return 0;
   }
  deletepixel(px,py);
  pixelbox(*a,*b,1);
 return 1;
}
int follow(int *a,int *b,int x,int y,int k)
{
 int c,w=x-*a,v=y-*b,px=*a,py=*b,sx,sy,hx[]={20,X-20,20,X-20},hy[]={30,30,Y-20,Y-20};
 int max=3600,min=-3600,mx=*a,my=*b,i,j,p=*a,o,q=*b,g=x,h=y;
 if(godmode(x,y)==1)
 {
  for(i=0;i<4;i++)
  {
      c=abs(hx[i]-p)+abs(hy[i]-q);
      if(c<max)
      {
	max=c;
	sx=hx[i];
	sy=hy[i];
      }
  }
  max=3600;
  x=sx,y=sy;
 }
 for(i=-k;i<=k;i++)
 {
  for(j=-k;j<=k && (abs(j)==k || abs(i)==k) ;j++)
  {
    p=*a+i;o=*b+j;
    c=abs(x-p)+abs(y-o);
     if(max>c)
     {
      max=c;
      mx=*a+i;
      my=*b+j;
     }
   }
  }
 *a=mx;
 *b=my;

  if(abs(*a-g)<4 && abs(*b-h)<4)
  {
   if(gmode==0 )
    return -1;
   else
    return 0;
   }
  // return 0;
  deletepixel(px,py);
  pixelbox(*a,*b,1);
 return 1;
}
int death(int x,int y)
{
  int p,q;
  for(int i=0;i<10;i++)
  {
   setcolor(i);
   circle(p,q,i);
  }
  if(abs(p-x)<9 && abs(q-y)<9)
   {
    return 1;
   }
}
void delwormhole(int x,int y)
{
 for(int i=0;i<10;i++)
  {
   setcolor(BLACK);
   circle(x,y,i);
  }
}
void wormhole1(int *l,int *m,int *l1,int *m1,int c)
{
int x=*l,y=*m,x1=*l1,y1=*m1,a,b,p,q;
if(c==0)
  a=whex,b=whey,p=whxx,q=whxy;
else
  {
  delwormhole(whex,whey);
  delwormhole(whxx,whxy);
  box(whxx,whxy,12,BLACK);
  a=rand()%600+20,b=rand()%390+30,p=rand()%600+20,q=rand()%390+30,p++;
  whex=a,whey=b,whxx=p,whxy=q;
  }
//  if(abs(p-x)<13 && abs(q-y)<13&&((p+9)||(p-9))!=x&&((q+9)||(q-9))!=y)
//   {   deletepixel(x,y);   }
box(p,q,9,WHITE);
 for(int i=0;i<13;i++)
  {

   if(i<10)
     {
       setcolor(i);
       circle(p,q,i);
     }
  else
    {
      setcolor(BLACK);
      circle(p,q,i);
    }
  }
   for(int j=0;j<10;j++)
  {
   setcolor(j);
   circle(a,b,10-j);
  }
  if(abs(p-x)<9 && abs(q-y)<9)
   {
    x=a,y=b,z=1;
    *l=x,*m=y;
   }
  if(abs(p-x1)<9 && abs(q-y1)<9)
   {
    x1=a,y1=b,z=1;
    *l1=x1,*m=y1;
   }
  if(z==1)
  {
   if(!(abs(a-x)<12 && abs(b-y)<12))
    {
     delwormhole(whex,whey);
     whex=rand()%600+20,whey=rand()%390+30;
     z=0;
    }
   }
}

void wormhole(int *l,int *m,int c)
{
int x=*l,y=*m,a,b,p,q;
if(c==0)
  a=whex,b=whey,p=whxx,q=whxy;
else
  {
  delwormhole(whex,whey);
  delwormhole(whxx,whxy);
  box(whxx,whxy,12,BLACK);
  a=rand()%600+20,b=rand()%390+30,p=rand()%600+20,q=rand()%390+30,p++;
  whex=a,whey=b,whxx=p,whxy=q;
  }
//  if(abs(p-x)<13 && abs(q-y)<13&&((p+9)||(p-9))!=x&&((q+9)||(q-9))!=y)
//   {   deletepixel(x,y);   }
box(p,q,9,WHITE);
 for(int i=0;i<13;i++)
  {

   if(i<10)
     {
       setcolor(i);
       circle(p,q,i);
     }
  else
    {
      setcolor(BLACK);
      circle(p,q,i);
    }
  }
   for(int j=0;j<10;j++)
  {
   setcolor(j);
   circle(a,b,10-j);
  }
  if(abs(p-x)<9 && abs(q-y)<9)
   {
    x=a,y=b,z=1;
   }
  if(z==1)
  {
   if(!(abs(a-x)<12 && abs(b-y)<12))
    {
     delwormhole(whex,whey);
     whex=rand()%600+20,whey=rand()%390+30;
     z=0;
    }
   }

   *l=x,*m=y;
}
void you(int *q,int *w,char c,int s)
{  int x=*q,y=*w;
   int a=x,b=y;
  // deletepixel(a,b);
  switch(c)
   {
    case 'i':
    case 'w':y-=s;break;
    case 'k':
    case 's':y+=s;break;
    case 'j':
    case 'a':x-=s;break;
    case 'l':
    case 'd':x+=s;break;
    case 'q':exit(0);
   }
    if(!(godmode(x,y)==1 && outside(x,y,10)))
   if( !((x<31&&y<41)||(x>X-31&&y<41)||(x<31&&y>Y-31)||(x>X-31&&y>Y-31)) )
   {

    *q=x,*w=y;
    deletepixel(a,b);
    pixelbox(x,y,GREEN);
    if(godmode(x,y)==1)
     pixelbox(x,y,RED);
    else
     gbox(10);
    }
  }

void formhouse()
{
 int p1[]={10,20,10,40,30,40,30,20},p2[]={X-10,Y-10,X-10,Y-30,X-30,Y-30,X-30,Y-10},p3[]={X-10,20,X-10,40,X-30,40,X-30,20},p4[]={10,Y-10,10,Y-30,30,Y-30,30,Y-10};
 setcolor(WHITE);
 drawpoly(4,p1);
 drawpoly(4,p2);
 drawpoly(4,p3);
 drawpoly(4,p4);
}
void main()
{
 char c=0,sa[3],si[2],c0=0,c1=0,*dis;
 int gd=DETECT,gm,m,fol;
 initgraph(&gd,&gm,"C:\\tc\\bgi");
 X=getmaxx();
 Y=getmaxy();
 int s=3,uc=1,im=1,x,y,e1x=20,e1y=30,e2x=X-20,e2y=Y-20,e3x=X-20,e3y=30,e4x=20,e4y=Y-20,s1=1,s2=2,s3=1,s4=1,x1,y1;
 x=X/2;
 y=Y/2;
 again:
   c=0,c0=0,c1=0,s=3,uc=1,im=1,e1x=20,e1y=30,e2x=X-20,e2y=Y-20,e3x=X-20,e3y=30,e4x=20,e4y=Y-20,s1=1,s2=2,s3=1,s4=1;
    reset();
uc= animate();
 if (uc==0)
  exit(0);
 outerbox(10);
 gbox(10);
 ran=rand()%10;
 cleardevice();
 graphdefaults();
 if(uc==1)
 while(!outside(x,y,10)|| s==5)
 {
  points=T+ek*10;
  outerbox(10);
  if(T<200)
  m=T/5;
  delay(50-m);
  s=3;
  if(godmode(x,y)==1)
   s=5;
  if(kbhit())
  {
   c=getch();
   you(&x,&y,c,s);
  }
  else
  {
   you(&x,&y,c,s);
  }
  if(T>n)
   wormhole(&x,&y,1),n*=T;
  else
   wormhole(&x,&y,0);
// if(abs(e1x-e2x)<4 && abs(e2y-e1x)<4)
//    e2x=X-20,e2y=30;
 fol=follow(&e1x,&e1y,x,y,s1);
 if (fol==-1)
  goto dead;
  if(fol==0)
  {
    //box(e1x,e2y,10,BLACK);
    box(200,4,10,BLACK);
    e1x=20,e1y=30;
    ek++;
    box(x,y,5,BLACK);
  }
  if((int)T==5)
   s1=2;
 if(T>15)
  {
    fol= follow(&e2x,&e2y,x,y,s2);
   if (fol==-1)
  goto dead;
   if(abs(e1x-e2x)<4 && abs(e2y-e1y)<4 ||fol==0)
    {
    box(e2x,e2y,10,BLACK);
     e2x=X-20,e2y=30;
     ek++;
     box(200,4,10,BLACK);
      box(x,y,5,BLACK);
     }

  }
 if(T>25)
 {
   s2=2;

 fol=follow(&e3x,&e3y,x,y,s3);
    if (fol==-1)
  goto dead;
   if((abs(e3x-e2x)<4 && abs(e2y-e3y)<4)||(abs(e3x-e1x)<4 && abs(e1y-e3y)<4) || fol==0)
    {
    box(e3x,e3y,10,BLACK);
    e3x=X-20,e3y=Y-20;
    ek++;
    box(200,4,10,BLACK);
     box(x,y,5,BLACK);
    }
  }
 if(T>35)
 {     s3=2;
  fol=follow(&e4x,&e4y,x,y,s1);
   if (fol==-1)
  goto dead;
  if( (abs(e3x-e4x)<4 && abs(e4y-e3y)<4) || (abs(e4x-e1x)<4 && abs(e1y-e4y)<4) || (abs(e4x-e2x)<4 && abs(e2y-e4y)<4) || fol==0)
   {
   box(e4x,e4y,10,BLACK);
   e4x=20,e4y=Y-20;
   ek++;
   box(200,4,10,BLACK);
    box(x,y,5,BLACK);
   }
 }
// if(gmode==1)  putpixel(100,100,RED); else  putpixel(100,100,WHITE);
 if((int)T==40)
  s4=2;
 T=T+0.05;
 cout<<"\r\r"<<points;
  sprintf(sa,"%d",(int)ek);
    sprintf(si,"%c",(int)im);

  outtextxy(180,4,si);
  outtextxy(200,4,sa);

if(godmode(x,y)==0)
  gmode=0;
formhouse();
}
else
{
 x=X/2-50;
 y=Y/2;
  x1=X/2+50;
 y1=Y/2;

 while(!outside(x,y,10)&&!outside(x1,y1,10)|| s==5)
 {
  points=T+ek*10;
  outerbox(10);
  if(T<200)
  m=T/5;
  delay(50-m);
  s=3;
  if(godmode(x,y)==1)
   s=5;
  if(kbhit())
  {
   c=getch();
   if(c=='w'||c=='s'||c=='d'||c=='a')
   {
    c0=c;
    you(&x,&y,c0,s);
   }
   else
   {
    you(&x1,&y1,c,s);
    c1=c;
    goto br;
    }
  }
  else
  {
   br:
   you(&x,&y,c0,s);
   you(&x1,&y1,c1,s);
  }
  if(T>n)
   wormhole1(&x,&y,&x1,&y1,1),n*=T;
  else
   wormhole1(&x,&y,&x1,&y1,0);
// if(abs(e1x-e2x)<4 && abs(e2y-e1x)<4)
//    e2x=X-20,e2y=30;
fol=follow1(&e1x,&e1y,x,y,x1,y1,s1);
if (fol==-1)
  goto dead;
  if(fol==0)
  {
    //box(e1x,e2y,10,BLACK);
    box(200,4,10,BLACK);
    e1x=20,e1y=30;
    ek++;
    box(x,y,5,BLACK);
      box(x1,y1,5,BLACK);
  }
  if((int)T==5)
   s1=2;
 if(T>15)
  {
  fol=follow1(&e2x,&e2y,x,y,x1,y1,s2);
  if (fol==-1)
  goto dead;

   if(abs(e1x-e2x)<4 && abs(e2y-e1y)<4 || fol==0)
    {
    box(e2x,e2y,10,BLACK);
     e2x=X-20,e2y=30;
     ek++;
     box(200,4,10,BLACK);
      box(x,y,5,BLACK);
	box(x1,y1,5,BLACK);
     }

  }
 if(T>25)
 {   s2=2;
 fol=follow1(&e3x,&e3y,x,y,x1,y1,s3);
 if (fol==-1)
  goto dead;

   if((abs(e3x-e2x)<4 && abs(e2y-e3y)<4)||(abs(e3x-e1x)<4 && abs(e1y-e3y)<4) || fol==0)
    {
    box(e3x,e3y,10,BLACK);
    e3x=X-20,e3y=Y-20;
    ek++;
    box(200,4,10,BLACK);
     box(x,y,5,BLACK);
     box(x1,y1,5,BLACK);
    }
  }
 if(T>35)
 {     s3=2;
   fol= follow1(&e4x,&e4y,x,y,x1,y1,s1);
 if (fol==-1)
  goto dead;

  if( (abs(e3x-e4x)<4 && abs(e4y-e3y)<4) || (abs(e4x-e1x)<4 && abs(e1y-e4y)<4) || (abs(e4x-e2x)<4 && abs(e2y-e4y)<4) ||fol==0)
   {
   box(e4x,e4y,10,BLACK);
   e4x=20,e4y=Y-20;
   ek++;
   box(200,4,10,BLACK);
    box(x,y,5,BLACK);
      box(x1,y1,5,BLACK);
   }
 }
// if(gmode==1)  putpixel(100,100,RED); else  putpixel(100,100,WHITE);
 if((int)T==40)
  s4=2;
 T=T+0.05;
 cout<<"\r\r"<<points;
  sprintf(sa,"%d",(int)ek);
    sprintf(si,"%c",(int)im);

  outtextxy(180,4,si);
  outtextxy(200,4,sa);

if(godmode(x,y)==0)
  gmode=0;
formhouse();
}
} dead:
  cleardevice();
  sprintf(dis,"your score is %d",points);
  outtextxy(X/2-50,Y/2,dis);
  outtextxy(X/2-50,Y/2+10,"Play Again(Y/N)");
  if(getch()=='y')
   goto again;
  delay(100);
  killed();
  closegraph();
}
