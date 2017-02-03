#include "astar.h"

void    create_pairs(t_pairs *pairs, int **goal, int size, int sum)
{
    int j = 0;

    if (pairs->x != -1)
    {
        pairs->p = malloc(sizeof(t_pos) * (sum));
        for (int y = 0; y < size - 1; y++)
            for (int i = y + 1; i < size; i++)
            {
                pairs->p[j].v[0] = goal[y][pairs->x];
                pairs->p[j].v[1] = goal[i][pairs->x];
                j++;
            }
    }
    else if (pairs->y != -1)
    {
        pairs->p = malloc(sizeof(t_pos) * (sum));
        for (int x = 0; x < size - 1; x++)
            for (int i = x + 1; i < size; i++)
            {
                pairs->p[j].v[0] = goal[pairs->y][x];
                pairs->p[j].v[1] = goal[pairs->y][i];
                j++;
            }
    }
}

void    generate_pairs(t_env *env)
{
    int     sum;
    t_pairs *pairs;

    sum = (int)(env->size * (float)((env->size - 1) * 0.5));
    pairs = malloc(sizeof(t_pairs) * (env->size * 2));
    for (int i = 0; i < env->size * 2; i++)
    {
        pairs[i].x = -1;
        pairs[i].y = -1;
        if (i < env->size)
            pairs[i].x = i;
        else
            pairs[i].y = i - env->size;
        create_pairs(&pairs[i], env->goal, env->size, sum);
        for (int c = 0; c < sum; c++)
            printf("(%d, %d)\n", pairs[i].p[c].v[0], pairs[i].p[c].v[1]);
    }
    // env->pairs = ;
    exit(0);
}

void    initialize(t_env *env, char *filename)
{
    if (!parse_file(env, filename))
        exit(0);
    generate_solution(env);
    generate_pairs(env);
}

int main(int argc, char **argv)
{
    t_env   env;
    t_list  *path;

    if (argc < 2)
        return (0); // CREATE ALT START
    initialize(&env, argv[1]);
    path = astar(&env, env.start, env.goal);
    list_print_content(&path, env.size);
    return (0);
}
