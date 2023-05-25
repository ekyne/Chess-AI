/* Author: 	Kyle Gilmore
 * Date: 	March 18, 2022
 * Project: 	Chess AI
 * File: 	SDL_Manager.h
 * Function: 	Holds the SDL_Manager class.
*/

#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct ColorValues {
	int red = 0;
	int green = 0;
	int blue = 0;
	int alpha = 0;
};

class SDL_Manager {
	public:
		SDL_Manager();
		~SDL_Manager();

		bool init();
		SDL_Texture* LoadImage(std::string);
		void renderSquare(SDL_Renderer*, int, int, int,bool);

		void setRenderer(SDL_Renderer* targetRenderer){renderer = targetRenderer;}
		void setWindow(SDL_Window* targetWindow){window = targetWindow;}
		void setSurface(SDL_Surface* targetSurface){surface = targetSurface;}
		void setLightColorValues(int targetRed, int targetGreen, int targetBlue, int targetAlpha){lightValues.red = targetRed;lightValues.green = targetGreen;lightValues.blue = targetBlue;lightValues.alpha = targetAlpha;}
		void setDarkColorValues(int targetRed, int targetGreen, int targetBlue, int targetAlpha){darkValues.red = targetRed;darkValues.green = targetGreen;darkValues.blue = targetBlue;darkValues.alpha = targetAlpha;}

		SDL_Renderer* getRenderer(){return renderer;}
		SDL_Window* getWindow(){return window;}
		SDL_Surface* getSurface(){return surface;}
		int getScreenDimension(){return SCREEN_DIMENSION;}
		int getSquareSize(){return SQUARE_SIZE;}
		ColorValues getLightColorValues(){return lightValues;}
		ColorValues getDarkColorValues(){return darkValues;}
	private:
		SDL_Renderer* renderer;
		SDL_Window* window;
		SDL_Surface* surface;
		const int SCREEN_DIMENSION = 1000;
		const int SQUARE_SIZE = SCREEN_DIMENSION / 8;
		ColorValues lightValues;
		ColorValues darkValues;
};

#endif
