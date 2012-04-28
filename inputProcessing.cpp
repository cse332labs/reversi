//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// inputProcessing.cpp

#include "stdafx.h"
#include "inputProcessing.h"

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

