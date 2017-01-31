#include "astar.h"

t_list  *list_new(t_node *node)
{
    t_list  *new;

    new = malloc(sizeof(t_list));
    new->node = *node;
    new->next = NULL;
    return (new);
}

void    list_push_head(t_list **head, t_node *node)
{
    t_list *new;

    new = malloc(sizeof(t_list));
    new->node = *node;
    new->next = *head;
    *head = new;
}

void    list_push_tail(t_list **head, t_node *node)
{
    t_list  *current;

    current = *head;
    while (current->next)
        current = current->next;
    current->next = malloc(sizeof(t_list));
    current->next->node = *node;
    current->next->next = NULL;
}

void    list_pop_head(t_list **head)
{
    t_list *next;

    if (*head == NULL)
        return ;
    next = NULL;
    next = (*head)->next;
    free(*head);
    *head = next;
}

void    list_pop_tail(t_list **head)
{
    t_list *current;

    if ((*head)->next == NULL)
    {
        free(*head);
        return ;
    }
    current = *head;
    while (current->next->next)
        current = current->next;
    free(current->next);
    current->next = NULL;
}

void    list_pop_node(t_list **head, t_node *node)
{
    t_list  *current;
    t_list  *tmp;

    if (compare_nodes(&(*head)->node, node))
    {
        list_pop_head(head);
        return ;
    }
    current = *head;
    tmp = NULL;
    while (current)
    {
        if (compare_nodes(&current->next->node, node))
        {
            tmp = current->next;
            current->next = tmp->next;
            free(tmp);
            return ;
        }
        current = current->next;
    }
}

int     list_contains(t_list **head, t_node *node)
{
    t_list  *current;

    current = *head;
    while (current)
    {
        if (compare_nodes(&current->node, node))
            return (1);
        current = current->next;
    }
    return (0);
}

t_node  *list_get_id(t_list **head, int id)
{
    t_list  *current;

    current = *head;
    while (current)
    {
        if (current->node.id == id)
            return (&current->node);
        current = current->next;
    }
    return (NULL);
}

t_node  *list_get_min(t_list **head)
{
    t_list  *current;
    t_node  *node;
    float   min;

    min = MAXINT;
    current = *head;
    while (current)
    {
        if (current->node.f_score < min)
        {
            min = current->node.f_score;
            node = &current->node;
        }
        current = current->next;
    }
    return (node);
}

void    list_print_content(t_list **head)
{
    t_list  *current;
    int     i;

    i = 0;
    current = *head;
    while (current)
    {
        printf("\nList(%i):\n node.g_score: %.3f\n node.f_score: %.3f\n", i,
            current->node.g_score, current->node.f_score);
        printf(" node.move: %d\n node.id: %d\n node.pid: %d\n",
            current->node.move, current->node.id, current->node.prev_id);
        print_grid(current->node.grid, 5);
        current = current->next;
        i++;
    }
}
