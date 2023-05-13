#include <stdio.h>

#include <win-graph.h>
#include <inputs.h>
#include <physics.h>

#define WINDOW_X 900 // 180
#define WINDOW_Y 500 // 100

int main(int argc, char *argv[])
{

	// Main graphics container
	struct graphics crap;
	graphics_init(&crap, WINDOW_X, WINDOW_Y);
		
	float scroll_speed = 0.2f;
	
	// Player box struct
	SDL_Rect pbox;
	pbox.w = 25; pbox.h = 50;
	pbox.x = (WINDOW_X / 2) - pbox.w; pbox.y = (WINDOW_Y - 25) - pbox.h;

	struct xyf p_pos; // Precise location of player
	p_pos.x = 50.f;
	p_pos.y = 50.f;

	struct xyf playerv; // Player velocity

	char grounded = 0;



	// MAP
	int map[100][180];

	// Map generation (should be replaced ASAP)
	for (int y = 0; y < 100; y++)
	{
		for (int x = 0; x < 180; x++)
		{
			map[y][x] = 0;

			if (y == 0 || y == 99)
			{
				map[y][x] = 1;
			}
			else if (x == 0 || x == 179)
			{
				map[y][x] = 1;
			}
			else if (y == 80 && x < 40)
			{
				map[y][x] = 1;
			}

		}

	}


	// These numbers store relevant inputs
	int input_store[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	while (crap.window != NULL)	// Part of the map drawn to the screen
	{

		// Draw background color	
		SDL_SetRenderDrawColor(crap.renderer, 255, 75, 150, 100);
		SDL_RenderClear(crap.renderer);		

		// Draws the map
		draw_map(map, crap.renderer);


		// Draw player box
		SDL_SetRenderDrawColor(crap.renderer, 0, 255, 0, 100);
		SDL_RenderFillRect(crap.renderer, &pbox);

		// Get keyboard inputs
		check_inputs(input_store, &crap.event);

		// Do something with inputs
		if (input_store[0] == 1)
		{
			crap.window = NULL;
			//crap_quit(&crap);
		}

		playerv.x = 0;

		// Define gravity constant
		float gravity_constant = 0.0002f;

		// Movement
		if (input_store[5] == 1 && grounded) // Jump
		{
			playerv.y = -0.3;
		}
		else if (input_store[2] == 1) // Fast fall
		{
			playerv.y = gravity_constant * 9999;
		}
		if (input_store[3] == 1) // Left
		{
			playerv.x -= scroll_speed;
		}
		else if (input_store[4] == 1) // Right
		{
			playerv.x += scroll_speed;
		}
		
		// Apply gravity
		
		playerv.y += gravity_constant;


		// Physics calcs
		
		// Convert player's precise location to the 
		// player's position in the map matrix
		int pvm_x = (int) (p_pos.x + playerv.x) / 5; 
		int pvm_y = (int) (p_pos.y + playerv.y + pbox.h) / 5;

		// Add all phys rects to an array to make checking easier
		struct phys_rect* hit_boxes[4];

		// This box has v
		struct phys_rect ppbox;
		ppbox.x1 = pbox.x + playerv.x; ppbox.x2 = pbox.x + pbox.w + playerv.x;
		ppbox.y1 = pbox.y + playerv.y; ppbox.y2 = pbox.y + pbox.h + playerv.y;

		struct phys_rect ppbox_project;
		ppbox_project.x1 = ppbox.x1 + playerv.x; ppbox_project.x2 = ppbox.x2 + playerv.x;
		ppbox_project.y1 = ppbox.y1 + playerv.y; ppbox_project.y2 = ppbox.y2 + playerv.y;

		struct phys_rect ground;
		ground.x1 = 0; ground.x2 = 900;
		ground.y1 = 495; ground.y2 = 600;
		hit_boxes[0] = &ground;

		struct phys_rect lwall;
		lwall.x1 = 0; lwall.x2 = 4;
		lwall.y1 = 0; lwall.y2 = 600;
		hit_boxes[1] = &lwall;

		struct phys_rect rwall;
		rwall.x1 = 896; rwall.x2 = 900;
		rwall.y1 = 0; rwall.y2 = 600;
		hit_boxes[2] = &rwall;
		
		struct phys_rect pform;
		pform.x1 = 0; pform.x2 = 200;
		pform.y1 = 400; pform.y2 = 394;
		hit_boxes[3] = &pform;		

		if (check_collision_two_dim(ppbox, ground) || check_collision_two_dim(ppbox, pform))
		{
			grounded = 1;
			playerv.y = 0;
		}
		else
		{
			//printf("this is happenenning\n");
			p_pos.y += playerv.y;
			grounded = 0;
		}

		if (check_collision_two_dim(ppbox, lwall) || check_collision_two_dim(ppbox, rwall))// || check_collision_two_dim(ppbox, pform))
		{
			//printf("Collisison\n");
		}
		else
		{
			p_pos.x += playerv.x;
		}

		/*
		// Check x axis collision
		if (map[(int)p_pos.y / 5][pvm_x] != 0)
		{
			// Pretty much just do nothing
		}
		else 
		{
			p_pos.x += playerv.x;
		}

		// Check y axis collision
		if (map[pvm_y][(int)p_pos.x / 5] != 0)
		{
			grounded = 1;
		}

		else
		{
			p_pos.y += playerv.y;
			grounded = 0;

		}*/



		pbox.x = (int) p_pos.x;
		pbox.y = (int) p_pos.y;



		// Draw to screen
		SDL_RenderPresent(crap.renderer);

	}

	return 0;
}