#include <GL/glut.h>
#include "objects.h"

block_t* includeAreaCheck(marble_t* marble){
    // �r�[�ʂ��u���b�N�̗̈�Ɋ܂܂��΁A�܂ރu���b�N��Ԃ�
    int i;

    for(i=0; i<blockNum; i++){
        if((blocks[i]->x <= marble->x && marble->x <= blocks[i]->width)
                && (blocks[i]->y <= marble->y && marble->y <= blocks[i]->width)
                && (blocks[i]->z <= marble->z && marble->z <= blocks[i]->width)){
            // �u���b�N�̗̈��
            return blocks[i];
        }

    }
    return NULL;
}

void drawCollisionline(block_t** blocks, int blocksNum){
    int i,j;
    collisionline_t** cls;

    for(i=0; i<blocksNum; i++){
        cls = blocks[i];
        for(j=0; j<blocks[i]->collisionlinesNum; j++){
            glPushMatrix();
                glBegin(GL_LINES);
                    
                glEnd();
            glPopMatrix();
        }
    }


}
