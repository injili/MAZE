#ifndef THEMAZE_H
#define THEMAZE_H

/**
 * Inclusion of SDL and C libraries
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/**
 * The definition of global variables
 */

#define ASSERT(cond, ...)                                                      \
  if (!cond) {                                                                 \
    fprintf(stderr, __VA_ARGS__);                                              \
    exit(1);                                                                   \
  }
#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAP_SIZE 16
#define PI 3.14159265f

/**
 * Structures go here
 */
typedef enum {
	NorthSouth,
	EastWest
} Side;
typedef struct {
    float x, y;
} Vec2F;
typedef struct {
    int x, y;
} Vec2I;
typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool quit;
} State;
typedef struct {
	Vec2F pos;
	Vec2F dir;
	Vec2F plane;
} Player;
typedef struct{
    uint8_t r,g,b,a;
} ColorRGBA;

/**
 * External declarations
 */
extern Player player;
extern State state;
extern const float playerFOV;
extern const float maxDepth;
extern const uint8_t MAP[MAP_SIZE * MAP_SIZE];
extern ColorRGBA RGBA_Red;
extern ColorRGBA RGBA_Green;
extern ColorRGBA RGBA_Blue;
extern ColorRGBA colorCeiling;
extern ColorRGBA colorFloor;
extern const uint8_t MOSSYSTONE_TEXTURE[];
extern const uint8_t PURPLESTONE_TEXTURE[];

/**
 * The functions come here
 */
void playerDirection(Player *player, int mouse_xrel, float rotateSpeed);
void moveX(Player *player, const uint8_t *keystate, const float motionSpeed);
void moveY(Player *player, const uint8_t *keystate, const float motionSpeed);
int xy2index(int x, int y, int w);
void render(State *state, Player* player);
#endif/* THEMAZE_H */
