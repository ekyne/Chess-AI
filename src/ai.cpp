/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	ai.cpp
 * Function: 	Holds functions used by the AI class.
*/

#include "ai.h"

//default constructor for AI
AI::AI(){

}

// AI destructor
AI::~AI(){

}

// board is evaluated from piece and square values
int AI::evaluateBoard(Piece* map[][8]){
	int summation = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(map[i][j] != nullptr && map[i][j]->getTeam() != Piece::NONE){
				summation += map[i][j]->getValue() * (map[i][j]->getTeam() == Piece::WHITE ? 1: -1);
			}
		}
	}
	return summation;	
}

// finds a move to act upon every possible move that can stem from its position
std::pair<int,Square> AI::findPriorityMove(int depth,Piece* map[][8],int i, int j,int playerTeam,SDL_Manager img,int alpha,int beta,bool maxPlayer){

	// if the recursive depth limit is reached, the value of the chess board is returned
	if(depth == 0){
		value = -1*(evaluateBoard(map)) + map[i][j]->getSquareValue(i,j);
		return std::make_pair(value,sqre);
	}
	int aflag = 0;
	int inc;
	int tempJ = -1;
	Square bestPosition;
	bestPosition.y = i;
	bestPosition.x = j;

	map[i][j]->findMoves(img,map,false);
		
	std::vector<Square> allMoves = map[i][j]->getMoves();

	// if there are no moves, the value of the chess board is returned
	if(allMoves.size() == 0){
	       	return std::make_pair(-1*(evaluateBoard(map)) + map[i][j]->getSquareValue(i,j),bestPosition);
	}
	random_shuffle(allMoves.begin(),allMoves.end());

	int priorityMoveValue = maxPlayer ? -10000 : 10000;
	Piece* temp;
	Piece* tempNone;

	// iterates through all moves and recursively calls with a move to find branching possible moves
	for(auto& move: allMoves){

		// if a move is not within the chess board
		if(move.y < 0 || move.y > 7 || move.x < 0 || move.x > 7) return std::make_pair(-1*(evaluateBoard(map)) + map[i][j]->getSquareValue(i,j),bestPosition);
		if(map[move.y][move.x] != nullptr){

			// if a move is an result of an empassant, the move is temporarily stored
		       	if(map[move.y][move.x]->getTeam() == Piece::NONE){
				temp = map[move.y + map[move.y][move.x]->getOffSet()][move.x];
				tempNone = map[move.y][move.x];
				aflag = 2;
				inc = map[move.y][move.x]->getOffSet();
			}
			else{
				temp = map[move.y][move.x];
				aflag = 1;
			}
		}
			if(map[i][j] != nullptr){
				
				// if a king is castled, the coordinates are temporarily stored
				if(map[i][j]->getClass() == Piece::KING && map[i][j]->getType() == Piece::CASTLE){
					if(move.x == 0) tempJ = 2;
					if(move.x == 7) tempJ = 6;
				}

			// the piece is moved
			map[i][j]->movePiece(i*img.getSquareSize(),j*img.getSquareSize(),move.y*img.getSquareSize(),move.x*img.getSquareSize(),map,img,true,false);
			}
			
			//iterates through each piece and recursively calls with piece coordinates
			for(int mi = 0; mi < 8; mi++){
				for(int mj = 0; mj < 8; mj++){
					if(map[mi][mj] != nullptr && map[move.y][move.x] != nullptr){
					       	if(map[mi][mj]->getTeam() != map[move.y][move.x]->getTeam() and map[mi][mj]->getTeam() != Piece::NONE){	
						value = findPriorityMove(depth-1,map,mi,mj,playerTeam,img,alpha,beta,!maxPlayer).first;
						// performs minimax with alpha-beta pruning here
							if(maxPlayer){
								if(value > priorityMoveValue){
									priorityMoveValue = value;
									bestPosition = move;
								}
								alpha = std::max(alpha,value);	
							}
							else{
								if(value < priorityMoveValue){
									priorityMoveValue = value;
									bestPosition = move;
								}
								beta = std::min(beta,value);
							}
							if(beta <= alpha){
								flag = 1;
								break;
							}
						}
					}
				}
				if(flag == 1){
					break;
				}
			}

			// if the move is within the chess board and is the result of an empassant, the piece is deleted
			if(map[move.y][move.x] != nullptr){
			if(move.y - map[move.y][move.x]->getOffSet() >= 0 or move.y - map[move.y][move.x]->getOffSet() < 8){
				if(map[move.y - map[move.y][move.x]->getOffSet()][move.x] != nullptr){
					if(map[move.y - map[move.y][move.x]->getOffSet()][move.x]->getTeam() == Piece::NONE){
						map[move.y - map[move.y][move.x]->getOffSet()][move.x] = nullptr;
					}
				}
			}

			// the moved piece is returned
			map[move.y][move.x]->movePiece(move.y*img.getSquareSize(),move.x*img.getSquareSize(),i*img.getSquareSize(),j*img.getSquareSize(),map,img,true,false);
			}
				else if(tempJ != -1 && map[move.y][tempJ] != nullptr){

				map[move.y][tempJ]->movePiece(move.y*img.getSquareSize(),move.x*img.getSquareSize(),i*img.getSquareSize(),j*img.getSquareSize(),map,img,true,false);

				tempJ = -1;
			}
		// if move was temporarily stored, return the coordinates
		if(aflag > 0 && temp != nullptr){
		       	if(aflag == 2){
				map[move.y + inc][move.x] = temp;
				map[move.y][move.x] = tempNone;
				aflag = 0;
			}
			else{
				map[move.y][move.x] = temp;
				aflag = 0;
			}
		}
		temp = nullptr;

		// if pruned, exit iteration
		if(flag == 1){
			flag = 0;
			break;
		}
		
	}
	return std::make_pair(priorityMoveValue,bestPosition);
}
