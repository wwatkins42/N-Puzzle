#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include "libft.h"

#define S 0
#define R 1
#define L 2
#define U 3
#define D 4
#define MAXINT 10e6

typedef struct  s_node
{
    int     **grid;
    float   f_score;
    float   g_score;
    int     move;
    int     id;
    int     prev_id;
}               t_node;

typedef struct  s_list
{
    t_node          node;
    struct s_list   *next;
}               t_list;

typedef struct  s_pos
{
    union {
        struct {
            int x;
            int y;
        };
        int v[2];
    };
}               t_pos;

// typedef struct  s_pos
// {
//     int x;
//     int y;
// }               t_pos;

typedef struct  s_pairs
{
    int x;
    int y;
    t_pos *p;
}               t_pairs;

typedef struct  s_env
{
    int     size;
    int     n;
    int     **start;
    int     **goal;
    t_pairs *pairs;
}               t_env;

/*
**  list.c
*/
t_list  *list_new(t_node *node);
void    list_push_head(t_list **head, t_node *node);
void    list_push_tail(t_list **head, t_node *node);
void    list_pop_head(t_list **head);
void    list_pop_tail(t_list **head);
void    list_pop_node(t_list **head, t_node *node);
int     list_contains(int size, t_list **head, t_node *node);
void    list_print_content(t_list **head, int size);
t_node  *list_get_id(t_list **head, int id);
t_node  *list_get_min(t_list **head);

/*
**  utils.c
*/
int     compare_grids(int size, int **a, int **b);
int     compare_nodes(t_node *a, t_node *b);
t_node  *new_node(int **grid, float g_score, float f_score, int move, int *id);
t_pos   find_cell_pos(int **grid, int value, int size);
int     **clone_grid(int **grid, int size);
void	print_grid(int **grid, int size);

/*
**  astar.c
*/
t_list  *astar(t_env *env, int **start, int **goal);
t_list  *reconstruct_path(t_list **head, t_node *current);
t_node  *get_successor(t_env *env, int **grid, int move, int *id);
float   manhattan(t_env *env, int **curr, int **goal);
void    initialize_env(t_env *env);

/*
**  parse.h
*/
char    *get_cmd_line(char *cmd, char *arg);
int     parse_file(t_env *env, char *filename);
int     generate_solution(t_env *env);
