#include <stdio.h>
#include <stdlib.h>

typedef struct  s_node
{
    int     **grid;
    float   f_score;
    float   g_score;
    int     id;
}               t_node;

t_node  *create_node(int **grid, float f_score, float g_score, int id)
{
    t_node  *new;

    new = malloc(sizeof(t_node));
    new->grid = grid;
    new->f_score = f_score;
    new->g_score = g_score;
    new->id = id;
    return (new);
}

int *find_empty_cell(int grid[3][3])
{
	int *pos;

	pos = malloc(sizeof(int) * 2);
    for (pos[0] = 0; pos[0] < 3; pos[0]++)
        for (pos[1] = 0; pos[1] < 3; pos[1]++)
            if (grid[pos[0]][pos[1]] == 0)
                return (pos);
    return (NULL);
}

void	print_grid(int **grid, int size)
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
			printf("%d ", grid[y][x]);
		printf("\n");
	}
}

int	main(void)
{
	int	**grid;

	grid = (int**)malloc(sizeof(int*) * 3);
	for (int i = 0; i < 3; i++)
		grid[i] = (int*)malloc(sizeof(int) * 3);
	grid[0][0] = 1;
	grid[0][1] = 2;
	grid[0][2] = 3;
	grid[1][0] = 8;
	grid[1][1] = 0;
	grid[1][2] = 4;
	grid[2][0] = 7;
	grid[2][1] = 6;
	grid[2][2] = 5;
	print_grid(grid, 3);

    t_node  *new;

    new = create_node(grid, 5, 4, 0);
    printf("%d\n", new->grid[1][2]);
}
