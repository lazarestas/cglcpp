<h2> Conway`s game of life in c++</h2> 
<h4>by @lazarestas (thx to Nupellot and Bezzubik)</h4>

![Gospers_glider_gun.gif](crap/Gospers_glider_gun.gif)

<h3>Rules</h3>
Rules
The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells,
each of which is in one of two possible states, live or dead (or populated and unpopulated, respectively).<br> 
Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. <br>
At each step in time, the following transitions occur:<br>
<br>
Any live cell with fewer than two live neighbours dies, as if by underpopulation.<br>
Any live cell with two or three live neighbours lives on to the next generation.<br>
Any live cell with more than three live neighbours dies, as if by overpopulation.<br>
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.<br>
These rules, which compare the behaviour of the automaton to real life, can be condensed into the following:<br>
<br>
Any live cell with two or three live neighbours survives.<br>
Any dead cell with three live neighbours becomes a live cell.<br>
All other live cells die in the next generation. Similarly, all other dead cells stay dead.<br>
The initial pattern constitutes the seed of the system. <br>
<br>
The first generation is created by applying the above rules simultaneously to every cell in the seed, live or dead; <br>
births and deaths occur simultaneously, and the discrete moment at which this happens is sometimes called a tick.<br>
Each generation is a pure function of the preceding one. <br>
The rules continue to be applied repeatedly to create further generations.

![img.png](crap/img.png)

<h3>Requirements:</h3>

1. Working simulation with autoframechange (in console)
2. Errors should be working EVERYWHERE please future me do not ignore
3. Customizable field properties (such as x/y size and looping)
4. Start/stop functionality 
5. Importing/exporting from/to text file (and input standart)
6. Some stats and cycle detection
7. Example base
8. Building tools to correct the frame
9. Windows GUI (next lvl play aha)
10. end goal - cgl in cgl would be kinda cool

<h3> Design:</h3>

1. main logic v1
2. output and error handling v1
3. i/o v1
4. file interaction v1
5. stats place v1
6. general menu layout

//
notes on main logic v1 <br>
THE FIELD will be built from 2d array of "Cells", which carry properties like dead/alive <br>
and their coordinates (not sure if i need coordinates) <br>
random filling the field will murder testing so for beginnig will use <br>
0000 <br>
0110 <br>
0100 <br>
0000 <br>
which is ok for the first test (lets name that CreateDefautArr)  <br>
THE STEP for the simulation means that you need to take the field, convert to the following <br>
frame and write that to the existing one <br>
