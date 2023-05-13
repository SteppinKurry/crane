#include "physics.h"

/**
struct xyf final_move(int x, int y, float velx, float vely)
{
	// Given a position, velocity, and a collision map (2d array), this determines 
	// how far an object should move (in pixels)

	struct xyf move;
	//move.x = (int) velx;
	//move.y = (int) vely;

	return move;

}
**/

int check_collision_one_dim(int first_x1, int first_x2, int second_x1, int second_x2)
{
	//
	return (first_x1 <= second_x2) && (second_x1 <= first_x2);
}

int check_collision_two_dim(struct phys_rect first, struct phys_rect second)
{
	int x_collision = check_collision_one_dim(first.x1, first.x2, second.x1, second.x2);
	int y_collision = check_collision_one_dim(first.y1, first.y2, second.y1, second.y2);
	return x_collision && y_collision;
}