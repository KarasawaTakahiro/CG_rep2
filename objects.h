#include <>

/*
    ビー玉の定義
*/
#define MARBLE_SIZE 1.0
#define MARBLE_MAX_NUM 10

typedef struct {
    double x, y, z;  // 座標
    double ax, ay, az;  // 加速度
    double vx, vy, vz;  // 速度
    double radius;  // 半径
    double r, g, b;
} marble_t;

marble_t* newMarble(double x, double y, double z, double r, double g, double b);
int createMarble(marble_t*** marbles, int* marbleNum, double x, double y, double z, double r, double g, double b);
void freeMarbles(marble_t** marbles, int num);

/* 
    ブロックの定義
*/

typedef struct{
    double x, y, z;  // 座標
    double height, width, depth;  // サイズ
    double e;  // ビー玉との反発係数
} block_t;

block_t* newBlock(char* path);
int createBlock(block_t*** blocks, int *blocksNum, char* path, double x, double y, double z);
void freeBlocks(block_t** blks, int num);

