#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "system.h"
#include "vector.h"

void xyzAxes(double length)
{
    glBegin(GL_LINES);
    glColor3d(1.0, 1.0, 0.0);	// yellow
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(length, 0.0, 0.0);	//x-axis
    glColor3d(1.0, 0.0, 0.0);	// red
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, length, 0.0);	//y-axis
    glColor3d(0.0, 0.0, 1.0);	// blue
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, 0.0, length);	//z-axis
    glEnd();
}

void myInit(char *progname)
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(progname);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void myReshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -5.0);  // move teapot
}

void polarView(double posX, double posY, double posZ, double distance, double twist, double elevation, double azimuth) {
    /*
       pos[XYZ]: カメラの座標
distance: 回転軸との距離
     */
    glRotated(-twist,      0.0, 0.0, 1.0);  // z軸の回転
    glRotated(-azimuth,  0.0, 1.0, 0.0);  // y
    glRotated(-elevation, 1.0, 0.0, 0.0);  // x
    glTranslated(posX, posY, posZ);
}

void exchange(double* a, double* b){
    double tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

double displacement(double v0, double a, double t){
    /*
       変位
     */
    return (v0*t + 0.5*a*t*t);
}

double velocity(double v0, double a, double t){
    return (v0 + a*t);
}

double acceleration(double theta){
    return (GRAVITY*sin(theta));
}

double theta(double x1, double y1, double x2, double y2){
    // 0 <= theta <= PI [rad]
    double theta = 0;

    // 角(x1, y1)がシータにする
    if(fabs(x2) < fabs(x1) && y2 < y1){
        exchange(&x1, &x2);
        exchange(&y1, &y2);
    }

    x2 -= x1;  // (x1, y1) = O に移動
    y2 -= y1;  // (x1, y1) = O に移動
    return atan2(y2, x2);
}

double toDegree(double rad){
    return (rad * 180.0 / PI);
}

int isIntersected( double sx1, double sy1, double sz1, double ex1, double ey1, double ez1,
                   double sx2, double sy2, double sz2, double ex2, double ey2, double ez2){
    int res = 0;
    double s, t;
    s = ( (sx2 - sx1) * (ey2 - sy2) - (ex2 - sx2) * (sy2 - sy1) ) / ( (ex1 -sx1) * (ey2 - sy2) - (ex2 - sx2) * (ey1 - sy1) );
    t = ( (sx1 - sx2) * (ey1 - sy1) - (ex1 - sx1) * (sy1 - sy2) ) / ( (ex2- sx2) * (ey1 - sy1) - (ex1 - sx1) * (ey2 - sy2) );
    if((0<=s) && (s<=1) && (0<=t) && (t<=1)
    && sz1 + s*(ez1 - sz1) == sz2 + t*(ez2 - sz2)){
        res = 1;
    }
    return res;
}

double distVertex(vertex_t a, vertex_t b){
    return ( sqrt((b.x - a.x) * (b.y - a.y) * (b.z - a.z)) );
}

// AB, CDの2直線の交点（最近点）を求める
/*
    戻り値
    0 計算できず（平行 or A=B or C=D) OR 交点なし
    1 交点あり resultAB, resultCDに交点を格納 NULLを渡すとキャンセル
*/
int intersect_lines(vertex_t* resultAB, vertex_t *resultCD,
                    vertex_t A,  vertex_t B,  vertex_t C,  vertex_t D ){
    vector_t AB, CD, uAB, uCD;
    vector_t AC;
    double work1, work2;
    double d1, d2;
    vertex_t npAB, npBC;

    // A=B C=D のときは計算できない
    if( distVertex( A,B ) == 0 || distVertex( C,D ) == 0 ) {
        return 0;
    }

    initVector(&AB, B.x-A.x, B.y-A.y, B.z-A.z);
    initVector(&CD, D.x-C.x, D.y-C.y, D.z-C.z);
    normalize(&uAB, AB);
    normalize(&uCD, CD);
    
    work1 = dotProduct(&uAB, &uCD);
    work2 = 1 - work1 * work1;

    // 直線が平行な時は計算できない
    if( work2 == 0 ) { return 0; }

    initVector(&AC, C.x-A.x, C.y-A.y, C.z-A.z);

    d1 = ( dotProduct(&AC, &uAB) - work1 * dotProduct( &AC, &uCD) ) / work2;
    d2 = ( work1 * dotProduct(&AC, &uAB) - dotProduct( &AC, &uCD) ) / work2;

    // AB上の最近点
    npAB.x = A.x + d1 * uAB.x;
    npAB.y = A.y + d1 * uAB.y;
    npAB.z = A.z + d1 * uAB.z;

    // BC上の最近点
    npBC.x = C.x + d2 * uCD.x;
    npBC.y = C.y + d2 * uCD.y;
    npBC.z = C.z + d2 * uCD.z;

    // 交差の判定
    if( distVertex(npAB, npBC) < 0.000001 ) {
        // 交差した
        if(resultAB != NULL){
            resultAB->x = npAB.x; resultAB->y = npAB.y; resultAB->z = npAB.z;
        }
        if(resultCD != NULL){
            resultCD->x = npBC.x; resultCD->y = npBC.y; resultCD->z = npBC.z;
        }

        return 1;
    }

    // 交差しなかった
    return 0;
}

//
void initVertex(vertex_t *v, double x, double y, double z){
    v->x = x;
    v->y = y;
    v->z = z;
}

