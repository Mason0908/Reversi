This is submitted as assignment of CS 246 at University of Waterloo


In this problem, you will use C++ classes to implement the game of Reversi. (https://en.wikipedia.org/ wiki/Reversi). An instance of Reversi consists of an n × n-grid of cells, each of which can be either empty, black, or white. When the game begins the middle 4 cells are populated following the pattern Black-White-Black-White. Reversi is a two-player game where players take turns placing a piece of their colour in a cell. Black plays first. The goal of Reversi is to have the most cells holding pieces of your colour at the end of the game. If a new piece A would form a line segment with an existing piece B of the same colour, such that all of the cells in between are occupied and of the opposite colour, those in-between pieces are flipped to the same colour as A and B. There is one slight difference from standard Reversi: whereas a legal move in standard Reversi must cause at least one flip, your program is not required to enforce this rule. This means that on any turn players can play a piece on any cell, so long as that cell is within the grid and not currently occupied by another piece.
To implement the game, you will use the following classes:
• class Subject — abstract base class for subjects (see provided subject.h);
• class Observer — abstract base class for observers (see provided observer.h);
• class Cell — implements a single cell in the grid (see provided cell.h);
• class Grid — implements a two-dimensional grid of cells (see provided grid.h);
• struct State — provides a representation of a cells state (see provided state.h);
• class TextDisplay—keepstrackofthecharactergridtobedisplayedonthescreen(seeprovidedtextdisplay.h); • file info.h structure definition for queries issued by the observer on the subject.
Note: you are not allowed to change the public interface of these classes (i.e., you may not add public fields or methods),
but you may add private fields or methods if you want.
Your solution to this problem must employ the Observer pattern. Each cell of the grid is an observer of all of its neighbours (that means that class Cell is its own observer). Thus, when the grid calls notifyNeighbours on a given cell, that cell must then call the notify method on each of its neighbours (each cell is told who its neighbours are when the grid is initialized). Moreover, the TextDisplay class is an observer of every cell (this is also set up when the grid is initialized). A subject’s collection of observers does not distinguish what kinds of observers are actually in the collection (so a cell could have arbitrary cells or displays subscribed to it). When the time comes to notify observers, you just go through the collection and notify them.
As a hint for implementation, consider how the rules of the game above can be replicated using an observer pattern where a notification can either be a notification of a new piece, a relay of that new piece message, or a reply to that new piece being found. A cell that receives a new piece can notify its observers (adjacent cells) that it has received a new piece of a certain colour. The cells notified of a new piece by their neighbour can relay that message along the line. When a message is received by a cell that contains the same colour piece as the new piece, it can reply back in a similar fashion. Hence, when a piece matching the colour of the new piece is reached, the message stops relaying and instead replies back. Similarly if there are no pieces in a cell to relay a message then it should stop. Since the observer pattern doesn’t distinguish what observers are in the collection the cell receiving a new piece can’t send out specific information about the direction of each line to its appropriate neighbours. However, when a neighbour receives a notification of a new piece they can check the information passed along and determine what direction they are from the original piece, and relay that information along. For more information on these messages see the state.h file provided to you.
You are to overload operator<< for the text display, such that the entire grid is printed out when this operator is invoked. Each empty cell prints as - and a cell with a white or black piece prints as W or B respectively. Further, you are to overload operator<< for grids, such that printing a grid invokes operator<< for the text display, thus making the grid appear on the screen.
When you run your program, it will listen on stdin for commands. Your program must accept the following commands:
• new nCreatesanewn×ngrid,wheren ≥ 4∧n ≡ 0(mod2). Iftherewasalreadyanactivegrid,thatgridis destroyed and replaced with the new one. When setting up the new grid your program should intialize the middle 4 squares following the Black-White-Black-White pattern.
Page 6 of 9
ASSIGNMENT #4 CS246, WINTER 2020
 • play r c Within a game, plays a piece at row r, column c of the colour corresponding to the player who’s move it is. If the row and column entered correspond to a cell that already has a piece, or a position outside the grid, then the input is ignored and nothing is done.
The program ends when the input stream is exhausted, or when the game is over. The game is over when there are no more empty cells on the grid.,
Whenthegameisover,iftheblackplayerwinstheprogramshoulddisplayBlack Wins!tostdoutbeforeterminating; if the white player wins it should display White Wins!; otherwise it should display Tie!. If input was exhausted before the game was won or lost, it should display nothing. A sample interaction follows (responses from the program are in italics):
new 8
-------- -------- -------- ---BW--- ---WB--- -------- -------- -------- play 3 5 -------- -------- -------- ---BBB-- ---WB--- -------- -------- -------- play 3 6 -------- -------- -------- ---BBBW- ---WB--- -------- -------- -------- play 3 2 -------- -------- -------- --BBBBW- ---WB--- -------- -------- -------- play 2 3 -------- -------- ---W---- --BWBBW- ---WB--- -------- --------
Page 7 of 9

ASSIGNMENT #4
CS246, WINTER 2020
 --------
play 0 0
B------- -------- ---W---- --BWBBW- ---WB--- -------- -------- -------- play 3 1 B------- -------- ---W---- -WWWBBW- ---WB--- -------- -------- -------- play 7 7 B------- -------- ---W---- -WWWBBW- ---WB--- -------- -------- -------B ˆd
Note: Your program should be well documented and employ proper programming style. It should not leak memory. Markers will be checking for these things.
Due on Due Date 2: Submit your solution. You must include a Makefile, such that issuing the command make will build your program. The executable should be called a4q4.
Question 5
Note: there is no sample executable for this problem, and no Marmoset tests. This problem will be entirely hand- marked. In this problem, you will adapt your solution from problem 4 to produce a graphical display. You are provided with a class Xwindow (files window.h and window.cc), to handle the mechanics of getting graphics to display. Declaring an Xwindow object (e.g., Xwindow xw;) causes a window to appear. When the object goes out of scope, the window will disappear (thanks to the destructor). The class supports methods for drawing rectangles and printing text in five different colours. For this assignment, you should only need black, white, and blue rectangles. In the graphical representation let blue represent an empty cell, black represent a cell containing a piece from the black player, and white represent a cell containing a piece from the white player. To do so you must complete the following tasks:
• Create a GraphicsDisplay class as a subclass of the abstract base class Observer, and register it as an observer of each cell object.
• The class GraphicsDisplay will be responsible for mapping the row and column numbers of a given cell object to the corresponding coordinates of the squares in the window.
• Your GraphicsDisplay class should have a composition relationship with Xwindow. So your constructor for GraphicsDisplay should also create a Xwindow object which is a member of the GraphicsDisplay class.
Page 8 of 9

ASSIGNMENT #4 CS246, WINTER 2020
 Each time a new game is created you should create a new GraphicsDisplay to set up an appropriate window for the game size.
• Your cell objects should not have to change at all.
The window you create should be of size 500×500, which is the default for the Xwindow class. The larger the grid you
create, the smaller the individual squares will be.
Note: to compile this program, you need to pass the option -lX11 to the compiler at link time. For example:
g++ -std=c++14 *.o -o a4q5 -lX11
This option is not relevant during compilation, so it should not be put in your CXXFLAGS variable. You should only use it
during the linking stage, i.e., the command that builds your final executable.
Note: Your program should be well documented and employ proper programming style. It should not leak memory (note, however, that the given Xwindow class leaks a small amount of memory; this is a known issue). Markers will be checking for these things.
Due on Due Date 2: Submit your solution. You must include a Makefile, such that issuing the command make will build your program. The executable should be called a4q5.