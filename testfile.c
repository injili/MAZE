#include <SDL2/SDL.h>

/**
 * main - the main function of the application
 * @void: no variable is passed to the function
 *
 * Return: The return value is 0 if all is well or 1 in case of an error
 */

int main(void)
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	/*Initializing SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprint(strderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	/* Creation of a new window instance */
	window = SDL_CreateWindow("SDL2 \\o/", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 1260, 720, 0);
	if (window == NULL)
	{
		fprint(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	/* Creation of a new Renderer instance */
	renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		SDL_DestroyWindow(window);
		fprint(stderr, "SDL_CreateRenderer Error; %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);
}
