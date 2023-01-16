#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/*The function starts by initializing a pointer to the head of the list, named "currentnode", and assigns it to the value of the pointer passed in as an argument.
The function then enters a while loop that continues until currentnode is equal to NULL. Inside the while loop, the function initializes a pointer to the edges of the current node, named "currentedges" and assigns it to the value of the edges field of the current node.
Then, the function enters another while loop that continues until currentedges is equal to NULL. Inside this while loop, the function creates a temporary pointer to an edge, named "temp", and assigns it to the value of currentedges. It then updates currentedges to the next edge in the list.
The function then calls the free() function on the temporary edge pointer, which releases the memory allocated for that edge.
Once all the edges of the current node have been freed, the function creates a temporary pointer to a node, named "temp" and assigns it the value of currentnode. It then updates currentnode to the next node in the list. The function then calls the free() function on the temporary node pointer, which releases the memory allocated for that node.
Finally, it sets head pointer to NULL to indicate that graph is deleted successfully.
*/
void deleteGraph_cmd(pnode *head)
{
    if (*head == NULL)
    {
        return;
    }
    pnode currentnode = *head;
    while (currentnode != NULL)
    {
        pedge currentedges = currentnode->edges;
        while (currentedges != NULL)
        {
            pedge temp = currentedges;
            currentedges = currentedges->next;
            if (temp)
                free(temp);
        }
        pnode temp = currentnode;
        currentnode = currentnode->next;
        if (temp)
            free(temp);
    }
    *head = NULL;
}
void build_graph_cmd(pnode *head)
{
    if (head == NULL)
    {
        return;
    }
    deleteGraph_cmd(head);
    int size = 0;
    if (scanf("%d", &size) != 1)
    {
        return;
    }
    char c = 'C';
    scanf("%c", &c);
    for (int i = 0; i < size; ++i)
    {
        scanf("%c", &c);
        insert_node_cmd(head);
    }
}
/*The function takes in two arguments: a pointer to the head of the graph, which is represented by a linked list of nodes and an integer value, "data".
The function starts by initializing a pointer to a node, named "temp" and assigns it to the value of the pointer passed in as an argument.
Then the function enters a while loop that continues until the temp pointer is equal to NULL. Inside the while loop,
 the function checks if the value of node_num field of the current node is equal to the value of data passed as an argument. If it is true, the function returns the current node.
Otherwise, the function updates temp pointer to the next node in the list.
If the while loop completes and temp pointer is NULL, the function returns NULL
, indicating that no node with the specified value was found in the graph.
This function allows to check if a node with specific data already exists in the graph or not. It will return the node if it exists otherwise return NULL.
*/
pnode check(pnode *head, int data)
{
    if (head == NULL)
    {
        return NULL;
    }
    pnode temp = *head;
    while (temp != NULL)
    {
        if (temp->node_num == data)
        {
            return temp;
        }

        temp = temp->next;
    }
    return NULL;
}

void insert_node_cmd(pnode *head)
{
    int data = -1;
    if (scanf("%d", &data) != 1)
    {
        return;
    }
    pnode node_c = check(head, data);
    if (node_c == NULL)
    {
        node_c = (pnode)calloc(1, sizeof(node));
        if (node_c == NULL)
        {
            return;
        }
        node_c->node_num = data;
        node_c->next = *head;
        node_c->edges = NULL;
        *head = node_c;
    }
    else
    {
        pedge edge_r = node_c->edges;
        while (edge_r != NULL)
        {
            pedge temp = edge_r->next;
            free(edge_r);
            edge_r = temp;
        }
        node_c->edges = NULL;
    }

    pedge *insert_edge = &(node_c->edges);
    int dest = -1;
    int weight = -1;
    while (scanf("%d %d", &dest, &weight) == 2)
    {
        pnode new_node = check(head, dest);
        if (new_node == NULL)
        {
            new_node = (pnode)calloc(1, sizeof(node));
            if (new_node == NULL)
            {
                return;
            }
            new_node->node_num = dest;
            new_node->edges = NULL;
            new_node->next = *head;
            *head = new_node;
        }
        *insert_edge = (pedge)calloc(1, sizeof(edge));
        if (*insert_edge == NULL)
        {
            return;
        }
        (*insert_edge)->weight = weight;
        (*insert_edge)->dest = new_node;
        (*insert_edge)->next = NULL;
        insert_edge = &((*insert_edge)->next);
    }
}
void delete_node_cmd(pnode *head)
{
    int data;
    scanf("%d", &data);
    pnode temp = *head;
    if ((*head)->node_num == data)
    {
        pnode temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    while (temp != NULL)
    {
        if (temp->edges != NULL && temp->edges->dest->node_num == data)
        {
            pedge edge_to_remove = temp->edges;
            temp->edges = temp->edges->next;
            free(edge_to_remove);
        }
        temp = temp->next;
    }
    pnode temp2 = *head;
    pnode next = *head;
    next = temp2->next;
    while (next)
    {
        if (next->node_num == data)
        {
            temp2->next = next->next;
            free(next);
            next = temp2->next;
        }
        else
        {
            temp2 = next;
            next = temp2->next;
        }
    }
}
void printGraph_cmd(pnode head)
{
    pnode n = head;
    while (n != NULL)
    {
        printf("Node %d: ", n->node_num);
        pedge e = n->edges;
        while (e != NULL)
        {
            printf("D= %d: W= %d, ", e->dest->node_num, e->weight);
            e = e->next;
        }
        printf("\n");
        n = n->next;
    }
}
