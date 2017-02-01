#include "astar.h"

void    initialize(t_env *env, char *filename)
{
    if (!parse_file(env, filename))
        exit(0);
    generate_solution(env);
}

int main(int argc, char **argv)
{
    t_env   env;
    int     **goal;
    int     **start;
    t_list  *path;

    if (argc < 2)
        return (0); // CREATE ALT START
    initialize(&env, argv[1]);
    path = astar(&env, env.start, env.goal);
    list_print_content(&path, env.size);
    return (0);
}
