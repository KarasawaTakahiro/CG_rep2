#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"

vector_t* newVector(double x, double y, double z){
    vector_t* v;
    if((v = (vector_t*)malloc(sizeof(vector_t))) != NULL){
        v->x = x;
        v->y = y;
        v->z = z;
    }else{
        return NULL;
    }
    return v;
}

/* vector*()関数はベクトルの領域を動的に確保するので解放すること */

// 初期化関数
void initVector(vector_t* v, double x, double y, double z){
    v->x = x;
    v->y = y;
    v->z = z;
}

void showVector(vector_t* v){
    printf("(%.2f, %.2f, %.2f)", v->x, v->y, v->z);
}

// 外積計算
vector_t* vectorCrossProduct(vector_t* v1, vector_t* v2){
    return newVector(v1->y*v2->z - v1->z-v2->y, v1->z*v2->x - v1->x*v2->z, v1->x*v2->y - v1->y*v2->x);
}

// 内積計算
double dotProduct(vector_t* v1, vector_t* v2){
    return (v1->x*v2->x + v1->y*v2->y + v1->z*v2->z);
}

// 大きさ
double length(vector_t* v){
    return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

// 引き算
vector_t* vectorSub(vector_t* v1, vector_t* v2){
    return newVector(v2->x-v1->x, v2->y - v1->y, v2->z - v1->z);
}

// 加算
vector_t* vectorAdd(vector_t* v1, vector_t* v2){
    return newVector(v2->x+v1->x, v2->y + v1->y, v2->z + v1->z);
}

// スカラー倍
vector_t* vectorScalarMul(double scalar, vector_t* v){
    return (newVector(v->x * scalar, v->y * scalar, v->z * scalar));
}

// スカラー倍
void scalarMul(double scalar, vector_t* v){
    initVector(v, v->x*scalar, v->y*scalar, v->z*scalar);
}

// 正規化
vector_t* normalize(vector_t* v){
    double size = length(v);
    return newVector(v->x/size, v->y/size, v->z/size);
}

/*
    2Dベクトル関数群
 */
void initVector2d(vector2d_t* v, double x, double y){
    v->x = x;
    v->y = y;
}

void showVector2d(vector2d_t v){
    printf("(%.2f, %.2f)", v.x, v.y);
}

double length2d(vector2d_t v){
    return (sqrt(v.x*v.x, v.y*v.y));
}

double dotProduct2d(vector2d_t v1, vector2d_t v2){
    return ( v1.x * v2.x + v1.y * v2.y );
}

// なす角[rad]を返す
double angleBetweenTwoVector2d(vector2d_t v1, vector2d_t v2){
    return ( acos( dotProduct2d(v1, v2) / ( length2d(v1) * length2d(v2) ) ) );
}

