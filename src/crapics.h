#ifdef CRAP_GRAPHICS
#define CRAP_GRAPHICS
#endif

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_image.h>

typedef struct crapics
{
	SDL_Window* window;
	SDL_Surface* screen_surface;
	SDL_Event event;
	SDL_Renderer* renderer;
} crapics;

int crap_init(crapics* app, int width, int height);
void crap_quit(crapics* app);
void crap_update(crapics* app);
void draw_squares(crapics* crap, float x, float y, int height, int width, int shade);