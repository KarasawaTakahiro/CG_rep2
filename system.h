/* todo
�����蔻��
	�r�[�ʂƃu���b�N�𑍓�����Ŕ��肷��
	�������Ă�����u���b�N�ɉ����ăr�[�ʂ��ړ�����
	�u���b�N�ł������̔���p�̐������`���Ă���(�p�x������Ƃ悢�H)
	//�u���b�N����邽�тɌ��_�ɋ߂����Ƀ\�[�g���Ȃ���

*/

#define PI 3.14159265359

// field
typedef struct {
	double x;  // �T�C�Y
	double y;  // 
	double e;  // �r�[�ʂƂ̔����W��
} field_t;

// physics
#define GRAVITY 1.0  //9.8
/*
	v = v0 + at
	x = v0t + 0.5at^2
	v^2 - v0^2 = 2ax
*/

// marble
#define MARBLE_SIZE 1.0
#define MARBLE_MAX_NUM 10

typedef struct {
	double x, y, z;  // ���W
	double ax, ay, az;  // �����x
	double vx, vy, vz;  // ���x
	double radius;  // ���a
	double r, g, b;
} marble_t;

// brock
/*
	���ƂȂ镔����y���͌Œ�
*/
typedef struct {
	// �����蔻��p�̋^����
	double startX, startY, startZ;
	double endX, endY, endZ;
} CDLine_t;

typedef struct{
	double x, y, z;  // ���W
	double height, width, depth;  // �T�C�Y
	double e;  // �r�[�ʂƂ̔����W��
	CDLine_t** cdLines;
	int cdLinesNum;
} block_t;

// prototype define
void xyzAxes(double length);
void myInit(char *progname);
void myReshape(int width, int height);
void polarView(double posX, double posY, double posZ, double distance, double twist, double elevation, double azimuth);
void exchange(double* a, double* b);
double distance(double v0, double a, double t);
double velocity(double v0, double a, double t);
double acceleration(double gravity, double theta);
double theta(double x1, double y1, double x2, double y2);
double toDegree(double rad);
