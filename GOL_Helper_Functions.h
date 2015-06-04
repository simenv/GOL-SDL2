//
//  GOL_Helper_Functions.h
//  Game of Life using SDL2
//

#ifndef __Game_of_Life_using_SDL2__GOL_Helper_Functions__
#define __Game_of_Life_using_SDL2__GOL_Helper_Functions__

#include "constants.h"
#include <random>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <iostream>


void cell_Init(int T, int* px, int* py, int cell[][N], int tempCell[][N]);

void fromFileToLife(int cell[][N], int tempCell[][N]);

#endif /* defined(__Game_of_Life_using_SDL2__GOL_Helper_Functions__) */
