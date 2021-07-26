#include <rclib/list.h>


//Memory allocation and de-allocation is done by the caller.

static List* GetLastListMem(List *head)
{
    List *list_ptr = head;
    while(list_ptr->next != NULL)
        list_ptr = list_ptr->next;
    return list_ptr;
}


void add_list_node(List *head, List *node)
{
    List *last_list_mem = GetLastListMem(head);
    last_list_mem->next = node;
    node->next = NULL;
    node->prev = last_list_mem;
}

void remove_list_node(List *node)
{
    List *prev_node= node->prev;
    List *next_node = node->next;

    if(prev_node == NULL)
    {
        next_node->prev = NULL;
    }        
    else if(next_node == NULL)
    {
        prev_node->next = NULL;
    }   
    else
    {
        prev_node->next = next_node;
        next_node->prev = prev_node;
    }

}