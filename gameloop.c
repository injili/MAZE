#include "themaze.h"

State state = {
	.quit = false,
};
Player player = {
	.pos = {.x = 4.0f, .y = 4.0f},
	.dir = {.x = -1.0f, .y = 0.0f},
	.plane = {.x = 0.0f, .y = 0.66f},
};
/**
 * xy2index - x y indexer
 * @y: the player's y position
 * @x: the player's x position
 * @w: the size of the map
 *
 * Return: an integer value
 */
int xy2index(int x, int y, int w)
{
	return (y * w + x);
}

/**
 * playerDirection - the direction the player is facing
 * @mouse_xrel: mouse entry
 * @rotateSpeed: the speed of rotation
 *
 * Return: no return value
 */
void playerDirection(int mouse_xrel, float rotateSpeed)
{
	if (mouse_xrel != 0)
	{
		float rotSpeed = rotateSpeed * (mouse_xrel * -0.1);
		Vec2F oldDir = player.dir;

		player.dir.x = player.dir.x * cosf(rotSpeed) -
			       player.dir.y * sinf(rotSpeed);
		player.dir.y = oldDir.x * sinf(rotSpeed) +
			       player.dir.y * cosf(rotSpeed);
		Vec2F oldPlane = player.plane;

		player.plane.x = player.plane.x * cosf(rotSpeed) -
				 player.plane.y * sinf(rotSpeed);
		player.plane.y = oldPlane.x * sinf(rotSpeed) +
				 player.plane.y * cosf(rotSpeed);
	}
}

/**
 * moveX - Move players along the X axis
 * @keystate: the player input for movement in the game
 * @motionSpeed: the speed of movement
 *
 * Return: no return value
 */
void moveX(const uint8_t *keystate, const float motionSpeed)
{
	Vec2F deltaPos = {.x = player.dir.x * motionSpeed,
			  .y = player.dir.y * motionSpeed,};

	if (keystate[SDL_SCANCODE_A])
	{
		if (MAP[xy2index(player.pos.x - deltaPos.y, player.pos.y,
				MAP_SIZE)] == 0)
		{
			player.pos.x -= deltaPos.y;
		}
		if (MAP[xy2index(player.pos.x, player.pos.y - -deltaPos.x,
				MAP_SIZE)] == 0)
		{
			player.pos.y -= -deltaPos.x;
		}
	}
	if (keystate[SDL_SCANCODE_D])
	{
		if (MAP[xy2index(player.pos.x - -deltaPos.y, player.pos.y,
				MAP_SIZE)] == 0)
		{
			player.pos.x -= -deltaPos.y;
		}
		if (MAP[xy2index(player.pos.x, player.pos.y - deltaPos.x,
				MAP_SIZE)] == 0)
		{
			player.pos.y -= deltaPos.x;
		}
	}
}

/**
 * moveY - Move players along the y axis
 * @keystate: the player input for movement in the game
 * @motionSpeed: the speed of motion
 *
 * Return: no return value
 */
void moveY(const uint8_t *keystate, const float motionSpeed)
{
	Vec2F deltaPos = {.x = player.dir.x * motionSpeed,
			  .y = player.dir.y * motionSpeed,};

	if (keystate[SDL_SCANCODE_W])
	{
		if (MAP[xy2index(player.pos.x + deltaPos.x, player.pos.y,
				MAP_SIZE)] == 0)
		{
			player.pos.x += deltaPos.x;
		}
		if (MAP[xy2index(player.pos.x, player.pos.y + deltaPos.y,
				MAP_SIZE)] == 0)
		{
			player.pos.y += deltaPos.y;
		}
	}
	if (keystate[SDL_SCANCODE_S])
	{
		if (MAP[xy2index(player.pos.x - deltaPos.x, player.pos.y,
				MAP_SIZE)] == 0)
		{
			player.pos.x -= deltaPos.x;
		}
		if (MAP[xy2index(player.pos.x, player.pos.y - deltaPos.y,
				MAP_SIZE)] == 0)
		{
			player.pos.y -= deltaPos.y;
		}
	}
}

/**
 * gameloop - the loop that the motion and the player moves
 * @void: the player and state are global now
 *
 * Return: no return value
 */
void gameloop(void)
{
	const float rotateSpeed = 0.025, motionSpeed = 0.05;
	int mouse_xrel;
	const uint8_t *keystate = SDL_GetKeyboardState(NULL);

	while (!state.quit)
	{
		SDL_Event event;

		mouse_xrel = 0;
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

		playerDirection(mouse_xrel, rotateSpeed);
		moveX(keystate, motionSpeed);
		moveY(keystate, motionSpeed);
		SDL_SetRenderDrawColor(state.renderer, 0x18, 0x18, 0x18, 0xFF);
		SDL_RenderClear(state.renderer);
		render(&state, &player);
		SDL_RenderPresent(state.renderer);
	}
}

