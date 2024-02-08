/**
 * themaze.c
 * contains the main function of the game
 */
#include <themaze.h>

/**
 * main - the main function of the game
 * @void: the function takes no arguments
 *
 * Return: the source code returns 0 on a successful run
 */
int main(void) {
	const float rotateSpeed = 0.025, motionSpeed = 0.05;

	ASSERT(!SDL_Init(SDL_INIT_VIDEO),
		"SDL Failed ro initialize; %s\n",
		SDL_GetError();
	State state = {
		.quit = false,
	};
	state.window = 
		SDL_CreateWindow("Raycast",
				 SDL_WINDOWPOS_CENTERED_DISPLAY(0),
				 SDL_WINDOWPOS_CENTERED_DISPLAY(0),
				 SCREEN_WIDTH,
				 SCREEN_HEIGHT,
				 SDL_WINDOW_ALLOW_HIGHDPI);
	ASSERT(state.window,
	       "failed to create SDL rendere: %s\n",
	       SDL_GetError());

	SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1");
	SDL_SetRelativeMouseMode(true);

	Player player = {
		.pos = {.x = 4.0f, .y = 4.0f},
		.dir = {.x = -1.0f, .y = 0.0f},
		.plane = {.x = 0.0f, .y = 0.66f},
	};

	while(!state.quit) {
		SDL_Event event;
		int mouse_xrel = 0;
		while (SDL_PollEvent(&event)){
			switch (event.type) {
				case SDL_QUIT:
					state.quit = true;
					break;
				case SDL_MOUSEMOTION:
					mouse+xrel = event.motion.xrel;
					break;
			}
		}

		const
	}
	return (0);
}
