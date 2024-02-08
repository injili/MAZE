/**
 * themaze.c
 * the main maze source code
 */
#include <themaze.h>

int main(int argc, char* args[])
{
	//the window will be rendered to
	SDL_Window* window = NULL;

	//the surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error %s\n", SDL_GetError());
	}
	else {
		//create window
		window = SDL_CreateWindow ("SDL MAZE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		} else {
			//get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//fill the surface with white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//update the surface
			SDL_UpdateWindowSurface(window);

			//hack to get window to stay up
			SDL_Event e; bool quit = false;	while(quit == false){ while(SDL_PollEvent (&e)) { if(e.type == SDL_QUIT) quit = true; }}
		}
	}

	//destroy window
	SDL_DestroyWindow(window);

	//quit SDL subsystems
	SDL_Quit();

	return (0);
}
