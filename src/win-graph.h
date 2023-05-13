#ifndef WIN_GRAPH
#define WIN_GRAPH

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct graphics
{
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
	SDL_Event event;
};

int graphics_init(struct graphics* graph, int width, int height);
void draw_map(int map[100][180], SDL_Renderer* renderer);
//void draw_player(struct player p, int size, SDL_Renderer* renderer);

#endif