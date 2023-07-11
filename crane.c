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
		
	float ground_speed = 0.2f;
	float air_speed = 0.05f;
	
	// Player box struct
	SDL_Rect pbox;
	pbox.w = 25; pbox.h = 50;
	pbox.x = (WINDOW_X / 2) - pbox.w; pbox.y = (WINDOW_Y - 25) - pbox.h;

	struct xyf p_pos; // Precise location of player
	p_pos.x = 50.f;
	p_pos.y = 50.f;

	struct xyf playerv; // Player velocity

	char grounded = 0;
	char wall_jumpable = 0;

	int count = 0;

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
		}

		playerv.x = 0;

		// Define gravity constant
		float gravity_constant = 0.0002f; // 0.0002f

		// Movement
		if (input_store[5] == 1) // Jump
		{	
			// regular jump
			if (grounded == 1) { playerv.y = -0.3; pbox.y -= 2; }

			// wall jump
			else if (wall_jumpable == 1)
			{
				playerv.y = -0.2;
				
				if (input_store[3] == 1) { playerv.x += 100; }
				else { playerv.x -= 100; }
				//printf("wall jump\n");
			}

		}
		else if (input_store[2] == 1) // Fast fall
		{
			playerv.y = gravity_constant * 999;
		}
		if (input_store[3] == 1) // Left
		{
			if (grounded == 1) { playerv.x -= ground_speed; }
			else { playerv.x -= air_speed; }
		}
		else if (input_store[4] == 1) // Right
		{
			if (grounded == 1) { playerv.x += ground_speed; }
			else { playerv.x += air_speed; }

		}
		
		// Apply gravity
		playerv.y += gravity_constant;

		// Physics calcs
		

		// Add all phys rects to an array to make checking easier
		struct phys_rect* hit_boxes[4];

		// This box has velocity
		struct phys_rect ppbox;
		ppbox.x1 = pbox.x + playerv.x; ppbox.x2 = pbox.x + pbox.w + playerv.x;
		ppbox.y1 = pbox.y + playerv.y; ppbox.y2 = pbox.y + pbox.h + playerv.y;

		// Changes to ppbox in the x direction
		struct phys_rect ppbox_x;
		ppbox_x.x1 = pbox.x + playerv.x; ppbox_x.x2 = pbox.x + pbox.w + playerv.x;
		ppbox_x.y1= pbox.y; ppbox_x.y2 = pbox.y + pbox.h;

		// Changes to ppbox in the y direction
		struct phys_rect ppbox_y;
		ppbox_y.x1 = pbox.x; ppbox.x2 = pbox.x + pbox.w;
		ppbox_y.y1 = pbox.y + playerv.y; ppbox_y.y2 = pbox.y + pbox.h + playerv.y + 2;

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

		grounded = 0;
		wall_jumpable = 0;

		// Check collisions in the x direction
		if (check_collision_two_dim(ppbox_x, ground) || check_collision_two_dim(ppbox_x, pform))
		{
			playerv.x = 0;
		}

		if (check_collision_two_dim(ppbox_x, lwall) || check_collision_two_dim(ppbox_x, rwall))
		{
			playerv.x = 0;
			wall_jumpable = 1;
		}

		// Check collisions in the y direction
		if (check_collision_two_dim(ppbox_y, ground))
		{
			grounded = 1;
			playerv.y = 0;
			p_pos.y = ground.y1 - (pbox.h + 1);
		}

		if (check_collision_two_dim(ppbox_y, pform))
		{
			playerv.y = 0;

			// hit the platform from above
			if (ppbox_y.y1 < pform.y2) 
			{
				p_pos.y = pform.y2 - (pbox.h - 5); 
				grounded = 1;
			}

			// hit the platform from below
			else if (ppbox_y.y2 > pform.y1) 
			{
				p_pos.y = pform.y1 + 3; 
			}
			
		}
		
		//printf("%d: grounded?: %d\n", count, grounded);


		p_pos.x += playerv.x;
		p_pos.y += playerv.y;

		pbox.x = (int) p_pos.x;
		pbox.y = (int) p_pos.y;

		// Draw to screen
		SDL_RenderPresent(crap.renderer);

		count += 1;

	}

	return 0;
}