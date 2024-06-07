#include "binary_trees.h"
#include <stdlib.h>

/**
 * queue_node_s - Queue node structure
 * @node: Binary tree node
 * @next: Pointer to the next queue node
 */
typedef struct queue_node_s
{
    const binary_tree_t *node;
    struct queue_node_s *next;
} queue_node_t;

/**
 * enqueue - Adds a node to the queue
 * @queue: Double pointer to the head of the queue
 * @node: Binary tree node to add
 */
void enqueue(queue_node_t **queue, const binary_tree_t *node)
{
    queue_node_t *new_node = malloc(sizeof(queue_node_t));
    queue_node_t *tmp;

    if (!new_node)
        return;

    new_node->node = node;
    new_node->next = NULL;

    if (*queue == NULL)
    {
        *queue = new_node;
    }
    else
    {
        tmp = *queue;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
    }
}

/**
 * dequeue - Removes a node from the queue
 * @queue: Double pointer to the head of the queue
 *
 * Return: Pointer to the binary tree node that was removed
 */
const binary_tree_t *dequeue(queue_node_t **queue)
{
    queue_node_t *tmp;
    const binary_tree_t *node;

    if (*queue == NULL)
        return (NULL);

    tmp = *queue;
    node = tmp->node;
    *queue = (*queue)->next;
    free(tmp);
    return (node);
}

/**
 * binary_tree_levelorder - Goes through a binary tree using level-order traversal
 * @tree: Pointer to the root node of the tree to traverse
 * @func: Pointer to a function to call for each node
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
    queue_node_t *queue = NULL;
    const binary_tree_t *current;

    if (tree == NULL || func == NULL)
        return;

    enqueue(&queue, tree);

    while ((current = dequeue(&queue)) != NULL)
    {
        func(current->n);

        if (current->left)
            enqueue(&queue, current->left);
        if (current->right)
            enqueue(&queue, current->right);
    }
}
