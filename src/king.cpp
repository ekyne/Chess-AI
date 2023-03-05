/* Author: 	Kylie Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	king.cpp
 * Function: 	Holds functions used by the King class.
*/

#include "king.h"

// default constructor for king
King::King(){

}

// king constuctor which renders a piece texture if it is needed
King::King(Team c_team,int i, int j,SDL_Manager img, bool visual) : Piece(c_team,i,j,KING){
	if(c_team == WHITE){
		setFile("img/Chess_klt45.svg.png");
	}
	else if(c_team == BLACK){
		setFile("img/Chess_kdt45.svg.png");
	}
	if(visual){
		setPieceTexture(img.LoadImage(getFile()));
		render(img);
	}
	setValue(10000);
}

// king deconstructor
King::~King(){

}

// finds the possible moves that can be made
void King::findMoves(SDL_Manager img,Piece* map[][8],bool lit){
	clearMoves();

	// searches all possible square moves
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){

			// if square checked is within the chess board, and if the piece is the enemy team, the move is computed
			if(getRow() + i >= 0 && getRow() + i < 8 && getCol() + j >= 0 && getCol() + j < 8){
				setSquare(getCol()+j,getRow()+i);
				if(map[getRow()][getCol()] != nullptr){
				if(map[getRow() + i][getCol() + j] != nullptr){
					if(map[getRow() + i][getCol() + j]->getTeam() != map[getRow()][getCol()]->getTeam()){		
						addMove(getSquare());
					}

				}
				else addMove(getSquare());
				}
			}
		}
	}

	// if square checked is within the chess board, and if the piece is a castled rook, the move is computed
	if(map[getRow()][getCol()] != nullptr){
	if(map[getRow()][getCol()]->getType() == CASTLE){
		int incJ = 1;
		while(getCol() + incJ < 8){
			if(map[getRow()][getCol()+incJ] != nullptr){
				if(map[getRow()][getCol()+incJ]->getType() == CASTLE){
					setSquare(getCol()+incJ,getRow());
					addMove(getSquare());
					if(lit == true) renderMoves(img,false,map);
				}
				break;
			}
			incJ += 1;
		}
		incJ = 1;
		while(getCol() - incJ < 8){
			if(map[getRow()][getCol()-incJ] != nullptr){
				if(map[getRow()][getCol()-incJ]->getType() == CASTLE){
					setSquare(getCol()-incJ,getRow());
					addMove(getSquare());
					if(lit == true) renderMoves(img,false,map);
				}
				break;
			}
			incJ += 1;
		}
	}
	}	
	if(lit == true) renderMoves(img,false,map);
}

