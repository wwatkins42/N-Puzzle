#include "astar.h"

void    initialize(t_env *env, char *filename, int argc)
{
    if (argc < 2)
        generate_random_puzzle(env);
    else if (!parse_file(env, filename))
        exit(0);
    generate_solution(env);
	env->sum = (int)(env->size * (float)((env->size - 1) * 0.5));
    env->pairs = generate_pairs(env, env->goal);
	linear_conflict(env, env->start);
}

int     main(int argc, char **argv)
{
    t_env   env;
    t_list  *path;

    initialize(&env, argv[1], argc);
    path = astar(&env, env.start, env.goal);
    list_print_content(&path, env.size);
    return (0);
}
