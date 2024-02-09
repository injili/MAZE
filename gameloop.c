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
