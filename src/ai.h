/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	ai.h
 * Function: 	Holds the AI class.
*/

#ifndef AI_H
#define AI_H
#include <iostream>
#include <algorithm>
#include "piece.h"
#include "SDL_Manager.h"

class AI {
	public:
		AI();
		~AI();

		int evaluateBoard(Piece*[][8]);
		std::pair<int,Square> findPriorityMove(int,Piece*[][8],int, int,int,SDL_Manager,int,int,bool);
	private:
		int value = 0;
		Square sqre;
		int flag = 0;
};

#endif
