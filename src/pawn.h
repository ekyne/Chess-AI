/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	pawn.h
 * Function: 	Holds the Pawn class.
*/

#ifndef PAWN_H
#define PAWN_H
#include <iostream>
#include <SDL2/SDL.h>
#include "piece.h"

class Pawn : public Piece {
	public:
		Pawn();
		Pawn(Team,int, int,SDL_Manager,bool);
		~Pawn();

		void findMoves(SDL_Manager,Piece*[][8],bool);
		void movePiece(int,int,int,int,Piece*[][8],SDL_Manager,bool,bool);

		int getSquareValue(int si, int sj){return squareValues[si][sj];}
	private:
		int squareValues[8][8] = {{0,0,0,0,0,0,0,0},
					{5,10,10,-20,-20,10,10,5},
					{5,-5,-10,0,0,-10,-5,5},
					{0,0,0,20,20,0,0,0},
					{5,5,10,25,25,10,5,5},
					{10,10,20,30,30,20,10,10},
					{5,5,5,5,5,5,5,5},
					{0,0,0,0,0,0,0,0}};
};

#endif
