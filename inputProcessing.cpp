//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// inputProcessing.cpp

#include "stdafx.h"
#include "inputProcessing.h"
#include "sstream"
#include <sstream>

using namespace std;

//modifies the input string to become lowercase
void lowerCase(string& str)
{
	for(unsigned int i=0; i < str.length(); ++i)
	{
		str[i]= tolower(str.at(i));
	}
}

//removes all punctuation from the string
void removePunctuation(string& str)
{
	for(unsigned int i=0; i < str.length(); ++i)
	{
		if (ispunct(str[i]))
		{
			str.at(i)=' ';
		}
	}
}

void sanitizeInput(string& str)
{
	removePunctuation(str);
	lowerCase(str);
	istringstream ins(str);
	str = "";
	getline(ins, str);
}

// returns the length of the int symbol as if it were a string.
int getLength(int symbol)
{
        string symbolStr = "";
        stringstream intToStr;
        intToStr << symbol;
        intToStr >> symbolStr;
        return symbolStr.size();
}

bool :: isNumber(string s)
{
	bool num=true;
	for(unsigned int i =0; i<s.length();++i)
	{
		if(!isdigit(s.at(i)))
		{
			num=false;
		}
	}
	return num;
}

gameType stringGetType(string s)
{
	if(s == "magicsquares" || s == "magicsquare")
	{
		return MAGIC;
	}
	else if(s == "reversi")
	{
		return REVERSI;
	}
	else if(s == "ninealmonds")
	{
		return ALMONDS;
	}
	else if(s == "checkers")
	{
		return CHECKERS;
	}
	else if(s == "")
	{
		return NOGAME;
	}
	else
		return INVALID;
}

void getNames(string& playerB, string& playerW)
{
	//begins by deleting the original content of the strings
	playerB = "", playerW = "";
	
	//asks for and extracts player one's name
	cout << "What is the first player's name? ";
	string input1;
	getline(cin, input1);
	lowerCase(input1);
	removePunctuation(input1);
	playerB = input1;
	
	//asks for and extracts player two's name
	cout << "What is the second player's name? ";
	string input2;
	getline(cin, input2);
	lowerCase(input2);
	removePunctuation(input2);
	playerW = input2;
	
	return;
}