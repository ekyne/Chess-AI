/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	knight.cpp
 * Function: 	Holds functions used by the Knight class.
*/

#include "knight.h"

// default constructor for knight
Knight::Knight(){

}

// knight constuctor which renders a piece texture if it is needed
Knight::Knight(Team c_team,int i, int j,SDL_Manager img, bool visual) : Piece(c_team,i,j,KNIGHT){
	if(c_team == WHITE){
		setFile("img/Chess_nlt45.svg.png");
	}
	else if(c_team == BLACK){
		setFile("img/Chess_ndt45.svg.png");
	}
	if(visual){
		setPieceTexture(img.LoadImage(getFile()));
		render(img);
	}
	setValue(350);
}

// knight deconstructor
Knight::~Knight(){

}

// finds the possible moves that can be made
void Knight::findMoves(SDL_Manager img,Piece* map[][8],bool lit){	
	clearMoves();

	// searches all possible square moves
	for(int i = -2; i <= 2; i+= 4){
		for(int j = -1; j <= 1; j+= 2){

			// if square checked is within the chess board, and if the piece is the enemy team, the move is computed
			if(getRow() + i < 0 || getRow() + i > 7 || getCol() + j < 0 || getCol() + j > 7) continue;
			setSquare(getCol()+j,getRow()+i);
			if(map[getRow() + i][getCol() + j] != nullptr){
				if(map[getRow() + i][getCol() + j]->getTeam() != map[getRow()][getCol()]->getTeam()){	
					addMove(getSquare());
				}
			}
			else addMove(getSquare());

			// if square checked is within the chess board, and if the piece is the enemy team, the move is computed
			if(getRow() + j < 0 || getRow() + j > 7 || getCol() + i < 0 || getCol() + i > 7) continue;
			setSquare(getCol()+i,getRow()+j);
			if(map[getRow() + j][getCol() + i] != nullptr){
				if(map[getRow() + j][getCol() + i]->getTeam() != map[getRow()][getCol()]->getTeam()){		
					addMove(getSquare());
				}
			}
			else addMove(getSquare());
		}
	}
	if(lit == true) renderMoves(img,false,map);
}

// piece is moved and the chosen board square is re-rendered
void Knight::movePiece(int startY,int startX,int endY, int endX, Piece* map[][8], SDL_Manager img,bool found, bool visual){

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
		if(map[si][sj]->getClass() == Piece::Class::KNIGHT) map[ei][ej] = new Knight(map[si][sj]->getTeam(),ei,ej,img,visual);

		map[si][sj] = nullptr;
		if(visual) SDL_RenderPresent(img.getRenderer());
	}
}

