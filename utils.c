#include "astar.h"

int     compare_grids(t_env *env, int **a, int **b)
{
    for (int y = 0; y < env->size; y++)
        for (int x = 0; x < env->size; x++)
            if (a[y][x] != b[y][x])
                return (0);
    return (1);
}

int     compare_nodes(t_node *a, t_node *b)
{
    if (a->g_score == b->g_score && a->move == b->move &&
        a->f_score == b->f_score && a->id == b->id)
        return (1);
    return (0);
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
    *id = *id + 1;
    return (new);
}

t_pos   find_cell_pos(int **grid, int value)
{
    t_pos   pos;

    for (pos.y = 0; pos.y < 3; pos.y++) // TMP
        for (pos.x = 0; pos.x < 3; pos.x++)
            if (grid[pos.y][pos.x] == value)
                return (pos);
    return (pos);
}

int     **clone_grid(int **grid, int size)
{
    int **clone;

    clone = (int**)malloc(sizeof(int*) * size);
    for (int y = 0; y < size; y++)
    {
        clone[y] = (int*)malloc(sizeof(int) * size);
        for (int x = 0; x < size; x++)
            clone[y][x] = grid[y][x];
    }
    return (clone);
}
