/* Author: 	Kylie Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	rook.cpp
 * Function: 	Holds functions used by the Rook class.
*/

#include "rook.h"

// default constructor for rook
Rook::Rook(){

}

// rook constuctor which renders a piece texture if it is needed
Rook::Rook(Team c_team,int i, int j,SDL_Manager img, bool visual) : Piece(c_team,i,j,ROOK){
	if(c_team == WHITE){
		setFile("img/Chess_rlt45.svg.png");
	}
	else if(c_team == BLACK){
		setFile("img/Chess_rdt45.svg.png");
	}
	if(visual){
		setPieceTexture(img.LoadImage(getFile()));
		render(img);
	}
	if(getType() == Piece::CASTLE){
		setValue(525);
	}
	else{
		setValue(325);
	}
}

// rook deconstructor
Rook::~Rook(){

}

// finds the possible moves that can be made
void Rook::findMoves(SDL_Manager img, Piece* map[][8],bool lit){
	clearMoves();
	int inc = 0;

	// searches all possible square moves
	for(int i = -1; i <= 1; i+= 2){
		inc = i;

		// if square checked is within the chess board, and if the piece is the enemy team, the move is computed
		while(getRow() + inc >= 0 && getRow() + inc < 8){
			setSquare(getCol(),getRow() + inc);
			if(map[getRow()][getCol()] != nullptr){
			if(map[getRow() + inc][getCol()] != nullptr){
				if(map[getRow() + inc][getCol()]->getTeam() != map[getRow()][getCol()]->getTeam()){		
					addMove(getSquare());
					break;
				}
				break;
			}
			else addMove(getSquare());
			}
			if(i == -1) inc -= 1;
			if(i == 1) inc += 1;
		}
	}
	for(int j = -1; j <= 1; j+= 2){
		inc = j;

		// if square checked is within the chess board, and if the piece is the enemy team, the move is computed
		while(getCol() + inc >= 0 && getCol() + inc < 8){
			setSquare(getCol()+inc,getRow());
			if(map[getRow()][getCol()] != nullptr){
			if(map[getRow()][getCol() + inc] != nullptr){
				if(map[getRow()][getCol() + inc]->getTeam() != map[getRow()][getCol()]->getTeam()){		
					addMove(getSquare());
					break;
				}
				break;
			}
			else addMove(getSquare());
			}
			if(j == -1) inc -= 1;
			if(j == 1) inc += 1;
		}
	}
	if(lit == true) renderMoves(img,false,map);
}

// piece is moved and the chosen board square is re-rendered
void Rook::movePiece(int startY,int startX,int endY, int endX, Piece* map[][8], SDL_Manager img,bool found, bool visual){

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
		if(map[si][sj]->getClass() == Piece::Class::ROOK) map[ei][ej] = new Rook(map[si][sj]->getTeam(),ei,ej,img,visual);
		if(visual == false && map[si][sj]->getType() == Piece::CASTLE) map[ei][ej]->setType(Piece::CASTLE);

		map[si][sj] = nullptr;
		if(visual) SDL_RenderPresent(img.getRenderer());
	}
}

