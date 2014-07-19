#include "collision.h"
#include "objects.h"
#include <math.h>
#include "move.h"
#include "myconstants.h"
#include "vector.h"
#include "system.h"

void updateSpeed(marble_t *marble, block_t **blocks, int blocksNum){
    int i;
    vector_t mvv;  // �r�[�ʂ̑��x�x�N�g��
    vector_t tmpv;

    vector2d_t v0;  // X���ɐ����ȒP�ʃx�N�g��, X���ɕ��s��
    int thetaI;  // ���ˊp
    vector2d_t mvv2d;  // �r�[�ʂ�XY���ʂɑ΂��鑬�x�x�N�g��
    int thetaC;  // �R���W�������C���̎Γx
    block_t *hitBlock;
    collisionline_t cl;

    initVector(&mvv, 0.0, 0.0, 0.0);

    if(marble->collision != MARBLE_NOT_HIT){
        // �u���b�N�ɂ������Ă���

        // ���ˊp���v�Z����
        initVector2d(&v0, 0.0, 1.0);  // X���ɐ����ȒP�ʃx�N�g��
        initVector2d(&mvv2d, marble->vx, marble->vy);
        thetaI = toDegree( angleBetweenTwoVector2d(v0, mvv2d));
        // �e�X�̃R���W�������C���ւ̏���
        hitBlock = getBlockById(blocks, blocksNum, marble->collision);
        for(i=0; i<hitBlock->collisionlinesNum; i++){
            cl = *(hitBlock->collisionlines[i]);
            tmpv.x = tmpv.y = tmpv.z = 0.0;
            // ���̃R���W�������C���Ɠ������Ă��邩
            if(isHittingLine(*marble, cl) != IS_HIT)
                continue;
            // �R���W�������C���̊p�x�𓾂�
            thetaC = cl.inclinationXY;
            // �x�N�g���v�Z
            // �R���W�������C���̊p�x�ɂ���ē��삪�Ⴄ
            if(thetaC == 0 || thetaC == 180){
                // X���ɕ��s�Ȏ�
                initVector(&tmpv, marble->vx, marble->vy * (-1), marble->vz);
            }else if(thetaC == 90 || thetaC == 270){
                // X���ɐ����Ȏ�
                initVector(&tmpv, marble->vx * (-1), marble->vy, marble->vz);
            }else{
                tmpv.x = sin(thetaI+thetaC) * marble->vx;
                tmpv.y = cos(thetaI+thetaC) * marble->vy * hitBlock->e;
            }
            // �x�N�g���X�V
            add(&mvv, tmpv);
        }
        marble->vx = mvv.x;//  + velocity(marble->vx, marble->ax, 1.0);
        marble->vy = mvv.y;//  + velocity(marble->vy, marble->ay, 1.0);
        marble->vz = mvv.z;//  + velocity(marble->vz, marble->az, 1.0);
    }else{
        // �u���b�N�ɂ������Ă��Ȃ�
        marble->ay = acceleration(-90.0);
        marble->vy = velocity(marble->vy, marble->ay, 1.0);
    }
    marble->ay = acceleration(-90.0);

    return ;
}

