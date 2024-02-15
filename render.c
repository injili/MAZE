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
		Vec2F rayDir = {
			.x = player->dir.x + player->plane.x * cameraX,
			.y = player->dir.y + player->plane.y * cameraX,
		};
		Vec2I mapBox = {
			.x = (int)player->pos.x,
			.y = (int)player->pos.y
		};
		Vec2F sideDist = {};
		Vec2F deltaDist = {
			.x = (rayDir.x == 0) ? 1e30 : fabsf(1 / rayDir.x),
			.y = (rayDir.y == 0) ? 1e30 : fabsf(1 / rayDir.y),
		};
		float perpWallDist;
		Vec2I stepDir = {};
		bool hit = false;
		Side side;

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
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;

		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT;

		int texWidth = ;
		int texX;
		if (side == EastWest)
			texX = (int)(player->pos.y + perpWallDist * rayDir.y);
		else
			texX = (int)(player->pos.x + perpWallDist * rayDir.x);
		texX %= texWidth;
		if (texX < 0)
			texX += texWidth;

		ColorRGBA color;
		const uint8_t *wallTexture;
		switch (MAP[xy2index(mapBox.x, mapBox.y, MAP_SIZE)])
		{
			case 1:
				wallTexture = PURPLESTONE_TEXTURE;
				break;
			case 2:
				wallTexture = MOSSYSTONE_TEXTURE;
				break;
			case 3:
				wallTexture = MOSSYSTONE_TEXTURE;
				break;
		}
		for (int y = drawStart; y < drawEnd; ++y)
		{
			int texY = (((y * 2 - SCREEN_HEIGHT + lineHeight) << 6) / lineHeight) / 2;
			uint32_t color = wallTexture[texWidth * texY + texX];
			SDL_SetRenderDrawColor(state->renderer, (color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
			SDL_RenderDrawPoint(state->renderer, x, y);
		}
		/**
		 * if (side == NorthSouth)
		{
			color.r /= 2;
			color.g /= 2;
			color.b /= 2;
		}
		SDL_SetRenderDrawColor(state->renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(state->renderer, x, drawStart, x, drawEnd);
		*/
		SDL_SetRenderDrawColor(state->renderer, colorCeiling.r, colorCeiling.g, colorCeiling.b, colorCeiling.a);
		SDL_RenderDrawLine(state->renderer, x, 0, x, drawStart);
		SDL_SetRenderDrawColor(state->renderer, colorFloor.r, colorFloor.g, colorFloor.b, colorFloor.a);
		SDL_RenderDrawLine(state->renderer, x, drawEnd, x, SCREEN_HEIGHT);
	}
}
