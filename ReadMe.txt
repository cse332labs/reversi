Graded by: Calvin Murdock (calvinmurdock@wustl.edu)
Score: 94/100 + 5 extra credit = 99/100
Comments:

Lab was received within the granted 1-day extension.

There were no errors/warnings when compiling your code.

-1: Don't use hard-coded constants. (Print the almond piece symbol instead.)

-5: Be sure sure to call the delete operator just before _any_ point where control flow would leave the program.
	(If play throws a QUIT exception, then the program will terminate without deallocating memory.)

All of our tests completed successfully; great lab!

------------------------------------------------------------------------------------------------------

// Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu)
// 5-7-12
// ReadMe.txt

========================================================================
    CONSOLE APPLICATION : Lab4 Project Overview
========================================================================

Important: We have a one day extension on this lab from Professor Gill

This file contains a summary of what you will find in each of the files of the Lab4 application.

Lab4.cpp
    This is the main application source file. This contains the main function which creates
	an abstractGame pointer that it assigns using a special function newGame() that uses the
	program arguments to create and assign a game to the pointer. Returns an endCondition, a
	typedef enum.

abstractGame.cpp
	This contains the methods and functions related to the abstract game. Many of the virtual
	functions have their intial definitions here. This is the class that is extended by 
	nineAlmonds and magicSquares

nineAlmonds.cpp
	This contains the methods and functions related to the nineAlmonds game class. This contains
	overriden virtual methods, references to abstractGame's methods, as well as new static methods.
	This game inherits from abstractGame.cpp

magicSquares.cpp
	This contains the methods and functions related to the magicSquare game class. This contains
	overriden virtual methods, references to abstractGame's methods, as well as new static methods.
	This game inherits from abstractGame.cpp

gamePiece.cpp
	This contains the struct definitions of all gamePiece types (abstract, almond, and number tile). 
	
inputProcessing.cpp
	Contains methods to removePunctuation, make lowerCase, and to get the length of chars of an int

Point.cpp
	Contains the struct used as a two dimensional point for location purposes in the abstractGame and
	its inherited classes.

/////////////////////////////////////////////////////////////////////////////

Header files:

endCondition.h
	Contains the definition for the endCondition enum that is used as a return
	type by the game/program.

abstractGame.h
	Contains forward declarations for the abstractGame class

nineAlmonds.h
	Contains forward declarations for the nineAlmonds game class

magicSquares.h
	Contains forward declarations for the magicSquares game class

Point.h
	Contains forward declarations for the struct Point, which is used for location in the game

inputProcessing.h
	Contains forward declarations for the input processing methods (lowerCase(), removePunctuation(),
	and getLength(), which returns the number of characters in an int).

gamePiece.h
	Contains the forward declarations for the gamePiece structs for all types (abstract, almond, and
	number tile).

/////////////////////////////////////////////////////////////////////////////
TEST CASES:
	We tested our program against a vareity of inputs. We found that it was able to handle most game sizes
	(although there are some problems viewing extremely large boards on the console). We tested it on a variety of 
	inputs all of them are handled properly (negative, out of bounds, etc).

/////////////////////////////////////////////////////////////////////////////
Errors:

We encountered a lot of errors with declaring friend methods and scoping them incorrectly. We resolved
these by only applying the scope operator to methods contained directly within a class (not including friend
declaration).

We also encountered errors when assigning the pointer values in newGame. We had difficulty as the value was 
always being stored as zero, because we were returning the local address and the object was being popped after
the frame was closed.

Lastly, we had issues with printing, which was complicated by the addition of n x n in magicSquares as well some
one off errors.

When dealing with negative values, we had to modify our code to allow the minus sign to be accepted and the number
to be correctly stored.

/////////////////////////////////////////////////////////////////////////////
Teamwork:
Group members: Atalie Holman and Mason Allen

We started with Mason's code from Lab3 as a base. Because Mason was more familiar with his code, he took on code 
refactoring. Atalie wrote the print methods and helped with pointers. We worked together on the game logic and 
many hours of debugging.

/////////////////////////////////////////////////////////////////////////////
Extra Credit:

