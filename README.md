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
in the linepuffer file I uploaded)
Place linepuffer.rle inside the directory where the programs exe file exists. When you run the program and the window
has opened up, press the LEFT directional key and it will run the file.


The reader is not necessary to enjoy the program, though. Once you run it and the window pops up you can draw
your own patterns (although large patterns would take quite a while) and after you've finished the initial pattern
you simply press the UP key on your keyboard. If drawing is boring and you'd rather watch life unfold, then instead
press the DOWN key and a certain percentage of the cells will be filled with living cells

The constants header file contains variables which gives you some ability to control the program, such as FPS, 
resolution and size of life grid.

To quit, just exit the window (as of now you cant quit while in draw mode, only after you have begun the simulation)
