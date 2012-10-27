#include <stdio.h>
#include <stdlib.h> 
#include <limits.h> 

#define MAXSIZE 100 

#define PARENT(x) (((x)%2 == 0) ? ((x)/2-1) :((x)/2))
#define L_CHILD(x) (2*(x)+1) 
#define R_CHILD(x) (2*(x)+2) 


typedef enum {

    WHITE, 
    BLACK

}COLOR; 

typedef struct {
    
    int key; 
    int vertex; 

}HEAP; 

typedef struct {

    COLOR color; 
    int parent; 
    int heap_pos; 

}NODE_TAG[MAXSIZE];

typedef int WEIGHT[MAXSIZE][MAXSIZE]; 


void keep_heap_property(HEAP heap[], NODE_TAG node_tag, int heap_pos, int rear) 
{
    int mark = heap_pos;
    int vertex = heap[heap_pos].vertex;

    if(L_CHILD(heap_pos) < rear && 
       heap[mark].key > heap[L_CHILD(heap_pos)].key) {
        
        mark = L_CHILD(heap_pos); 
    }

    if(R_CHILD(heap_pos) < rear && 
       heap[mark].key > heap[R_CHILD(heap_pos)].key) {
        
        mark = R_CHILD(heap_pos); 
    }
   
    if(mark != heap_pos) {
        
        HEAP tmp = heap[heap_pos]; 
        heap[heap_pos] = heap[mark]; 
        heap[mark] = tmp;

        keep_heap_property(heap, node_tag, mark, rear); 
    }

    node_tag[heap[heap_pos].vertex].heap_pos = heap_pos; 

    
}

void decrease_heap_key(HEAP heap[], NODE_TAG node_tag, int i)
{
    if(node_tag[i].heap_pos == 0) 
        return; 

    int heap_pos = node_tag[i].heap_pos; 
    int parent_pos = PARENT(heap_pos); 

    HEAP h_x = heap[heap_pos]; 
    HEAP h_y = heap[parent_pos]; 

    int x = i; 
    int y = heap[parent_pos].vertex; 

    while(h_x.key < h_y.key) {
        
        heap[heap_pos] = heap[parent_pos]; 
        heap[parent_pos] = h_x; 
        
        node_tag[x].heap_pos = parent_pos; 
        node_tag[y].heap_pos = heap_pos; 
    
        heap_pos = parent_pos;
        parent_pos = PARENT(heap_pos); 

        if(parent_pos < 0) return; 

        h_y = heap[parent_pos]; 
        y = heap[parent_pos].vertex; 
        
    }


}

void prim(WEIGHT weight, int len) 
{
    
    HEAP heap[MAXSIZE]; 
    NODE_TAG node_tag; 

    int i; 
    for(i = 0; i < len; ++i) {
        heap[i].vertex = i; 
        heap[i].key = LONG_MAX; 

        node_tag[i].color = WHITE; 
        node_tag[i].heap_pos = i; 
    }

    heap[0].key = 0; 

    //at beginning, key[0] = 0, it is already a heap. 
    //build_min_heap(heap, len); 
    
    int rear = len;

    while(rear > 1) {

        HEAP q = heap[0]; 
        heap[0] = heap[--rear]; 
        heap[rear] = q; 

        node_tag[q.vertex].color = BLACK; 

        keep_heap_property(heap, node_tag, 0, rear);  

        int i; 
        for(i = 0; i < len; ++i) {
            if(node_tag[i].color == WHITE && weight[q.vertex][i] != 0 && 
               weight[q.vertex][i] < heap[node_tag[i].heap_pos].key) {
                
                heap[node_tag[i].heap_pos].key = weight[q.vertex][i]; 
                node_tag[i].parent = q.vertex; 
                decrease_heap_key(heap, node_tag, i);  
            }
        }
    }

    int sum = 0; 
    for(i = 1; i < len; ++i) {
        printf("%d--%d, weight:%d\n", node_tag[i].parent, i, weight[node_tag[i].parent][i]);
        sum += weight[node_tag[i].parent][i]; 
    }

    printf("sum = %d\n", sum); 

}


int main() 
{
    FILE *fp = fopen("prim.txt", "r"); 

    int len; 
    fscanf(fp, "%d\n", &len); 

    int i, j; 
    WEIGHT weight; 

    for(i = 0; i < len; ++i) 
        for(j = 0; j < len; ++j) 
            fscanf(fp, "%d", &weight[i][j]); 

    fclose(fp); 

    prim(weight, len); 

    return 0; 
}

