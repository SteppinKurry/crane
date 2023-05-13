#ifndef PHYS
#define PHYS

struct xyf
{
	float x;
	float y;
};

struct phys_rect
{
	int x1;
	int x2;
	int y1;
	int y2;
};

struct xyf final_move(int x, int y, float velx, float vely);

int check_collision_one_dim(int first_x1, int first_x2, int second_x1, int second_x2);
int check_collision_two_dim(struct phys_rect first, struct phys_rect second);

#endif
