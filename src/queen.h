/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	queen.h
 * Function: 	Holds the Queen class.
*/

#ifndef QUEEN_H
#define QUEEN_H
#include <iostream>
#include <SDL2/SDL.h>
#include "piece.h"

class Queen : public Piece {
	public:
		Queen();
		Queen(Team,int, int,SDL_Manager,bool);
		~Queen();

		void findMoves(SDL_Manager,Piece*[][8],bool);
		void movePiece(int,int,int,int,Piece*[][8],SDL_Manager,bool,bool);

		int getSquareValue(int si, int sj){return squareValues[si][sj];} 
	private:
		int squareValues[8][8] = {{-20,-10,-10,-5,-5,-10,-10,-20},
					{-10,0,0,0,0,5,0,-10},
					{-10,0,5,5,5,5,5,-10},
					{-5,0,5,5,5,5,0,0},
					{-5,0,5,5,5,5,0,-5},
					{-10,0,5,5,5,5,0,-10},
					{-10,0,0,0,0,0,0,-10},
					{-20,-10,-10,-5,-5,-10,-10,-20}};
};

#endif
