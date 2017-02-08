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
    env->stats.openList_states_maximum = 0;
    env->stats.openList_states_complexity = 0;
    env->stats.pathList_length = 0;
}

int     main(int argc, char **argv)
{
    t_env   env;
    t_list  *path;

    initialize(&env, argv[1], argc);
    path = astar(&env, env.start, env.goal);
    list_print_content(&path, env.size);
    env.stats.pathList_length = list_size(&path) - 1; // Don't count the first state.
    printf("     moves: %d\n", env.stats.pathList_length);
    printf("   maximum: %d\n", env.stats.openList_states_maximum);
    printf("complexity: %d\n", env.stats.openList_states_complexity);
    return (0);
}
