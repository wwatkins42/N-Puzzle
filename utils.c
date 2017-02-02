#include "astar.h"

int     compare_grids(int size, int **a, int **b)
{
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++)
            if (a[y][x] != b[y][x])
                return (0);
    return (1);
}

int     compare_nodes(t_node *a, t_node *b)
{
    return ((a->id == b->id && a->prev_id == b->prev_id));
}

t_node  *new_node(int **grid, float g_score, float f_score, int move, int *id)
{
    t_node  *new;

    new = malloc(sizeof(t_node));
    new->grid = grid;
    new->g_score = g_score;
    new->f_score = f_score;
    new->move = move;
    new->id = *id;
    new->prev_id = -1;
    *id = *id + 1;
    return (new);
}

t_pos   find_cell_pos(int **grid, int value, int size)
{
    t_pos   pos;

    for (pos.y = 0; pos.y < size; pos.y++)
        for (pos.x = 0; pos.x < size; pos.x++)
            if (grid[pos.y][pos.x] == value)
                return (pos);
    return (pos);
}

int     **clone_grid(int **grid, int size)
{
    int **clone;

    clone = (int**)malloc(sizeof(int*) * size + 1);
    for (int y = 0; y < size; y++)
    {
        clone[y] = (int*)malloc(sizeof(int) * size + 1);
        for (int x = 0; x < size; x++)
            clone[y][x] = grid[y][x];
    }
    return (clone);
}

void	print_grid(int **grid, int size)
{
	for (int y = 0; y < size; y++)
	{
        printf("[");
		for (int x = 0; x < size; x++)
			printf("% 3d", grid[y][x]);
		printf(" ]\n");
	}
    printf("\n");
}
