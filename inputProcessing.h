//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// inputProcessing.h

#include "stdafx.h"

#ifndef INPUTPROCESSING_H
#define INPUTPROCESSING_H

typedef enum{ALMONDS, MAGIC, REVERSI, CHECKERS, NOGAME, INVALID} gameType;

#include <string>
#include <sstream>
#include <iostream>
#include "abstractGame.h"

using namespace std;

void lowerCase(string&);
void removePunctuation(string&);
void sanitizeInput(string&);

bool isNumber(string s);

gameType stringGetType(string s);

void getNames(string& playerB, string& playerW);

// returns length of the string of an int
int getLength(int symbol);

#endif