/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	king.h
 * Function: 	Holds the King class.
*/

#ifndef KING_H
#define KING_H
#include <iostream>
#include <SDL2/SDL.h>
#include "piece.h"

class King : public Piece {
	public:
		King();
		King(Team,int, int,SDL_Manager,bool);
		~King();	

		void findMoves(SDL_Manager,Piece*[][8],bool);
		void movePiece(int,int,int,int,Piece*[][8],SDL_Manager,bool,bool);

		int getSquareValue(int si, int sj){return squareValues[si][sj];} 
	private:
		int squareValues[8][8] = {{20,30,10,0,0,10,30,20},
					{20,20,0,0,0,0,20,20},
					{-10,-20,-20,-20,-20,-20,-20,-10},
					{-20,-30,-30,-40,-40,-30,-30,-20},
					{-30,-40,-40,-50,-50,-40,-40,-30},
					{-30,-40,-40,-50,-50,-40,-40,-30},
					{-30,-40,-40,-50,-50,-40,-40,-30},
					{-30,-40,-40,-50,-50,-40,-40,-30}};
};

#endif
