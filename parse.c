#include "astar.h"

char    *get_cmd_line(char *cmd, char *arg)
{
    char    *new;

    new = malloc(strlen(cmd) + strlen(arg));
    new = strcpy(new, cmd);
    new = strncat(new, arg, strlen(arg));
    return (new);
}

int     **grid_from_str(char *str, char sep, int n)
{
    int     **grid;
    char    **split;

    split = ft_strsplit(str, sep);
    grid = (int**)malloc(sizeof(int*) * n);
    for (int y = 0; y < n; y++)
    {
        grid[y] = (int*)malloc(sizeof(int) * n);
        for (int x = 0; x < n; x++)
        {
            grid[y][x] = ft_atoi(split[y * n + x]);
            ft_strdel(&split[y * n + x]);
        }
    }
    ft_strdel(split);
    return (grid);
}

int     parse_file(t_env *env, char *filename)
{
    FILE    *fp;
    char    *line;
    char    *cmd;

    env->size = 0;
    cmd = get_cmd_line("ruby parse.rb ", filename);
    fp = popen(cmd, "r");
    fscanf(fp, "%d", &env->size);
    if (env->size == 0)
        return (0);
    env->n = env->size * env->size + ((env->size + 1) % 2);
    line = malloc(sizeof(char) * (env->n * 16));
    fscanf(fp, "%s", line);
    pclose(fp);
    env->start = grid_from_str(line, ',', env->size);
    ft_strdel(&line);
    ft_strdel(&cmd);
    return (1);
}

int     generate_solution(t_env *env)
{
    FILE    *fp;
    char    *line;
    char    *cmd;
    char    *siz;

    siz = ft_itoa(env->size);
    cmd  = get_cmd_line("ruby generate_solution.rb ", siz);
    fp = popen(cmd, "r");
    line = malloc(sizeof(char) * (env->n * 16));
    fscanf(fp, "%s", line);
    pclose(fp);
    env->goal = grid_from_str(line, ',', env->size);
    ft_strdel(&line);
    ft_strdel(&cmd);
    ft_strdel(&siz);
    return (1);
}
