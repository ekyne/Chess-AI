/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	SDL_Manager.cpp
 * Function: 	Holds functions used by the SDL_Manager class.
*/

#include "SDL_Manager.h"

// default constructor for SDL_Manager
SDL_Manager::SDL_Manager(){

}

// SDL_Manager constuctor
SDL_Texture* SDL_Manager::LoadImage(std::string file){
	SDL_Surface* loaded = IMG_Load(file.c_str());
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, loaded);
	return text;
}

// SDL_Manager destructor
SDL_Manager::~SDL_Manager(){

}

// initializes the SDL renderer and SDL window
bool SDL_Manager::init(){
	setLightColorValues(225,200,225,255);
	setDarkColorValues(152,115,172,255);
    bool success=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0){
	    std::cout<<"SDL Error: " << SDL_GetError() << std::endl;
        success=false;
    }
    else{
        if(!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))){
		std::cout<<"Linear Texture Filtering isn't enabled." << std::endl;
        }
        window=SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_DIMENSION, SCREEN_DIMENSION, SDL_WINDOW_SHOWN);
        if(window==NULL){
		std::cout<<"SDL Error: "<< SDL_GetError() << std::endl;
            success=false;
        }
        else{
            renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer==NULL){
		    std::cout<<"SDL Error: "<< SDL_GetError() << std::endl;
                success=false;
            }
        }
    }
    return success;
}

// renders a chess board square with chosen coordinates
void SDL_Manager::renderSquare(SDL_Renderer* imgRenderer, int i, int j, int positionValue, bool randomPiece){
	int sizeMultiple = 1;

	// if randomPiece is chosen, square is twice as big
	if(randomPiece) sizeMultiple = 2;
	SDL_Rect rect = {j*getSquareSize()*sizeMultiple,i*getSquareSize()*sizeMultiple,getSquareSize(),getSquareSize()};
	if(positionValue % 2 == 0){
		SDL_SetRenderDrawColor(getRenderer(), getDarkColorValues().red, getDarkColorValues().green, getDarkColorValues().blue, getDarkColorValues().alpha);
	}
	else{
		SDL_SetRenderDrawColor(getRenderer(), getLightColorValues().red, getLightColorValues().green, getLightColorValues().blue, getLightColorValues().alpha);
	}
	SDL_RenderFillRect(getRenderer(), &rect);
}
