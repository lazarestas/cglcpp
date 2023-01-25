<h2> Conway`s game of life by @lazarestas (thx to Nupellot and Bezzubik)</h2>

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