We originally had the game prompt you for board size during the creation of the board, but that was taken out. Instead, we have the 
newGame method create a placeholder value of each default condition (size = 3, starting value = 1) and then we try to extract new values
to replace them. If those fail, it uses the default condition. We also had to change the way we calculated if someone was finished 
becuase we originally used the magic constant formula ((n(n^2+1))/2) but that was changed with the ability to move starting value.
Now we simply check to make sure they all sum to the same value, which we select as the sum of row 0. If any of them are different
than this, done returns false.

H:\My Documents\Visual Studio 2010\Projects\Lab4\Debug>Lab4.exe magicSquares 3 -9
 y
  |-----------|
2 |   |   |   |
  |-----------|
1 |   |   |   |
  |-----------|
0 |   |   |   |
  |-----------|
    0   1   2  x

 Available Pieces: -9 -8 -7 -6 -5 -4 -3 -2 -1


Which piece do you want to move? -2
 y
  |-----------|
2 |   |   |   |
  |-----------|
1 |   |   |   |
  |-----------|
0 |   |   |   |
  |-----------|
    0   1   2  x

 Available Pieces: -9 -8 -7 -6 -5 -4 -3 -2 -1


Where do you want to place that piece? 0,2
  y
  |--------------|
2 | -2 |    |    |
  |--------------|
1 |    |    |    |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -9 -8 -7 -6 -5 -4 -3 -1


Which piece do you want to move? -7
  y
  |--------------|
2 | -2 |    |    |
  |--------------|
1 |    |    |    |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -9 -8 -7 -6 -5 -4 -3 -1


Where do you want to place that piece? 1,2
  y
  |--------------|
2 | -2 | -7 |    |
  |--------------|
1 |    |    |    |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -9 -8 -6 -5 -4 -3 -1


Which piece do you want to move? 2
  y
  |--------------|
2 | -2 | -7 |    |
  |--------------|
1 |    |    |    |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -9 -8 -6 -5 -4 -3 -1


Which piece do you want to move? -6
  y
  |--------------|
2 | -2 | -7 |    |
  |--------------|
1 |    |    |    |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -9 -8 -6 -5 -4 -3 -1


Where do you want to place that piece? 2,2
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 |    |    |    |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -9 -8 -5 -4 -3 -1


Which piece do you want to move? -9
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 |    |    |    |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -9 -8 -5 -4 -3 -1


Where do you want to place that piece? 0,1
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 | -9 |    |    |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -8 -5 -4 -3 -1


Which piece do you want to move? -5
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 | -9 |    |    |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -8 -5 -4 -3 -1


Where do you want to place that piece? 1,1
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 | -9 | -5 |    |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -8 -4 -3 -1


Which piece do you want to move? -1
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 | -9 | -5 |    |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -8 -4 -3 -1


Where do you want to place that piece? 2,1
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 | -9 | -5 | -1 |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -8 -4 -3


Which piece do you want to move? -4
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 | -9 | -5 | -1 |
  |--------------|
0 |    |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -8 -4 -3


Where do you want to place that piece? 0,0
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 | -9 | -5 | -1 |
  |--------------|
0 | -4 |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -8 -3


Which piece do you want to move? -3
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 | -9 | -5 | -1 |
  |--------------|
0 | -4 |    |    |
  |--------------|
     0    1    2  x

 Available Pieces: -8 -3


Where do you want to place that piece? 1,0
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 | -9 | -5 | -1 |
  |--------------|
0 | -4 | -3 |    |
  |--------------|
     0    1    2  x

 Available Pieces: -8


Which piece do you want to move? -8
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 | -9 | -5 | -1 |
  |--------------|
0 | -4 | -3 |    |
  |--------------|
     0    1    2  x

 Available Pieces: -8


Where do you want to place that piece? 2,0
  y
  |--------------|
2 | -2 | -7 | -6 |
  |--------------|
1 | -9 | -5 | -1 |
  |--------------|
0 | -4 | -3 | -8 |
  |--------------|
     0    1    2  x

 Available Pieces:


Congratulations! You completed the Magic Square Game of size 3 x 3.
You made 1 undoes/invalid moves while placing the pieces.