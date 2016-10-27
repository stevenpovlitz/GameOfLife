# Game-Of-Life

C++ class based implementation of Conway's Game of Life

![alt tag](http://i.imgur.com/7uZckVq.gif)


## Memory Savings
Most Implementations of Conway's Game Of Life usually require two boards. One for the current step, and one to store the next step. By having all conceptions of x-y coordinates stored in the loops rather than each node knowing its position, additional nodes add very little memory pressure. 

To save space with the board, we simply use one board and two vectors storing the current and previous lines. To achieve this efficiency, we retain the current line being evaluated and the line above it in vectors. When the current line is finished being evaluated, then the previous line no longer has any effect on the rest of the board, and therefore is able to be saved. The program then loads the next line into a temp array, continuing  until it reaches the end of the board.

Each node in the board only stores one boolean, indicating whether it is alive or not. They do not have a conception of their coordinate on the board. 

## Credits
Created Ian Granger (https://github.com/icgranger9) and Steven Povlitz (me)
