#include <stdlib.h>
#include "system.h"
#include "objects.h"
#include "GLMetaseq.h"

// ビー玉の定義
int marbleid = 1;
marble_t* newMarble(double x, double y, double z, double r, double g, double b){
    marble_t *marble;
    if((marble = (marble_t*)malloc(sizeof(marble_t))) != NULL){
        marble->x = x;
        marble->y = y;
        marble->z = z;
        marble->r = r;
        marble->g = g;
        marble->b = b;
        marble->ax = marble->ay = marble->az = 0.0;
        marble->vx = marble->vy = marble->vz = 0.0;
        marble->radius = MARBLE_SIZE/2.0;
        marble->id = marbleid++;
        return marble;
    }else{
        return NULL;
    }
}

int createMarble(marble_t*** marbles, int* marblesNum, double x, double y, double z, double r, double g, double b){
    // ビー玉を新しく作って配列に追加
    // 成功すれば1以上のID、失敗すれば0を返す
    marble_t** tmpA;
    marble_t* tmp;
    int res = 0;
    int ensure = 0;
    int num = *marblesNum;

    // 配列領域の確保
    if(num == 0){
        if((tmpA = (marble_t**) malloc(sizeof(marble_t*))) != NULL){
            ensure = 1;
        }
    }else{
        if((tmpA = (marble_t**) realloc(*marbles, sizeof(marble_t)*(num+1))) != NULL){
            ensure = 1;
        }
    }
    
    // 要素の領域を確保して配列に入れる
    if(ensure){
        if((tmp = newMarble(x, y, z, r, g, b)) != NULL){  // 領域を確保
            tmpA[num] = tmp;
            num ++;
            (*marbles) = tmpA;  // 変数に入れる
            *marblesNum = num;
            res = tmp->id;
        }
    }
    return res;
}

void freeMarbles(marble_t** marbles, int num){
    int i;
    for(i=0; i<num; i++){
        free(marbles[i]);
    }
}

// ブロックの定義
int blkid = 1;
/*
    複数のモデルデータを読み込めるようにする
    newblock()にモデルデータを表す定数を渡して、ブロックの領域を定義する
*/
block_t* newBlock(int modelType){
    /*
       メタセコイアでのモデルデータを読み込む
     */
    block_t* block = (block_t*)malloc(sizeof(block_t));
    block->id = blkid ++;
    block->x = 0.0;
    block->y = 0.0;
    block->z = 0.0;
    block->height = 2.0;
    block->width = 2.0;
    block->depth = 2.0;
    block->e = 0.1;
    block->model = mqoCreateModel(path, 0.02);
    block->shown = BLOCK_SHOW;
    block->collisionlines = NULL;
    block->collisionlinesNum = 0;
    return block;
}

int createBlock(block_t*** blocks, int *blocksNum, int modelType, double x, double y, double z){
    /*
        ブロックを作成して配列に追加する
        blocks : ブロックを保持する配列
        blocksNum : 保持するブロックの数
        return
            success : 1~ , failed : 0
    */
    block_t** tmpA;
    block_t* tmp;
    int res = 0;
    int ensure = 0;
    int num = *blocksNum;

    // 配列領域の確保
    if(num == 0){
        if((tmpA = (block_t**) malloc(sizeof(block_t*))) != NULL){
            ensure = 1;
        }
    }else{
        if((tmpA = (block_t**) realloc(*blocks, sizeof(block_t)*(num+1))) != NULL){
            ensure = 1;
        }
    }
    
    // 要素の領域を確保して配列に入れる
    if(ensure){
        if((tmp = newBlock(modelType)) != NULL){  // 領域を確保
            tmp->x = x; tmp->y = y; tmp->z = z;  // パラメータを代入
            tmpA[num] = tmp;
            num ++;
            (*blocks) = tmpA;  // 変数に入れる
            *blocksNum = num;
            res = tmp->id;
        }
    }
    return res;
}


void freeBlocks(block_t** blks, int num){
    /*
        ブロックの領域を解放する
    */
    int i;
    for(i=0; i<num; i++){
        deleteModel(blks[i]);
        free(blks[i]);
    }
}

void callModel(block_t* block){
    mqoCallModel(block->model);
}

void deleteModel(block_t* block){
    mqoDeleteModel(block->model);
    block->shown = 0;
}

// あたり判定用の線
collisionline_t* newCollisionline(sx, sy, sz, ex, ey, ez){
    collisionline_t* line = (collisionline_t*) malloc(sizeof(collisionline_t));
    line->sx = sx;
    line->sy = sy;
    line->sz = sz;
    line->ex = ex;
    line->ey = ey;
    line->ez = ez;
    return line;
}

int addCollisionline(block_t** block, collisionline_t* cl){
    int ensure = 0;
    int res = 0;
    int clNum = (*block)->collisionlinesNum;
    collisionline_t** tmpcls;

    if(clNum == 0){
        if((tmpcls = (collisionline_t**)malloc(sizeof(collisionline_t*))) != NULL){
            ensure = 1;
        }

    }else{
        if((tmpcls = (collisionline_t**)realloc((*block)->collisionlines, sizeof(collisionline_t*)*(clNum+1))) != NULL){
            ensure = 1;
        }
    }
    if(ensure){
        tmpcls[clNum] = cl;
        clNum ++;
        (*block)->collisionlines = tmpcls;
        (*block)->collisionlinesNum = clNum;
        res = 1;
    }

    return res;
}

/*
    各モデルを読み込む関数群
*/
void loadPost(block_t* block, double scale){
    block->* scale;
    block->* scale;
    block->* scale;
    block->* scale;
    block->* scale;
}







