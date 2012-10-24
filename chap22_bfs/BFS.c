#include <stdio.h> 
#include <stdlib.h> 
#include <memory.h> 

#define MAXSIZE 100 

enum COLOR {WHITE, GRAY, BLACK}; 

typedef struct info_of_node {
    
    enum COLOR color;
    int parent; 
    int depth; 

}INFO_OF_NODE[MAXSIZE];

typedef struct node{ 
    int data; 
    struct node* next; 
}*NODE;

typedef NODE ADJACENT_LIST[MAXSIZE]; 

void print_path(int start, int v, INFO_OF_NODE info) 
{
    if(v == start) 
        printf("%d", v); 
    else {
        print_path(start, info[v].parent, info); 
        printf("-->%d", v); 
    }
}

void BFS(int start, ADJACENT_LIST graph, int vertex_num)
{
    INFO_OF_NODE info; 
    int queue[MAXSIZE]; 
    int head = 0, tail = 1; 
    
    memset(queue, 0, sizeof(queue)); 
    queue[0] = start; 
    
    info[start].color = GRAY;
    info[start].parent = -1;
    info[start].depth = 0;

    int i; 
    for(i = 1; i <= vertex_num; ++i) 
        if(i != start) {
            info[i].color = WHITE; 
            info[i].depth = -1;
            info[i].parent = -1; 
        }

    while(head != tail) {
        int u = queue[head++]; 
        
        NODE iter = graph[u]; 
        int adjacency = iter->data; 
        
        while(adjacency != -1) {
            if(info[adjacency].color == WHITE) {
            
                info[adjacency].color = GRAY; 
                info[adjacency].parent = u; 
                info[adjacency].depth = info[u].depth+1; 
                queue[tail++] = adjacency; 
            }

            iter = iter->next; 
            adjacency = iter->data; 
        }

    }
    
    // print BFS tree. 

    int max_depth = -1; 
    for(i = 1; i <= vertex_num; ++i) {
        if(info[i].depth > max_depth) 
            max_depth = info[i].depth; 
    }

    i = 0; 
    int j; 
    while(i <= max_depth) {
        for(j = 1; j <= vertex_num; ++j) 
            if(info[j].depth == i) printf("%d ", j); 
        printf("\n"); 
        i++;
    }

    print_path(start, 8, info); 
}

int main() 
{
    FILE* fp = fopen("BFS.txt", "r"); 

    int vertex_num; 
    ADJACENT_LIST graph;  

    fscanf(fp, "%d\n", &vertex_num); 

    int tmp; 
    int i; 
    for(i = 1; i <= vertex_num; ++i) {

        fscanf(fp, "%d", &tmp); 
        graph[i] = (NODE)malloc(sizeof(struct node)); 
        NODE node_p = graph[i]; 
        node_p->data = tmp; 
        node_p->next = NULL; 

        while(tmp != -1) {
           
            fscanf(fp, "%d", &tmp); 
            node_p->next = (NODE)malloc(sizeof(struct node)); 
            node_p = node_p->next; 
            node_p->data = tmp; 
            node_p->next = NULL; 
        }
    }

    fclose(fp); 

    int start = 3; 
    
    freopen("BFS.out", "w", stdout); 

    BFS(start, graph, vertex_num); 

    return 0; 
}

