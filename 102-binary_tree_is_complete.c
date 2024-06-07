#include "binary_trees.h"
#include <stdlib.h>

/**
 * struct queue_node_s - Queue node structure
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
 * binary_tree_is_complete - Checks if a binary tree is complete
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if the tree is complete, otherwise 0
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
    queue_node_t *queue = NULL;
    const binary_tree_t *current;
    int flag = 0;

    if (tree == NULL)
        return (0);

    enqueue(&queue, tree);

    while ((current = dequeue(&queue)) != NULL)
    {
        if (current->left)
        {
            if (flag)
            {
                while (queue != NULL)
                    dequeue(&queue);
                return (0);
            }
            enqueue(&queue, current->left);
        }
        else
        {
            flag = 1;
        }

        if (current->right)
        {
            if (flag)
            {
                while (queue != NULL)
                    dequeue(&queue);
                return (0);
            }
            enqueue(&queue, current->right);
        }
        else
        {
            flag = 1;
        }
    }
    return (1);
}
