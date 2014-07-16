#include "objects.h"  // GL/glut.hよりも先にincludeすべき.includeの衝突が起きる
#include <GL/glut.h>
#include <math.h>
#include "vector.h"

/* todo あたり判定
    ビー玉とブロックを総当たりで判定する
    当たっていたらブロックに応じてビー玉を移動する
    ブロックでいくつかの判定用の線分を定義しておく(角度もあるとよい？)
    ブロックを作るたびに原点に近い順にソートしなおす

*/

block_t* includeAreaCheck(marble_t* marble, block_t** blocks, int blockNum){
    // ビー玉がブロックの領域に含まれれば、含むブロックを返す
    int i;

    for(i=0; i<blockNum; i++){
        if((abs(blocks[i]->x) <= abs(marble->x) && abs(marble->x) <= abs(blocks[i]->x+blocks[i]->width))
        && (abs(blocks[i]->y) <= abs(marble->y) && abs(marble->y) <= abs(blocks[i]->y+blocks[i]->height))
        && (abs(blocks[i]->z) <= abs(marble->z) && abs(marble->z) <= abs(blocks[i]->z+blocks[i]->width))){
            printf("hit: blockId: %d\n", blocks[i]->id);
            // ブロックの領域内
            return blocks[i];
        }

    }
    return NULL;
}

/*
    当たったコリジョンラインから受ける速度のベクトルを得る
*/
vector_t* hitVector(marble_t* marble, block_t* block){
    int i;
    int hit = 0;  // ヒットフラグ
    collisionline_t* cl;
    vector_t* velocity = newVector(0.0, 0.0, 0.0);  // 速度のベクトル
    vector_t* clv;  // コリジョンラインのベクトル
    vector_t* mblv; // コリジョンラインの始点からビー玉の中心までのベクトル
    double clmbl, mblv2;  // 計算用
    for(i=0; i<block->collisionlinesNum; i++){
        cl = block->collisionlines[i];
        // 当たり判定
        clv = newVector(cl->ex - cl->sx, cl->ey - cl->sy, cl->ez - cl->sz);
        mblv = newVector(marble->x - cl->sx, marble->y - cl->sy, marble->z - cl->sz);
        clmbl = dotProduct(clv, mblv);
        if(clmbl < 0){
            /* 球の中心がclの始点よりも遠く*/
            if(vectorLength(clv) < marble->radius){
                /* 距離と半径とを比較 */
                // hit!
                hit = 1;
            }
        }else{
            mblv2 = dotProduct(mblv, mblv);
            if(mblv2 < clmbl){
                /* 球の中心が線分の終点よりも遠くにある */
                if(pow(vectorLength(vectorSub(mblv, clv)), 2) < (marble->radius*marble->radius)){
                    /* 距離と半径とを2乗で比較 */
                    // hit!
                    hit = 1;
                }
            }else{
                /* 球の中心から線分に下した足があるはず */
                if((dotProduct(clv, clv)-(clmbl*clmbl)/mblv2) < (marble->radius*marble->radius)){
                    /* 球の中心から線分に下した足の長さの2乗が半径の2乗よりも小さければhit */
                    // hit!
                    hit = 1;
                }
            }
        }
        printf("hitVector: %d\n", i);
    }
    return velocity;
}

vector_t* calcHitVector(marble_t* marble, block_t** blocks, int blocksNum){
    int i;
    block_t* hold;
    vector_t* velocity = newVector(0.0, 0.0, 0.0);
    vector_t* hit;
    for(i=0; i<blocksNum; i++){
        if(((hold = includeAreaCheck(marble, blocks, blocksNum)) != NULL)
        && ((hit = hitVector(marble, hold)) != NULL)){
            vectorAdd(velocity, hit);
            free(hit);
        }
    }
    return velocity;
}

// コリジョンラインを描画する
// テスト用関数
void drawCollisionline(block_t** blocks, int blocksNum){
    int i,j;
    collisionline_t** cls;

    for(i=0; i<blocksNum; i++){
        cls = blocks[i]->collisionlines;
        for(j=0; j<blocks[i]->collisionlinesNum; j++){
            glColor3d(0.5, 0.0, 0.0);
            glPushMatrix();
                glBegin(GL_LINES);
                    glVertex3d(cls[j]->sx, cls[j]->sy, cls[j]->sz);
                    glVertex3d(cls[j]->ex, cls[j]->ey, cls[j]->ez);
                glEnd();
            glPopMatrix();
        }
    }
}

