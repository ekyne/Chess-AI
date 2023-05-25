/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	bishop.h
 * Function: 	Holds the Bishop class.
*/

#ifndef BISHOP_H
#define BISHOP_H
#include <iostream>
#include <SDL2/SDL.h>
#include "piece.h"

class Bishop : public Piece {
	public:
		Bishop();
		Bishop(Team,int, int,SDL_Manager,bool);
		~Bishop();

		void findMoves(SDL_Manager,Piece*[][8],bool);
		void movePiece(int,int,int,int,Piece*[][8],SDL_Manager,bool,bool);

		int getSquareValue(int si, int sj){return squareValues[si][sj];}
	private:
		int squareValues[8][8] = {{-20,-10,-10,-10,-10,-10,-10,-20},
					{-10,5,0,0,0,0,5,-10},
					{-10,10,10,10,10,10,10,-10},
					{-10,0,10,10,10,10,0,-10},
					{-10,5,5,10,10,5,5,-10},
					{-10,0,5,10,10,5,0,-10},
					{-10,0,0,0,0,0,0,-10},
					{-20,-10,-10,-10,-10,-10,-10,-20}};
};

#endif
