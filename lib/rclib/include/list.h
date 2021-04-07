#ifndef _LIST_H_
#define _LIST_H_

#include <rtypes.h>

typedef struct _List List;

struct _List{
    void *This;
    List *prev;
    List *next;
};


void add_list_node(List *head, List *node);
void remove_list_node(List *node); 



#endif