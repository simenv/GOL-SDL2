//
//  constants.h
//  Game of Life using SDL2
//

#ifndef __Game_of_Life_using_SDL2__constants__
#define __Game_of_Life_using_SDL2__constants__

//Screen dimension constants
const int SCREEN_WIDTH = 1680;
const int SCREEN_HEIGHT = 1050;

/* Some GOL constants which need the screen width */
// Approximate size of grid (N()xN). The real size of the grid depends on the pixel resolution of the window (see divisor)
const int N = 500;
// The ratio between the w and h of the windowSurface
const int screenRatio = SCREEN_WIDTH / SCREEN_HEIGHT;

// Millisecond delay between frames - Lower this to increase speed of simulation (20 = 50fps, 200 = 5fps, 1000 = 1fps)
const int S = 10;

// Percentage of alive cells at initialization
const int T = 15;

// Constants for currC and currY ints in fromFileToLife. Got sick of changing them manually all the time
const int xCurr = 0;
const int yCurr = 0;

#endif /* defined(__Game_of_Life_using_SDL2__constants__) */
