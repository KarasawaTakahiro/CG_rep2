
#include <GL/glut.h>

/* todo
�����蔻��
	�r�[�ʂƃu���b�N�𑍓�����Ŕ��肷��
	�������Ă�����u���b�N�ɉ����ăr�[�ʂ��ړ�����
	�u���b�N�ł������̔���p�̐������`���Ă���(�p�x������Ƃ悢�H)
	�u���b�N����邽�тɌ��_�ɋ߂����Ƀ\�[�g���Ȃ���

*/

// field
typedef struct {
	double x;  // �T�C�Y
	double y;  // 
	double e;  // �r�[�ʂƂ̔����W��
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

