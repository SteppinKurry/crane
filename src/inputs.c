#include "inputs.h"

void check_inputs(int* active_inputs, SDL_Event* event)
{

	// Gives the states (up or down) of relevant keys. The 
	// states are stored in an array, the array gets updated 
	// with the key states.

	while (SDL_PollEvent(event))
	{

		switch (event->type)
		{
			case SDL_QUIT:
				active_inputs[0] = 1;
				return;

			// Sets states to 'not pressed'
			case SDL_KEYUP:
				if (event->key.keysym.sym == SDLK_w) { active_inputs[1] = 0;}
				if (event->key.keysym.sym == SDLK_s) { active_inputs[2] = 0;}
				if (event->key.keysym.sym == SDLK_a) { active_inputs[3] = 0;}
				if (event->key.keysym.sym == SDLK_d) { active_inputs[4] = 0;}
				if (event->key.keysym.sym == SDLK_SPACE) { active_inputs[5] = 0;}
				if (event->key.keysym.sym == SDLK_RIGHT) { active_inputs[6] = 0;}
				if (event->key.keysym.sym == SDLK_LEFT) { active_inputs[7] = 0;}

				break;

			// Sets states to 'pressed'
			case SDL_KEYDOWN:
				if (event->key.keysym.sym == SDLK_q) { active_inputs[0] = 1; return;}
				
				if (event->key.keysym.sym == SDLK_w) { active_inputs[1] = 1;}
				if (event->key.keysym.sym == SDLK_s) { active_inputs[2] = 1;}
				if (event->key.keysym.sym == SDLK_a) { active_inputs[3] = 1;}
				if (event->key.keysym.sym == SDLK_d) { active_inputs[4] = 1;}
				if (event->key.keysym.sym == SDLK_SPACE) { active_inputs[5] = 1;}
				if (event->key.keysym.sym == SDLK_RIGHT) { active_inputs[6] = 1;}
				if (event->key.keysym.sym == SDLK_LEFT) { active_inputs[7] = 1;}

				break;

		}
	}
}
