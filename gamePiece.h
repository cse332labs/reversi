//Lab 4 - Nine Almonds and Magic Squares
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu)
// 5-7-12
// gamePiece.h

#include "stdafx.h"

#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include "Point.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

//declarations for basic gamepiece
struct gamePiece
{
	string name_;
	string symbol_;
	int value_;

	bool operator==(const gamePiece& piece);

	gamePiece();
};

// the almondpiece has no special variables, but the default constructor knows to assing the proper name and symbol
struct almondPiece : gamePiece
{
	almondPiece();
	bool operator==(const almondPiece& piece);
};

// the numberSquare has an added variable (value_) and a special constructor. 
struct numberSquare : gamePiece
{
	// the key of the point in the map
	Point key_;
	//constructor to assign value of parameter
	numberSquare(unsigned int value);
	//default constructor value = 0
	numberSquare();

	bool operator==(const numberSquare& piece);

	// sets the symbol and Value of the given piece
	void setPiece(int n);

	//for sorting
	bool const operator<(const numberSquare &other);
};

#endif