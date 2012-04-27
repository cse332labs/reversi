// Atalie Holman (aholman@go.wustl.edu), Mason Allen (mrallen@wustl.edu), and Chris Lauber()
// 4-27-12
// ReadMe.txt - This file contains a summary of what you will find in each of the files of the Lab4 application.

TO-DO:
-testing and documenting
-update error section
-change our main source file from Lab4 to Lab5
-extras - Mason - describe extra functionality in save
-include memento details
========================================================================
    CONSOLE APPLICATION : Lab 5 Project Overview
========================================================================

SOURCE FILES:

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
	overridden virtual methods, references to abstractGame's methods, as well as new static methods.
	This game inherits from abstractGame.cpp

magicSquares.cpp
	This contains the methods and functions related to the magicSquare game class. This contains
	overridden virtual methods, references to abstractGame's methods, as well as new static methods.
	This game inherits from abstractGame.cpp

reversiGame.cpp
	This contains the methods and functions related to the mulitplayer reversiGame game class. It 
	contains overridden virtual methods, references to abstractGame's methods, as well as new static
	method. This game inherits from abstractGame.cpp.

gamePiece.cpp
	This contains the struct definitions of all gamePiece types (abstract, almond, reversi and 
	number tile). 
	
inputProcessing.cpp
	Contains methods to removePunctuation, make lowerCase, and to get the length of chars of an int

Point.cpp
	Contains the struct used as a two dimensional point for location purposes in the abstractGame 
	and	its inherited classes.

/////////////////////////////////////////////////////////////////////////////
HEADER FILES:

endCondition.h
	Contains the definition for the endCondition enum that is used as a return
	type by the game/program.

abstractGame.h
	Contains forward declarations for the abstractGame class

nineAlmonds.h
	Contains forward declarations for the nineAlmonds game class

magicSquares.h
	Contains forward declarations for the magicSquares game class

reversiGame.h
	Contains forward declarations for the reversiGame game class

Point.h
	Contains forward declarations for the struct Point, which is used for  board coordinate locations 
	in each game

inputProcessing.h
	Contains forward declarations for the input processing methods (lowerCase(), removePunctuation(),
	and getLength(), which returns the number of characters in an int).

gamePiece.h
	Contains the forward declarations for the gamePiece structs for all types (abstract, almond, and
	number tile).

/////////////////////////////////////////////////////////////////////////////
TEST CASES:
	We tested our program against a vareity of inputs. We found that it was able to handle most 
	game sizes (although there are some problems viewing extremely large boards on the console). 
	We tested it on a variety of inputs all of them are handled properly (negative, out of bounds, 
	etc).

/////////////////////////////////////////////////////////////////////////////
ERRORS: 

Linker 2001 and Linker 2019 errors

We have also faced errors with static/non-static objects as we implemented the Singleton pattern.

In lab 4, the only game that needed to handle extra arguments was Magic Square. We had to make changes
to allow for extra arguments to be passed in and handled to create either Magic Square and Reversi from
the abstractGame newGame method.

no significant compiler errors

/////////////////////////////////////////////////////////////////////////////
TEAMWORK:
Group members: Atalie Holman, Mason Allen, and Chris Lauber

We started with Atalie and Mason's code from Lab4 as a base. Mason had started save functionality during Lab4, so he
focused on implementing Memento while Atalie and Chris teamed up to implement reversi. Atalie worked on construction
and game set-up while Chris worked on game logic (play, done, turn, etc.).

To make code updating and sharing more efficient than working from one monitor or emailing versions back and forth,
we set up a github group account (https://github.com/cse332labs/reversi). While this took a little getting used to, 
it ultimately made merging and version control far more effective.

/////////////////////////////////////////////////////////////////////////////
EXTRAS:

Extra save features?