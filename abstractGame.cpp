//Lab 4 - Nine Almonds and Magic Squares
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu)
// 5-7-12
// abstractGame.cpp

#include "stdafx.h"
#include "abstractGame.h"
#include "nineAlmonds.h"
#include "magicSquares.h"
#include "reversiGame.h"
#include "inputProcessing.h"

abstractGame::abstractGame()
	: state_(SETUP), quitGuard_(true), quitting_(false), comingBack_(false), maxSymbol_(1), validFirst_(false) 
{
}

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

void abstractGame :: nameChecker()
{
	cout << "What would you like to name this game? ";
	listen();
	ifstream name;
	string gameType;

	name.open(name_ + ".txt");



	getline(name, gameType);

	lowerCase(gameType);
	removePunctuation(gameType);

	if(gameType == "ninealmonds")
	{
		loadAlmonds(name_);
		return;
	}
	else if(gameType =="magicsquare")
	{
		loadSquares(name_);
		return;
	}
	else if(gameType == "reversi")
	{

	}
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
			game->nameChecker();
			return game;
		}
		else if(gameName == "magicsquare" || gameName == "magicsquares")
		{
			abstractGame* game = new magicSquares(size, lowest);
			game->nameChecker();
			return game;
		}
		else if(gameName == "reversi" || gameName == "reversigame")
		{
			abstractGame* game = new reversiGame();
			game->nameChecker();
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
	boardx_=i;
	boardy_=i;
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
			name_=in1;
			cout << endl << endl;
			return;
		}
		else if(quitting_)
		{
			if(in1 == "yes")
			{
				this->createSave();
				return;
			}
			else
			{
				this->noSave();
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
					case WHITETURN:
						if(board_.count(p)==0)
						{
							dest_=p;
						}
						break;
					case BLACKTURN:
						if(board_.count(p)==0)
						{
							dest_=p;
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

void abstractGame :: noSave()
{
	ofstream save;

	save.open (name_ + ".txt");
	save << "NO SAVE DATA" << endl << endl;
}

void abstractGame :: setState(gameState s)
{
	state_ = s;
}

void abstractGame :: loadSave(string name)
{
	ifstream save;
	string input;

	save.open(name + ".txt");

	getline(save, input);

	lowerCase(input);
	removePunctuation(input);

	if(input == "ninealmonds")
	{
		loadAlmonds(name);
	}
	else if(input == "magicsquare" || input == "magicsquares")
	{
		loadSquares(name);
	}
	else
	{
		cout << "Sorry, that's not a valid game file. Please try again." << endl << endl;
		return;
	}
}

void abstractGame :: loadAlmonds(string name)
{
	nineAlmonds load = nineAlmonds();

	
	
	ifstream save;
	string input;

	save.open(name + ".txt");
	getline(save, input);
	input="";
	getline(save, input);
	lowerCase(input);
	removePunctuation(input);
	load.name_=name;
	input = "";

	getline(save, input);
	lowerCase(input);
	removePunctuation(input);

	istringstream ins(input);

	string in1, in2, in3, in4, in5;
	int int1, int2, int3, int4, int5;
	if(!(ins >> in1))
	{
		cout << "Sorry, that's not a valid game file. You're missing the turn value" << endl << endl;
		return;
	}
	if(!(ins >> in2))
	{
		cout << "Sorry, that's not a valid game file. You're missing the state value." << endl << endl;
		return;
	}
	if(!(ins >> in3))
	{
		cout << "Sorry, that's not a valid game file. You're missing the validFirst boolean" << endl << endl;
		return;
	}
	if(!(ins >> in4))
	{
		cout << "Sorry, that's not a valid game file. You're missing the Board X" << endl << endl;
		return;
	}
	if(!(ins >> in5))
	{
		cout << "Sorry, that's not a valid game file. You're missing the Board Y" << endl << endl;
		return;
	}

	gameState state = intToState(atoi(in2.c_str()));
	bool check1 = isNumber(in1);
	bool check2 = ((isNumber(in2)) && (state != BADSTATE));
	bool check3 = isNumber(in3);
	bool check4 = isNumber(in4);
	bool check5 = isNumber(in5);
	if(!(check1 && check2 && check3 && check4 && check5))
	{
		cout << "One of your items failed its validity check in line 3 [The line with 5 numers]" << endl << endl;
		return;
	}
	int1 = atoi(in1.c_str());
	int3 = atoi(in3.c_str());
	int4 = atoi(in4.c_str());
	int5 = atoi(in5.c_str());
	bool validFirst;
	if(int3 == 0)
	{
		validFirst=false;
	}
	else if (int3 == 1)
	{
		validFirst=true;
	}
	else
	{
		cout << "Sorry, that's not a valid game file. Your ValidFirst was not a 0 or 1" << endl << endl;
		return;
	}

	load.turn_=int1;
	load.state_=state;
	load.validFirst_=validFirst;
	load.boardx_=int4;
	load.boardy_=int5;

	input="";

	getline(save, input);

	lowerCase(input);
	removePunctuation(input);
	
	istringstream ins2(input);

	in1 = "", in2="", in3="", in4="", in5="";

	if(!(ins2 >> in1))
	{
		cout << "Sorry, that's not a valid game file. You're missing the Start Point X." << endl << endl;
		return;
	}
	if(!(ins2 >> in2))
	{
		cout << "Sorry, that's not a valid game file. You're missing the Start Point Y." << endl << endl;
		return;
	}
	if(!(ins2 >> in3))
	{
		cout << "Sorry, that's not a valid game file. You're missing Destination X." << endl << endl;
		return;
	}
	if(!(ins2 >> in4))
	{
		cout << "Sorry, that's not a valid game file. You're missing Destination Y." << endl << endl;
		return;
	}

	check1 = isNumber(in1);
	check2 = isNumber(in2);
	check3 = isNumber(in3);
	check4 = isNumber(in4);
	if(!(check1 && check2 && check3 && check4))
	{
		cout << "Sorry, that's not a valid game file. One of your start or end points failed validity check." << endl << endl;
		return;
	}
	int1 = atoi(in1.c_str());
	int2 = atoi(in2.c_str());
	int3 = atoi(in3.c_str());
	int4 = atoi(in4.c_str());

	Point start = Point(int1, int2);
	Point dest = Point(int3, int4);

	load.start_=start;
	load.dest_=dest;

	input = "";

	getline(save, input);

	lowerCase(input);
	removePunctuation(input);

	in1="", in2="", in3="", in4="";

	istringstream ins3(input);

	if(!(ins3>>in1))
	{
		cout << "Sorry, that's not a valid game file. You're missing the Original Point X." << endl << endl;
		return;
	}
	if(!(ins3>>in2))
	{
		cout << "Sorry, that's not a valid game file. you're missing the Original Point Y." << endl << endl;
		return;
	}
	
	check1 = isNumber(in1);
	check2 = isNumber(in2);

	if(!(check1 && check2))
	{
		cout << "Sorry, that's not a valid game file. Original Point failed validity." << endl << endl;
		return;
	}
	int1 = atoi(in1.c_str());
	int2 = atoi(in2.c_str());

	Point original = Point(int1, int2);
	load.original_=original;

	input = "";
	
	getline(save, input);
	lowerCase(input);
	removePunctuation(input);

	if(input != "board start")
	{
		cout << "Sorry, that's not a valid game file. The Board is not started properly." << endl << endl;
		return; 
	}

	input="";

	map<Point, gamePiece> board;

	bool boardDone = false;

	input="";
	getline(save, input);
	lowerCase(input);
	removePunctuation(input);

	while(!boardDone)
	{


	

	istringstream piece(input);

	string xval, yval, name, symbol;
	int xint, yint;
	
	if(!(piece >> xval))
	{
		cout << "Sorry, that's not a valid game file. You're missing an X value for a Piece. It has been skipped" << endl << endl;
	}
	if(!(piece >> yval))
	{
		cout << "Sorry, that's not a valid game file. You're missing a Y value for a Piece. It has been skipped." << endl << endl;
	}
	if(!(piece >> name))
	{
		cout << "Sorry, that's not a valid game file. You're missing the name for a piece. It has been skipped." << endl << endl;
	}
	if(!(piece >> symbol))
	{
		cout << "Sorry, that's not a valid game file. You're missing the symbol for a piece. It has been skipped." << endl << endl;
	}



	check1 = isNumber(xval);
	check2 = isNumber(yval);
	check3 = (name == "almond");
	check4 = (symbol == "a");

	xint = atoi(xval.c_str());
	yint = atoi(yval.c_str());

	if((xint <0 || yint < 0) || (xint > load.boardx_ || yint > load.boardy_))
	{
		cout << "A piece is out of bounds for this board. It has been skipped" << endl;
		break;
	}

	if(!(check1 && check2 && check3 && check4))
	{
		cout <<"Sorry, that's not a valid game file. One of your pieces failed a validity check." << endl << endl;
		return; 
	}

	almondPiece almond = almondPiece();

	board[Point(xint, yint)] = almond;

	input="";
	getline(save, input);
	lowerCase(input);
	removePunctuation(input);

	if(input == "end")
	{
		boardDone=true;
	}

	}

	load.board_=board;
	load.comingBack_=true;
	*this=load;
	
}

void abstractGame :: loadSquares(string name)
{
	ifstream save;
	string input;

	save.open(name + ".txt");
	getline(save, input);

	lowerCase(input);
	removePunctuation(input);


}

gameState abstractGame :: intToState(int i)
{
	switch(i)
	{
	case 0:
		return SETUP;
	case 1:
		return TURNSTART;
	case 2:
		return FIRSTLOCKED;
	case 3:
		return NEEDPIECE;
	case 4:
		return NEEDLOC;
	case 5:
		return EXTENDEDTURN;
	case 6:
		return ENDTURN;
	case 7:
		return FINISHED;
	case 8: 
		return QUITTING;
	default:
		return BADSTATE;
	}
}

void abstractGame :: isQuitting()
{
	quitting_=true;
}