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
        marble->radius = MARBLE_SIZE;
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

    if(MARBLE_MAX_NUM < num){
        return 0;
    }

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
        printf("freeMarble: %d\n",i);
        free(marbles[i]);
    }
}

// ブロックの定義
int blkid = 1;

block_t* newBlock(int modelType, double scale, double x, double y, double z){
    /*
       メタセコイアでのモデルデータを読み込む
       height, width, depth, model, collisionlines, collisionlinesNumは各々のload*関数で定義する
       load*関数を呼ぶ前にx, y, zに代入しておくこと
     */
    block_t* block;
    if((block = (block_t*)malloc(sizeof(block_t))) == NULL){
        return NULL;
    }
    block->id = blkid ++;
    block->x = x;
    block->y = y;
    block->z = z;
    block->e = 0.1;
    block->model = NULL;
    block->collisionlinesNum = 0;
    block->shown = BLOCK_SHOW;

    switch(modelType){
        case MODEL_TYPE_POST:
            loadPost(block, scale);
            break;
        case MODEL_TYPE_STRAIGHT:
            loadStraight(block, scale);
            break;
        default:
            free(block);
            return NULL;
    }

    return block;
}

int createBlock(block_t*** blocks, int *blocksNum, int modelType, double x, double y, double z, double scale){
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
        if((tmp = newBlock(modelType, scale, x, y, z)) != NULL){  // 領域を確保
            tmpA[num] = tmp;
            num ++;
            (*blocks) = tmpA;  // 変数に入れる
            *blocksNum = num;
            res = tmp->id;
            printf("new block: id:%d x:%.2f y%.2f z:%.2f l:%d\n", tmp->id, tmp->x, tmp->y, tmp->z, tmp->collisionlinesNum);
        }
    }else{
        res = 0;
    }
    return res;
}


void freeBlocks(block_t** blks, int num){
    /*
        ブロックの領域を解放する
    */
    int i;
    for(i=0; i<num; i++){
        printf("free block id: %d\n", blks[i]->id);
        deleteCollisionline(blks[i]);
        deleteModel(blks[i]);
        free(blks[i]);
    }
}

// モデルの描画関数
void callModel(block_t* block){
    mqoCallModel(block->model);
}

void deleteModel(block_t* block){
    mqoDeleteModel(block->model);
    printf("deleted model\n");
    block->shown = 0;
}

// あたり判定用の線
collisionline_t* newCollisionline(double sx, double sy, double sz, double ex, double ey, double ez){
    collisionline_t* line;
    if((line = (collisionline_t*) malloc(sizeof(collisionline_t))) != NULL){
        line->sx = sx;
        line->sy = sy;
        line->sz = sz;
        line->ex = ex;
        line->ey = ey;
        line->ez = ez;
        printf("new collisionline: (%.2f, %.2f, %.2f) to (%.2f, %.2f, %.2f)\n", sx, sy, sz, ex, ey, ez);
        return line;
    }else{
        return NULL;
    }
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

void deleteCollisionline(block_t* block){
    int i;
    for(i=block->collisionlinesNum; i<0; i++){
        printf("delete collisionline: %d\n", i);
        free(block->collisionlines[i]);
        block->collisionlinesNum--;
    }
}

/*
   各モデルを読み込む関数群
 */

void initModel(model_t *model, char* path, double scale, double corX, double corY, double corZ){
    model->model = mqoCreateModel(path, scale);
    model->correction_x = corX;
    model->correction_y = corY;
    model->correction_z = corZ;
}

void loadPost(block_t* block, double scale){
    collisionline_t* cl;
    int theta;
    double x, z;  // シータの時のx,z座標
    block->height = POST_HEIGHT * scale;
    block->width = POST_WIDTH * scale;
    block->depth = POST_WIDTH * scale;
    block->model = mqoCreateModel(POST_PATH, scale);
    printf("post block pos: %.2f %.2f %.2f\n", block->x, block->y, block->z);
    for(theta=0; theta<360; theta+=45){  // あたり判定用の線を定義して追加する
        x = ((POST_INTERNAL_RADIUS * scale) * cos(theta)) + block->x;
        z = ((POST_INTERNAL_RADIUS * scale) * sin(theta)) + block->z;
        if((cl = newCollisionline(x, block->y, z, x, block->y+block->height, z)) == NULL)
            continue;
        addCollisionline(&block, cl);
    }
}

void loadBrige(block_t *block, double scale){
    collisionline_t *cl;
    int theata;

    block->height = STRAIGHT_HEIGHT * scale;
    block->width = STRAIGHT_WIDTH * scale;
    block->depth = STRAIGHT_WIDTH * scale;
    block->modelsNum = 3;
    block->models[0] = initModel("straight.mqo", scale, 0.0, 0.0, 0.0);
    block->models[1] = initModel("bridge_entrance.mqo", scale, BRIDGE_ENTRANCE_CORRECTION_X, 0.0, 0.0);
    block->models[2] = initModel("bridge_outlet.mqo", scale, BRIDGE_OUTLET_CORRECTION_X, 0.0, 0.0);
    printf("stright block pos: %.2f %.2f %.2f\n", block->x, block->y, block->z);
    // 通路部分のコリジョンラインの定義
    // 入り口側のコリジョンラインの定義
    for(theata=0; theata<=180; theata += 45){
    }
    // 出口側のコリジョンラインの定義
}

