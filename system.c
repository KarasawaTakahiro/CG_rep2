
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
	glTranslated(0.0, 0.0, -5.0);		// move teapot
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


