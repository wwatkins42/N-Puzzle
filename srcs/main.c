#include "astar.h"

int				get_opt_number(char **av, char c)
{
	int		i;

	i = -1;
	while (av[++i])
		if (av[i][0] == '-' && av[i][1] == c && av[i][2] == '\0')
			return (ft_atoi(av[i + 1]));
	return (-1);
}

static int		add_opt(int pos, int opt)
{
	int		tmp;

	if (pos == -1)
	{
		write(1, "ERROR : Illegal option.\n", 24);
		exit(0);
	}
	tmp = 1;
	tmp = tmp << pos;
	opt = opt | tmp;
	return (opt);
}

static int		position_in_opt(char *opt, char o)
{
	int		i;

	i = -1;
	while (opt[++i])
	{
		if (o == opt[i])
			return (i);
	}
	return (-1);
}

int				have_opt(char o, int opt)
{
	int tmp;
	int i;

	tmp = 1;
	i = position_in_opt(OPT_STRING, o);
	tmp = tmp << i;
	if (tmp & opt)
		return (1);
	return (0);
}

static int				get_opt(char **av, char *l_opt)
{
	int		opt;
	int		i;
	int		j;

	i = -1;
	opt = 0;
	while (av[++i])
	{
		j = 0;
		if (av[i][0] == '-' && av[i][1] != '\0' && !ft_isdigit(av[i][1]))
		{
			while (av[i][++j])
				opt = add_opt(position_in_opt(l_opt, av[i][j]), opt);
		}
	}
	return (opt);
}

void    initialize(t_env *env, char *filename, int argc)
{
    if (argc < 2 || !filename)
        generate_random_puzzle(env);
    else if (!parse_file(env, filename))
    {
        printf("Puzzle is incorrect or unsolvable.\n");
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
	int 	i;
    int     length;

	env.opt = get_opt(&argv[1], OPT_STRING);
	if (have_opt('h', env.opt))
		env.opt_heuristic = get_opt_number(&argv[1], 'h');
	else
		env.opt_heuristic = MANHATTAN | MISSPLACE | LINEAR_C;
	i = 0;
	while (++i < argc)
		if (argv[i][0] != '-' && argv[i - 1][0] != '-')
			break ;
	initialize(&env, argv[i], argc);
    path = astar(&env, env.start, env.goal);
    length = list_size(&path);
    env.stats.pathList_length = (length > 0 ? length - 1 : length);
    print_output(&env, &path);
    return (0);
}
