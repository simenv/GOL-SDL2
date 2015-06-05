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

// Constants for currC and currY ints in fromFileToLife. Got sick of changing them manually all the time. Change these to change where the pattern file is drawn on screen.
const int xCurr = 0;
const int yCurr = 0;

/* Game of life constants */
// Standard rules are u2o3b3
// No death rules = u0o8bx (x means arbitrary value)

//Some cool ones I found:
//u1o4b3 I think it looks like a bacterial culture, if there were digital bacteria.
//u3o4b2 This one seems to expand in a way where no matter the initial configuration it always
//turns into a diamond pattern before it engulfs the entire screen.
//u1o1b2 Interesting expansion. The expansion front has very clear lines, and just preceding it
//there is some interesting turmoil occasionally.
//u1o1b1 This one! Draw a single point on the screen and observe what happens! Now try two, or
//three or four. This one makes you think.
//u4o4b1 Draw a single point in the middle and wait until it expands to the entire screen. Then
//pause(LEFT key, UP key to unpause) and witness a different psychadelic vista each time you
//do.

// Less than underPop neighbours (for live cell) = dies
const int underPop = 1;

// More than overPop neighbours (for live cells) = dies
const int overPop = 1;

// Exactly birth neighbours (for dead cells) = born
const int birth = 2;

#endif /* defined(__Game_of_Life_using_SDL2__constants__) */
