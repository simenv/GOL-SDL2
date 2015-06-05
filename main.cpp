/*
 List of thing to do:
 - Fix rle reader
 - Add buttons (Pause/unpause, reset&&pause, drawing mode,size of brush?, load pattern file)
 - Add fields for modification of constants (fps, ruleset, )
 - Make constants NOT be constants anymore
 - Add fullscreen option
 - Add popup window where user can choose pattern file
 - Add color selector (alternatively add color pallettes which user can choose)
 
 
 */


//Using SDL, SDL_image, standard IO, math, strings random and GOL helper functions
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <random>
#include "GOL_Helper_Functions.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "Game of life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Nothing to load
    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    return newTexture;
}


int main(int argc, char* args[])
{
    
    /* Init of game of life variables */

    // positions of cells
    int px[N*screenRatio];
    int py[N];
    
    // cell alive = 1, cell dead = 0, tempCell array contains result of calculations done on cell array between frames
    int cell[N*screenRatio][N];
    int tempCell[N*screenRatio][N];
    
    // Initializing cells to zero
    for(int i = 0; i < N*screenRatio; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cell[i][j] = 0;
            tempCell[i][j] = 0;
        }
    }
    
    // Counts neighbours of each cell during midframe calculations
    int cellCount[N*screenRatio][N];

    SDL_Rect fillRect[N*screenRatio][N];
    
    
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;
            //Init loop flag
            bool wait = true;
            
            //Event handler
            SDL_Event e;
            
            //While application is running
            while( !quit )
            {
                
                // Initial config
                while(wait)
                {
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }
                        
                        if( e.type == SDL_KEYDOWN )
                        {
                            if(e.key.keysym.sym == SDLK_UP)
                            {
                                wait = false;
                            }
                            if(e.key.keysym.sym == SDLK_DOWN)
                            {
                                cell_Init(T, px, py, cell, tempCell);
                                wait = false;
                            }
                            if(e.key.keysym.sym == SDLK_LEFT)
                            {
                                fromFileToLife(cell, tempCell);
                                wait = false;
                            }
                        }
                        
                        int a, b;
                        if (SDL_GetMouseState( &a, &b ) & SDL_BUTTON(SDL_BUTTON_LEFT))
                        {
                            //Clear screen
                            SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                            SDL_RenderClear( gRenderer );
                            
                            int x = (N*screenRatio*a)/SCREEN_WIDTH, y = N*b/SCREEN_HEIGHT;
                            
                            if(cell[x][y] == 0)
                            {
                                cell[x][y] = 1;
                                tempCell[x][y] = 1;
                            }
                            else
                            {
                                cell[x][y] = 0;
                                tempCell[x][y] = 0;
                            }
                            
                            for (int i = 0; i < N*screenRatio; i++)
                            {
                                for (int j = 0; j < N; j++)
                                {
                                    if (cell[i][j] == 1)
                                    {
                                        fillRect[i][j] = { SCREEN_WIDTH * i/N, SCREEN_HEIGHT * j/N, SCREEN_WIDTH / (N*screenRatio+(N/4)), SCREEN_HEIGHT / (N+5)};
                                        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x99, 0x33, 0x99 );
                                        SDL_RenderFillRect( gRenderer, &fillRect[i][j] );
                                        
                                    }
                                }
                            }
                            SDL_RenderPresent( gRenderer );
                        }
                    }
                }
                
                
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    // To pause and reset
                    if( e.type == SDL_KEYDOWN )
                    {
                        if(e.key.keysym.sym == SDLK_UP)
                        {
                            for(int i = 0; i < N*screenRatio; i++)
                            {
                                for(int j = 0; j < N; j++)
                                {
                                    cell[i][j] = 0;
                                    tempCell[i][j] = 0;
                                }
                            }
                            wait = true;
                        }
                        // To pause
                        if(e.key.keysym.sym == SDLK_RIGHT)
                        {
                            wait = true;
                        }
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                SDL_RenderClear( gRenderer );
                
                /* GAME OF LIFE CODE*/

                for (int i = 0; i < N*screenRatio; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        int nx = i;
                        int ny = j;
                        
                        if (i == 0)
                        {
                            nx = N*screenRatio;
                        }
                        if (j == 0)
                        {
                            ny = N;
                        }
                        // Checks living cells, counts live neighbours
                        if (cell[i][j] == 1)
                        {
                            if (cell[(i+1)%(N*screenRatio)][j] == 1) cellCount[i][j]++;
                            if (cell[(nx-1)][j] == 1) cellCount[i][j]++;
                            
                            if (cell[i][(j+1)%(N)] == 1) cellCount[i][j]++;
                            if (cell[i][ny-1] == 1) cellCount[i][j]++;
                            
                            if (cell[(i+1)%(N*screenRatio)][(j+1)%(N)] == 1) cellCount[i][j]++;
                            if (cell[(i+1)%(N*screenRatio)][ny-1] == 1) cellCount[i][j]++;
                            if (cell[nx-1][(j+1)%(N)] == 1) cellCount[i][j]++;
                            if (cell[nx-1][ny-1] == 1) cellCount[i][j]++;
                            
                            // Kills living cells if cellCount is more than 3 or less than 2
                            if (cellCount[i][j] > overPop || cellCount[i][j] < underPop)
                            {
                                tempCell[i][j] = 0;
                            }
                            // resets cellCount to zero because the values are not needed anymore
                            cellCount[i][j] = 0;
                        }
                        // checks dead cells, checks live neighbours
                        else
                        {
                            if (cell[(i+1)%(N*screenRatio)][j] == 1) cellCount[i][j]++;
                            if (cell[nx-1][j] == 1) cellCount[i][j]++;
                            
                            if (cell[i][(j+1)%(N)] == 1) cellCount[i][j]++;
                            if (cell[i][ny-1] == 1) cellCount[i][j]++;
                            
                            if (cell[(i+1)%(N*screenRatio)][(j+1)%(N)] == 1) cellCount[i][j]++;
                            if (cell[(i+1)%(N*screenRatio)][ny-1] == 1) cellCount[i][j]++;
                            if (cell[nx-1][(j+1)%(N)] == 1) cellCount[i][j]++;
                            if (cell[nx-1][ny-1] == 1) cellCount[i][j]++;
                            
                            // Birth of living cells
                            if (cellCount[i][j] == birth)
                            {
                                tempCell[i][j] = 1;
                            }
                            cellCount[i][j] = 0;
                        }
                    }
                }
                
                
                for (int i = 0; i < N*screenRatio; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        if (tempCell[i][j] == 1)
                        {
                            cell[i][j] = 1;
                            fillRect[i][j] = { SCREEN_WIDTH * i/N, SCREEN_HEIGHT * j/N, SCREEN_WIDTH / (N*screenRatio+(N/4)), SCREEN_HEIGHT / (N+5)};
                            int check = rand();
                            if(check%5)
                            {
                                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x99, 0x33, 0x99 );
                            }
                            
                            if(check%4)
                            {
                                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x88, 0x22, 0x99 );
                            }
                            
                            if(check%3)
                            {
                                SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x33, 0x99 );
                            }
                            
                            if(check%2)
                            {
                                SDL_SetRenderDrawColor( gRenderer, 0x11, 0xCC, 0x44, 0x99 );
                            }
                            
//                            SDL_SetRenderDrawColor( gRenderer, rand()%255, rand()%255, rand()%255, 0x99 );
                            
//                            SDL_SetRenderDrawColor( gRenderer, 0x00, 0x99, 0x33, 0xFF );
                            
                            
                            SDL_RenderFillRect( gRenderer, &fillRect[i][j] );
                            
                        }
                        else
                        {
                            cell[i][j] = 0;
                        }
                    }
                }
                
                
                
                
                
                
                
                
                
                
            
                //Update screen
                SDL_RenderPresent( gRenderer );
                
                SDL_Delay( S );
            }
        }
    }
    
    //Free resources and close SDL
    close();
    
    return 0;
}