#include "themaze.h"

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
