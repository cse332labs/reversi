//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// inputProcessing.h

#include "stdafx.h"

#ifndef INPUTPROCESSING_H
#define INPUTPROCESSING_H

typedef enum{ALMONDS, MAGIC, REVERSI, INVALID} gameType;

#include <string>
#include <sstream>
#include "abstractGame.h"

using namespace std;

void lowerCase(string& s);
void removePunctuation(string&);

bool isNumber(string s);

gameType stringGetType(string s);

void getNames(string& playerB, string& playerW);

// returns length of the string of an int
int getLength(int symbol);

#endif