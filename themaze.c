#include <themaze.h>

const uint8_t MAP[MAP_SIZE * MAP_SIZE] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 2, 0, 1,
	1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 2, 0, 1,
	1, 0, 0, 0, 0, 0, 3, 2, 2, 2, 2, 2, 2, 2, 0, 1,
	1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 2, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 2, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 2, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
}
/**
 * main - check the code
 *
 * Return: Always 0.
 */
int main(void)
{
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

	gameloop(&state, &player, &motionSpeed, &mouse_xrel, keystate, &rotSpeed);

	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	return (0);
}
