#include<GL/glut.h> 
#include<stdio.h> 
double xmin=50,xmax=100,ymin=50,ymax=100; 
double xvmin=200,xvmax=300,yvmin=200,yvmax=300; 
float xc[10],yc[10]; 
int n; 
typedef int outcode; 
const int TOP=8; 
const int BOTTOM=4; 
const int RIGHT=2; 
const int LEFT=1; 
/computing/ assigning region codes to end points of line/ 
outcode ComputeCode(double x, double y) 
{ 
outcode code=0; 
if(y>ymax) 
code|=TOP; 
else if(y<ymin) 
code|=BOTTOM; 
if(x>xmax) 
code|=RIGHT; 
else if(x<xmin) 
code|=LEFT; 
return code; 
} 
void CohenSutherlandLineClipper(double x0,double y0,double x1,double 
y1)
{ 
outcode outcode0,outcode1,outcodeout; 
double x,y; 
bool accept=false,done=false; 
outcode0=ComputeCode(x0,y0); 
outcode1=ComputeCode(x1,y1); 
do 
{ 
if(!(outcode0|outcode1)) 
{
accept=true;
done=true;
} 
else if(outcode0& outcode1)
done=true; 
else 
{ 
outcodeout=outcode0?outcode0:outcode1; 
if(outcodeout&TOP) 
{ 
y=ymax; 
x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
} 
else if(outcodeout&BOTTOM) 
{ 
y=ymin; 
x=x0+(x1-x0)*(ymin-y0)/(y1-y0); 
} 
else if(outcodeout & RIGHT) 
{ 
x=xmax; 
y=y0+(y1-y0)*(xmax-x0)/(x1-x0); 
} 
else
{ 
x=xmin; 
y=y0+(y1-y0)*(xmin-x0)/(x1-x0); 
} 
if(outcodeout==outcode0) 
{ 
x0=x; 
y0=y; 
outcode0=ComputeCode(x0,y0); 
} 
else 
{ 
x1=x; 
y1=y; 
outcode1=ComputeCode(x1,y1); 
} 
} 
}while(done==false); 
if(accept) 
{ 
double sx=(xvmax-xvmin)/(xmax-xmin); 
double sy=(yvmax-yvmin)/(ymax-ymin); 
double vx0=xvmin+(x0-xmin)*sx; 
double vy0=yvmin+(y0-ymin)*sy; 
double vx1=xvmin+(x1-xmin)*sx; 
double vy1=yvmin+(y1-ymin)*sy; 
glColor3f(0.0,0.0,1.0); 
glBegin(GL_LINE_LOOP); 
glVertex2f(xvmin,yvmin); 
glVertex2f(xvmax,yvmin); 
glVertex2f(xvmax,yvmax); 
glVertex2f(xvmin,yvmax); 
glEnd(); 
glColor3f(1.0,0.0,0.0);
glBegin(GL_LINES); 
glVertex2f(vx0,vy0); 
glVertex2f(vx1,vy1); 
glEnd(); 
} 
} 
void display() 
{ 
glClear(GL_COLOR_BUFFER_BIT); 
glColor3f(0.0,1.0,0.0); 
glBegin(GL_LINE_LOOP); 
glVertex2f(xmin,ymin); 
glVertex2f(xmax,ymin); 
glVertex2f(xmax,ymax); 
glVertex2f(xmin,ymax); 
glEnd(); 
glColor3f(1.0,0.0,0.0); 
glBegin(GL_LINES); 
for(int i=0;i<n*2;i=i+2) 
{ 
glVertex2f(xc[i],yc[i]); 
glVertex2f(xc[i+1],yc[i+1]); 
} 
glEnd(); 
for( i=0;i<n*2;i=i+2) 
CohenSutherlandLineClipper(xc[i],yc[i],xc[i+1],yc[i+1]); 
glFlush(); 
} 
void myinit() 
{ 
glClearColor(1.0,1.0,1.0,1.0); 
gluOrtho2D(0.0,499.0,0.0,499.0); 
} 
void main(int argc, char **argv) 
{ 
int c=0; 
printf("Enter the no of lines\n"); 
scanf("%d",&n); 
printf("Enter the co-ordinates of the lines to be clipped\n");
for(int i=0;i<n;i++) 
{ 
printf("\nEnter the co ordinates of line %d\n",i+1); 
for(int j=0;j<2;j++) 
{ 
scanf("%f%f",&xc[c],&yc[c]);c++; 
}
}
glutInit(&argc,argv); 
glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE); 
glutInitWindowPosition(0,0); 
glutInitWindowSize(500,500); 
glutCreateWindow("Cohen-Sutherland Line Clipper"); 
myinit(); 
glutDisplayFunc(display); 
glutMainLoop();
}