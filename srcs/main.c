#include "astar.h"

void    initialize(t_env *env, char *filename, int argc)
{
    if (argc < 2)
        generate_random_puzzle(env);
    else if (!parse_file(env, filename))
    {
        printf("Puzzle is unsolvable.\n");
        exit(1);
    }
    generate_solution(env);
	env->sum = (int)(env->size * (float)((env->size - 1) * 0.5));
    env->pairs = generate_pairs(env, env->goal);
	linear_conflict(env, env->start);
    env->stats.openList_states_maximum = 0;
    env->stats.openList_states_complexity = 0;
    env->stats.pathList_length = 0;
}

void    print_output(t_env *env, t_list **head)
{
    t_list  *current;
    int     i, n;

    i = 0;
    current = *head;
    while (current)
    {
        n = current->node.move;
        printf("Path.%i,", i);
        printf(" move: \'%c\'\n", (n == 0?'S':(n == 1?'R':(n == 2?'L':(n == 3?'U':'D')))));
        print_grid(current->node.grid, env->size);
        current = current->next;
        i++;
    }
    printf("A* algorithm search stats:\n");
    printf(" - Path length: %d\n", env->stats.pathList_length);
    printf(" - OpenHeap maximum: %d (size complexity)\n", env->stats.openList_states_maximum);
    printf(" - OpenHeap complexity: %d (time complexity)\n", env->stats.openList_states_complexity);
}

int     main(int argc, char **argv)
{
    t_env   env;
    t_list  *path;
    int     length;

    initialize(&env, argv[1], argc);
    path = astar(&env, env.start, env.goal);
    length = list_size(&path);
    env.stats.pathList_length = (length > 0 ? length - 1 : length);
    print_output(&env, &path);
    return (0);
}