// piece is moved and the chosen board square is re-rendered
void King::movePiece(int startY,int startX,int endY, int endX, Piece* map[][8], SDL_Manager img, bool found, bool visual){

	// starting and ending coordinates chosen
	int si = startY / img.getSquareSize();
	int sj = startX / img.getSquareSize();
	int ei = endY / img.getSquareSize();
	int ej = endX / img.getSquareSize();
	int castledKLoc = 0;
	int castledRLoc = 0;
	bool castledR = false;
	bool castledL = false;

	if(visual) renderMoves(img,true,map);

	// checks for a valid move
	for(auto& square : getMoves()){
		if(ei == square.y && ej == square.x){
			found = true;
		}
	}
	if(ej == 4){
		if(sj == 0){
			castledL = true;
			sj = 2;
			ej = 3;
		}
		if(sj == 7){
			castledR = true;
			sj = 6;
			ej = 5;
		}
	}

	if(((map[si][sj] != nullptr || (ei != si && ej != sj)) && found == true) || (castledL || castledR)){
		if(visual){
			img.renderSquare(img.getRenderer(),si,sj,si+sj,false);
			img.renderSquare(img.getRenderer(),ei,ej,ei+ej,false);
		}
		if((map[si][sj] != nullptr && map[ei][ej] != nullptr) || (castledL || castledR)){

		// if the move is a castling, the move is computed relative to the rook position chosen
		if((map[ei][ej]->getType() == Piece::CASTLE) || (castledL || castledR)){
			if(ej == 0 || castledL){
				if((si == 0 || si == 7) && sj == 2){
					castledKLoc = 4;
					castledRLoc = 0;
					sj = 2;
					ej = 3;
				}
				else{
					castledKLoc = 2;
					castledRLoc = 3;
				}
				if(visual){
					SDL_Rect kRect = {castledKLoc*img.getSquareSize(),si*img.getSquareSize(),img.getSquareSize(),img.getSquareSize()};
					SDL_Rect rRect = {castledRLoc*img.getSquareSize(),si*img.getSquareSize(),img.getSquareSize(),img.getSquareSize()};
					img.renderSquare(img.getRenderer(),si,castledKLoc,si+castledKLoc,false);
					img.renderSquare(img.getRenderer(),ei,castledRLoc,si+castledRLoc,false);

					map[si][castledKLoc] = map[si][sj];
					map[si][castledKLoc]->setType(Piece::NORMAL);
					map[si][castledKLoc]->setCol(castledKLoc);
					SDL_RenderCopy(img.getRenderer(), map[si][castledKLoc]->getPieceTexture(), NULL, &kRect);
					map[ei][castledRLoc] = map[ei][ej];
					map[ei][castledRLoc]->setType(Piece::NORMAL);
					map[si][castledRLoc]->setCol(castledRLoc);
					SDL_RenderCopy(img.getRenderer(), map[ei][castledRLoc]->getPieceTexture(), NULL, &rRect);
				}
				else{

					map[si][castledKLoc] = map[si][sj];
					map[si][castledKLoc]->setCol(castledKLoc);
					if(map[si][sj]->getType() == Piece::Type::CASTLE) map[si][castledKLoc]->setType(Piece::CASTLE);
					map[ei][castledRLoc] = map[ei][ej];
					map[si][castledRLoc]->setCol(castledRLoc);
					if(map[ei][ej]->getType() == Piece::Type::CASTLE) map[ei][castledRLoc]->setType(Piece::CASTLE);
				}
				map[si][sj] = nullptr;
				map[ei][ej] = nullptr;
			}
			else if(ej == 7 || castledR){

				if((si == 0 || si == 7) && sj == 6){

					castledKLoc = 4;
					castledRLoc = 7;

				}
				else{
					castledKLoc = 6;
					castledRLoc = 5;
				}
				if(visual){
					SDL_Rect kRect = {castledKLoc*img.getSquareSize(),si*img.getSquareSize(),img.getSquareSize(),img.getSquareSize()};
					SDL_Rect rRect = {castledRLoc*img.getSquareSize(),si*img.getSquareSize(),img.getSquareSize(),img.getSquareSize()};
					img.renderSquare(img.getRenderer(),si,castledKLoc,si+castledKLoc,false);
					img.renderSquare(img.getRenderer(),ei,castledRLoc,si+castledRLoc,false);

					map[si][castledKLoc] = map[si][sj];
					map[si][castledKLoc]->setType(Piece::NORMAL);
					map[si][castledKLoc]->setCol(castledKLoc);
					SDL_RenderCopy(img.getRenderer(), map[si][castledKLoc]->getPieceTexture(), NULL, &kRect);
					map[ei][castledRLoc] = map[ei][ej];
					map[si][castledRLoc]->setType(Piece::NORMAL);
					map[ei][castledRLoc]->setCol(castledRLoc);
					SDL_RenderCopy(img.getRenderer(), map[ei][castledRLoc]->getPieceTexture(), NULL, &rRect);
				}
				else{
					map[si][castledKLoc] = map[si][sj];
					map[ei][castledKLoc]->setCol(castledKLoc);
					map[ei][castledRLoc] = map[ei][ej];
					map[ei][castledRLoc]->setCol(castledRLoc);
				}
				map[si][sj] = nullptr;
				map[ei][ej] = nullptr;
			}
		}
		}

		// new piece is rendered here and previous piece is deleted
		if(map[si][sj] != nullptr){
			if(map[si][sj]->getClass() == Piece::KING) map[ei][ej] = new King(map[si][sj]->getTeam(),ei,ej,img,visual);
			if(visual == false && map[si][sj]->getType() == Piece::CASTLE) map[ei][ej]->setType(Piece::CASTLE);
		}
		map[si][sj] = nullptr;
		if(visual) SDL_RenderPresent(img.getRenderer());
	}

}

