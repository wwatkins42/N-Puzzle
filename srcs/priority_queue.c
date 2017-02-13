#include "astar.h"

t_heap      *heap_new(void)
{
    t_heap  *heap;

    heap = (t_heap*)calloc(1, sizeof(t_heap));
    heap->n = 0;
    heap->alloc = 4;
    heap->nodes = (t_node*)malloc(sizeof(t_node) * heap->alloc);
    return (heap);
}

void        heap_push(t_heap *heap, t_node *node)
{
    int s, f;

    if (heap->n >= heap->alloc)
    {
        heap->alloc *= 2;
        heap->nodes = (t_node*)realloc(heap->nodes, heap->alloc * sizeof(t_node));
    }
    heap->n++;
    s = heap->n - 1;
    f = (s - 1) / 2;
    while (s > 0 && node->f_score < heap->nodes[f].f_score)
    {
        heap->nodes[s] = heap->nodes[f];
        s = f;
        f = (s - 1) / 2;
    }
    heap->nodes[s] = *node;
}

void    heap_pop(t_heap *heap)
{
    int f = 0;
    int s1 = 1;
    int s2 = 2;
    int size;

    while (s1 <= heap->n - 1)
    {
        if (s2 > heap->n - 1 || heap->nodes[s1].f_score < heap->nodes[s2].f_score)
        {
            heap->nodes[f] = heap->nodes[s1];
            f = s1;
        }
        else
        {
            heap->nodes[f] = heap->nodes[s2];
            f = s2;
        }
        s1 = 2 * f + 1;
        s2 = 2 * f + 2;
    }
    size = heap->n;
    for (int current = f + 1; current != size; current++)
    {
        heap->n = current - 1;
        heap_push(heap, &heap->nodes[current]);
    }
    heap->n = size - 1;
    if (heap->n < heap->alloc / 2 && heap->n >= 4)
    {
        heap->alloc /= 2;
        heap->nodes = realloc(heap->nodes, sizeof(t_heap) * heap->alloc);
    }
}

int     heap_contains(t_heap *heap, t_node *node, int gsize)
{
    for (int i = 0; i < heap->n; i++)
        if (compare_grids(gsize, heap->nodes[i].grid, node->grid))
            return (1);
    return (0);
}

t_node  *heap_get_node_by_id(t_heap *heap, int id)
{
    for (int i = 0; i < heap->n; i++)
        if (heap->nodes[i].id == id)
            return (&heap->nodes[i]);
    return (NULL);
}
