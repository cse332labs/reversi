//Lab 4 - Nine Almonds and Magic Squares
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu)
// 5-7-12
// abstractGame.cpp

#include "stdafx.h"
#include "abstractGame.h"
#include "nineAlmonds.h"
#include "magicSquares.h"
#include "inputProcessing.h"

abstractGame::abstractGame()
	: state_(SETUP), quitGuard_(true), maxSymbol_(1), validFirst_(false) {}

//basic piecemover for the all games. moves piece at Map[start] to map[finished] 
// if no piece is there or the destination is full, return false
bool abstractGame :: pieceMover(Point start, Point destination)
{
	if(board_.count(start)==1 && board_.count(destination)==0)
	{
		board_.at(destination)=board_.at(start);
		board_.erase(start);
		return true;
	}
	else
		return false;
}


// returns a pointer of AbstractGame type that is based off the string in argv[1]
// if there are improper argument numbers (or the argv[1] is not a valid game name)
// the pointer is null, otherwise it is to the appropriate game type.
abstractGame* abstractGame::newGame(int argc, char* argv[])
{
	enum{PROGRAMNAME, GAMENAME, SIZE, LOWEST};
	string gameName;
	int lowest = 1;
	int size = 3;
	switch(argc)
	{
	case 4:
	{
		istringstream lowestString(argv[LOWEST]);

		lowestString>>lowest;
	}
	case 3:
	{
		istringstream sizeString(argv[SIZE]);
		if(sizeString >> size)
		{
			if(size <= 0)
			{
				cout << "That isn't a valid size. Exiting Program";
				return 0;
			}
		}
		else
		{
			cout << "That isn't a valid size. Exiting Program";
			return 0;
		}
	}
	case 2:
	{
		gameName = argv[GAMENAME];
		lowerCase(gameName);
		removePunctuation(gameName);
		break;
	}
	default:
		return 0;
	}

	try
	{
		if(gameName == "ninealmonds")
		{
			abstractGame* game = new nineAlmonds();
			return game;
		}
		else if(gameName == "magicsquare" || gameName == "magicsquares")
		{
			abstractGame* game = new magicSquares(size, lowest);
			return game;
		}
		return 0;

	}
	catch (bad_alloc ba)
	{
		cout << "Failed to allocate memory. " << ba.what() << endl;
		return 0;
	}
}

// state accessor
gameState abstractGame :: getState()
{
	return state_;
}

// sets board dimensions equal to i x i
void abstractGame :: setBoardDim(int i)
{
	cout << "wut" << endl;
	return;
}

// uses the gameState enum to determine appropriate prompt for user.
void abstractGame :: prompt()
{
	switch(state_)
	{
	case TURNSTART:
		cout << "Please select a piece to move.  ";
		break;
	case FIRSTLOCKED:
		cout << "Moving Piece at " << start_ << ". Where would you like to move it? ";
		break;
	case EXTENDEDTURN:
		cout << "Continuing turn. Where would you like to move to next? " << endl << "You may type 'done' or 'finished' to end your turn. ";
		break;
	default:
		break;
	}
}

// called when a user input is needed. it uses gameState as well as other variables
// to determine appropriate action. Information is extracted into a string, which is 
// put into an istringstream and sanitized before functions are called.
void abstractGame :: listen()
{
	if(state_ == ENDTURN || state_ == FINISHED)
	{
		return;
	}
	string input;
	getline(cin, input);
	lowerCase(input);
	removePunctuation(input);
	istringstream iss(input);
	string in1, in2;

	if(iss >> in1)
	{
		if(state_==SETUP)
		{
			bool num1=true;
			for(unsigned int i = 0; i < in1.length(); ++i)
			{
				if(!isdigit(in1.at(i)))
				{
					num1=false;
				}
			}
			if(num1)
			{
				this->setBoardDim(atoi(in1.c_str()));
				return;
			}
		}
		if(iss >> in2)
		{
			bool num1 = true, num2 = true;
			for(unsigned int i = 0; i < in2.length(); ++i)
			{
				if(!isdigit(in2.at(i)))
				{
					num2=false;
				}
			}
			if(num1 && num2)
			{
				int x = atoi(in1.c_str());
				int y = atoi(in2.c_str());
				if(x>=0 && y>= 0)
				{
					Point p = Point(x, y);
					switch(state_)
					{
					case NEEDLOC:
						if(board_.count(p)==0 && p.x_ < boardx_ && p.y_ <boardy_)
						{
							start_=p;
							state_=EXTENDEDTURN;
							return;
						}
						else
						{
							cout << "There is already a piece there. Try again" << endl;
							listen();
						}
						break;
					case TURNSTART:
						if(board_.count(p)==1)
						{
							start_=p;
							state_=FIRSTLOCKED;
						}
						break;
					case FIRSTLOCKED:
						if(board_.count(p)==0)
						{
							dest_=p;
							if(pieceMover(start_, dest_))
							{
								state_=EXTENDEDTURN;
								start_=dest_;
							}
						}
						break;
					case EXTENDEDTURN:
						if(board_.count(p)==0)
						{
							dest_=p;
							if(pieceMover(start_, dest_))
							{
								start_=dest_;
							}
						}
						break;
					default:
						cout << "You can't choose a piece right now. Try again later" << endl;
					}
				}
			}
		}
		else if(in1 == "quit" || !quitGuard_)
		{
			if(quitGuard_)
			{
				quitGuard_=false;
				cout << "Are you sure you want to quit? Type 'yes' to confirm. ";
				this->listen();
			}
			else if(in1 != "yes")
			{
				quitGuard_=true;
				return;
			}
			else
				throw QUIT;
		}
		else if(in1 == "cancel")
		{
			state_ = NEEDPIECE;
		}
		else if(in1 == "undo")
		{
			this->undo();
			return;
		}
		else if(in1 == "finished" || in1 == "fin" || in1 == "done")
		{
			if(validFirst_)
			{
				state_=ENDTURN;
				return;
			}
			else
			{
				cout << "You can't end your turn until you've made at least one valid turn!" << endl << endl;
				return;
			}
		}
		else if(in1 == "board")
		{
			this->print();
			return;
		}
		else
		{
			cout << "I'm sorry, that doesn't appear to be a valid command. Try again." << endl << endl;
		}
	}
}

// maxSymbol accessor
int abstractGame :: maxSymbol()
{
	return maxSymbol_;
}
