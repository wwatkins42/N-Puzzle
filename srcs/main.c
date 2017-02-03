#include "astar.h"

void    initialize(t_env *env, char *filename)
{
    if (!parse_file(env, filename))
        exit(0);
    generate_solution(env);
	env->sum = (int)(env->size * (float)((env->size - 1) * 0.5));
    env->pairs = generate_pairs(env, env->goal);
	write(1, "\n\n", 2);
	print_grid(env->start, env->size);
	linear_conflict(env, env->start);
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
