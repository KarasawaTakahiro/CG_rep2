/* todo
あたり判定
	ビー玉とブロックを総当たりで判定する
	当たっていたらブロックに応じてビー玉を移動する
	ブロックでいくつかの判定用の線分を定義しておく(角度もあるとよい？)
	ブロックを作るたびに原点に近い順にソートしなおす

*/

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

// marble
#define MARBLE_SIZE 1.0
#define MARBLE_MAX_NUM 10

typedef struct {
	double x, y, z;  // 座標
	double ax, ay, az;  // 加速度
	double vx, vy, vz;  // 速度
	double radius;  // 半径
	double r, g, b;
} marble_t;

// brock
/*
	柱となる部分のy軸は固定
*/
typedef struct{
	double x, y, z;  // 座標
	double height, width, depth;  // サイズ
	double e;  // ビー玉との反発係数
} block_t;

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

