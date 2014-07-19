#ifndef SYSTEM
#define SYSTEM

#include <GL/glut.h>

// 3D座標
typedef struct{
    double x, y, z;
} vertex_t;

// field
typedef struct {
    double x;  // サイズ
    double y;  // 
    double e;  // ビー玉との反発係数
} field_t;

// physics
#define GRAVITY 0.5  //9.8
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
int isIntersected( double sx1, double sy1, double sz1, double ex1, double ey1, double ez1,
                   double sx2, double sy2, double sz2, double ex2, double ey2, double ez2);
double distVertex(vertex_t a, vertex_t b);
int intersect_lines(vertex_t* resultAB, vertex_t *resultCD, 
                    vertex_t A, vertex_t B, vertex_t C, vertex_t D);
void initVertex(vertex_t *v, double x, double y, double z);

#endif

