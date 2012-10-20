#include <stdio.h> 
#include <stdlib.h> 

typedef struct LinkNode{
    int data;
    struct LinkNode* next, *previous; 

}*LINKNODE;


LINKNODE insert(LINKNODE head_p, int i)
{
    LINKNODE new_node_p = (LINKNODE)malloc(sizeof(struct LinkNode)); 
    new_node_p->data = i; 

    LINKNODE tmp = head_p->next; 

    tmp->previous = new_node_p; 
    new_node_p->previous = head_p; 

    head_p->next = new_node_p; 
    new_node_p->next = tmp; 

    return head_p; 

}


int empty(LINKNODE head_p)
{
    return (head_p->next == head_p && head_p->previous == head_p); 
}

int main() 
{
    LINKNODE head = (LINKNODE)malloc(sizeof(struct LinkNode)); 
    head->next =  head; 
    head->previous = head; 
   
    int i; 
    for(i = 0; i < 10; ++i) 
        insert(head, i); 

    LINKNODE iter = head; 

    while(iter->previous != head) {
        iter = iter->previous; 
        printf("%d ", iter->data); 
    }

    printf("\n"); 

    iter = head; 
    while(iter->next != head) {
        iter = iter->next; 
        printf("%d ", iter->data); 
    }
    printf("\n"); 
    
    iter->next = NULL; 

    iter = head; 
    while(iter->next != NULL) {
        LINKNODE tmp = iter->next; 
        printf("free %d\n", iter->data); 
        free(iter); 
        iter = tmp; 
    }

    printf("free %d\n", iter->data); 
    free(iter); 

    return 0; 
}

