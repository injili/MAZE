#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main ( int argc, char* args[] )
{
	//the window will be rendered to
	SDL_Window* window = NULL;

	//the surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if ( SDL_Init(SDL_INIT_VIDEO ) < 0 )
	{
		printf ( "SDL could not initialize! SDL Error %s\n", SDL_GetError() );
	}
	else {
		//create window
		window = SDL_CreateWindow ( "SDL MAZE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if (window == NULL ) {
			printf ( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
	}
	return (0);
}
