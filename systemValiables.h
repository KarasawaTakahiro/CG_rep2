#include <GL/glut.h>

unsigned char	mouseFlag = GL_FALSE;		// flag for moving or not
int				xStart, yStart;				// start position when drug begins
double			xAngle = 0.0, yAngle = 0.0;	// angles of the teapot
int samplingTime = 50;
