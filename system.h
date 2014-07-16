#ifndef SYSTEM
#define SYSTEM

#include <GL/glut.h>

// field
typedef struct {
    double x;  // サイズ
    double y;  // 
    double e;  // ビー玉との反発係数
} field_t;

// physics
#define GRAVITY 1.0  //9.8
#define PI 3.14
/*
   v = v0 + at
   x = v0t + 0.5at^2
   v^2 - v0^2 = 2ax
 */



// prototype define
void xyzAxes(double length);
void myInit(char *progname);
void myReshape(int width, int height);
void exchange(double* a, double* b);
double displacement(double v0, double a, double t);
double velocity(double v0, double a, double t);
double acceleration(double theta);
double theta(double x1, double y1, double x2, double y2);
double toDegree(double rad);
void polarView(double posX, double posY, double posZ, double distance, double twist, double elevation, double azimuth);

#endif
