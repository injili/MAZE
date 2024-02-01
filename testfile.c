#include <SDL2/SDL.h>

int main(void)
{
	SDL_Window *window;
	SDL_Render *renderer;

	if (SDL_Init(SDL_INIT_VIDEO) !- 0)
	{
		fprint(strderr, "unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	window = SDL_CreateWindow("SDL2\\o/", SDL_WINDOWS_CENTERED,
			SDL_WINDOW_CENTERED, 1260, 720, 0);
	if (window == NULL)
	{
		fprint(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		SDL_DestroyWindow(window);
		fprint(stderr, "SDL_CreateRenderer Error; %s\n", SDL_GetError());
		SDL_Quit();
		return(1);
	}
	return(0);
}
