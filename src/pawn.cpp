/* Author: 	Kylie Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	pawn.cpp
 * Function: 	Holds functions used by the Pawn class.
*/

#include "pawn.h"

// default constructor for pawn
Pawn::Pawn(){

}

// pawn constuctor which renders a piece texture if it is needed
Pawn::Pawn(Team c_team,int i, int j,SDL_Manager img, bool visual) : Piece(c_team,i,j,PAWN){	
	if(c_team == WHITE){
		setFile("img/Chess_plt45.svg.png");
		setOffSet(-1);
		if(visual){
			setPieceTexture(img.LoadImage(getFile()));
			render(img);
		}
	}
	else if(c_team == BLACK){
		setFile("img/Chess_pdt45.svg.png");
		setOffSet(1);
		if(visual){
			setPieceTexture(img.LoadImage(getFile()));
			render(img);
		}
	}
	setValue(100);
}

// pawn deconstructor
Pawn::~Pawn(){

}

// finds the possible moves that can be made
void Pawn::findMoves(SDL_Manager img,Piece* map[][8],bool lit){
	int emOffSet = 0;
	if(getTeam() == WHITE){
		emOffSet = -2;
		setOffSet(-1);	
	}
	else if(getTeam() == BLACK){
		emOffSet = 2;
		setOffSet(1);
	}

	// if pawn possible moves are within the chess board
	if(getRow() + getOffSet() < 0 || getRow() + getOffSet() > 7) return;
	if(getRow() + getOffSet() >= 0 && getRow() + getOffSet() < 8){

		// possible moves for a pawn are computed
		if(map[getRow() + getOffSet()][getCol()] == nullptr){
				setSquare(getCol(),getRow() + getOffSet());
				addMove(getSquare());	
				if(lit == true) renderMoves(img,false,map);

				//if pawn piece is of type empassant, its offset is stored
				if(map[getRow()][getCol()]->getType() == Piece::EMPASSANT){
					if(getRow() + emOffSet >= 0 && getRow() + emOffSet < 8){
						if(map[getRow() + emOffSet][getCol()] == nullptr){
							setSquare(getCol(),getRow() + emOffSet);
							addMove(getSquare());	
							if(lit == true) renderMoves(img,false,map);
						}
					}
				}	
			}
			
			// possible moves for pawn piece are checked whether it is the enemy team and if valid moves could be played depending on the affiliation of the piece evaluated
			if(getCol()-1 >= 0){
				if(map[getRow()+getOffSet()][getCol()-1] != nullptr && map[getRow()+getOffSet()][getCol() - 1]->getTeam() != map[getRow()][getCol()]->getTeam()){
					if(map[getRow() + getOffSet()][getCol() - 1] != nullptr){
						if(map[getRow() + getOffSet()][getCol() - 1]->getTeam() != map[getRow()][getCol()]->getTeam()){
							if(map[getRow() + getOffSet() + map[getRow()+getOffSet()][getCol()-1]->getOffSet()][getCol()-1] != nullptr){
								if(map[getRow() + getOffSet()][getCol() - 1]->getTeam() == Piece::NONE && map[getRow() + getOffSet() + map[getRow()+getOffSet()][getCol()-1]->getOffSet()][getCol() - 1]->getTeam() != map[getRow()][getCol()]->getTeam()){
									setSquare(getCol()-1,getRow() + getOffSet());
									addMove(getSquare());
									if(lit == true) renderMoves(img,false,map);
								}
								else if(map[getRow() + getOffSet()][getCol() - 1]->getTeam() != Piece::NONE){
									setSquare(getCol()-1,getRow() + getOffSet());
									addMove(getSquare());
									if(lit == true) renderMoves(img,false,map);
								}
							}
							else if(map[getRow() + getOffSet()][getCol() - 1]->getTeam() != Piece::NONE){
								setSquare(getCol()-1,getRow() + getOffSet());
								addMove(getSquare());
								if(lit == true) renderMoves(img,false,map);
							}
						}
					}
				}	
			}
			if(getCol()+1 < 8){	
				if(map[getRow()+getOffSet()][getCol()+1] != nullptr && map[getRow()+getOffSet()][getCol()+1]->getTeam() != map[getRow()][getCol()]->getTeam()){
					if(map[getRow() + getOffSet()][getCol() + 1] != nullptr){
						if(map[getRow() + getOffSet()][getCol() + 1]->getTeam() != map[getRow()][getCol()]->getTeam()){
							if(map[getRow() + getOffSet() + map[getRow()+getOffSet()][getCol()+1]->getOffSet()][getCol()+1] != nullptr){
								if(map[getRow() + getOffSet()][getCol() + 1]->getTeam() == Piece::NONE && map[getRow() + getOffSet() + map[getRow()+getOffSet()][getCol()+1]->getOffSet()][getCol() + 1]->getTeam() != map[getRow()][getCol()]->getTeam()){
									setSquare(getCol()+1,getRow() + getOffSet());
									addMove(getSquare());
									if(lit == true) renderMoves(img,false,map);
								}
								else if(map[getRow() + getOffSet()][getCol() + 1]->getTeam() != Piece::NONE){
									setSquare(getCol()+1,getRow() + getOffSet());
									addMove(getSquare());
									if(lit == true) renderMoves(img,false,map);
								}
							}
							else if(map[getRow() + getOffSet()][getCol() + 1]->getTeam() != Piece::NONE){
								setSquare(getCol()+1,getRow() + getOffSet());
								addMove(getSquare());
								if(lit == true) renderMoves(img,false,map);
							}
						}
					}
				}
			}
		}
}

// piece is moved and the chosen board square is re-rendered
void Pawn::movePiece(int startY,int startX,int endY, int endX, Piece* map[][8], SDL_Manager img,bool found,bool visual){

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
		if(map[ei][ej] != nullptr){
			if(map[ei][ej]->getTeam() == NONE){
				map[ei + map[ei][ej]->getOffSet()][ej] = nullptr;
				if(visual){
					img.renderSquare(img.getRenderer(),ei+map[ei][ej]->getOffSet(),ej,(ei+map[ei][ej]->getOffSet())+ej,false);
					SDL_RenderPresent(img.getRenderer());
				}
			}
		}
		if(map[si][sj]->getClass() == Piece::Class::PAWN) map[ei][ej] = new Pawn(map[si][sj]->getTeam(),ei,ej,img,visual);
		if(visual == false && map[si][sj]->getType() == Piece::EMPASSANT) map[ei][ej]->setType(Piece::EMPASSANT);
		if(abs(ei - si) == 2 && map[ei - getOffSet()][ej] == nullptr){
		       	map[ei - getOffSet()][ej] = new Pawn(NONE,ei-getOffSet(),ej,img,visual);
			map[ei - getOffSet()][ej]->setOffSet(map[si][sj]->getOffSet());
		}
		map[si][sj] = nullptr;
		if(visual) SDL_RenderPresent(img.getRenderer());
	}
}

