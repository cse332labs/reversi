//Lab 4 - Nine Almonds and Magic Squares
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu)
// 5-7-12
// inputProcessing.h

#include "stdafx.h"

#ifndef INPUTPROCESSING_H
#define INPUTPROCESSING_H

#include <string>
#include <sstream>

using namespace std;

void lowerCase(string& s);
void removePunctuation(string&);

// returns length of the string of an int
int getLength(int symbol);

#endif