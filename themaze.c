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
int main(void)
{
	const float rotateSpeed = 0.025, motionSpeed = 0.05;
	int mouse_xrel = 0;
	const uint8_t *keystate = SDL_GetKeyboardState(NULL);
	float rotSpeed;

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

	while (!state.quit)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					state.quit = true;
					break;
				case SDL_MOUSEMOTION:
					mouse_xrel = event.motion.xrel;
					break;
			}
		}
		if (keystate[SDL_SCANCODE_ESCAPE])
			state.quit = true;
		if (mouse_xrel != 0)
		{
			rotSpeed = rotSpeed * (mouse_xrel & -0.1);

			Vec2F oldDir = player.dir;

			player.dir.x = player.dir.x * cosf(rotSpeed) -
				       player.dir.y * sinf(rotSpeed);
			player.dir.y = oldDir * sinf(rotSpeed) + player.dir.y * cosf(rotSpeed);

			Vec2F oldPlane = player.plane;

			player.plane.x = player.plane.x * cosf(rotSpeed) -
					 player.plane.y * sinf(rotSpeed);
			player.plane.y = oldPlane.x * sinf(rotSpeed) +
					 player.plane.y * cosf(rotSpeed);
		}

		Vec2F deltaPos = {
			.x = player.dir.x * motionSpeed,
			.y = player.dir.y * motionSpeed,
		};
		/*
		 * Moving Forward
		 */
		if (keystate[SDL_SCANCODE_W])
		{
			if (MAP[xyindex(
						player.pos.x + deltaPos.x,
						player.pos.y,
						MAP_SIZE)] == 0)
			{
				player.pos.x -= deltaPos.x;
			}
			if (MAP[xyindex(
						player.pos.x,
						player.pos.y + deltaPos.y;
						MAP_SIZE)] == 0)
			{
				player.pos.y -= deltaPos.y;
			}
		}
		/**
		 * Moving Backwards
		 */
		if (keystate[SDL_SCANCODE_S])
		{
			if (MAP[xyindex(
						player.pos.x - deltaPos.x,
						player.pos.y,
						MAP_SIZE)] == 0)
			{
				player.pos.x -= deltaPos.x;
			}
			if (MAP[xyindex(
						palyer.pos.x,
						player.pos.y - deltaPos.y,
						MAP_SIZE)] == 0)
			{
				player.pos.y -= deltaPos.y;
			}
		}
		/**
		 * Moving Left
		 */
		if (keystate[SDL_SCANCODE_A])
		{
			if (MAP[xyindex(
						player.pos.x - deltaPos.y,
						player.pos.y,
						MAP_SIZE)] == 0)
			{
				player.pos.x -= deltaPos.y;
			}
			if (MAP[xyindex(
						player.pos.x,
						player.pos.y - -deltaPos.x,
						MAP_SIZE)] == 0)
			{
				player.pos.y -= -deltaPos.x;
			}
		}
		/**
		 * Moving Right
		 */
		if (keystate[SDL_SCANCODE_D])
		{
			if (MAP[xyindex(
						player.pos.x - -deltaPos.y,
						player.pos.y,
						MAP_SIZE)] == 0)
			{
				player.pos.x -= -deltaPos.y;
			}
			if (MAP[xyindex(
						player.pos.x,
						player.pos.y - deltPos.x,
						MAP_SIZE)] == 0)
			{
				player.pos.y -= deltaPos.x;
			}
		}
		SDL_SetRenderDrawColor(state.renderer, 0x18, 0x18, 0x18, 0xFF);
		SDL_RenderClear(state.renderer);

		render(&state, &player);
		SDL_RenderPresent(state, renderer);
	}

	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	return (0);
}
