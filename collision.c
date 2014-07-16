#include <GL/glut.h>
#include "objects.h"

/* todo �����蔻��
    �r�[�ʂƃu���b�N�𑍓�����Ŕ��肷��
    �������Ă�����u���b�N�ɉ����ăr�[�ʂ��ړ�����
    �u���b�N�ł������̔���p�̐������`���Ă���(�p�x������Ƃ悢�H)
    �u���b�N����邽�тɌ��_�ɋ߂����Ƀ\�[�g���Ȃ���

*/

block_t* includeAreaCheck(marble_t* marble){
    // �r�[�ʂ��u���b�N�̗̈�Ɋ܂܂��΁A�܂ރu���b�N��Ԃ�
    /*
    int i;

    for(i=0; i<blockNum; i++){
        if((blocks[i]->x <= marble->x && marble->x <= blocks[i]->width)
                && (blocks[i]->y <= marble->y && marble->y <= blocks[i]->width)
                && (blocks[i]->z <= marble->z && marble->z <= blocks[i]->width)){
            // �u���b�N�̗̈��
            return blocks[i];
        }

    }
    */
    return NULL;
}

void drawCollisionline(block_t** blocks, int blocksNum){
    int i,j;
    collisionline_t** cls;

    for(i=0; i<blocksNum; i++){
        cls = blocks[i]->collisionlines;
        for(j=0; j<blocks[i]->collisionlinesNum; j++){
            glPushMatrix();
                glBegin(GL_LINES);
                    glVertex3d(cls[j]->sx, cls[j]->sy, cls[j]->sz);
                    glVertex3d(cls[j]->ex, cls[j]->ey, cls[j]->ez);
                glEnd();
            glPopMatrix();
        }
    }


}
