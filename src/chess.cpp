/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	chess.cpp
 * Function: 	Main Driver of the Chess AI Project.
*/

#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include "SDL_Manager.h"
#include "piece.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "ai.h"

void MovePiece(int,int,int, int, Piece*[][8], SDL_Manager);
void createAnyPiece(int, int, int, int,Piece*[][8], SDL_Manager);
void clearBoard(Piece*[][8]);

// SDL manager
SDL_Manager img;
SDL_Event event;

// map of chess board
Piece* map[8][8];
bool aiTurn = false;

int main(){

	// initializes SDL manager
	img.init();

	// each piece off the chess board is constructed and rendered to the board
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			map[i][j] = nullptr;
			img.renderSquare(img.getRenderer(),i,j,i+j,false);
			if(i == 1){
				map[i][j] = new Pawn(Piece::BLACK,i,j,img,true);
				map[i][j]->setType(Piece::EMPASSANT);
			}
			if(i == 6){
				map[i][j] = new Pawn(Piece::WHITE,i,j,img,true);
				map[i][j]->setType(Piece::EMPASSANT);
			}

		}
	}
	map[0][0] = new Rook(Piece::BLACK,0,0,img,true);
	map[0][0]->setType(Piece::CASTLE);
	map[0][7] = new Rook(Piece::BLACK,0,7,img,true);
	map[0][7]->setType(Piece::CASTLE);
	map[0][1] = new Knight(Piece::BLACK,0,1,img,true);
	map[0][6] = new Knight(Piece::BLACK,0,6,img,true);
	map[0][5] = new Bishop(Piece::BLACK,0,5,img,true);
	map[0][2] = new Bishop(Piece::BLACK,0,2,img,true);
	map[0][3] = new Queen(Piece::BLACK,0,3,img,true);
	map[0][4] = new King(Piece::BLACK,0,4,img,true);
	map[0][4]->setType(Piece::CASTLE);

	map[7][0] = new Rook(Piece::WHITE,7,0,img,true);
	map[7][0]->setType(Piece::CASTLE);
	map[7][7] = new Rook(Piece::WHITE,7,7,img,true);
	map[7][7]->setType(Piece::CASTLE);
	map[7][1] = new Knight(Piece::WHITE,7,1,img,true);
	map[7][6] = new Knight(Piece::WHITE,7,6,img,true);
	map[7][5] = new Bishop(Piece::WHITE,7,5,img,true);
	map[7][2] = new Bishop(Piece::WHITE,7,2,img,true);
	map[7][3] = new Queen(Piece::WHITE,7,3,img,true);
	map[7][4] = new King(Piece::WHITE,7,4,img,true);
	map[7][4]->setType(Piece::CASTLE);

	SDL_RenderPresent(img.getRenderer());

	// starting x and y coordinates, and ending x and y coordinates
	int sx, sy;
	int ex, ey;

	// coordinates for chosen piece for AI
	int py;
	int px;

	// coordinates for king checking for AI
	int cky = -1;
	int ckx = -1;

	// coordinates for king checking for user
	int kx = -1;
	int ky = -1;

	bool turn = false;
	int found = false;

	//AI object
	AI ai;

	// board values are evaluated
	ai.evaluateBoard(map);
	std::pair<int,Square> sqre;
	Square sq;


	std::cout << std::endl;
	std::cout << "Welcome to the Chess AI program!" << std::endl;
	std::cout << std::endl;
	std::cout << "Click on any light piece to make a move." << std::endl;
	std::cout << "Press Q to quit the program." << std::endl;
	std::cout << std::endl;

	// program waits until user input is made
	while(SDL_WaitEvent(&event)){

		//if a mouse click is made, coordinates of mouse click are found
		if(event.type == SDL_MOUSEBUTTONDOWN){
			sx = event.button.x;
			sy = event.button.y;	
			int ox = sx / img.getSquareSize();
			int oy = sy / img.getSquareSize();

			// if a piece is clicked on, its moves are computed and waits for another mouse click
			if(map[oy][ox] != nullptr){
				if(map[oy][ox]->getTeam() == Piece::BLACK) continue;
				map[oy][ox]->findMoves(img,map,true);
				while(SDL_WaitEvent(&event)){

					// if a valid move is chosen, the piece is moved and checked for a king in AI moves
					if(event.type == SDL_MOUSEBUTTONDOWN){
						ex = event.button.x;
						ey = event.button.y;
						int ux = ex / img.getSquareSize();
						int uy = ey / img.getSquareSize();
						for(auto& square : map[oy][ox]->getMoves()){
							if(uy == square.y && ux == square.x){
								found = true;
							}
						}
						map[oy][ox]->movePiece(sy,sx,ey,ex,map,img,false,true);
						if(map[uy][ux] != nullptr){
							if(map[uy][ux]->getClass() == Piece::PAWN){
								createAnyPiece(oy,ox,uy,ux,map,img);
							}
							if(map[uy][ux]->kingCheck(img,map)){
								ky = uy;
								kx = ux;
							}
						}

						// if a king is in a move, the game is lost if the user does not intervene
						if(cky != -1 && ckx != -1){
							if(map[cky][ckx]->kingCheck(img,map)){
								std::cout << "Game Lost" << std::endl;
								clearBoard(map);
								return 0;
							}
							cky = -1;
							ckx = -1;
						}

						// if a move is valid, pawn pieces that moved via empassant are checked for capture restraints
						if(found == true){
							aiTurn = true;	
							turn = !turn;
							for(int i = 0; i < 8; i++){
								for(int j = 0; j < 8; j++){
									if(map[i][j] != nullptr){
										if(map[i][j]->getTeam() == Piece::NONE){
											if(turn){
												if(map[i][j]->getOffSet() == 1){
													map[i][j] = nullptr;
												}	
											}
											else{
												if(map[i][j]->getOffSet() == -1){
													map[i][j] = nullptr;
												}

											}
										}
									}
								}
							}
							found = false;
						}

						// AI turn after a successful move has been made
						if(aiTurn){

						// coordinates for best AI candinate for moving
						int by = 0;
						int bx = 0;

						// counter for number of pieces on each team
						int bCounter = 0;
						int wCounter = 0;

						// stores piece coordinates
						std::vector<std::pair<int,int>> pieceOrder;
						std::vector<std::pair<int,int>> wPieceOrder;
						int bValue = -10000;

						// stores each piece coordinate
						for(py = 0; py < 8; py++){
							for(px = 0; px < 8; px++){
								if(map[py][px] != nullptr){
									if(map[py][px]->getTeam() == Piece::BLACK){	
										bCounter += 1;
										pieceOrder.push_back(std::make_pair(py,px));
									}
									else if(map[py][px]->getTeam() == Piece::WHITE){
										wCounter += 1;
										wPieceOrder.push_back(std::make_pair(py,px));
									}
								}
							}
						}

						//AI moves are shuffled 
						random_shuffle(pieceOrder.begin(),pieceOrder.end());

						// stores piece icons for efficient computational memory usage
						std::vector<Piece> wStoredTextures(wCounter);
						std::vector<Piece> bStoredTextures(bCounter);
						for(int i = 0; i < bCounter; i++){
			
						bStoredTextures[i].setPieceTexture(map[pieceOrder[i].first][pieceOrder[i].second]->getPieceTexture());
						}

						for(int i = 0; i < wCounter; i++){

						wStoredTextures[i].setPieceTexture(map[wPieceOrder[i].first][wPieceOrder[i].second]->getPieceTexture());
						}

						// iterates through each AI piece counted and computes its possible moves
						for(int i = 0; i < bCounter; i++){


									map[pieceOrder[i].first][pieceOrder[i].second]->findMoves(img,map,false);
									if(map[pieceOrder[i].first][pieceOrder[i].second]->kingCheck(img,map)){
										std::cout << "Game Won" << std::endl;
										clearBoard(map);
										return 0;
									}
									sqre = ai.findPriorityMove(4,map,pieceOrder[i].first,pieceOrder[i].second,1,img,-10000,10000,true);
									// finds the best AI move to chose
									if(sqre.first > bValue){
										map[pieceOrder[i].first][pieceOrder[i].second]->findMoves(img,map,false);
										for(auto& square : map[pieceOrder[i].first][pieceOrder[i].second]->getMoves()){	
											if(sqre.second.y == square.y && sqre.second.x == square.x){
												by = pieceOrder[i].first;
												bx = pieceOrder[i].second;
												sq = sqre.second;
												bValue = sqre.first;
											}
										}
									}

						}

						// returns piece icons for the sake of efficient computational memory usage
						for(int i = 0; i < wCounter; i++){
			
						map[wPieceOrder[i].first][wPieceOrder[i].second]->setPieceTexture(wStoredTextures[i].getPieceTexture());
						}
						for(int i = 0; i < bCounter; i++){
			
						map[pieceOrder[i].first][pieceOrder[i].second]->setPieceTexture(bStoredTextures[i].getPieceTexture());
						}
						if(map[oy][ox] != nullptr){
							if(map[oy][ox]->getTeam() == Piece::NONE){
						       		map[oy][ox] = nullptr; 
							}
						}

						// AI move is made
						map[by][bx]->movePiece(by*img.getSquareSize(),bx*img.getSquareSize(),sq.y*img.getSquareSize(),sq.x*img.getSquareSize(),map,img,true,true);

						// if a king is found in user moves and the AI does not intervene, the user will win
						if(ky != -1 && kx != -1){
							if(map[ky][kx]->kingCheck(img,map)){
								std::cout << "Game Won/Lost" << std::endl;
								clearBoard(map);
								return 0;
							}
							ky = -1;
							kx = -1;
						}

						// king check for AI moves is found here
						if(map[sq.y][sq.x] != nullptr){
							if(map[sq.y][sq.x]->getClass() == Piece::Class::PAWN){
								createAnyPiece(-1,-1,sq.y,sq.x,map,img);
							}
							if(map[sq.y][sq.x]->kingCheck(img,map)){
								cky = sq.y;
								ckx = sq.x;
							}
						}
						if(map[by][bx] != nullptr){
							if(map[by][bx]->getTeam() == Piece::NONE){
						       		map[by][bx] = nullptr; 
							}
						}
						SDL_RenderPresent(img.getRenderer());
						found = false;
						}
						aiTurn = false;
						break;
					}

					// if user keystroke is Q, the game exits
					if(event.type == SDL_KEYDOWN){
						const Uint8* smState = SDL_GetKeyboardState(NULL);
						if(smState[SDL_SCANCODE_Q]){
							clearBoard(map);
							return 0;
						}
					}
				}
			}
			else continue;
		}

		// if user keystroke is Q, the game exits
		if(event.type == SDL_KEYDOWN){
			const Uint8* fmState = SDL_GetKeyboardState(NULL);
			if(fmState[SDL_SCANCODE_Q]){
				clearBoard(map);
				return 0;
			}
		}
	}
	return 0;
}

