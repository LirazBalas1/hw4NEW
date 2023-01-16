#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

pnode graph = NULL;
int weight = 0;

void delete_list(pdijk list)
{
    pdijk curr_n = list;
    while (curr_n != NULL)
    {
        list = list->next;
        free(curr_n);
        curr_n = list;
    }
}

pdijk build_dijkstra_graph(pnode h_node, int data)
{
    pdijk head = NULL;
    pdijk current = NULL;
    while (h_node != NULL)
    {
        pdijk new_node = (pdijk)malloc(sizeof(dijk));
        if (new_node == NULL)
        {
            delete_list(head);
            return NULL;
        }
        new_node->node = h_node;
        new_node->prev = h_node->node_num == data ? new_node : NULL;
        new_node->weight = h_node->node_num == data ? 0 : INF;
        new_node->iNside = 0;
        new_node->next = NULL;
        if (head == NULL)
        {
            head = new_node;
        }
        if (current != NULL)
        {
            current->next = new_node;
        }
        current = new_node;
        h_node = h_node->next;
    }
    return head;
}

pdijk getD_node(int x, pdijk list)
{
    pdijk result = NULL;
    while (list != NULL)
    {
        if (list->node->node_num == x)
        {
            result = list;
            break;
        }
        list = list->next;
    }
    return result;
}

pdijk find_min(pdijk head)
{
    pdijk result = NULL;
    while (head != NULL)
    {
        if (!head->iNside && head->weight < INF && (result == NULL || result->weight < head->weight))
        {
            result = head;
        }
        head = head->next;
    }
    if (result != NULL)
    {
        result->iNside = 1;
    }
    return result;
}

int shortsPath_cmd(pnode head, int src, int dest)
{
    {
        pdijk list = build_dijkstra_graph(head, src);
        if (list == NULL)
        {
            return -1;
        }
        pdijk node_min = find_min(list);
        while (node_min != NULL)
        {
            pedge build_edge = node_min->node->edges;
            while (build_edge != NULL)
            {
                pdijk node_dijk = getD_node(build_edge->dest->node_num, list);
                int dist = node_min->weight + build_edge->weight;
                if (node_dijk->weight > dist)
                {
                    node_dijk->weight = dist;
                    node_dijk->prev = node_min;
                }
                build_edge = build_edge->next;
            }
            node_min = find_min(list);
        }
        int result = getD_node(dest, list)->weight;
        delete_list(list);
        return result == INF ? -1 : result;
    }
}

void calculate_distance(int *arr, int len)
{
    int curr_d = 0;
    for (int i = 0; i < len - 1; ++i)
    {
        int dist = shortsPath_cmd(graph, arr[i], arr[i + 1]);
        if (dist == -1)
        {
            curr_d = INF;
            return;
        }
        curr_d += dist;
    }
    if (curr_d < weight)
    {
        weight = curr_d;
    }
}

void generate_permutations(int i, int *arr, int len)
{
    if (i == len - 1)
    {
        calculate_distance(arr, len);
        return;
    }
    for (int j = i; j < len; ++j)
    {
        swap(arr, i, j);
        generate_permutations(i + 1, arr, len);
        swap(arr, i, j);
    }
}
int TSP_cmd(pnode head)
{
    graph = head;
    weight = INF;
    int n = 0;
    pnode node = head;
    while (node != NULL)
    {
        node = node->next;
        n++;
    }
    if (n == 0)
    {
        return INF;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        return INF;
    }
    node = head;
    int i = 0;
    while (node != NULL)
    {
        arr[i] = node->node_num;
        node = node->next;
        i++;
    }
    generate_permutations(0, arr, n);
    free(arr);
    int result = weight;
    weight = INF;
    return result;
}
