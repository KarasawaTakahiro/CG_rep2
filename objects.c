#include <stdlib.h>
#include "system.h"
#include "objects.h"
#include "GLMetaseq.h"
#include "vector.h"

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
        marble->collision = MARBLE_NOT_HIT;
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
    block->collisionlinesNum = 0;
    block->shown = BLOCK_SHOW;

    switch(modelType){
        case MODEL_TYPE_POST:
            loadPost(block, scale);
            break;
        case MODEL_TYPE_STRAIGHT:
            loadBridge(block, scale);
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

// idからブロックを得る
block_t* getBlockById(block_t **blocks, int blocksNum, int id){
    int i;

    for(i=0; i<blocksNum; i++){
        if(blocks[i]->id == id){
            return blocks[i];
        }
    }
    return NULL;
}

// モデルの描画関数
void callModel(block_t* block){
    int i;
    for(i=0; i<block->modelsNum; i++){
        mqoCallModel(block->models[i].model);
    }
}

void deleteModel(block_t* block){
    int i;
    for(i=0; i<block->modelsNum; i++){
        mqoDeleteModel(block->models[i].model);
    }
    printf("deleted model\n");
    block->shown = 0;
}

// あたり判定用の線
collisionline_t* newCollisionline(double sx, double sy, double sz, double ex, double ey, double ez){
    collisionline_t* line;
    vector2d_t *v1=NULL, *v2=NULL;
    if((line = (collisionline_t*) malloc(sizeof(collisionline_t))) != NULL){
        line->sx = sx;
        line->sy = sy;
        line->sz = sz;
        line->ex = ex;
        line->ey = ey;
        line->ez = ez;
        // 角度の算出
        initVector2d(v1, sx, sy);
        initVector2d(v2, ex, ey);
        line->inclinationXY = (int) toDegree( angleBetweenTwoVector2d(*v1, *v2));
        initVector2d(v1, sy, sz);
        initVector2d(v2, ey, ez);
        line->inclinationYZ = (int) toDegree( angleBetweenTwoVector2d(*v1, *v2));
        initVector2d(v1, sx, sz);
        initVector2d(v2, ex, ez);
        line->inclinationXZ = (int) toDegree( angleBetweenTwoVector2d(*v1, *v2));

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
    block->modelsNum = 1;
    initModel(&(block->models[0]), POST_PATH, scale, 0.0, 0.0, 0.0);
    printf("post block pos: %.2f %.2f %.2f\n", block->x, block->y, block->z);
    for(theta=0; theta<360; theta+=45){  // あたり判定用の線を定義して追加する
        x = ((POST_INTERNAL_RADIUS * scale) * cos(theta)) + block->x;
        z = ((POST_INTERNAL_RADIUS * scale) * sin(theta)) + block->z;
        if((cl = newCollisionline(x, block->y, z, x, block->y+block->height, z)) == NULL)
            continue;
        addCollisionline(&block, cl);
    }
}

void loadBridge(block_t *block, double scale){
    collisionline_t *cl;
    int theata;
    double corrz;  // Z方向の補正値
    double x, z;

    block->height = STRAIGHT_HEIGHT * scale;
    block->width = STRAIGHT_WIDTH * scale;
    block->depth = STRAIGHT_WIDTH * scale;
    block->modelsNum = 3;
    initModel(&(block->models[0]), STRAIGHT_PATH, scale, 0.0, 0.0, 0.0);
    initModel(&(block->models[1]), BRIDGE_OUTLET_PATH, scale, BRIDGE_OUTLET_CORRECTION_X, 0.0, 0.0);
    initModel(&(block->models[2]), BRIDGE_ENTRANCE_PATH, scale, BRIDGE_ENTRANCE_CORRECTION_X, 0.0, 0.0);
    printf("stright block pos: %.2f %.2f %.2f\n", block->x, block->y, block->z);
    // 通路部分のコリジョンラインの定義
    corrz = scale * STRAIGHT_RADIUS * cos(asin(scale * STRAIGHT_RADIUS/(scale * STRAIGHT_RADIUS/scale * STRAIGHT_GROOVE_DEPTH)));
    // 最も手前の辺
    if((cl = newCollisionline(block->x + scale * STRAIGHT_LENGTH_UPPER_SIDE,
                              block->y + scale * STRAIGHT_BASE_HIGHEST + scale * STRAIGHT_GROOVE_DEPTH,
                              block->z + corrz, 
                              block->x - scale * STRAIGHT_LENGTH_LOWER_SIDE,
                              block->y + scale * STRAIGHT_BASE_LOWEST + scale * STRAIGHT_GROOVE_DEPTH,
                              block->z + corrz)
                              ) != NULL){
        addCollisionline(&block, cl);
    }
    // 最も下の辺
    /*
    if((cl = newCollisionline(block->x + scale * STRAIGHT_LENGTH_UPPER_SIDE,
                              block->y + scale * STRAIGHT_BASE_HIGHEST,
                              block->z,
                              block->x - scale * STRAIGHT_LENGTH_LOWER_SIDE,
                              block->y + scale * STRAIGHT_BASE_LOWEST,
                              block->z)
                              ) != NULL){
        addCollisionline(&block, cl);
    }
    // 最も奥の辺
    if((cl = newCollisionline(block->x + scale * STRAIGHT_LENGTH_UPPER_SIDE,
                              block->y + scale * STRAIGHT_BASE_HIGHEST + scale * STRAIGHT_GROOVE_DEPTH,
                              block->z - corrz, 
                              block->x - scale * STRAIGHT_LENGTH_LOWER_SIDE,
                              block->y + scale * STRAIGHT_BASE_LOWEST + scale * STRAIGHT_GROOVE_DEPTH,
                              block->z - corrz)
                              ) != NULL){
        addCollisionline(&block, cl);
    }
    // 入り口側のコリジョンラインの定義
    for(theata=0; theata<360; theata += 45){
        if(135 < theata && theata < 225){continue;}  // 出入り口は判定しない
        x = BRIDGE_ENTRANCE_INTERNAL_RADIUS * scale * cos(theata) + block->x + BRIDGE_ENTRANCE_CORRECTION_X * scale;
        z = BRIDGE_ENTRANCE_INTERNAL_RADIUS * scale * sin(theata) + block->z;
        if((cl = newCollisionline(x, block->y, z, x, block->y+block->height, z)) == NULL)
            continue;
        addCollisionline(&block, cl);
    }
    // 出口側のコリジョンラインの定義
    for(theata=45; theata<=315; theata += 45){
        x = BRIDGE_OUTLET_INTERNAL_RADIUS * scale * cos(theata) + block->x + BRIDGE_OUTLET_CORRECTION_X * scale;
        z = BRIDGE_OUTLET_INTERNAL_RADIUS * scale * sin(theata) + block->z;
        if((cl = newCollisionline(x, block->y, z, x, block->y+block->height, z)) == NULL)
            continue;
        addCollisionline(&block, cl);
    }
    */
}

