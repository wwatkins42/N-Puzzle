#include "astar.h"

t_node  *get_successor(t_env *env, int **grid, int move, int *id)
{
    t_node  *successor;
    t_pos   pos;
    int     **clone;

    successor = NULL;
    clone = clone_grid(grid, env->size);
    pos = find_cell_pos(grid, 0, env->size);
    if (move == D && pos.y > 0)
    {
        clone[pos.y][pos.x] = grid[pos.y - 1][pos.x];
        clone[pos.y - 1][pos.x] = grid[pos.y][pos.x];
        successor = new_node(clone, 0, MAXINT + 1, D, id);
    }
    else if (move == U && pos.y + 1 < env->size)
    {
        clone[pos.y][pos.x] = grid[pos.y + 1][pos.x];
        clone[pos.y + 1][pos.x] = grid[pos.y][pos.x];
        successor = new_node(clone, 0, MAXINT + 1, U, id);
    }
    else if (move == R && pos.x > 0)
    {
        clone[pos.y][pos.x] = grid[pos.y][pos.x - 1];
        clone[pos.y][pos.x - 1] = grid[pos.y][pos.x];
        successor = new_node(clone, 0, MAXINT + 1, R, id);
    }
    else if (move == L && pos.x + 1 < env->size)
    {
        clone[pos.y][pos.x] = grid[pos.y][pos.x + 1];
        clone[pos.y][pos.x + 1] = grid[pos.y][pos.x];
        successor = new_node(clone, 0, MAXINT + 1, L, id);
    }
    return (successor);
}

t_list  *reconstruct_path(t_heap *heap, t_node *current)
{
    t_list  *path;
    t_node  *tmp;
    t_node  *curr;

    if (heap->n == 0)
        return (NULL);
    path = list_new(current);
    curr = current;
    while (1)
    {
        tmp = heap_get_node_by_id(heap, curr->pid);
        list_push_head(&path, tmp);
        if (curr->pid == 0)
            break;
        curr = tmp;
    }
    return (path);
}

t_list  *astar(t_env *env, int **start, int **goal)
{
    t_heap  *openHeap = NULL;
    t_heap  *closedHeap = NULL;
    t_node  current;
    t_node  *successor = NULL;
    float   t_gScore = 0;

	  float	t_fScore = 0;
    int     openList_size = 0;
    int     id = 0;
	  int 	temp_size;

    openHeap = heap_new();
    closedHeap = heap_new();
    heap_push(openHeap, new_node(start, 0, manhattan(env, start, goal), S, &id));
    while (openHeap)
    {
        current = openHeap->nodes[0];
        if (compare_grids(env->size, current.grid, goal))
          return (reconstruct_path(closedHeap, &current));
        heap_pop(openHeap);
        heap_push(closedHeap, &current);
        for (int move = 1; move < 5; move++)
        {
            if ((successor = get_successor(env, current.grid, move, &id)))
            {
                if (heap_contains(closedHeap, successor, env->size))
                    continue;
                t_gScore = current.g_score + 1.0;
				t_fScore = 0;
                if (!heap_contains(openHeap, successor, env->size))

                {
                    successor->pid = current.id;
                    successor->g_score = t_gScore;

					successor->f_score = 0;
					temp_size = env->size;
					if ((MANHATTAN & env->opt_heuristic) > 1)
						t_fScore += WEIGHT * manhattan(env, successor->grid, goal);
					if ((LINEAR_C & env->opt_heuristic) > 1)
						t_fScore += WEIGHT * linear_conflict(env, successor->grid);
					if ((MISSPLACE & env->opt_heuristic) > 1)
						t_fScore += missplaced_tiles(env, successor->grid);
					successor->f_score = successor->g_score + t_fScore;
            heap_push(openHeap, successor);
                    env->stats.openList_states_complexity++;
                }
            }
        }
        if (env->stats.openList_states_maximum < openHeap->n)
            env->stats.openList_states_maximum = openHeap->n;
    }
    return (NULL);
}
