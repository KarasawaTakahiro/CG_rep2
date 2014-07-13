
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "system.h"
#include "systemValiables.h"

// 視点
double posX=0.0, posY=0.0, posZ=0.0;
double vector[3]={0.0, 0.0, 0.0};
double speed=0.5;
double distance = 1.0;  // 回転中心との距離

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

void updateMarbles(){
    // ビー玉の更新
    int i;
    marble_t* marble;

    for(i=0; i<marbleNum; i++){
        marble = (marble_t*)marbles[i];


        marble->ay = acceleration(90.0);
        marble->vy = velocity(marble->vy, marble->ay, 1.0);
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
    double x, y, z;

    for(b=0; b<blockNum; b++){
        if((blocks[i]->x <= marble->x && marble->x <= blocks[i]->width)
        && (blocks[i]->y <= marble->y && marble->y <= blocks[i]->width)
        && (blocks[i]->z <= marble->z && marble->z <= blocks[i]->width)){
            // ブロックの領域内
            return blocks[i];
        }

    }
    return null;
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

block_t* newBlock(){
    /*
        メタセコイアでのモデルデータを読み込む
    */
    block_t* block = (block_t*)malloc(sizeof(block_t));
    block->x = -1.0;
    block->y = 4.0;
    block->z = -1.0;
    block->height = 2.0;
    block->width = 2.0;
    block->depth = 2.0;
    block->e = 0.1;
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
	int i;
	for(i=0; i<blockNum; i++){
		free(blocks[i]);
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
    blocksInit();

    glutMainLoop();
    return 0;
}

