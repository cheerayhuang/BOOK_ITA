#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 

#define MAXSIZE 100

typedef enum colors {
    
    WHITE, 
    GRAY, 
    BLACK

}COLORS;

typedef struct info_of_node {
    
    COLORS color; 
    int parent; 
    int path_len; 

}INFO_OF_NODE[MAXSIZE];

typedef int MARTRIX[MAXSIZE][MAXSIZE];

typedef struct link_list {

    struct link_list* next;
    int data; 

}*LINK_LIST;


void init_node_info(INFO_OF_NODE info, int len, int src) 
{
    int i; 

    for(i = 0; i < len; ++i) {
        
        info[i].color = WHITE; 
        info[i].parent = src; 
        info[i].path_len = LONG_MAX; 
    }

    info[src].path_len = 0; 

}

void dfs_visit(int i, MARTRIX weight, INFO_OF_NODE info, int len, LINK_LIST head) 
{
    int j; 

    for(j = 0; j < len; ++j) {
        if(weight[i][j] != 0 && info[j].color == WHITE) {
            info[j].color = GRAY; 
            dfs_visit(j, weight, info, len, head); 
        }
    }

    LINK_LIST tmp = (LINK_LIST)malloc(sizeof(struct link_list)); 
    tmp->data = i; 
    tmp->next = head->next; 
    head->next = tmp; 
}

LINK_LIST dfs_topology_sort(MARTRIX weight, int len) 
{

    INFO_OF_NODE info; 

    init_node_info(info, len, 0);

    int i, time; 

    LINK_LIST head = (LINK_LIST)malloc(sizeof(struct link_list)); 
    head->next = NULL; 

    for(i = 0; i < len; ++i) { 
        if(info[i].color == WHITE) {
            info[i].color = GRAY; 
            dfs_visit(i, weight, info, len, head);

        }

    }

    return head; 

}

void relax_edge(int u, int v, INFO_OF_NODE info, MARTRIX weight) 
{
    int tmp = info[u].path_len + weight[u][v]; 
    if(info[v].path_len > tmp) {
        info[v].path_len = tmp; 
        info[v].parent = u; 
    }
}

void print_shortest_path(INFO_OF_NODE info, int i, int src) 
{
    if(info[i].parent != src) {

        print_shortest_path(info, info[i].parent, src); 
        printf("-->%d", i); 
    }
    else 
        printf("%d-->%d", src, i); 

}

void dag_shortest_path(LINK_LIST head, MARTRIX weight, int len, int src) 
{
    INFO_OF_NODE info; 

    init_node_info(info, len, src); 

    LINK_LIST tmp = head->next;

    while(tmp->data != src) tmp = tmp->next; 

    while(tmp->next != NULL) {
     
        int i; 
        for(i = 0; i < len; ++i) {
            if(weight[tmp->data][i] != 0) {
                relax_edge(tmp->data, i, info, weight); 
            }
        }
        
        tmp = tmp->next; 
        
    }

    int i; 
    for(i = 0; i < len; ++i) {
        
        print_shortest_path(info, i, src); 

        if(info[i].path_len == LONG_MAX) 
            printf(" can't reach.\n"); 
        else 
            printf(" weight of path = %d\n", info[i].path_len);
    }
}

int main() 
{
    MARTRIX weight; 

    FILE *fp = fopen("dag_s_p.txt", "r"); 

    int len; 
    fscanf(fp, "%d\n", &len); 

    int i, j;

    for(i = 0; i < len; ++i) 
        for(j = 0; j < len; ++j) 
            fscanf(fp, "%d", &weight[i][j]); 

    fclose(fp); 

    LINK_LIST head;     
    head = dfs_topology_sort(weight, len); 

    /*while(head->next != NULL) {
        head = head->next; 
        printf("%d ", head->data); 
    }*/ 

    printf("src = 0:\n"); 
    dag_shortest_path(head, weight, len, 0);

    printf("src = 1:\n"); 
    dag_shortest_path(head, weight, len, 1);

    printf("src = 5:\n"); 
    dag_shortest_path(head, weight, len, 5);

    printf("src = 4:\n"); 
    dag_shortest_path(head, weight, len, 4);

    return 0; 
}

