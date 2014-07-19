#ifndef COLLISION
#define COLLISION

#include "objects.h"
#include "vector.h"

block_t* includeAreaCheck(marble_t* marble, block_t** blocks, int blockNum);
vector_t* hitVector(marble_t* marble, block_t* block);
vector_t* calcHitVector(marble_t* marble, block_t** blocks, int blocksNum);
void drawCollisionline(block_t** blocks, int blocksNum);

#endif

