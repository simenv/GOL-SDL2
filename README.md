# GOL-SDL2
Game of life using SDL2 frameworks

Basically transferred my Java GOL to c++ using the SDL2 framework.

First off: It's far from done and it doesn't look pretty. I will be working to make it a bit more modular
and organized in time and as I learn a bit more stuff. Moving the SDL functions to their own .cpp file 
and possibly moving the life calculations to the GOL helper functions file, etc.

I will also (probably):
- Add buttons
- Add popup window for opening pattern files
- Add various options like frames-per-sec and perhaps modifying ruleset while it's going on
- Prettier graphics
- Option to read more than just RLE files (.lif, .cells)
- Plan to add more constants to constants.h so that, pre-buttons, one can simply go into the constants header 
to experiment with settings.


RLE reader (fromFileToLife()):
The reader supposedly reads from the RLE file and makes the appropriate cells dead or alive.
I doesn't work very well. I can get a linepuffer to function, but thats only because I modified the content
inside the file a bit (read the encoding rules (<a href="http://www.conwaylife.com/wiki/Run_Length_Encoded" target="_blank">Here</a>) for the RLE format and you might see what I modified 
in the linepuffer file below)

Here is the text inside the RLE file for the linepuffer:

\#N Line-puffer
\#O Tim Coe
\#C A c/2 orthogonal line-puffer of width 76
x = 156, y = 32, rule = b3/s23
34b3o27b3o13b3o27b3o43b$33b1o3b1o25b1o3b1o11b1o3b1o25b1o3b1o42b$32b2o4b1o11b1o
11b1o4b2o9b2o4b1o11b1o11b1o4b2o41b$31b1o1b1o1b2o1b2o3b4o1b2o1b2o1b4o3b2o1b2o1b1o1b1o7b1o
1b1o1b2o1b2o3b4o1b2o1b2o1b4o3b2o1b2o1b1o1b1o40b$30b2o1b1o4b1o1b2o1b4o7b4o1b2o1b1o4b1o1b2o5b
2o1b1o4b1o1b2o1b4o7b4o1b2o1b1o4b1o1b2o39b$29b1o4b1o3b1o4b1o2b2o1b1o1b1o1b2o2b1o4b1o3b1o4b1o3b
1o4b1o3b1o4b1o2b2o1b1o1b1o1b2o2b1o4b1o3b1o4b1o38b$6b1o17b1o16b1o4b1o7b1o4b1o27b1o4b1o7b1o4b1o
25b1o17b1o6b$5b3o15b3o3b2o7b2o6b1o7b1o6b2o7b2o3b2o7b2o6b1o7b1o6b2o7b2o12b3o
15b3o5b$3b2o1b3o13b3o1b2o100b2o1b3o13b3o1b2o3b$4b1o2b1o1b2o4b1o4b2o1b1o2b1o18b2o
7b2o35b2o7b2o27b1o2b1o1b2o4b1o4b2o1b1o2b1o4b$1b2o1b1o4b1o1b1o1b2o1b2o1b1o1b1o4b1o1b2o17b1o5b
1o39b1o5b1o26b2o1b1o4b1o1b1o1b2o1b2o1b1o1b1o4b1o1b2o1b$1b2o1b1o1b1o2b1o1b1o7b1o1b1o2b1o1b1o1b2o15b1o2b1o
3b1o2b1o35b1o2b1o3b1o2b1o24b2o1b1o1b1o2b1o1b1o7b1o1b1o2b1o1b1o1b2o1b$1b1o8b3o1b1o1b1o1b3o8b1o16b1o2b
1o1b1o2b1o37b1o2b1o1b1o2b1o25b1o8b3o1b1o1b1o1b3o8b1o1b$2o7b2o9b2o7b3o1b1o15b1o1b1o43b1o1b1o24b1o
b3o7b2o9b2o7b2o$33b2o12b1o1b1o1b1o1b1o39b1o1b1o1b1o1b1o21b2o33b$31b2o1b1o11b2o1b1o1b1o1b2o
37b2o1b1o1b1o1b2o20b1o1b2o31b$34b2o9b1o3b1o1b1o3b1o35b1o3b1o1b1o3b1o18b2o34b$33b1o88b1o
33b$35b3o7b2o1b2o1b2o1b2o35b2o1b2o1b2o1b2o16b3o35b$7b3o15b3o9b2o78b2o9b3o15b
3o7b$6b1o3b1o13b1o3b1o9b1o7b1o3b1o3b1o37b1o3b1o3b1o16b1o9b1o3b1o13b1o3b1o6b$5b2o4b1o11b
1o4b2o8b2o6b1o3b1o3b1o7b3o9b3o9b3o3b1o3b1o3b1o4b3o8b2o8b2o4b1o11b1o4b2o5b$4b1o1b1o
1b2o1b2o3b3o3b2o1b2o1b1o1b1o8b1o21b1o3b1o7b1o3b1o7b1o3b1o14b1o3b1o7b1o8b1o1b1o1b2ob2o3b3o3b
2o1b2o1b1o1b1o4b$3b2o1b1o4b1o1b2o1b3o1b2o1b1o4b1o1b2o6b1o1b1o5b2o5b2o5b2o3b2o5b2o3b2o5b
2o3b2o5b2o5b2o3b2o5b1o1b1o6b2o1b1o4b1o1b2o1b3o1b2o1b1o4bo1b2o3b$2b1o4b1o3b1o4b1ob1o4b1o
3b1o4b1o6b3o3b4o3b4o3b2o1b1o1b1o1b2o3b2o1b1o1b1o1b2o3b2o1b1o1b1o1b2o3b4o3b2o1b1o1b1o1b2o3b3o
6b1o4b1o3b1o4b1ob1o4b1o3b1o4b1o2b$14b1o5b1o20b2o1b2o2b2o1b2o2b2o1b2o1b2o1b2o1b2o1b2o1b2o
1b2o1b2o1b2o1b2o1b2o1b2o1b2o2b2o1b2o1b2o1b2o1b2o1b2o20b1o5b1o14b$2b2o7b2o9b2o7b2o1b3o
5b1o1b1o4b1o1b1o4b1o1b1o3b1o1b1o3b1o1b1o3b1o1b1o3b1o1b1o3b1o1b1o3b1o1b1o4b1o1b1o3b1o1b1o3b1o1b1o5b3o1b2o7b
2o9b2o7b2o2b$36b1o82b1o36b$34bo6b2o1b2o2b2o1b2o2b2o1b2o1b2o1b2o1b2o1b2o1b2o1b2o1b
2o1b2o1b2o1b2o1b2o1b2o2b2o1b2o1b2o1b2o1b2o1b2o6bo34b$34b1o1b2o80b2o1b1o34b$39b78o39b
$38b1o78b1o!

Just put it into a vanilla text file(.txt only, no encoding) and change the name to  linepuffer.rle, then place it 
into the directory where the program's exe file exists. When you run the program and the window has opened up, press 
the LEFT directional key and it will run the file.


The reader is not necessary to enjoy the program, though. Once you run it and the window pops up you can draw
your own patterns (although large patterns would take quite a while) and after you've finished the initial pattern
you simply press the UP key on your keyboard. If drawing is boring and you'd rather watch life unfold, then instead
press the DOWN key and a certain percentage of the cells will be filled with living cells

The constants header file contains variables which gives you some ability to control the program, such as FPS, 
resolution and size of life grid.

To quit, just exit the window (as of now you cant quit while in draw mode, only after you have begun the simulation)
