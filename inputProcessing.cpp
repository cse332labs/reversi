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