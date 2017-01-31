#include "astar.h"

void    initialize_env(t_env *env)
{
    env->size = 3;
    // env->size = 4;
    env->n = env->size * env->size;
}

int main(void)
{
    t_env   env;
    int     **goal;
    int     **start;
    t_list  *path;

    initialize_env(&env);

    goal = (int**)malloc(sizeof(int*) * env.size);
    start = (int**)malloc(sizeof(int*) * env.size);
    for (int i = 0; i < env.size; i++)
    {
        goal[i] = (int*)malloc(sizeof(int) * env.size);
        start[i] = (int*)malloc(sizeof(int) * env.size);
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

    // goal[0][0] = 1;
    // goal[0][1] = 2;
    // goal[0][2] = 3;
    // goal[0][3] = 4;
    // goal[1][0] = 12;
    // goal[1][1] = 13;
    // goal[1][2] = 14;
    // goal[1][3] = 5;
    // goal[2][0] = 11;
    // goal[2][1] = 0;
    // goal[2][2] = 15;
    // goal[2][3] = 6;
    // goal[3][0] = 10;
    // goal[3][1] = 9;
    // goal[3][2] = 8;
    // goal[3][3] = 7;
    //
    // start[0][0] = 1;
    // start[0][1] = 2;
    // start[0][2] = 3;
    // start[0][3] = 4;
    // start[1][0] = 12;
    // start[1][1] = 13;
    // start[1][2] = 14;
    // start[1][3] = 5;
    // start[2][0] = 11;
    // start[2][1] = 15;
    // start[2][2] = 0;
    // start[2][3] = 6;
    // start[3][0] = 10;
    // start[3][1] = 9;
    // start[3][2] = 8;
    // start[3][3] = 7;

    path = astar(&env, start, goal);
    list_print_content(&path);
    return (0);
}
