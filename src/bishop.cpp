/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	bishop.cpp
 * Function: 	Holds functions used by the Bishop class.
*/

#include "bishop.h"

// default constructor for bishop
Bishop::Bishop(){

}

// bishop constuctor which renders a piece texture if it is needed
Bishop::Bishop(Team c_team,int i, int j,SDL_Manager img, bool visual) : Piece(c_team,i,j,BISHOP){
	if(c_team == WHITE){
		setFile("img/Chess_blt45.svg.png");
	}
	else if(c_team == BLACK){
		setFile("img/Chess_bdt45.svg.png");
	}
	if(visual){
		setPieceTexture(img.LoadImage(getFile()));
		render(img);
	}
	setValue(350);
}


// bishop deconstructor
Bishop::~Bishop(){

}

// finds the possible moves that can be made
void Bishop::findMoves(SDL_Manager img, Piece* map[][8],bool lit){
	clearMoves();
	int incX = 0;
	int incY = 0;

	// searches all possible square moves
	for(int i = -1; i <= 1; i+= 2){
		for(int j = -1; j <= 1; j+= 2){
			incX = j;
			incY = i;

			// while square checked is within the chess board, and if the piece is the enemy team, the move is computed
			while(getRow() + incY >= 0 && getRow() + incY < 8 && getCol() + incX >= 0 && getCol() + incX < 8){
				setSquare(getCol()+incX,getRow()+incY);
				if(map[getRow() + incY][getCol() + incX] != nullptr){
					if(map[getRow() + incY][getCol() + incX]->getTeam() != map[getRow()][getCol()]->getTeam()){		
						addMove(getSquare());
						break;
					}
					break;
				}
				else addMove(getSquare());
				if(i == -1) incY += -1;
				if(j == -1) incX += -1;
				if(i == 1) incY += 1;
				if(j == 1) incX += 1;
			}
		}
	}
	if(lit == true) renderMoves(img,false,map);
}

// piece is moved and the chosen board square is re-rendered
void Bishop::movePiece(int startY,int startX,int endY, int endX, Piece* map[][8], SDL_Manager img,bool found, bool visual){

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
		if(map[si][sj]->getClass() == Piece::Class::BISHOP) map[ei][ej] = new Bishop(map[si][sj]->getTeam(),ei,ej,img,visual);
		map[si][sj] = nullptr;
		if(visual) SDL_RenderPresent(img.getRenderer());
	}
}

