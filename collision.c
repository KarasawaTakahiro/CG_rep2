#include "objects.h"  // GL/glut.h�������include���ׂ�.include�̏Փ˂��N����
#include <GL/glut.h>
#include <math.h>
#include "vector.h"

/* todo �����蔻��
    �r�[�ʂƃu���b�N�𑍓�����Ŕ��肷��
    �������Ă�����u���b�N�ɉ����ăr�[�ʂ��ړ�����
    �u���b�N�ł������̔���p�̐������`���Ă���(�p�x������Ƃ悢�H)
    �u���b�N����邽�тɌ��_�ɋ߂����Ƀ\�[�g���Ȃ���

*/

block_t* includeAreaCheck(marble_t* marble, block_t** blocks, int blockNum){
    // �r�[�ʂ��u���b�N�̗̈�Ɋ܂܂��΁A�܂ރu���b�N��Ԃ�
    int i;

    for(i=0; i<blockNum; i++){
        if((abs(blocks[i]->x) <= abs(marble->x) && abs(marble->x) <= abs(blocks[i]->x+blocks[i]->width))
        && (abs(blocks[i]->y) <= abs(marble->y) && abs(marble->y) <= abs(blocks[i]->y+blocks[i]->height))
        && (abs(blocks[i]->z) <= abs(marble->z) && abs(marble->z) <= abs(blocks[i]->z+blocks[i]->width))){
            printf("hit: blockId: %d\n", blocks[i]->id);
            // �u���b�N�̗̈��
            return blocks[i];
        }

    }
    return NULL;
}

/*
    ���������R���W�������C������󂯂鑬�x�̃x�N�g���𓾂�
*/
vector_t* hitVector(marble_t* marble, block_t* block){
    int i;
    int hit = 0;  // �q�b�g�t���O
    collisionline_t* cl;
    vector_t* velocity = newVector(0.0, 0.0, 0.0);  // ���x�̃x�N�g��
    vector_t* clv;  // �R���W�������C���̃x�N�g��
    vector_t* mblv; // �R���W�������C���̎n�_����r�[�ʂ̒��S�܂ł̃x�N�g��
    double clmbl, mblv2;  // �v�Z�p
    for(i=0; i<block->collisionlinesNum; i++){
        cl = block->collisionlines[i];
        // �����蔻��
        clv = newVector(cl->ex - cl->sx, cl->ey - cl->sy, cl->ez - cl->sz);
        mblv = newVector(marble->x - cl->sx, marble->y - cl->sy, marble->z - cl->sz);
        clmbl = dotProduct(clv, mblv);
        if(clmbl < 0){
            /* ���̒��S��cl�̎n�_��������*/
            if(vectorLength(clv) < marble->radius){
                /* �����Ɣ��a�Ƃ��r */
                // hit!
                hit = 1;
            }
        }else{
            mblv2 = dotProduct(mblv, mblv);
            if(mblv2 < clmbl){
                /* ���̒��S�������̏I�_���������ɂ��� */
                if(pow(vectorLength(vectorSub(mblv, clv)), 2) < (marble->radius*marble->radius)){
                    /* �����Ɣ��a�Ƃ�2��Ŕ�r */
                    // hit!
                    hit = 1;
                }
            }else{
                /* ���̒��S��������ɉ�������������͂� */
                if((dotProduct(clv, clv)-(clmbl*clmbl)/mblv2) < (marble->radius*marble->radius)){
                    /* ���̒��S��������ɉ��������̒�����2�悪���a��2��������������hit */
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

// �R���W�������C����`�悷��
// �e�X�g�p�֐�
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

