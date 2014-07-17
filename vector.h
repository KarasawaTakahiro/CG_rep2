#ifndef VECTOR
#define VECTOR

typedef struct{
    double x, y, z;
} vector_t;

void initVector(vector_t* v, double x, double y, double z);
void showVector(vector_t* v);
vector_t* newVector(double x, double y, double z);
vector_t* vectorCrossProduct(vector_t* v1, vector_t* v2);  // 外積
double dotProduct(vector_t* v1, vector_t* v2);  // 内積計算
double length(vector_t* v);
vector_t* vectorSub(vector_t* v1, vector_t* v2);
vector_t* normalize(vector_t* v);
vector_t* vectorScalarMul(double scalar, vector_t* v);
void scalarMul(double scalar, vector_t* v);
vector_t* vectorAdd(vector_t* v1, vector_t* v2);

#endif