void createAnyPiece(int si, int sj, int ei, int ej,Piece* map[][8], SDL_Manager img){
	std::string lpieceImages[4] = {"Images/Chess_blt60.png","Images/Chess_nlt60.png","Images/Chess_qlt60.png","Images/Chess_rlt60.png"};	
	std::string dpieceImages[4] = {"Images/Chess_bdt60.png","Images/Chess_ndt60.png","Images/Chess_qdt60.png","Images/Chess_rdt60.png"};
	SDL_Rect rect;
		if(ei == 0 || ei == 7){

			// possible pieces are rendered here
			for(int i = 0; i < 4; i++){
				if(!aiTurn){
					if(ei == 0){
						img.renderSquare(img.getRenderer(),0,i,i,true);
					}
					if(ei == 7){
						img.renderSquare(img.getRenderer(),3,i,i,true);
					}
					if(map[ei][ej]->getTeam() == Piece::WHITE){

						SDL_RenderCopy(img.getRenderer(),img.LoadImage(lpieceImages[i]), NULL, &rect);
					}
					else if(map[ei][ej]->getTeam() == Piece::BLACK){ 

						SDL_RenderCopy(img.getRenderer(),img.LoadImage(dpieceImages[i]), NULL, &rect);
					}
					std::cout << SDL_GetError();
					SDL_RenderPresent(img.getRenderer());
				}
			}
			SDL_Event event;

			// if the AI has the turn, it will randomly select a possible piece
			if(aiTurn){
				if(ei == 7){
					srand(time(0));
					int choice = rand() % 4;
					if(choice == 0) map[ei][ej] = new Bishop(Piece::BLACK,ei,ej,img,true);
					if(choice == 1) map[ei][ej] = new Knight(Piece::BLACK,ei,ej,img,true);
					if(choice == 2) map[ei][ej] = new Queen(Piece::BLACK,ei,ej,img,true);
					if(choice == 3) map[ei][ej] = new Rook(Piece::BLACK,ei,ej,img,true);
				}
			}
			else{

			// if a piece is chosen, the user will gain their desired possible piece
			while(SDL_WaitEvent(&event)){
				if(event.type == SDL_MOUSEBUTTONDOWN){
					if(ei == 0){
						sj = event.button.x;
						si = event.button.y;
						if(si <= 250){
							int ox = sj / (img.getSquareSize()*2);
							if(ox == 0) map[ei][ej] = new Bishop(Piece::WHITE,ei,ej,img,true);
							if(ox == 1) map[ei][ej] = new Knight(Piece::WHITE,ei,ej,img,true);
							if(ox == 2) map[ei][ej] = new Queen(Piece::WHITE,ei,ej,img,true);
							if(ox == 3) map[ei][ej] = new Rook(Piece::WHITE,ei,ej,img,true);
							break;
						}
					}
					if(ei == 7){
						sj = event.button.x;
						si = event.button.y;
						if(si >= 750){
							int ox = sj / (img.getSquareSize()*2);
							if(ox == 0) map[ei][ej] = new Bishop(Piece::BLACK,ei,ej,img,true);
							if(ox == 1) map[ei][ej] = new Knight(Piece::BLACK,ei,ej,img,true);
							if(ox == 2) map[ei][ej] = new Queen(Piece::BLACK,ei,ej,img,true);
							if(ox == 3) map[ei][ej] = new Rook(Piece::BLACK,ei,ej,img,true);
							break;
						}
					}
 				}
			}
			}

			// chess board is re-rendered after selections are chosen
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){
					img.renderSquare(img.getRenderer(),i,j,i+j,false);
					
					if(map[i][j] != nullptr && map[i][j]->getTeam() != Piece::NONE){
						SDL_Rect rect = {j*img.getSquareSize(),i*img.getSquareSize(),img.getSquareSize(),img.getSquareSize()};
						SDL_RenderCopy(img.getRenderer(),map[i][j]->getPieceTexture(), NULL, &rect);
					}
				}
			}
			SDL_RenderPresent(img.getRenderer());
		}
}

// chess board is cleared
void clearBoard(Piece* map[][8]){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(map[i][j] != nullptr){
				map[i][j] = nullptr;
			}
		}
	}
}
