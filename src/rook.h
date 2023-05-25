/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	rook.h
 * Function: 	Holds the Rook class.
*/

#ifndef ROOK_H
#define ROOK_H
#include <iostream>
#include <SDL2/SDL.h>
#include "piece.h"

class Rook : public Piece {
	public:
		Rook();
		Rook(Team,int, int,SDL_Manager,bool);
		~Rook();

		void findMoves(SDL_Manager,Piece*[][8],bool);
		void movePiece(int,int,int,int,Piece*[][8],SDL_Manager,bool,bool);

		int getSquareValue(int si, int sj){return squareValues[si][sj];} 
	private:
		int squareValues[8][8] = {{0,0,0,5,5,0,0,0},
					{-5,0,0,0,0,0,0,-5},
					{-5,0,0,0,0,0,0,-5},
					{-5,0,0,0,0,0,0,-5},
					{-5,0,0,0,0,0,0,-5},
					{-5,0,0,0,0,0,0,-5},
					{-5,10,10,10,10,10,10,-5},
					{0,0,0,0,0,0,0,0}};
};

#endif
