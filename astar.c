#include "astar.h"

t_node  *get_successor(t_env *env, int **grid, int move, int *id)
{
    t_node  *successor;
    t_pos   pos;
    int     **clone;

    move++;
    successor = NULL;
    clone = clone_grid(grid, env->size);
    pos = find_cell_pos(grid, 0);
    if (move == U && pos.y > 0)
    {
        clone[pos.y][pos.x] = grid[pos.y - 1][pos.x];
        clone[pos.y - 1][pos.x] = grid[pos.y][pos.x];
        successor = new_node(clone, 0, 0, U, id);
    }
    else if (move == D && pos.y + 1 < env->size)
    {
        clone[pos.y][pos.x] = grid[pos.y + 1][pos.x];
        clone[pos.y + 1][pos.x] = grid[pos.y][pos.x];
        successor = new_node(clone, 0, 0, D, id);
    }
    else if (move == R && pos.x > 0)
    {
        clone[pos.y][pos.x] = grid[pos.y][pos.x - 1];
        clone[pos.y][pos.x - 1] = grid[pos.y][pos.x];
        successor = new_node(clone, 0, 0, R, id);
    }
    else if (move == L && pos.x + 1 < env->size)
    {
        clone[pos.y][pos.x] = grid[pos.y][pos.x + 1];
        clone[pos.y][pos.x + 1] = grid[pos.y][pos.x];
        successor = new_node(clone, 0, 0, L, id);
    }
    return (successor);
}

int manhattan(t_env *env, int **curr, int **goal)
{
    t_pos   c;
    t_pos   g;
    int score;

    score = 0;
    for (int i = 1; i < env->n; i++)
    {
        c = find_cell_pos(curr, i);
        g = find_cell_pos(goal, i);
        score += abs(g.x - c.x) + abs(g.y - c.y);
    }
    return (score);
}

int astar(t_env *env, int **start, int **goal)
{
    t_list  *openList;
    t_list  *closedList;
    t_node  *startNode;
    t_node  *current;
    t_node  *successor;
    int     id = 0;
    int     t_gScore = 0;

    startNode = new_node(start, 0, manhattan(env, start, goal), S, &id);
    list_push_head(&openList, startNode);
    while (openList)
    {
        current = list_get_min(&openList); // Current is a "t_node"

        if (compare_grids(env, current->grid, goal))
        {
            return (1); // TMP
        }
        list_pop_node(&openList, current);
        list_push_head(&closedList, current);

        for (int move = 0; move < 4; move++)
        {
            successor = get_successor(env, current->grid, move, &id);
            if (successor)
            {
                if (list_contains(&closedList, successor))
                    continue;
                t_gScore = current->g_score + 1;
                if (!list_contains(&openList, successor))
                {
                    successor->g_score = t_gScore;
                    successor->f_score = successor->g_score + manhattan(env, successor->grid, goal);
                    list_push_head(&openList, successor);
                    // list_print_content(&openList);
                }
            }
        }
    }
    return (0);
}

void    initialize_env(t_env *env)
{
    env->size = 3;
    env->n = env->size * env->size - 1;
}

int main(void)
{
    t_env   env;

    int **goal;
    int **start;
    goal = (int**)malloc(sizeof(int*) * 3);
    start = (int**)malloc(sizeof(int*) * 3);
    for (int i = 0; i < 3; i++)
    {
        goal[i] = (int*)malloc(sizeof(int) * 3);
        start[i] = (int*)malloc(sizeof(int) * 3);
    }
    goal[0][0] = 1;
    goal[0][1] = 2;
    goal[0][2] = 3;
    goal[1][0] = 8;
    goal[1][1] = 0;
    goal[1][2] = 4;
    goal[2][0] = 7;
    goal[2][1] = 6;
    goal[2][2] = 5;

    start[0][0] = 1;
    start[0][1] = 4;
    start[0][2] = 5;
    start[1][0] = 8;
    start[1][1] = 0;
    start[1][2] = 3;
    start[2][0] = 7;
    start[2][1] = 2;
    start[2][2] = 6;

    initialize_env(&env);
    astar(&env, start, goal);
    return (0);
}

// int main(void)
// {
//     t_list  *openList;
//     t_node  n[4];
//
//     n[0] = new_node(NULL, 5, 10, 'R', NULL);
//     n[1] = new_node(NULL, 1, 2, 'L', &n[0]);
//     n[2] = new_node(NULL, 8, 3, 'D', &n[1]);
//     n[3] = new_node(NULL, 666, 42, 'U', &n[2]);
//     openList = list_new(&n[0]);
//
//     list_push_head(&openList, &n[1]);
//     list_push_head(&openList, &n[2]);
//
//     list_print_content(&openList);
//
//     list_pop_tail(&openList);
//     list_push_tail(&openList, &n[3]);
//
//     printf("------------------------\n");
//     list_print_content(&openList);
//
//     list_pop_node(&openList, &n[3]);
//
//     printf("------------------------\n");
//     list_print_content(&openList);
//
//     while (openList)
//     {
//         printf("OK");
//         list_pop_tail(&openList);
//     }
//     list_print_content(&openList);
//
//     return (0);
// }
