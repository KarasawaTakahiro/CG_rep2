#include "objects.h"
#include "move.h"
#include "myconstants.h"

void updateSpeed(marble_t *marble, block_t **blocks, int blocksNum){
    vector_t mvv;  // �r�[�ʂ̑��x�x�N�g��

    /*
    if(merble->collision != MARBLE_NOT_HIT){
        // �u���b�N�ɂ������Ă���

        // ���ˊp���v�Z����
        // �R���W�������C���̊p�x�𓾂�
        // �x�N�g���v�Z
        // �x�N�g���X�V


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
        // �u���b�N�ɂ������Ă��Ȃ�
        marble->ay = acceleration(-90.0);
        marble->vy = velocity(marble->vy, marble->ay, 1.0);
    }
    */
}

