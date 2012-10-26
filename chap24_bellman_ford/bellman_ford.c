#include <stdio.h> 
#include <stdlib.h> 
#include <memory.h> 
#include <limits.h> 

#define MAXSIZE 100 

typedef struct info_of_node {
    
    int parent; 
    int path_len; 

}INFO_OF_NODE[MAXSIZE];

typedef struct node{ 
    int data; 
    struct node* next; 
}*NODE;

typedef NODE ADJACENT_LIST[MAXSIZE]; 

void init_node_info(INFO_OF_NODE info, int vertex_num) 
{
    int i;

    for(i = 0; i < vertex_num; ++i) {
        info[i].parent = -1; 
        info[i].path_len = LONG_MAX; 
    }
      
    info[0].path_len = 0; 
    
}

void relax_edge(INFO_OF_NODE info, int u, int v, int weight[][MAXSIZE]) 
{
    if(weight[u][v] != 0 && info[u].path_len + weight[u][v] < info[v].path_len) {
        info[v].path_len = info[u].path_len+weight[u][v]; 
        info[v].parent = u; 
    }
}

void print_shortest_path(INFO_OF_NODE info, int vertex) 
{
    int i; 

    if(info[vertex].parent != 0) 
        print_shortest_path(info, info[vertex].parent); 

    
    printf("%d-->", vertex); 

}

int bellman_ford(ADJACENT_LIST graph, int weight[][MAXSIZE], int vertex_num) 
{
    int i, j; 

    INFO_OF_NODE info; 

    init_node_info(info, vertex_num); 

    for(i = 0; i < vertex_num-1; ++i) {
        
        // iterate edges in graph
        for(j = 0; j < vertex_num; ++j) {
           
            if(info[j].path_len == LONG_MAX) continue; 

            NODE h = graph[j]->next; 

            while(h->data != -1) {
                relax_edge(info, j, h->data, weight);     
                h = h->next; 
            }
        
        }
    }

    
    for(i = 0; i < vertex_num; ++i) {
        
        if(info[i].path_len == LONG_MAX) continue; 

        NODE h = graph[i]->next; 

        while(h->data != -1) {
            if(info[j].path_len + weight[j][h->data] < info[h->data].path_len) 
                return 0; 
            h = h->next; 
        }
    }

    // Print 
    for(i = 1; i < vertex_num; ++i) {
        print_shortest_path(info, i);
        printf("\n"); 
        //printf("\b\b\b\n"); 
    }

    return 1; 
}

int main() 
{
    FILE* fp = fopen("bellman_ford.txt", "r"); 

    int vertex_num; 
    ADJACENT_LIST graph;  

    int weight[MAXSIZE][MAXSIZE]; 

    fscanf(fp, "%d\n", &vertex_num); 

    int tmp; 
    int i, j; 
    for(i = 0; i < vertex_num; ++i)
        for(j = 0; j < vertex_num; ++j) 
            fscanf(fp, "%d", &weight[i][j]);  

    for(i = 0; i < vertex_num; ++i) {

        graph[i] = (NODE)malloc(sizeof(struct node)); 
        graph[i]->next = NULL; 
        
        NODE node_p, h = graph[i]; 

        do {
           
            fscanf(fp, "%d", &tmp); 
            node_p = (NODE)malloc(sizeof(struct node)); 
            node_p->data = tmp; 
            node_p->next = NULL;

            h->next = node_p; 
            h = h->next; 

        }while(tmp != -1); 
    }

    fclose(fp); 

    if(!bellman_ford(graph, weight, vertex_num)) {
        printf("find a negtive weight circle in graph!\n"); 
    }

    return 0; 
}

