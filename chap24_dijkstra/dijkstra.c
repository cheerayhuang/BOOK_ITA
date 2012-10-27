#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <memory.h> 

#define MAXSIZE 100

#define L_CHILD(x) (2*(x)+1) 
#define R_CHILD(x) (2*(x)+2) 

typedef enum {
    WHITE, 
    BLACK
} COLOR; 

typedef struct info_of_node {

    COLOR color; 
    int parent; 
    int path_len;

    // the position in heap 
    int heap_pos; 

}INFO_OF_NODE[MAXSIZE]; 

// a priority queue, using heap.
typedef int HEAP[MAXSIZE]; 

typedef int WEIGHT[MAXSIZE][MAXSIZE];

void init_node_info(INFO_OF_NODE info, int len, int src) 
{
    int i; 

    for(i = 0; i < len; ++i) {
        info[i].color = WHITE; 
        info[i].parent = src; 
        info[i].path_len = LONG_MAX;
    }

    info[src].color = BLACK;
    info[src].path_len = 0; 
}

void keep_heap_property(HEAP heap, INFO_OF_NODE info, int p, int rear)
{
    int pos = p; 

    if(L_CHILD(p) < rear && 
       info[heap[L_CHILD(p)]].path_len < info[heap[pos]].path_len) {
    
        pos = L_CHILD(p); 
    }

    if(R_CHILD(p) < rear && 
       info[heap[R_CHILD(p)]].path_len < info[heap[pos]].path_len) {
        
        pos = R_CHILD(p); 

    }

    if(pos != p) {
        
        int tmp = heap[p]; 
        heap[p] = heap[pos]; 
        heap[pos] = tmp; 

        keep_heap_property(heap, info, pos, rear); 
    
    }

    info[heap[p]].heap_pos = p; 
    

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

void build_min_heap(HEAP heap, INFO_OF_NODE info, int rear) 
{
    int last_parent = (rear-1)%2 == 0 ? rear/2-1 : rear/2; 

    int i; 

    for(i = last_parent; i >= 0; --i) {
        keep_heap_property(heap, info, i, rear); 
    }
}

void decrease_heap_node(HEAP heap, INFO_OF_NODE info, int heap_pos) 
{
    if(heap_pos == 0) 
        return ;

    int x = info[heap[heap_pos]].path_len; 
    int parent_pos = heap_pos % 2 == 0 ? heap_pos / 2 - 1 : heap_pos / 2;
    int y = info[heap[parent_pos]].path_len; 

    while(x < y) {
        
        int tmp = heap[heap_pos]; 
        heap[heap_pos] = heap[parent_pos]; 
        heap[parent_pos] = tmp; 

        info[heap[heap_pos]].heap_pos = heap_pos; 
        info[heap[parent_pos]].heap_pos = parent_pos; 

        heap_pos = parent_pos; 
        parent_pos = heap_pos % 2 == 0 ? heap_pos / 2 - 1 : heap_pos / 2;

        x = y; 
        y = info[heap[parent_pos]].path_len; 
    }
}

void relax_edge(int u, int v, HEAP heap, INFO_OF_NODE info, WEIGHT weight) 
{
    int tmp = info[u].path_len + weight[u][v]; 

    if(info[v].path_len > tmp) {
    
        info[v].path_len = tmp; 
        info[v].parent = u;

        decrease_heap_node(heap, info, info[v].heap_pos); 
    }
}

void dijkstra(WEIGHT weight, int len, int src) 
{
    INFO_OF_NODE info; 

    init_node_info(info, len, src); 

    HEAP heap; 

    int i; 
    for(i = 0; i < len; ++i) 
        heap[i] = i; 

    build_min_heap(heap, info, len);
    
    int rear = len; 

    while(rear > 0) {

        int q = heap[0]; 
        info[q].color = BLACK; 

        int i; 
        for(i = 0; i < len; ++i) {
            
            //cause dijkstra can't support negative weight. 
            if(weight[q][i] > 0 && info[i].color == WHITE) {
                relax_edge(q, i, heap, info, weight); 
            }

        }

        heap[0] = heap[--rear]; 
        heap[rear] = q; 

        keep_heap_property(heap, info, 0, rear); 
    }

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
    FILE *fp = fopen("dijkstra.txt", "r"); 

    int i, j; 
    int len; 

    WEIGHT weight; 
    
    fscanf(fp, "%d\n", &len); 

    for(i = 0; i < len; ++i) 
        for(j = 0; j < len; ++j) 
            fscanf(fp, "%d", &weight[i][j]); 

    fclose(fp); 

    printf("src = 0:\n"); 
    dijkstra(weight, len, 0); 

    printf("src = 1:\n"); 
    dijkstra(weight, len, 1); 

    return 0; 
}

