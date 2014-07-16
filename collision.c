#include <GL/glut.h>
#include "objects.h"

/* todo あたり判定
    ビー玉とブロックを総当たりで判定する
    当たっていたらブロックに応じてビー玉を移動する
    ブロックでいくつかの判定用の線分を定義しておく(角度もあるとよい？)
    ブロックを作るたびに原点に近い順にソートしなおす

*/

block_t* includeAreaCheck(marble_t* marble){
    // ビー玉がブロックの領域に含まれれば、含むブロックを返す
    /*
    int i;

    for(i=0; i<blockNum; i++){
        if((blocks[i]->x <= marble->x && marble->x <= blocks[i]->width)
                && (blocks[i]->y <= marble->y && marble->y <= blocks[i]->width)
                && (blocks[i]->z <= marble->z && marble->z <= blocks[i]->width)){
            // ブロックの領域内
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
