#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "system.h"
#include "objects.h"

// 視点
double posX=0.0, posY=0.0, posZ=0.0;
double vector[3]={0.0, 0.0, 0.0};
double speed=0.5;
double distance = 1.0;  // 回転中心との距離
// 視点変更関連
unsigned char mouseFlag = GL_FALSE; // flag for moving or not
int xStart, yStart;  // start position when drug begins
double xAngle = 0.0, yAngle = 0.0; // angles of the teapot
int samplingTime = 50;


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

void myKeyboard(unsigned char key, int x, int y) {
    if ( key == 27 ) exit (0);
    switch(key){
        case '27':
            freeMarbles(marbles, marbleNum);
            freeBlocks(blocks, blockNum);
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
            createMarble(&marbles, &marbleNum, 0.0, 10.0, 0.0, 0.0, 0.0, 1.0);
            break;
        case 'b':
            printf("createBlk: %d\n", createBlock(&blocks, &blockNum, "post_2_blue.mqo", 0.0, 5.0, 0.0));
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

void updateMarblePos(marble_t* marble){
    // ビー玉の座標の更新
    //x = v0t + 0.5at^2

    marble->x += displacement(marble->vx, marble->ax, 1.0);
    marble->y += displacement(marble->vy, marble->ay, 1.0);
    marble->z += displacement(marble->vz, marble->az, 1.0);
    if(marble->y < 0){
        marble->y = marble->radius;
    } 
    if(fabs(marble->y - marble->radius) < 0.1){
        marble->vy = marble->vy * field.e;
    }
}

void updateMarbles(marble_t** mrbls, int num){
    // ビー玉の更新
    int i;
    marble_t* marble;

    for(i=0; i<num; i++){
        marble = (marble_t*)mrbls[i];
        marble->ay = acceleration(-90.0);
        marble->vy = velocity(marble->vy, marble->ay, 1.0);
        updateMarblePos(marble);
    }
}

void drawMarbles(marble_t** mrbls, int mNum){
    // ビー玉の描画
    int i;
    marble_t* marble;

    for(i=0; i<mNum; i++){
        marble = mrbls[i];
        glColor3d(marble->r, marble->g, marble->b);
        glPushMatrix();
        glTranslated(marble->x, marble->y, marble->z);
        glutSolidSphere(marble->radius, 10, 10);
        glPopMatrix();
    }
}

block_t* includeAreaCheck(marble_t* marble){
    // ビー玉がブロックの領域に含まれれば、含むブロックを返す
    int i;

    for(i=0; i<blockNum; i++){
        if((blocks[i]->x <= marble->x && marble->x <= blocks[i]->width)
                && (blocks[i]->y <= marble->y && marble->y <= blocks[i]->width)
                && (blocks[i]->z <= marble->z && marble->z <= blocks[i]->width)){
            // ブロックの領域内
            return blocks[i];
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
}

void drawBlocks(){
    int i;
    block_t* block;
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
    drawMarbles(marbles, marbleNum);
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

        updateMarbles(marbles, marbleNum);

        glutPostRedisplay();
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutKeyboardFunc(myKeyboard);
    glutTimerFunc(samplingTime, myTimer, 1);
    glutMouseFunc(myMouseFunc);
    glutMotionFunc(myMouseMotion);	
    glutReshapeFunc(myReshape);  // ウィンドウサイズ変更時
    glutDisplayFunc(myDisplay);

    // user define

    glutMainLoop();
    return 0;
}

