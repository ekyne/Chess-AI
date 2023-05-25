/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	piece.cpp
 * Function: 	Holds functions used by the Piece class.
*/

#include <iostream>
#include <SDL2/SDL_image.h>
#include "piece.h"

// default constructor for piece
Piece::Piece(){
}

// piece constuctor
Piece::Piece(Team c_team, int i, int j,Class c_class){
	p_team = c_team;
	row = i;
	col = j;
	p_class = c_class;
}

// piece destructor
Piece::~Piece(){

}

// renders valid moves held by a piece
void Piece::renderMoves(SDL_Manager img, bool moved,Piece* map[][8]){
	ColorValues targetDarkValues = img.getDarkColorValues();
	ColorValues targetLightValues = img.getLightColorValues();
	
	// for each valid move, it is rendered on the chess board
	for(auto& square: moves){
		if(moved == false){
			img.setDarkColorValues(204,136,0,255);
			img.setLightColorValues(255,235,175,255);

			img.renderSquare(img.getRenderer(),square.y,square.x,square.y+square.x,false);
			if(map[square.y][square.x] != nullptr && map[square.y][square.x]->p_team != NONE){
				SDL_Rect rect = {square.x*img.getSquareSize(),square.y*img.getSquareSize(),img.getSquareSize(),img.getSquareSize()};
				SDL_RenderCopy(img.getRenderer(),map[square.y][square.x]->getPieceTexture(), NULL, &rect);
			}
			SDL_RenderPresent(img.getRenderer());
		}
		else{
			img.setDarkColorValues(targetDarkValues.red,targetDarkValues.green,targetDarkValues.blue,targetDarkValues.alpha);
			img.setLightColorValues(targetLightValues.red,targetLightValues.green,targetLightValues.blue,targetLightValues.alpha);
			img.renderSquare(img.getRenderer(),square.y,square.x,square.y+square.x,false);
			if(map[square.y][square.x] != nullptr && map[square.y][square.x]->p_team != NONE){

				SDL_Rect rect = {square.x*img.getSquareSize(),square.y*img.getSquareSize(),img.getSquareSize(),img.getSquareSize()};
				SDL_RenderCopy(img.getRenderer(),map[square.y][square.x]->getPieceTexture(), NULL, &rect);
			}
			SDL_RenderPresent(img.getRenderer());
		}
	}
}

// renders a piece icon
void Piece::render(SDL_Manager img){
	SDL_Rect rect = {col*img.getSquareSize(),row*img.getSquareSize(),img.getSquareSize(),img.getSquareSize()};
	SDL_RenderCopy(img.getRenderer(),getPieceTexture(), NULL, &rect);
	std::cout << SDL_GetError();
	SDL_RenderPresent(img.getRenderer());
}

// virtual function for findMoves
void Piece::findMoves(SDL_Manager,Piece*[][8],bool){

}

// virtual function for movePiece
void Piece::movePiece(int startY,int startX,int endY, int endX, Piece* map[][8], SDL_Manager img, bool found, bool visual){

}

// searches for a king in the possible moves
bool Piece::kingCheck(SDL_Manager img, Piece* map[][8]){

	map[row][col]->findMoves(img,map,false);

	for(auto& square : moves){
		if(map[square.y][square.x] != nullptr){
		if(map[square.y][square.x]->p_class == KING){

			return true;

		}
		}
	}
	return false;

}

// virtual function for getSquareValue
int Piece::getSquareValue(int squareI, int squareJ){
	return 0;
}
