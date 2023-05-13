#include "win-graph.h"

int graphics_init(struct graphics* graph, int width, int height)
{
	// Sets up a window for use with SDL. Ideally, 
	// I'll make everything work through here and 
	// I won't need to deal with it later.

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	//Create window
	graph->window = SDL_CreateWindow("SDLol", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	SDL_Delay(100); // So that the OS and window manager have time to resolve conflicts

	// Create renderer
	graph->renderer = SDL_CreateRenderer(graph->window, -1, SDL_RENDERER_ACCELERATED);

	// Error checking
	if (graph->window == NULL || graph->renderer == NULL)
	{
		printf("Someting wong! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}
	
	// For loading PNGs later
	IMG_Init(IMG_INIT_PNG);
	
	return 0;
}

void draw_map(int map[100][180], SDL_Renderer* renderer)
{

	// At the moment, only capable of putting a black
	// square on the screen everywhere the grid does 
	// not equal 0
	
	// Number of tiles for the x and y axes
	int x_bound = 180;
	int y_bound = 100;

	// Location and color of tile to be drawn
	SDL_Rect tile;
	tile.w = 5; tile.h = 5;
	tile.x = 0; tile.y = 0;

	// Draw grid
	for (int y = 0; y < y_bound; y++)
	{
		// Increment the y axis
		tile.y = tile.w * y;

		for (int x = 0; x < x_bound; x++)
		{
			// Increment the x axis
			tile.x = tile.w * x;

			// Draw if necessary
			if (map[y][x] > 0)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
				SDL_RenderFillRect(renderer, &tile);

			}
		}


	}

}

/**
void draw_map(struct map map, int tile_x, int tile_y, SDL_Renderer* renderer)
{
	// Draws a 2d tile based map to an 
	// SDL renderer. Ideally, this will 
	// be the renderer for the main window.

	int tile_width = 32; int tile_height = 32; int num_columns = 6;

	SDL_Texture* texture = IMG_LoadTexture(renderer, "./assets/tileset.png");
	if (texture == NULL)
	{
		printf("WHYYYYYYY\n");
		return;
	}

	// Location in the tilemap to use, location on the screen to draw tile
	SDL_Rect tile; tile.x = 0; tile.y = 0; tile.w = tile_width; tile.h = tile_height;
	SDL_Rect location; location.x = 0; location.y = 0; location.w = tile_x; location.h = tile_y;

	// Map drawing, left to right, top to bottom
	//printf("Frmame\n");
	for (int y = 0; y < map.y_size; y++)
	{
		for (int x = 0; x < map.x_size; x++)
		{
			// Pick the tile
			unsigned char current_id = map.tile_id[y * map.x_size + x];
			tile.x = current_id % num_columns * tile_width;
			tile.y = (int)floor(current_id / num_columns) * tile_width;

			// Draw tile to the renderer
			SDL_RenderCopy(renderer, texture, &tile, &location);

			// Move right to the next spot on the screen
			location.x += location.w;
		}

		// Move down and left
		location.x = 0;
		location.y += location.h;
	}

	SDL_DestroyTexture(texture);

}

void draw_player(struct player p, int size, SDL_Renderer* renderer)
{
	// Draws the player on the screen based 
	// upon its internal px and py.

	SDL_Texture* ptexture = IMG_LoadTexture(renderer, "./assets/player.png");

	// Location in the tilemap to use, location on the screen to draw tile
	SDL_Rect ptile; ptile.x = p.frame * 32; ptile.y = p.rotation * 32; ptile.w = 32; ptile.h = 32;
	SDL_Rect pdest; pdest.x = p.px; pdest.y = p.py; pdest.w = size; pdest.h = size;

	// Draw player to renderer
	SDL_RenderCopy(renderer, ptexture, &ptile, &pdest);

	SDL_DestroyTexture(ptexture);

	return;
}**/