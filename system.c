
#include <stdlib.h>
#include <GL/glut.h>

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
       pos[XYZ]: ÉJÉÅÉâÇÃç¿ïW
       distance: âÒì]é≤Ç∆ÇÃãóó£
     */
    glRotated(-twist,      0.0, 0.0, 1.0);  // zé≤ÇÃâÒì]
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
    ïœà 
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

    // äp(x1, y1)Ç™ÉVÅ[É^Ç…Ç∑ÇÈ
    if(fabs(x2) < fabs(x1) && y2 < y1){
        exchange(&x1, &x2);
        exchange(&y1, &y2);
    }

    x2 -= x1;  // (x1, y1) = O Ç…à⁄ìÆ
    y2 -= y1;  // (x1, y1) = O Ç…à⁄ìÆ
    return atan2(y2, x2);
}

double toDegree(double rad){
    return (rad * 180.0 / PI);
}

void polarView(double posX, double posY, double posZ, double distance, 
	                  double twist, double elevation, double azimuth)
{
	/*
	pos[XYZ]: ÉJÉÅÉâÇÃç¿ïW
	distance: âÒì]é≤Ç∆ÇÃãóó£
	*/
	glRotated(-twist,      0.0, 0.0, 1.0);  // zé≤ÇÃâÒì]
	glRotated(-azimuth,  0.0, 1.0, 0.0);  // y
	glRotated(-elevation, 1.0, 0.0, 0.0);  // x
	glTranslated(posX, posY, posZ);
}

