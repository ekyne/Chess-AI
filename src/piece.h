/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	piece.h
 * Function: 	Holds the Pawn class.
*/

#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "SDL_Manager.h"

struct Square{
	int x = 0;
	int y = 0;
};

class Piece {
	public:
		enum Team {NONE,WHITE,BLACK};
		enum Type {NORMAL,EMPASSANT,CASTLE,ANYPIECE};
		enum Class {PAWN,BISHOP,KNIGHT,ROOK,QUEEN,KING};

		Piece();
		~Piece();
		
		Piece(Team,int,int,Class);
		void renderMoves(SDL_Manager,bool,Piece*[][8]);
		void render(SDL_Manager);
		virtual void findMoves(SDL_Manager,Piece*[][8],bool);
		virtual void movePiece(int,int,int,int,Piece*[][8],SDL_Manager,bool,bool);
		virtual int getSquareValue(int si, int sj);
		bool kingCheck(SDL_Manager, Piece*[][8]);
		void clearMoves(){moves.clear();}

		void setFile(std::string targetFile){file = targetFile;}
		void setPieceTexture(SDL_Texture* targetTexture){pieceTexture = targetTexture;}
		void setTeam(Team targetTeam){p_team = targetTeam;}
		void setType(Type targetType){p_type = targetType;}
		void setClass(Class targetClass){p_class = targetClass;}
		void setSquare(int x, int y){squre.x = x; squre.y = y;}
		void setOffSet(int targetOffSet){offSet = targetOffSet;}
		void addMove(Square targetSquare){moves.push_back(targetSquare);}
		void setValue(int targetValue){value = targetValue;}
		void setRow(int targetRow){row = targetRow;}
		void setCol(int targetCol){col = targetCol;}
		void setVisualImage(bool visual){visualImage = visual;}
		std::string getFile(){return file;}
		SDL_Texture* getPieceTexture(){return pieceTexture;}
		Team getTeam(){return p_team;}
		Type getType(){return p_type;}
		Class getClass(){return p_class;}
		Square getSquare(){return squre;}
		int getOffSet(){return offSet;}
		std::vector<Square>getMoves(){return moves;}
		int getValue(){return value;}
		int getRow(){return row;}
		int getCol(){return col;}
		bool getVisualImage(){return visualImage;}
	private:
		std::string file;
		SDL_Texture* pieceTexture;
		Team p_team = BLACK;
		Type p_type = NORMAL;
		Class p_class;
		Square squre;
		std::vector<Square> moves;
		int value;
		int row;
		int col;
		int offSet = 0;
		bool visualImage = false;
};
