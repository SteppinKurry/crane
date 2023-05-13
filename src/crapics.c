#include "crapics.h"

int crap_init(crapics* app, int width, int height)
{

	app->window = NULL;
	app->screen_surface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 3;
	}

	//Create window
	app->window = SDL_CreateWindow("SDLol", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_RENDERER_PRESENTVSYNC);

	SDL_Delay(500); // So that the OS and window manager have time to resolve conflicts


	if (app->window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 3;
	}

	//Get window surface
	app->screen_surface = SDL_GetWindowSurface(app->window);
	app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
	if (app->renderer == NULL)
	{
		printf("Megafuck\n");
	}

	return 0;
}

void crap_quit(crapics* app)
{
	SDL_FreeSurface(app->screen_surface);
	SDL_DestroyWindow(app->window);
	app->window = NULL;

	SDL_Quit();
	return;
}

void crap_update(crapics* app)
{

	while (SDL_PollEvent(&app->event))
	{
		switch (app->event.type)
		{
			case SDL_QUIT:
				app->window = NULL;
				crap_quit(app);
		}
	}
	SDL_UpdateWindowSurface(app->window);
}

void draw_squares(crapics* crap, float x, float y, int height, int width, int shade)
{
	SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    if (shade)
    {
    	SDL_SetRenderDrawColor(crap->renderer, 0, 255, 0, 10);
    }
    else
    {
    	SDL_SetRenderDrawColor(crap->renderer, 255, 0, 0, 255);
    }
	SDL_RenderDrawRect(crap->renderer, &rect);
	SDL_RenderFillRect(crap->renderer, &rect);

}
