
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "system.h"
#include "systemValiables.h"
#include "dammy.h"

// 視点
double posX=0.0, posY=0.0, posZ=0.0;
double vector[3]={0.0, 0.0, 0.0};
double speed=0.5;
double eyedistance = 1.0;  // 回転中心との距離

// フィールド
field_t field = { 100.0, 100.0, -0.8 };

// ビー玉
marble_t** marbles;
int marbleNum = 0;

// ブロック
block_t** blocks;
int blockNum = 0;

// prototype define
void rotatePosition(double side, double updown);
int createMarble(double x, double y, double z, double r, double g, double b);
void freeMarbles();
void freeBlocks();
int createBlock();


void myKeyboard(unsigned char key, int x, int y) {
    if ( key == 27 ) exit (0);
    switch(key){
        case '27':
            freeMarbles();
            freeBlocks();
            exit(0);
            break;
        case 'w':
            vector[2] = speed;
            break;
        case 's':
            vector[2] = -speed;
            break;
        case 'W':
            vector[1] = -speed;
            break;
        case 'S':
            vector[1] = speed;
            break;
        case 'd':
            vector[0] = -speed;
            break;
        case 'a':
            vector[0] = speed;
            break;
        case 'n':
            //createMarble(posX, posY, posZ-2.0, 0.0, 0.0, 1.0);
            createMarble(0.0, 10.0, 0.0, 0.0, 0.0, 1.0);
            break;
        default:
            vector[0] = vector[1] = vector[2] = 0.0;
            break;
    }
}

void myMouseMotion(int x, int y)
{
    int		xdis, ydis;
    double	a = 0.01;
    double distance = 1.0;

    if (mouseFlag == GL_FALSE) return;
    xdis = x - xStart;
    ydis = y - yStart;

    xAngle += (double)ydis *a;
    yAngle += (double)xdis *a;

    xStart = x;
    yStart = y;

    //rotatePosition(xAngle, yAngle);
    glutPostRedisplay();
}

void myMouseFunc(int button, int state, int x, int y)
{
    if ( button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN ){
        xStart = x;
        yStart = y;
        mouseFlag = GL_TRUE;
    }
    else {
        mouseFlag = GL_FALSE;
    }
}

void movePosition(){
    glTranslated(vector[0], vector[1], vector[2]);
    vector[0] = vector[1] = vector[2] = 0.0;
}

void rotatePosition(double side, double updown){
    glRotated(updown, 1.0, 0.0, 0.0);
    glRotated(side, 0.0, 1.0, 0.0);
}

void freeMarbles(){
    int i;
    for(i=0; i<marbleNum; i++){
        free(marbles[i]);
    }
}

marble_t* newMarble(double x, double y, double z, double r, double g, double b){
    marble_t *marble = (marble_t*)malloc(sizeof(marble_t));
    marble->x = x;
    marble->y = y;
    marble->z = z;
    marble->r = r;
    marble->g = g;
    marble->b = b;
    marble->ax = marble->ay = marble->az = 0.0;
    marble->vx = marble->vy = marble->vz = 0.0;
    marble->radius = MARBLE_SIZE/2.0;
    return marble;
}

int createMarble(double x, double y, double z, double r, double g, double b){
    // ビー玉を新しく作って配列に追加
    // 成功すれば1、失敗すれば0を返す
    marble_t** tmp;
    int res = 0;

    if(MARBLE_MAX_NUM <= marbleNum){
        return 0;
    }else if(marbleNum == 0){
        if((marbles = (marble_t**) malloc(sizeof(marble_t*))) != NULL){
            marbles[0] = newMarble(x, y, z, r, g, b);
            marbleNum++;
            res = 1;
        }
    }else{
        if((tmp = (marble_t**) realloc(marbles, sizeof(marble_t)*(marbleNum+1))) != NULL){
            marbles = tmp;
            marbles[marbleNum] = newMarble(x, y, z, r, g, b);
            marbleNum++;
            res = 1;
        }
    }
    return res;
}

void updateMarblePos(marble_t* marble){
    // ビー玉の座標の更新
    //x = v0t + 0.5at^2

    marble->x += marble->vx + 0.5 * marble->ax;
    marble->y += marble->vy + 0.5 * marble->ay;
    marble->z += marble->vz + 0.5 * marble->az;
    if(marble->y < 0){
        marble->y = marble->radius;
    } 
    if(fabs(marble->y - marble->radius) < 0.1){
        marble->vy = marble->vy * field.e;
    }
}

void updateMarbles(){
    // ビー玉の更新
    int i;
    marble_t* marble;

    for(i=0; i<marbleNum; i++){
        marble = (marble_t*)marbles[i];
        marble->ay = -GRAVITY;
        marble->vy = marble->vy + 1 * marble->ay;
        updateMarblePos(marble);
    }
}

