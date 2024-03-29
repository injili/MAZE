#include "themaze.h"

/**
 * gameloop - the loop that the motion and the player moves
 * @state: this is the state of the game
 * @player: this is the player of the game
 *
 * Return: no return value
 */
void gameloop(State *state, Player *player)
{
	const float rotateSpeed = 0.025, motionSpeed = 0.05;
	int mouse_xrel;
	const uint8_t *keystate = SDL_GetKeyboardState(NULL);

	while (!state->quit)
	{
		SDL_Event event;

		mouse_xrel = 0;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					state->quit = true;
					break;
				case SDL_MOUSEMOTION:
					mouse_xrel = event.motion.xrel;
					break;
			}
		}
		if (keystate[SDL_SCANCODE_ESCAPE])
			state->quit = true;

		playerDirection(player, mouse_xrel, rotateSpeed);
		moveX(player, keystate, motionSpeed);
		moveY(player, keystate, motionSpeed);
		SDL_SetRenderDrawColor(state->renderer, 0x18, 0x18, 0x18, 0xFF);
		SDL_RenderClear(state->renderer);
		render(state, player);
		SDL_RenderPresent(state->renderer);
	}
}

/**
 * main - the main function of the program
 *
 * Return: Always 0.
 */
int main(void)
{
	const float playerFOV = (PI / 2.0f);
	const float maxDepth = 20.0f;
	State state = {
		.quit = false,
	};
	Player player = {
		.pos = {.x = 4.0f, .y = 4.0f},
		.dir = {.x = -1.0f, .y = 0.0f},
		.plane = {.x = 0.0f, .y = 0.66f},
	};

	ASSERT(!SDL_Init(SDL_INIT_VIDEO),
		"SDL Failed ro initialize; %s\n",
		SDL_GetError());

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

	state.renderer =
		SDL_CreateRenderer(state.window, -1, SDL_RENDERER_PRESENTVSYNC);

	ASSERT(state.renderer,
		   "failed to create SDL renderer: %s\n",
		   SDL_GetError());

	SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1");
	SDL_SetRelativeMouseMode(true);

	gameloop(&state, &player);
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	return (0);
}
