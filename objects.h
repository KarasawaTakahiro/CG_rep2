#ifndef OBJECTS
#define OBJECTS

#include "GLMetaseq.h"
#include "myconstants.h"

/*
    構造体の定義
*/
// ビー玉の定義

typedef struct {
    double x, y, z;  // 座標
    double ax, ay, az;  // 加速度
    double vx, vy, vz;  // 速度
    double radius;  // 半径
    double r, g, b;
    int id;
    int collision;  // 衝突しているか
} marble_t;

// あたり判定用の線
typedef struct {
    double sx, sy, sz;  // 始点座標 ワールド座標系で指定すること
    double ex, ey, ez;  // 終点座標 ワールド座標系で指定すること
} collisionline_t;

// モデル
typedef struct {
    MQO_MODEL model;  // モデル構造体
    double correction_x;  // 親ブロックの中心との補正値
    double correction_y;  // 親ブロックの中心との補正値
    double correction_z;  // 親ブロックの中心との補正値
} model_t;

// ブロックの定義
typedef struct{
    int id;
    double x, y, z;  // 座標
    double height, width, depth;  // サイズ
    double e;  // ビー玉との反発係数
    model_t models[MODEL_MAX_DEVISION];
    int modelsNum;
    int shown;
    collisionline_t** collisionlines;
    int collisionlinesNum;
} block_t;

/*
    プロトタイプ宣言
 */
// ビー玉
marble_t* newMarble(double x, double y, double z, double r, double g, double b);
int createMarble(marble_t*** marbles, int* marbleNum, double x, double y, double z, double r, double g, double b);
void freeMarbles(marble_t** marbles, int num);
// ブロック
block_t* newBlock(int modelType, double scale, double x, double y, double z);
int createBlock(block_t*** blocks, int *blocksNum, int modelType, 
                double x, double y, double z, double scale);
void freeBlocks(block_t** blks, int num);
// コリジョンライン
collisionline_t* newCollisionline(double sx, double sy, double sz, double ex, double ey, double ez);
int addCollisionline(block_t** block, collisionline_t* cl);
void deleteCollisionline(block_t* block);
// モデル
void callModel(block_t* block);
void deleteModel(block_t* block);
void initModel(model_t *model, char* path, double scale, double corX, double corY, double corZ);
void loadPost(block_t* block, double scale);
void loadBridge(block_t *block, double scale);

#endif
