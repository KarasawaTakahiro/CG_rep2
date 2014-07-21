#include "collision.h"
#include "objects.h"
#include <math.h>
#include "move.h"
#include "myconstants.h"
#include "vector.h"
#include "system.h"

void updateSpeed(marble_t *marble, block_t **blocks, int blocksNum){
    int i;
    vector_t mvv;  // ビー玉の速度ベクトル
    vector_t tmpv;

    vector2d_t v0;  // X軸に垂直な単位ベクトル, X軸に平行な
    int thetaI;  // 入射角
    vector2d_t mvv2d;  // ビー玉のXY平面に対する速度ベクトル
    int thetaC;  // コリジョンラインの斜度
    block_t *hitBlock;
    collisionline_t cl;

    initVector(&mvv, 0.0, 0.0, 0.0);

    if(marble->collision != MARBLE_NOT_HIT){
        // ブロックにあたっている

        // 入射角を計算する
        initVector2d(&v0, 0.0, 1.0);  // X軸に垂直な単位ベクトル
        initVector2d(&mvv2d, marble->vx, marble->vy);
        thetaI = toDegree( angleBetweenTwoVector2d(v0, mvv2d));
        // 各々のコリジョンラインへの処理
        hitBlock = getBlockById(blocks, blocksNum, marble->collision);
        for(i=0; i<hitBlock->collisionlinesNum; i++){
            cl = *(hitBlock->collisionlines[i]);
            tmpv.x = tmpv.y = tmpv.z = 0.0;
            // そのコリジョンラインと当たっているか
            if(isHittingLine(*marble, cl) != IS_HIT)
                continue;
            // コリジョンラインの角度を得る
            thetaC = cl.inclinationXY;
            // ベクトル計算
            // コリジョンラインの角度によって動作が違う
            if(thetaC == 0 || thetaC == 180){
                // X軸に平行な時
                initVector(&tmpv, marble->vx, marble->vy * (-1), marble->vz);
            }else if(thetaC == 90 || thetaC == 270){
                // X軸に垂直な時
                initVector(&tmpv, marble->vx * (-1), marble->vy, marble->vz);
            }else{
                tmpv.x = sin(thetaI+thetaC) * marble->vx;
                tmpv.y = cos(thetaI+thetaC) * marble->vy * hitBlock->e;
            }
            // ベクトル更新
            add(&mvv, tmpv);
        }
        marble->vx = mvv.x;//  + velocity(marble->vx, marble->ax, 1.0);
        marble->vy = mvv.y;//  + velocity(marble->vy, marble->ay, 1.0);
        marble->vz = mvv.z;//  + velocity(marble->vz, marble->az, 1.0);
    }else{
        // ブロックにあたっていない
        marble->ay = acceleration(-90.0);
        marble->vy = velocity(marble->vy, marble->ay, 1.0);
    }
    marble->ay = acceleration(-90.0);

    return ;
}

