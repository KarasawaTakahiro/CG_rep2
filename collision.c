#include "objects.h"  // GL/glut.hよりも先にincludeすべき.includeの衝突が起きる
#include <GL/glut.h>
#include <math.h>

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

