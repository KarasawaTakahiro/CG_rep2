#include "objects.h"
#include "move.h"
#include "myconstants.h"

void updateSpeed(marble_t *marble, block_t **blocks, int blocksNum){
    vector_t mvv;  // ビー玉の速度ベクトル

    /*
    if(merble->collision != MARBLE_NOT_HIT){
        // ブロックにあたっている

        // 入射角を計算する
        // コリジョンラインの角度を得る
        // ベクトル計算
        // ベクトル更新


        initVector(&mvv, marble->x, marble->y, marble->z);
        normal = vectorCrossProduct(&mvv, clv);
        ndash = normalize(normal);
        inv = vectorScalarMul(-1.0, &mvv);
        p = vectorScalarMul(dotProduct(inv, ndash), ndash);
        v = vectorAdd(&mvv, p);
        movevector = vectorAdd(v, p);
        tmp = velocity;
        velocity = vectorAdd(tmp, movevector);

        printf("tmp: "); showVector(tmp); printf("\n");
        printf("velocity: "); showVector(velocity); printf("\n");

        free(normal);
        free(ndash);
        free(inv);
        free(p);
        free(v);
        free(movevector);
        free(tmp);
    }else{
        // ブロックにあたっていない
        marble->ay = acceleration(-90.0);
        marble->vy = velocity(marble->vy, marble->ay, 1.0);
    }
    */
}

