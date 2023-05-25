/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	queen.cpp
 * Function: 	Holds functions used by the Queen class.
*/

#include "queen.h"

// default constructor for queen
Queen::Queen(){

}

// queen constuctor which renders a piece texture if it is needed
Queen::Queen(Team c_team,int i, int j,SDL_Manager img, bool visual) : Piece(c_team,i,j,QUEEN){
	if(c_team == WHITE){
		setFile("img/Chess_qlt45.svg.png");
	}
	else if(c_team == BLACK){
		setFile("img/Chess_qdt45.svg.png");
	}
	if(visual){
		setPieceTexture(img.LoadImage(getFile()));
		render(img);
	}
	setValue(1000);
}

// queen deconstructor
Queen::~Queen(){

}

// finds the possible moves that can be made
void Queen::findMoves(SDL_Manager img,Piece* map[][8],bool lit){
	clearMoves();
	int incI = 0;
	int incJ = 0;

	// searches all possible square moves
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			incI = i;
			incJ = j;

			// while square checked is within the chess board, and if the piece is the enemy team, the move is computed
			while(getRow() + incI >= 0 && getRow() + incI < 8 && getCol() + incJ >= 0 && getCol() + incJ < 8){
				setSquare(getCol()+incJ,getRow()+incI);
				if(map[getRow() + incI][getCol() + incJ] != nullptr){
					if(map[getRow() + incI][getCol() + incJ]->getTeam() != map[getRow()][getCol()]->getTeam()){		
						addMove(getSquare());
						break;
					}
					break;
				}
				else addMove(getSquare());
				if(i == -1) incI -= 1;
				if(i == 1) incI += 1;
				if(j == -1) incJ -= 1;
				if(j == 1) incJ += 1;
			}
		}
	}
	if(lit == true) renderMoves(img,false,map);
}

// piece is moved and the chosen board square is re-rendered
void Queen::movePiece(int startY,int startX,int endY, int endX, Piece* map[][8], SDL_Manager img,bool found, bool visual){

	// starting and ending coordinates chosen
	int si = startY / img.getSquareSize();
	int sj = startX / img.getSquareSize();
	int ei = endY / img.getSquareSize();
	int ej = endX / img.getSquareSize();

	if(visual) renderMoves(img,true,map);

	// checks for a valid move
	for(auto& square : getMoves()){
		if(ei == square.y && ej == square.x){
			found = true;
		}
	}

	// new piece is rendered here and previous piece is deleted
	if((map[si][sj] != nullptr || (ei != si && ej != sj)) && found == true){
		if(visual){

			img.renderSquare(img.getRenderer(),si,sj,si+sj,false);
			img.renderSquare(img.getRenderer(),ei,ej,ei+ej,false);
		}
		if(map[si][sj]->getClass() == Piece::QUEEN) map[ei][ej] = new Queen(map[si][sj]->getTeam(),ei,ej,img,visual);
		map[si][sj] = nullptr;
		if(visual) SDL_RenderPresent(img.getRenderer());
	}
}

