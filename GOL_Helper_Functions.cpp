//
//  GOL_Helper_Functions.cpp
//  Game of Life using SDL2
//

#include "GOL_Helper_Functions.h"

// Populates the cell and tempCell arrays with a random population
void cell_Init(int T, int* px, int* py, int cell[][N], int tempCell[][N])
{
    
    srand((unsigned) time(NULL));
    // initial configuration of cells
    for (int i = 0; i < N*screenRatio; i++)
    {
        // sets all possible x co-ordinates
        px[i] = i;
        
        for (int j = 0; j < N; j++)
        {
            // sets all possible y co-ordinates
            py[j] = j;
            
            // T determines percent of squares filled with living cells
            if (rand()%100 < T)
            {
                cell[i][j] = 1;
            }
            else
            {
                cell[i][j] = 0;
            }
        }
    }
}

// Reads .rle files into cell and tempCell arrays.
// NOT DONE- Needs rewriting, only works with some files
void fromFileToLife(int cell[][N*screenRatio], int tempCell[][N*screenRatio])
{
    int x = 50, x2 = 50, y = 50, y2 = 50, num = 0, num1 = 0, num2 = 0, num3 = 0, currX = xCurr, currY = yCurr;
    /*
     Available files:
     linepuffer.rle - Works
     halfmaxv2.rle - not working
     bargeextended.rle - not working
     movingsawtooth.rle - not working
     originalp15prepulsarspaceship.rle - nope, not at all
     p50trafficjam_synth.rle - Crashes program
     
     */
    
    
    std::ifstream inf("linepuffer.rle");
    
    if(!inf)
    {
        std::cerr << "Error occured while attempting to open file." << std::endl;
        exit(1);
    }
    
    char c;
    char lastC = '5';
    inf.get(c);
    while (c != '!')
    {
        
        inf.get(c);
        if(c == '#')
        {
            while(inf.get(c))
            {
                if(c == '\n')
                    break;
            }
        }
        if(c == 'x')
        {
            for(int i = 0; i < 5; i++)
            {
                inf.get(c);
                if (isdigit(c))
                {
                    x = atoi(&c);
                    inf.get(c);
                    if(isdigit(c))
                    {
                        x2 = atoi(&c);
                    }
                }
            }
        }
        
        if(c == 'y')
        {
            for(int i = 0; i < 5; i++)
            {
                inf.get(c);
                if (isdigit(c))
                {
                    y = atoi(&c);
                    inf.get(c);
                    if(isdigit(c))
                    {
                        y2 = atoi(&c);
                    }
                }
            }
        }
        
        if(y != 50)
        {
            // Not using x and y for the moment, may change in the future
//            if(x2 != 50)
//            {
//                x = x*10 + x2;
//            }
//            
//            if(y2 != 50)
//            {
//                y = y*10 + y2;
//            }
            
            while(c != '!')
            {
                lastC = c;
                inf.get(c);
                if(c == '\n')
                {
                    bool skip = false;
                    while(1)
                    {
                        skip = false;
                        
                        if(isdigit(c))
                        {

                            num1 = c - '0';
                            lastC = c;
                            inf.get(c);
                            if(isdigit(c))
                            {
                                num2 = c - '0';
                                num1 = num1*10;
                                lastC = c;
                                inf.get(c);
                                if(isdigit(c))
                                {
                                    num3 = c - '0';
                                    num2 = num2 * 10;
                                    num1 = num1 * 10;
                                }
                            }
                            num = num1 + num2 + num3;
                            num1 = 0;
                            num2 = 0;
                            num3 = 0;
                        }
                        
                        if(c == 'b')
                        {
                            if(lastC == 'o' || lastC == '$')
                            {
                                num = 1;
                            }
                            
                            for(int i = currX; i < currX+num; i++)
                            {
                                cell[i][currY] = 0;
                                tempCell[i][currY] = 0;
                            }
                            currX += num;
                        }
                        
                        if(c == 'o')
                        {
                            if(lastC == 'b' || lastC == '$')
                            {
                                num = 1;
                            }
                            
                            for(int i = currX; i < currX+num; i++)
                            {
                                cell[i][currY] = 1;
                                tempCell[i][currY] = 1;
                            }
                            currX += num;
                        }
                        
                        if(c == '$')
                        {
                            currY++;
                            currX = xCurr;
                        }
                        
                        if(c == '!')
                            break;
                        
                        if(!skip)
                        {
                            lastC = c;
                            inf.get(c);
                        }
                    }
                }
            }
        }
    }
    
    inf.close();                // close file
}
