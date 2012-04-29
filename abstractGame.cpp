///Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// abstractGame.cpp

#include "stdafx.h"
#include "abstractGame.h"
#include "nineAlmonds.h"
#include "Checkers.h"
#include "reversiGame.h"
#include "magicSquares.h"
#include "inputProcessing.h"

gameState abstractGame :: state_ = SETUP;
abstractGame* abstractGame ::self_ = 0;
gameType abstractGame :: type_ = INVALID;

const int defaultSize = 8;

string abstractGame :: roughType_ = "";
string abstractGame :: roughArg1_ = "";
string abstractGame :: roughArg2_ = "";

abstractGame::abstractGame()
	: quitGuard_(true), quitting_(false), comingBack_(false), maxSymbol_(1), validFirst_(false)
{
}

//gameType stringGetType(string s)
//{
//	if(s == "magicsquares" || s == "magicsquare")
//	{
//		return MAGIC;
//	}
//	else if(s == "reversi")
//	{
//		return REVERSI;
//	}
//	else if(s == "ninealmonds")
//	{
//		return ALMONDS;
//	}
//	else
//		return INVALID;
//}


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


//prompts user for the name of a game. It checks to see if there is already a game
//with that file name that has been previously saved
void abstractGame :: nameChecker()
{
	cout << "What would you like to name this game? ";
	listen();
	ifstream name;
	gameType gameType;
	string typestring;

	name.open(name_ + ".txt");

	getline(name, typestring);
	
	lowerCase(typestring);
	removePunctuation(typestring);

	gameType = stringGetType(typestring);

	if(gameType == ALMONDS)
	{
		loadAlmonds(name_);
		return;
	}
	else if(gameType == MAGIC)
	{
		loadSquares(name_);
		return;
	}
	else if(gameType == REVERSI)
	{
		loadReversi(name_);
		return;
	}
	else if(gameType == CHECKERS)
	{
		loadCheckers(name_);
		return;
	}
	else if(gameType == NOGAME)
	{
		return;
	}
	else
		throw BADGAME;
}


// returns a pointer of AbstractGame type that is based off the string in argv[1]
// if there are improper argument numbers (or the argv[1] is not a valid game name)
// the pointer is null, otherwise it is to the appropriate game type.
void abstractGame::newGame(int argc, abstractGame*& pointer)
{
	string firstvar, secondvar;
	bool first=false, second=false;

	int lowest = 1;
	int size = 3;

	sanitizeInput(roughType_);
	istringstream typeStream(roughType_);

	string type;
	typeStream >> type;
	type_ = stringGetType(type);


	switch(argc)
	{
	case 1:
		throw BADARGC;
		break;
	case 2:
		break;
	case 4:
		secondvar = roughArg2_;
		lowerCase(secondvar);
		removePunctuation(secondvar);
		roughArg2_ = "2";
		second = true;
	case 3:
		firstvar = roughArg1_;
		lowerCase(firstvar);
		removePunctuation(firstvar);
		roughArg1_ = "1";
		first = true;
		break;
	default:
		throw BADARGC;
		break;
	}

	if((type_ == REVERSI || type_ == CHECKERS) && (!first || !second)) 
	{
		getNames(firstvar, secondvar);
	}

	try
	{
		if(type_ == MAGIC)
		{
			pointer = new magicSquares(size, lowest);
			pointer->nameChecker();
			return;
		}
		else if (type_ == REVERSI)
		{
			pointer = new reversiGame(firstvar, secondvar);
			pointer->nameChecker();
			type_ = REVERSI;
			return;
		}
		else if(type_ == ALMONDS)
		{
			pointer = new nineAlmonds();
			type_ = ALMONDS;
			pointer->nameChecker();
			return;
		}
		else if(type_ == CHECKERS)
		{
			pointer = new Checkers(firstvar, secondvar);
			pointer -> nameChecker();
			type_ = CHECKERS;
			return;
		}
		else
		{
			type_ = INVALID;
			return;
		}
	}
	catch (bad_alloc ba)
	{
		cout << "Failed to allocate memory. " << ba.what() << endl;
		throw BADMEM;
	}
}

