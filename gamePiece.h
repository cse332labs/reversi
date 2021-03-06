//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// gamePiece.h

#include "stdafx.h"

#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include "Point.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

typedef enum{BLACK, WHITE, RED, INVALID_COLOR} pieceColor;

//declarations for basic gamepiece
struct gamePiece
{
        string name_;
        pieceColor color_;
        string symbol_;
        int value_;

        bool operator==(const gamePiece& piece);

        gamePiece();

        virtual void flip();
};

// the almondpiece has no special variables, but the default constructor knows to assing the proper name and symbol
struct almondPiece : gamePiece
{
        almondPiece();
        virtual void flip();
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

        virtual void flip();

        bool operator==(const numberSquare& piece);

        // sets the symbol and Value of the given piece
        void setPiece(int n);

        //for sorting
        bool const operator<(const numberSquare &other);
};

struct reversiPiece : gamePiece
{
        reversiPiece(); //default is true
        reversiPiece(pieceColor color);

        virtual void flip();
};

struct checkerPiece : gamePiece
{
        checkerPiece();

        bool isKing_;

        virtual void flip();
        void crown();

        void set(gamePiece p);
};

checkerPiece checkerByColor(pieceColor color);  

#endif