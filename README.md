Showcase of a school project.
The assignment was to make a GUI to play Binairo. The Binairo model code was premade, but 
modification/adding rules was allowed (the model initially did not include all Binairo rules).

Below I list implemented features and my grade. For a more in-depth documentation, see the file /binairo_gui/instructions.txt.
In total, 100 points were available, and i got 90.

**Minimum requirements (worth 50 points):**
- display a game window and binairo grid to player
- allow player the choice between a randomly generated binairo board, or a string-inputted board
- size of the Binairo board must be easy to change in code (by changing global constant NUMBER_OF_SYMBOLS)
- display and update the state of the game, i.e. which cells are filled and which ones are empty
- implement a way to reset the game whenever you like, be it before, during or after a game
- when the game is over, display the time it took to finish
- define and document all implemented features (undocumented features not graded; applies to bonus features, too)
  
I got 40/50 points for minimum features, although the 10 point reduction came for reasons I don't quite understand.
Something about having extraneous files and folders in my project repository. I did implement all the minimum features quite excellently.

**Bonus features (worth another 50 points):**
We were allowed to implement any bonus features we liked. Some features were given as examples, 
and others I came up with myself. Pregiven features I implemented:
- Binairo grid was implemented with pictures, not text
- user can change grid size in the UI, not only through code
- background changes color when game is won
- the third rule of Binairo (identical rows/columns not allowed)
- an info/help button with instructions and documentation
- pause button
- something (the info text) is shown in a separate window
I added also:
- third setup option: manual placement of stones on the board
- user input is intuitive: right and left mouse button add different colored stones, and are also used for removing stones.
- the starting board is immutable, i.e. the preset stones cannot be altered or removed after the game starts
- a clear graphical indication of which stones can and cannot be changed
- two ways to reset: either reset the current board, or generate a brand new one
- extra-beautiful GUI

For these bonus features, I got 50/50 points.
  