void abstractGame :: instance(int argc, char* argv[])
{
	if(self_ != 0)
	{
		throw INSTANCEFAIL;
	}

	roughType_ = argv[1];
	if(argc == 4)
	{
		roughArg1_ = argv[2];
		roughArg2_ = argv[3];
	}

	abstractGame* g = 0;
	newGame(argc, g);
	self_=g;
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

			//disables certain checks that are not used during checkers games.
			if(type_ == CHECKERS)
			{
				if(isNumber(in1) && isNumber(in2))
				{
					int x = atoi(in1.c_str());
					int y = atoi(in2.c_str());

					if(state_ == NEEDPIECE)
					{
						start_ = Point(x, y);
					}
					else
					{
						dest_ = Point(x, y);
					}
				}
			}

			
			if(isNumber(in1) && isNumber(in2) && type_ != CHECKERS)
			{
				int x = atoi(in1.c_str());
				int y = atoi(in2.c_str());
				if(x>=0 && y>= 0)
				{
					Point p = Point(x, y);
					switch(state_)
					{
					case REVERSIPOINT:
						if(board_.count(p)==0 && p.x_ < boardx_ && p.y_ <boardy_)
						{
							dest_=p;
							return;
						}
						else
						{
							cout << "There is already a piece there. Try again" << endl;
							listen();
						}
						break;
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
		
		//picks up relevant quit commands that might be used by the player.
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
		//listens for the cancel message for almondGame. Probably shouldnt be here but legacy code now.
		else if(in1 == "cancel" && type_ == ALMONDS)
		{
			state_ = NEEDPIECE;
		}

		//calls the virtual undo method of the particular game type.
		else if(in1 == "undo")
		{
			this->undo();
			return;
		}

		// is used to advanced to the ENDTURN state for advancing purposes.
		else if(in1 == "finished" || in1 == "fin" || in1 == "done")
		{
			if(validFirst_  || type_ == CHECKERS)
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

		//forces the game to reprint the board in case it is lost for some reason.
		else if(in1 == "board")
		{
			this->print();
			return;
		}

		//rejects unknown commands
		else if(type_ != CHECKERS)
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


//if a player responds 'no' when prompted to save, the game will wipe the data
//from the current text file and and only leave "NO SAVE DATA" in the file
void abstractGame :: noSave()
{
	ofstream save;

	save.open (name_ + ".txt");
	save << "NO SAVE DATA" << endl << endl;
}

//updates the state of a game
void abstractGame :: setState(gameState s)
{
	state_ = s;
}

//calls the loadsave method for the correct game type with the specified file name
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


//the string name that is passed in is the name of the txt file to open
//parses the saved game file to create a nineAlmonds game with the saved data
void abstractGame :: loadAlmonds(string name)
{
	nineAlmonds load = nineAlmonds();

	bool badSave = false;

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
			badSave = true;
		}
		if(!(piece >> yval))
		{
			cout << "Sorry, that's not a valid game file. You're missing a Y value for a Piece. It has been skipped." << endl << endl;
			badSave = true;
		}
		if(!(piece >> name))
		{
			cout << "Sorry, that's not a valid game file. You're missing the name for a piece. It has been skipped." << endl << endl;
			badSave = true;
		}
		if(!(piece >> symbol))
		{
			cout << "Sorry, that's not a valid game file. You're missing the symbol for a piece. It has been skipped." << endl << endl;
			badSave = true;
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
			badSave = true;
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
		if(!check1)
		{
			cout << "Critical piece error. Bad save file." << endl;
			badSave = true;
		}

	}

	if(!badSave)
	{
		cout << "File successfully loaded." << endl;
		load.board_=board;
		load.comingBack_=true;
		self_= &load;
		return;
	}
	else
	{
		throw BADSAVE;
	}

}


//the string name that is passed in is the name of the txt file to open
//parses the saved game file to create a magicSquares game with the saved data
void abstractGame :: loadSquares(string name)
{
	magicSquares load = magicSquares();

	bool badSave = false;

	ifstream save;
	string input;

	save.open(name + ".txt");
	getline(save, input);

	int line = 1, loaded = 0, failed = 0;

	vector<int> badPieceLines;

	bool finished = false;

	while(!finished || badSave)
	{
		istringstream ins(input);

		if(input == "end")
		{
			finished=true;
		}
		if(line == 3)
		{
			string in1, in2, in3, in4, in5;
			int int1, int2, int3, int4, int5;
			if(ins >> in1)
			{
				if(isNumber(in1) && ins >> in2)
				{
					if(isNumber(in2) && ins >> in3)
					{
						if(isNumber(in3) && ins >> in4)
						{
							if(isNumber(in4) && ins >> in5)
							{
								if(isNumber(in5))
								{
									int1 = atoi(in1.c_str());
									int2 = atoi(in2.c_str());
									int3 = atoi(in3.c_str());
									int4 = atoi(in4.c_str());
									int5 = atoi(in5.c_str());

									load.turn_ = int1;
									load.state_= intToState(int2);
									if(int3 == 1)
									{
										load.validFirst_ = true;
									}
									else
										load.validFirst_ = false;
									load.boardx_ = int4;
									load.boardy_ = int5;
								}
								else
								{
									cout << "The fifth item in Line 3 is not a number. Bad Save File" << endl;
									badSave = true;
								}
							}
							else
							{
								if(!isNumber(in4))
								{
									cout << "The fourth item in Line 3 is not a number. Bad Save File" << endl;
									badSave = true;
								}
								else
								{
									cout << "There is no fifth item in Line 3. Bad Save File" << endl;
									badSave = true;
								}
							}
						}
						else
						{
							if(!isNumber(in3))
							{
								cout << "The third item in Line 3 is not a number. Bad Save File" << endl;
								badSave = true;
							}
							else
							{
								cout << "There is no fourth item in Line 3. Bad Save File" << endl;
								badSave = true;
							}
						}
					}
					else
					{
						if(!isNumber(in2))
						{
							cout << "The second item in Line 3 is not a number. Bad Save File" << endl;
							badSave = true;
						}
						else
						{
							cout << "There is no third item in Line 3. Bad Save File" << endl;
							badSave = true;
						}
					}
				}
				else
				{
					if(!isNumber(in1))
					{
						cout << "The first item in Line 3 is not a number. Bad Save File" << endl;
						badSave = true;
					}
					else
					{
						cout << "There is no second item in Line 3. Bad Save File" << endl;
						badSave = true;
					}
				}
			}
			else
			{
				cout << "It appears as though Line 3 is Misformed. Bad Save file." << endl;
				badSave = true;
			}
		}

		if(line == 4)
		{
			string startx, starty, destx, desty;
			int intsx, intsy, intdx, intdy;

			if(ins >> startx)
			{
				if(isNumber(startx) && ins >> starty)
				{
					if(isNumber(starty) && ins >> destx)
					{
						if(isNumber(destx) && ins >> desty)
						{
							if(isNumber(desty))
							{
								intsx = atoi(startx.c_str());
								intsy = atoi(starty.c_str());
								intdx = atoi(destx.c_str());
								intdy = atoi(desty.c_str());
								Point start = Point(intsx, intsy);
								Point dest = Point(intdx, intdy);
								load.start_ = start;
								load.dest_ = dest;
							}
							else
							{
								cout << "The fourth item in Line 4 is not a number. Bad save file." << endl;
								badSave = true;
							}
						}
						else
						{
							if(!isNumber(destx))
							{
								cout << "The third item in Line 4 is not a number. Bad save file." << endl;
								badSave = true;
							}
							else
							{
								cout << "There is no fourth item on Line 4. Bad save file." << endl;
								badSave = true;
							}
						}
					}
					else
					{
						if(!isNumber(starty))
						{
							cout << "The second item in Line 4 is not a number. Bad save file." << endl;
							badSave = true;
						}
						else
						{
							cout << "There is no third item in Line 4. Bad save file." << endl;
							badSave = true;
						}
					}
				}
				else
				{
					if(!isNumber(startx))
					{
						cout << "The first item in Line 4 is not a number. Bad save file." << endl; 
						badSave = true; 
					}
					else
					{
						cout << "There is no second item in Line 4. Bad Save File" << endl;
						badSave = true;
					}
				}
			}
			else
			{
				cout << "There is no content in Line 4. Bad Save File" << endl;
				badSave = true;
			}
		}

		if(line == 5)
		{
			string schosenTile, slowest, smaxAxis;
			int chosenTile, lowest, maxAxis;

			if(ins >> schosenTile)
			{
				if(isNumber(schosenTile) && ins >> slowest)
				{
					if(isNumber(slowest) && ins >> smaxAxis)
					{
						if(isNumber(smaxAxis))
						{
							chosenTile = atoi(schosenTile.c_str());
							lowest = atoi(slowest.c_str());
							maxAxis = atoi(smaxAxis.c_str());

							load.chosenTile_ = chosenTile;
							load.lowest_ = lowest;
							load.maxAxis_ = maxAxis;
						}
						else
						{
							cout << "The third item in Line 5 is not a number. Bad save file. " << endl;
							badSave = true;
						}
					}
					else
					{
						if(!isNumber(slowest))
						{
							cout << "The second item in Line 5 is not a number. Bad save file." << endl;
							badSave = true;
						}
						else
						{
							cout << "There is no third item in Line 5. Bad save file." << endl;
							badSave = true; 
						}
					}
				}
				else
				{
					if(!isNumber(schosenTile))
					{
						cout << "The first item in Line 5 is not a number. Bad save File. " << endl;
						badSave = true;
					}
					else
					{
						cout << "There is no second item in Line 5. Bad save file." << endl;
						badSave = true;
					}
				}
			}
			else
			{
				cout << "There is no content in Line 5. Bad save file." << endl;
				badSave = true;
			}
		}

		string in1;
		int value, count = 0;

		switch(line)
		{
		case 1:
			break;
		case 2:
			ins >> in1;
			if(!(in1 == name))
			{
				cout << "Encountered an unknown name error. Bad save file." << endl;
				badSave = true;
			}
			else
				cout << "Game name read and verified." << endl;
			break;
		case 6:
			if(true)

				while(ins >> in1)
				{
					value = atoi(in1.c_str());
					load.availablePieces_.push_back(value);
					in1 == "";
				}
				cout << "Available pieces read. " << count << " pieces loaded." << endl;
				break;
		case 7:
			cout << "Loading board information. " << endl;
			break;
		default:
			if(!finished)
			{
				string xvalS, yvalS, numberS;
				int xval, yval, number;

				if(ins >> xvalS)
				{
					if(isNumber(xvalS) && ins >> yvalS)
					{
						if(isNumber(yvalS) && ins >> numberS)
						{
							if(isNumber(numberS))
							{

								xval = atoi(xvalS.c_str());
								yval = atoi(yvalS.c_str());
								number = atoi(numberS.c_str());

								Point location = Point(xval, yval);

								if(load.board_.count(location) == 0)
								{
									numberSquare temp = numberSquare(number);
									load.board_[location] = temp;
									++loaded;
								}
								else
								{
									++failed;
									badPieceLines.push_back(line);
								}
							}
							else
							{
								++failed;
								badPieceLines.push_back(line);
							}
						}
						else
						{
							++failed;
							badPieceLines.push_back(line);
						}
					}
					else
					{
						++failed;
						badPieceLines.push_back(line);
					}
				}
				else
				{
					cout << "There was a critical piece error. Bad save file. " << endl;
					++failed;
					badPieceLines.push_back(line);
					badSave = true; 
				}
			}
		}

		++line;

	}

	if(!badSave)
	{
		cout << "File successfully loaded." << endl;
		load.comingBack_=true;
		self_=&load;
		return;
	}
	else
	{
		throw BADSAVE;
	}

}


//the string name that is passed in is the name of the txt file to open
//parses the saved game file to create a reversiGame game with the save data
void abstractGame :: loadReversi(string name)
{
	reversiGame load = reversiGame();

	bool badSave = false;

	ifstream save;
	string input;

	save.open(name + ".txt");
	getline(save, input);

	int line = 1, loaded = 0, failed = 0;

	vector<int> badPieceLines;

	bool finished = false;

	//parsing starts here - are we sure we want badSave instead of !badSave?
	while(!finished || badSave)
	{
		istringstream ins(input);

		if(input == "end")
		{
			finished=true;
		}
		//this line contains the turn, state, and board dimensions
		if(line == 3)
		{
			string in1, in2, in3, in4;
			int int1, int2, int3, int4;
			if(ins >> in1)
			{
				if(isNumber(in1) && ins >> in2)
				{
					if(isNumber(in2) && ins >> in3)
					{
						if(isNumber(in3) && ins >> in4)
						{
							if(isNumber(in4))
							{
								int1 = atoi(in1.c_str());
								int2 = atoi(in2.c_str());
								int3 = atoi(in3.c_str());
								int4 = atoi(in4.c_str());

								load.state_= intToState(int1);
								if(int2 == 1)
								{
									load.validFirst_ = true;
								}
								else
									load.validFirst_ = false;
								load.boardx_ = int3;
								load.boardy_ = int4;
							}
							else
							{
								cout << "The fifth item in Line 3 is not a number. Bad Save File" << endl;
								badSave = true;
							}
						}
						else
						{
							if(!isNumber(in3))
							{
								cout << "The third item in Line 3 is not a number. Bad Save File" << endl;
								badSave = true;
							}
							else
							{
								cout << "There is no fourth item in Line 3. Bad Save File" << endl;
								badSave = true;
							}
						}
					}
					else
					{
						if(!isNumber(in2))
						{
							cout << "The second item in Line 3 is not a number. Bad Save File" << endl;
							badSave = true;
						}
						else
						{
							cout << "There is no third item in Line 3. Bad Save File" << endl;
							badSave = true;
						}
					}
				}
				else
				{
					if(!isNumber(in1))
					{
						cout << "The first item in Line 3 is not a number. Bad Save File" << endl;
						badSave = true;
					}
					else
					{
						cout << "There is no second item in Line 3. Bad Save File" << endl;
						badSave = true;
					}
				}
			}
			else
			{
				cout << "It appears as though Line 3 is Misformed. Bad Save file." << endl;
				badSave = true;
			}
		}

		//parse 4th line - contains dest.x and dest.y

		if(line == 4)
		{
			string destx, desty;
			int intdx, intdy;

			if(ins >> destx)
			{
				if(isNumber(destx) && ins >> desty)
				{

					if(isNumber(desty))
					{

						intdx = atoi(destx.c_str());
						intdy = atoi(desty.c_str());
						Point dest = Point(intdx, intdy);
						load.dest_ = dest;
					}
					else
					{
						cout << "The second item in Line 4 is not a number. Bad save file." << endl;
						badSave = true;
					}

				}
				else
				{
					if(!isNumber(destx))
					{
						cout << "The first item in Line 4 is not a number. Bad save file." << endl; 
						badSave = true; 
					}
					else
					{
						cout << "There is no second item in Line 4. Bad Save File" << endl;
						badSave = true;
					}
				}
			}
			else
			{
				cout << "There is no content in Line 4. Bad Save File" << endl;
				badSave = true;
			}
		}


		//following lines should contain pieces on the board (coordinates, name, symbol, value)
		if(input != "START")
		{
			cout << "Sorry, that's not a valid game file. The Board is not started properly." << endl << endl;
			return; 
		}

		map<Point, gamePiece> board;

		bool boardDone = false;

		input="";
		getline(save, input);
		lowerCase(input);
		removePunctuation(input);

		while(!boardDone)
		{
			istringstream piece(input);

			string xval, yval, symbol;
//			int xint, yint;

			if(!(piece >> xval))
			{
				cout << "Sorry, that's not a valid game file. You're missing an X value for a Piece. It has been skipped" << endl << endl;
				badSave = true;
			}
			if(!(piece >> yval))
			{
				cout << "Sorry, that's not a valid game file. You're missing a Y value for a Piece. It has been skipped." << endl << endl;
				badSave = true;
			}
			if(!(piece >> symbol))
			{
				cout << "Sorry, that's not a valid game file. You're missing the symbol for a piece. It has been skipped." << endl << endl;
				badSave = true;
			}
		}


		/////
		while(!boardDone)
		{
			string xvalS, yvalS, symbol;
			int xval, yval;

			if(ins >> xvalS)
			{
				if(isNumber(xvalS) && ins >> yvalS)
				{
					if(isNumber(yvalS) && ins >> symbol)
					{
						xval = atoi(xvalS.c_str());
						yval = atoi(yvalS.c_str());


						Point location = Point(xval, yval);

						if(load.board_.count(location) == 0)
						{
							if (symbol[0] == 'X')
							{
								reversiPiece temp = reversiPiece(BLACK);
								load.board_[location] = temp;
								++loaded;
							}
							else if (symbol[0] == 'O')
							{
								reversiPiece temp = reversiPiece(WHITE);
								load.board_[location] = temp;
								++loaded;
							}
							else
							{
								cout << "Line did not contain a valid symbol" << endl;
							}	
						}
						else
						{
							++failed;
							badPieceLines.push_back(line);
						}
					}
					else
					{
						++failed;
						badPieceLines.push_back(line);
					}
				}
				else
				{
					++failed;
					badPieceLines.push_back(line);
				}
			}
			else
			{
				cout << "There was a critical piece error. Bad save file. " << endl;
				++failed;
				badPieceLines.push_back(line);
				badSave = true; 
			}
		}
		++line;
	}


	//end parsing
	if(!badSave)
	{
		cout << "File successfully loaded." << endl;
		load.comingBack_=true;
		self_=&load;
		return;
	}
	else
	{
		throw BADSAVE;
	}
}

void abstractGame :: loadCheckers(string name)
{
	return;
}

//transforms an int to a corresponding state of the gameState enum
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

//sets the quitting safeguard bool to true after the user confirms that they 
//do want to quit. Prevents accidental quitting
void abstractGame :: isQuitting()
{
	quitting_=true;
}