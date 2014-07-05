#include "system.h"
#include <stdlib.h>
#include "rep2.h"


block_t* getDammy(){
    block_t* block = (block_t*)malloc(sizeof(block_t));
    block->x = -1.0;
    block->y = 4.0;
    block->z = -1.0;
    block->height = 2.0;
    block->width = 2.0;
    block->depth = 2.0;
    block->e = 0.1;
    block->cdLines = (CDLine_t**)malloc(sizeof(CDLine_t*));
    block->cdLinesNum = 0;

    addCDline(block, 0.0, 4.0, 1.0, 2.0, 0.0, 1.0);
    return block;
}

