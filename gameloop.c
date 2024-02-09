#include "themaze.h"

/**
 * xy2index - x y indexer
 * @y: y value
 * @x: x value
 *
 * Return: an integer value
 */
int xy2index(int x, int y, int w) {
    return y * w + x;
}
	 * Moving Forward
		 */
		if (keystate[SDL_SCANCODE_W])
		{
			if (MAP[xy2index(player.pos.x + deltaPos.x, player.pos.y,
					MAP_SIZE)] == 0)
			{
				player.pos.x -= deltaPos.x;
			}
			if (MAP[xy2index(player.pos.x, player.pos.y + deltaPos.y,
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
		/**
		 * Moving Left
		 */
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
		/**
		 * Moving Right
		 */
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
		SDL_SetRenderDrawColor(state.renderer, 0x18, 0x18, 0x18, 0xFF);
		SDL_RenderClear(state.renderer);
		render(&state, &player);
		SDL_RenderPresent(state.renderer);
	}
}
