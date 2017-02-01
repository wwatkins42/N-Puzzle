#include "astar.h"

t_node  *get_successor(t_env *env, int **grid, int move, int *id)
{
    t_node  *successor;
    t_pos   pos;
    int     **clone;

    successor = NULL;
    clone = clone_grid(grid, env->size);
    pos = find_cell_pos(grid, 0, env->size);
    if (move == U && pos.y > 0)
    {
        clone[pos.y][pos.x] = grid[pos.y - 1][pos.x];
        clone[pos.y - 1][pos.x] = grid[pos.y][pos.x];
        successor = new_node(clone, 0, MAXINT + 1, U, id);
    }
    else if (move == D && pos.y + 1 < env->size)
    {
        clone[pos.y][pos.x] = grid[pos.y + 1][pos.x];
        clone[pos.y + 1][pos.x] = grid[pos.y][pos.x];
        successor = new_node(clone, 0, MAXINT + 1, D, id);
    }
    else if (move == R && pos.x > 0)
    {
        clone[pos.y][pos.x] = grid[pos.y][pos.x - 1];
        clone[pos.y][pos.x - 1] = grid[pos.y][pos.x];
        successor = new_node(clone, 0, MAXINT + 1, R, id);
    }
    else if (move == L && pos.x + 1 < env->size)
    {
        clone[pos.y][pos.x] = grid[pos.y][pos.x + 1];
        clone[pos.y][pos.x + 1] = grid[pos.y][pos.x];
        successor = new_node(clone, 0, MAXINT + 1, L, id);
    }
    return (successor);
}

float     manhattan(t_env *env, int **curr, int **goal)
{
    t_pos   c;
    t_pos   g;
    float   dx, dy = 0;

    for (int i = 1; i < env->n; i++)
    {
        c = find_cell_pos(curr, i, env->size);
        g = find_cell_pos(goal, i, env->size);
        dx += abs(c.x - g.x);
        dy += abs(c.y - g.y);
    }
    return (dx + dy);
}

t_list  *reconstruct_path(t_list **head, t_node *current)
{
    t_list  *path;
    t_node  *tmp;
    t_node  *curr;

    path = list_new(current);
    curr = current;
    while (1)
    {
        tmp = list_get_id(head, curr->prev_id);
        list_push_head(&path, tmp);
        if (curr->prev_id == 0)
            break;
        curr = tmp;
    }
    return (path);
}

t_list  *astar(t_env *env, int **start, int **goal)
{
    t_list  *openList;
    t_list  *closedList;
    t_node  *startNode;
    t_node  current;
    t_node  *successor;
    float   t_gScore = 0;
    int     id = 0;

    startNode = new_node(start, 0, manhattan(env, start, goal), S, &id);
    openList = list_new(startNode);
    while (openList)
    {
        current = *list_get_min(&openList);
        if (compare_grids(env, current.grid, goal))
            return (reconstruct_path(&closedList, &current));
        list_pop_node(&openList, &current);
        list_push_head(&closedList, &current);

        print_grid(current.grid, env->size);

        for (int move = 1; move < 5; move++)
        {
            if ((successor = get_successor(env, current.grid, move, &id)))
            {
                if (list_contains(&closedList, successor))
                    continue;
                t_gScore = current.g_score + 1.0;
                if (!list_contains(&openList, successor))
                {
                    successor->prev_id = current.id;
                    successor->g_score = t_gScore;
                    successor->f_score = successor->g_score + 1.0 * manhattan(env, successor->grid, goal);
                    list_push_head(&openList, successor);
                }
            }
        }
    }
    return (NULL);
}
