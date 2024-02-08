#ifndef THEMAZE_H
#define THEMAZE_H

/**
 * Inclusion of SDL and C libraries
 */
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>

/**
 * The definition of global variables
 */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

/**
 * Structures go here
 */
typedef struct {
    int quit;
} State;

typedef struct {
    struct {
        float x;
        float y;
    } pos;
    struct {
        float x;
        float y;
    } dir;
    struct {
        float x;
        float y;
    } plane;
} Player;

/**
 * External declarations
 */
extern State state;
extern Player player;

/**
 * The functions come here
 */
void gameLoop(void);
#endif/* THEMAZE_H */
