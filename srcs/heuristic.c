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

int			compare_pairs(t_env *env, t_pos *cur, t_pos *goal)
{
	int cost = 0;

	for (int i = 0; i < env->sum; i++)
	{
		for (int j = 0; j < env->sum; j++)
		{
			if ((cur[i].v[0] == goal[j].v[0] || cur[i].v[0] == goal[j].v[1]) &&
				(cur[i].v[1] == goal[j].v[0] || cur[i].v[1] == goal[j].v[1]) &&
				(cur[i].v[0] - cur[i].v[1] != goal[j].v[0] - goal[j].v[1]))
				// printf("(%d, %d) (%d, %d)\n", cur[i].v[0], cur[i].v[1], goal[j].v[0], goal[j].v[1]);
				cost += 2;
		}
	}
	return (cost);
}

t_pairs    *generate_pairs(t_env *env, int **cur)
{
    t_pairs *pairs;

    pairs = malloc(sizeof(t_pairs) * (env->size * 2));
    for (int i = 0; i < env->size * 2; i++)
    {
        pairs[i].x = -1;
        pairs[i].y = -1;
        if (i < env->size)
            pairs[i].x = i;
        else
            pairs[i].y = i - env->size;
        create_pairs(&pairs[i], cur, env->size, env->sum);
        // for (int c = 0; c < env->sum; c++)
            // printf("%d %d (%d, %d)\n", pairs[i].x, pairs[i].y, pairs[i].p[c].v[0], pairs[i].p[c].v[1]);
    }
    return (pairs);
}

float     manhattan(t_env *env, int **curr, int **goal)
{
    t_pos   c;
    t_pos   g;
    float   dx = 0;
    float   dy = 0;

    for (int i = 1; i < env->n; i++)
    {
        c = find_cell_pos(curr, i, env->size);
        g = find_cell_pos(goal, i, env->size);
        dx += abs(c.x - g.x);
        dy += abs(c.y - g.y);
    }
    return (dx + dy);
}

float       linear_conflict(t_env *env, int **cur)
{
    int cost = 0;
	t_pairs *pairs = NULL;

	pairs = generate_pairs(env, cur);
	for (int i = 0; i < env->size * 2; i++)
	{
		cost += compare_pairs(env, pairs[i].p, env->pairs[i].p);
	}
    return (cost);
}
