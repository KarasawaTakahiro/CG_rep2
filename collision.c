#include "objects.h"  // GL/glut.h�������include���ׂ�.include�̏Փ˂��N����
#include <GL/glut.h>
#include <math.h>

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