void drawMarbles(){
    // ビー玉の描画
    int i;
    marble_t* marble;

    for(i=0; i<marbleNum; i++){
        marble = marbles[i];
        glColor3d(marble->r, marble->g, marble->b);
        glPushMatrix();
        glTranslated(marble->x, marble->y, marble->z);
        glutSolidSphere(marble->radius, 10, 10);
        glPopMatrix();
    }

}

block_t* includeAreaCheck(marble_t* marble){
    // ビー玉がブロックの領域に含まれれば、含むブロックを返す
    int b;

    for(b=0; b<blockNum; b++){
        if((blocks[b]->x <= marble->x && marble->x <= blocks[b]->width)
                && (blocks[b]->y <= marble->y && marble->y <= blocks[b]->width)
                && (blocks[b]->z <= marble->z && marble->z <= blocks[b]->width)){
            // ブロックの領域内
            return blocks[b];
        }

    }
    return NULL;
}

void drawField(){
    // 地面
    glColor3d(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslated(0.0, 0.0, field.y/2);
    glTranslated(-field.x/2, 0.0, 0.0);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    glRectd(0.0, 0.0, field.x, field.y);
    glPopMatrix();
    /*
    // 斜面
    glColor3d(0.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0.0, 3.0, 0.0);
    glRotated(-30.0, 0.0, 0.0, 1.0);
    glTranslated(-1.0, 0.0, 1.0);
    glRotated(-90.0, 1.0, 0.0, 0.0);
    glRectd(0.0, 0.0, 2.0, 2.0);
    glPopMatrix();
     */
}

void drawBlocks(){
    int i;
    block_t* block;

    for(i=0; i<blockNum; i++){
        block = blocks[i];
        glPushMatrix();
        // テストバージョン
        glTranslated(0.0, 3.0, 0.0);
        glRotated(-30.0, 0.0, 0.0, 1.0);
        glTranslated(-1.0, 0.0, 1.0);
        glRotated(-90.0, 1.0, 0.0, 0.0);
        glRectd(0.0, 0.0, 2.0, 2.0);
        glPopMatrix();
    }
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT
            | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    xyzAxes(100.0);

    glPushMatrix();
    glColor3d(1.0, 0.0, 0.0);
    //glutWireTeapot(1.0);
    drawMarbles();
    drawBlocks();
    drawField();
    glPopMatrix();

    // 必須
    movePosition();
    glDisable(GL_DEPTH_TEST);
    glutSwapBuffers();
}

void myTimer(int value)
{
    if (value==1)
    {
        glutTimerFunc(samplingTime,myTimer,1);

        updateMarbles();

        glutPostRedisplay();
    }
}

void blocksInit(){
    createBlock();
}

CDLine_t* newCDLine(double startx, double starty, double startz, double endx, double endy, double endz){
    CDLine_t* cdLine = (CDLine_t*)malloc(sizeof(CDLine_t));
    cdLine->startX = startx;
    cdLine->startY = starty;
    cdLine->startZ = startz;
    cdLine->endX   = endx;
    cdLine->endY   = endy;
    cdLine->endZ   = endz;
    return cdLine;
}

int addCDline(block_t* block, double startx, double starty, double startz, double endx, double endy, double endz){
    CDLine_t* cdline = newCDLine(block->x+startx, block->y+starty, block->z+startz,
                                 block->z+endz, block->z+endz, block->z+endz);
    CDLine_t** tmp;
    int res = 0;

    if( (tmp = (CDLine_t**)realloc(block->cdLines, sizeof(CDLine_t*) * (block->cdLinesNum+1))) != NULL){
        block->cdLines = tmp;
        *(block->cdLines + (block->cdLinesNum)) = cdline;
        block->cdLinesNum ++;
        res = 1;
    }

    return res;
}

block_t* newBlock(){
    /*
       メタセコイアでのモデルデータを読み込む
     */
     block_t* block = getDammy();
    return block;
}

int createBlock(){
    block_t** tmp;
    int res = 0;

    if(blockNum == 0){
        if((blocks = (block_t**) malloc(sizeof(block_t*))) != NULL){
            blocks[0] = newBlock();
            blockNum++;
            res = 1;
        }
    }else{
        if((tmp = (block_t**) realloc(blocks, sizeof(block_t)*(blockNum+1))) != NULL){
            blocks = tmp;
            blocks[blockNum] = newBlock();
            blockNum++;
            res = 1;
        }
    }
    return res;
}

void freeBlocks(){
    int i, lineIndex;

    for(i=0; i<blockNum; i++){
        for(lineIndex=0; lineIndex < (blocks[i]->cdLinesNum); lineIndex++){
            free(blocks[i]->cdLines[lineIndex]);

        }
        free(blocks[i]);
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutKeyboardFunc(myKeyboard);
    glutTimerFunc(samplingTime, myTimer, 1);
    glutMouseFunc(myMouseFunc);
    glutMotionFunc(myMouseMotion);	
    glutReshapeFunc(myReshape);  // ウィンドウサイズ変更時
    glutDisplayFunc(myDisplay);

    // user define
    blocksInit();

    glutMainLoop();
    return 0;
}
