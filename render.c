#include "themaze.h"

/**
 * render - draws the images on window
 * @state: gaming state
 * @player: the player
 *
 * Return: no return value
 */
void render(State *state, Player *player)
{
	for (int x = 0; x < SCREEN_WIDTH; ++x)
	{
		float cameraX = 2 * x / (float)SCREEN_WIDTH - 1;
		float perpWallDist;
		Vec2I stepDir = {};
		bool hit = false;
		Vec2F sideDist = {};
		Side side;
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		ColorRGBA color;
		Vec2F rayDir = {
			.x = player->dir.x + player->plane.x * cameraX,
			.y = player->dir.y + player->plane.y * cameraX,
		};
		Vec2I mapBox = {
			.x = (int)player->pos.x,
			.y = (int)player->pos.y
		};
		Vec2F deltaDist = {
			.x = (rayDir.x == 0) ? 1e30 : fabsf(1 / rayDir.x),
			.y = (rayDir.y == 0) ? 1e30 : fabsf(1 / rayDir.y),
		};

		if (rayDir.x < 0)
		{
			stepDir.x = -1;
			sideDist.x = (player->pos.x - mapBox.x) * deltaDist.x;
		} else
		{
			stepDir.x = 1;
			sideDist.x = (mapBox.x + 1.0f - player->pos.x) * deltaDist.x;
		}
		if (rayDir.y < 0)
		{
			stepDir.y = -1;
			sideDist.y = (player->pos.y - mapBox.y) * deltaDist.y;
		} else
		{
			stepDir.y = 1;
			sideDist.y = (mapBox.y + 1.0f - player->pos.y) * deltaDist.y;
		}
		while (!hit)
		{
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += deltaDist.x;
				mapBox.x += stepDir.x;
				side = EastWest;
			} else
			{
				sideDist.y += deltaDist.y;
				mapBox.y += stepDir.y;
				side = NorthSouth;
			}
			if (MAP[xy2index(mapBox.x, mapBox.y, MAP_SIZE)] > 0)
			{
				hit = true;
			}
		}
		switch (side)
		{
			case EastWest:
				perpWallDist = (sideDist.x - deltaDist.x);
				break;
			case NorthSouth:
				perpWallDist = (sideDist.y - deltaDist.y);
				break;
		}
		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT;
		switch (MAP[xy2index(mapBox.x, mapBox.y, MAP_SIZE)])
		{
			case 1:
				color = RGBA_Red;
				break;
			case 2:
				color = RGBA_Green;
				break;
			case 3:
				color = RGBA_Blue;
				break;
		}
		if (side == NorthSouth)
		{
			color.r /= 2;
			color.g /= 2;
			color.b /= 2;
		}
		SDL_SetRenderDrawColor(state->renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(state->renderer, x, drawStart, x, drawEnd);
	}
}
