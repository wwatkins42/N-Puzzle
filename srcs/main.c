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
	int 	i;

	env.opt = get_opt(&argv[1], OPT_STRING);
	if (have_opt('h', env.opt))
		env.opt_heuristic = get_opt_number(&argv[1], 'h');
	else
		env.opt_heuristic = MANHATTAN | MISSPLACE | LINEAR_C;
	i = 0;
	while (++i < argc)
		if (argv[i][0] != '-' && argv[i - 1][0] != '-')
			break ;
	printf("%s\n", argv[i] );
	initialize(&env, argv[i], argc);
    path = astar(&env, env.start, env.goal);
    list_print_content(&path, env.size);
    env.stats.pathList_length = list_size(&path) - 1; // Don't count the first state.
    printf("     moves: %d\n", env.stats.pathList_length);
    printf("   maximum: %d\n", env.stats.openList_states_maximum);
    printf("complexity: %d\n", env.stats.openList_states_complexity);
    return (0);
}
