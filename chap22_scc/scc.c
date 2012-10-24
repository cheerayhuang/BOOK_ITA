#include <stdio.h> 
#include <stdlib.h> 
#include <memory.h> 

#define MAXSIZE 100 

enum COLOR {WHITE, GRAY, BLACK}; 

typedef struct info_of_node {
    
    enum COLOR color;
    int parent; 
    //int depth; 
    int finish_time, detect_time; 

}INFO_OF_NODE[MAXSIZE];

typedef struct node{ 
    int data; 
    struct node* next; 
}*NODE;

typedef NODE ADJACENT_LIST[MAXSIZE]; 

typedef struct topology_result {
    int vertex; 
    struct topology_resut* next; 

}*TOPOLOGY_RESULT;

TOPOLOGY_RESULT result;

void DFS_visit(int i, INFO_OF_NODE info, ADJACENT_LIST graph, int *time)

{
    NODE node_p = graph[i]->next; 

    int u = node_p->data; 

    while(u != -1) {
    
        if(info[u].color == WHITE) {
            info[u].color = GRAY; 
            info[u].detect_time = ++(*time); 
            info[u].parent = i; 

            printf("-->%d", u);     
        
            DFS_visit(u, info, graph, time); 

            printf("==back==>%d", i); 
        }
        else if(info[u].color == GRAY) {
            printf("--B-->%d %d", u, i); 
        }
        else if(info[u].detect_time < info[i].detect_time) {
            printf("--C-->%d %d", u, i);         
        }
        else {
            printf("--F-->%d %d", u, i); 
        }
        node_p = node_p->next; 
        u = node_p->data; 
        
    }

    info[i].color = BLACK; 
    info[i].finish_time = ++(*time);
    TOPOLOGY_RESULT t = (TOPOLOGY_RESULT)malloc(sizeof(struct topology_result));

    t->vertex = i; 
    t->next = result;
    result = t; 
}

void DFS(ADJACENT_LIST graph, int vertex_num)
{
    INFO_OF_NODE info; 
    int i; 


    for(i = 1; i <= vertex_num; ++i) {
        info[i].color = WHITE; 
        info[i].finish_time=info[i].detect_time = 0; 
        info[i].parent = -1;
    }

    int time = 0; 
    for(i = 1; i <= vertex_num; ++i) {
        if(info[i].color == WHITE) {
            printf("%d", i);
            info[i].detect_time = ++time; 
            info[i].color = GRAY; 
            DFS_visit(i, info, graph, &time); 
            printf("\n"); 
        }

        // change to a new line to print another dfs tree..
    }
    
    // print detect/finish time.
    printf("\ntime seal:\n");
    for(i = 1; i <= vertex_num; ++i) {
        printf("%d: %d/%d\n", i, info[i].detect_time, info[i].finish_time); 

    }

    // topology sort. 

    printf("\ntopology sort:\n"); 
    TOPOLOGY_RESULT t = result; 
    while(t != NULL) {
        printf("%d ", t->vertex); 
        t = t->next; 
    }

    printf("\n");
    // strongly connected component
    
    printf("\nstrongly connected component:\n"); 
    ADJACENT_LIST graph2; 

    NODE tmp = (NODE)malloc(sizeof(struct node)); 
    tmp->data = -1; 
    tmp->next = NULL; 

    for(i = 1; i <= vertex_num; ++i) {
        graph2[i] = (NODE)malloc(sizeof(struct node)); 
        graph2[i]->next = tmp ;
    }

    for(i = 1; i <= vertex_num; ++i) {
        
        NODE node_p = graph[i]->next; 
        while(node_p->data != -1) {
            NODE node2_p = (NODE)malloc(sizeof(struct node)); 
            node2_p->data = i; 
            node2_p->next = graph2[node_p->data]->next; 
            graph2[node_p->data]->next = node2_p; 
            node_p = node_p->next; 

        }
    }
    
    for(i = 1; i <= vertex_num; ++i) {
        info[i].color = WHITE; 
        info[i].finish_time=info[i].detect_time = 0; 
        info[i].parent = -1;
    }
   
    t = result; 
    time = 0; 
    while(t != NULL) {
        
        if(info[t->vertex].color == WHITE) {
            info[t->vertex].color = GRAY; 
            info[t->vertex].detect_time = ++time;
            printf("%d", t->vertex); 
            DFS_visit(t->vertex, info, graph2, &time); 

            printf("\n"); 
        }
        t = t->next; 
    }

    
}

int main() 
{
    FILE* fp = fopen("SCC.txt", "r"); 

    int vertex_num; 
    ADJACENT_LIST graph;  

    fscanf(fp, "%d\n", &vertex_num); 

    int tmp; 
    int i; 
    for(i = 1; i <= vertex_num; ++i) {

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

    freopen("SCC.out", "w", stdout); 
    result = NULL; 

    DFS(graph, vertex_num); 

    return 0; 
}

