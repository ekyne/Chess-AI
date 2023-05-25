/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	knight.h
 * Function: 	Holds the Knight class.
*/

#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include <SDL2/SDL.h>
#include "piece.h"

class Knight : public Piece {
	public:
		Knight();
		Knight(Team,int, int,SDL_Manager,bool);
		~Knight();

		void findMoves(SDL_Manager,Piece*[][8],bool);
		void movePiece(int,int,int,int,Piece*[][8],SDL_Manager,bool,bool);

		int getSquareValue(int si, int sj){return squareValues[si][sj];}
	private:
		int squareValues[8][8] = {{-50,-40,-30,-30,-30,-30,-40,-50},
					{-40,-20,0,5,5,0,-20,-40},
					{-30,5,10,15,15,10,5,-30},
					{-30,0,15,20,20,15,0,-30},
					{-30,5,15,20,20,15,5,-30},
					{-30,0,10,15,15,10,0,-30},
					{-40,-20,0,0,0,0,-20,-40},
					{-50,-40,-30,-30,-30,-30,-40,-50}}; 
};

#endif
