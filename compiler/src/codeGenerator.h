#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <stdio.h>
#include "ASTNodes.h"

void generate_code(FILE* file, struct block_item_t* item);

#endif