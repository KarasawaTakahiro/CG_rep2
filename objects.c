#include <stdlib.h>
#include "system.h"
#include "objects.h"

// ビー玉の定義
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
        return marble;
    }else{
        return NULL;
    }
}

int createMarble(marble_t*** marbles, int* marbleNum, double x, double y, double z, double r, double g, double b){
    // ビー玉を新しく作って配列に追加
    // 成功すれば1、失敗すれば0を返す
    marble_t** tmpA;
    marble_t* tmp;
    int res = 0;
    int num = *marbleNum;

    if(MARBLE_MAX_NUM <= *marbleNum){
        return 0;
    }else if(*marbleNum == 0){
        if((tmpA = (marble_t**) malloc(sizeof(marble_t*))) != NULL){
            if((tmpA[0] = newMarble(x, y, z, r, g, b)) != NULL){
                *marbles = tmpA;
                (*marbleNum)++;
                res = 1;
            }
        }
    }else{
        if((tmpA = (marble_t**) realloc(*marbles, sizeof(marble_t)*(num+1))) != NULL){
            if((tmp = newMarble(x, y, z, r, g, b)) != NULL){
                tmpA[num] = tmp;
                *marbles = tmpA;
                num ++;
                *marbleNum = num;
                res = 1;
            }
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

block_t* newBlock(char* path){
    /*
       メタセコイアでのモデルデータを読み込む
     */
    block_t* block = (block_t*)malloc(sizeof(block_t));
    block->x = -1.0;
    block->y = 4.0;
    block->z = -1.0;
    block->height = 2.0;
    block->width = 2.0;
    block->depth = 2.0;
    block->e = 0.1;
    return block;
}

int createBlock(block_t*** blocks, int *blocksNum, char* path, double x, double y, double z){
    /*
        ブロックを作成して配列に追加する
        blocks : ブロックを保持する配列
        blocksNum : 保持するブロックの数
        return
            success : 1 , failed : 0
    */
    block_t** tmpA;
    block_t* tmp;
    int res = 0;
    int num = *blocksNum;

    if(*blocksNum == 0){
        if((tmpA = (block_t**) malloc(sizeof(block_t*))) != NULL){
            if((tmpA[0] = newBlock(path)) != NULL){
                *blocks = tmpA;
                (*blocksNum)++;
                res = 1;
            }
        }
    }else{
        if((tmpA = (block_t**) realloc(*blocks, sizeof(block_t)*(num+1))) != NULL){
            if((tmp = newBlock(path))){
                tmpA[num] = tmp;
                *blocks = tmpA;
                num ++;
                *blocksNum = num;
                res = 1;
            }
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
        free(blks[i]);
    }
}

