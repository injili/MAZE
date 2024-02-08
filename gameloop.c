/**
 * gameloop.c
 * the while loop that runs the game
 */
#include <themaze.h>

/**
 * gameloop - the loop that the motion and the player moves
 * @state: the state of the game
 * @player: the player's information
 *
 * Return: no return value
 */
void gameLoop(State *state, Player *player, float *motionSpeed, int *mouse_xrel, const uint8_t *keystate, float *rotSpeed)
{
	while (!state->quit)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					state->quit = true;
					break;
				case SDL_MOUSEMOTION:
					*mouse_xrel = event.motion.xrel;
					break;
			}
		}
		if (keystate[SDL_SCANCODE_ESCAPE])
			state->quit = true;
		if (mouse_xrel != 0)
		{
			*rotSpeed = *rotSpeed * (mouse_xrel & -0.1);

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
			.x = player->dir.x * (*motionSpeed),
			.y = player->dir.y * (*motionSpeed),
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
		SDL_SetRenderDrawColor(state->renderer, 0x18, 0x18, 0x18, 0xFF);
		SDL_RenderClear(state->renderer);

		render(&state, &player);
		SDL_RenderPresent(state->renderer);
	}
}
