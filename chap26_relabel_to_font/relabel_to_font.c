#include <stdio.h> 
#include <stdlib.h> 
#include <memory.h> 
#include <limits.h> 

#define MAXSIZE 100 

typedef int FLOW[MAXSIZE][MAXSIZE];

typedef FLOW RESIDUAL; 

typedef FLOW CAPACITY; 

typedef struct {
    
    int overplus; 
    int hight; 

}NODE_INFO[MAXSIZE]; 

struct list {

    int data; 
    struct list * next;
};

typedef struct list *LIST; 
typedef struct list *ADJACENT_LIST[MAXSIZE]; 


// define source and termination.
const int s = 0; 
const int t = 3;

void push(int u, int v, FLOW f, RESIDUAL r, NODE_INFO n) 
{    
    
    // push u to v. 
    int d = n[u].overplus < r[u][v] ? n[u].overplus : r[u][v];

    n[u].overplus -= d; 
    n[v].overplus += d; 

    f[u][v] += d;  
    f[v][u] -= d; 

    r[u][v] -= d; 
    r[v][u] += d; 

}

void relabel(int u, RESIDUAL r, NODE_INFO n, LIST adj) 
{
    LIST h = adj->next; 

    int min = LONG_MAX; 

    while(h != NULL) {
        
        if(r[u][h->data] > 0 && n[h->data].hight + 1 < min) 
            min = n[h->data].hight + 1; 

        h = h->next; 
    }

    n[u].hight = min; 
}

void discharge(int u, FLOW f, RESIDUAL r, NODE_INFO n, ADJACENT_LIST adj) 
{
    LIST h = adj[u]->next; 

    int v; 
    
    while(n[u].overplus > 0) {
    
        if(h == NULL) {

            relabel(u, r, n, adj[u]);  
            h = adj[u]->next; 
            continue; 
        }

        v = h->data; 
        if(r[u][v] > 0 && n[u].hight == n[v].hight+1) {
           
            push(u, v, f, r, n); 
                
        }

        h = h->next; 
    
    }
}

void init_flow_state(CAPACITY capacity, FLOW flow, RESIDUAL residual, NODE_INFO node_info, int vertex_num) 
{

    memset(flow, 0, sizeof(flow));
    memset(node_info, 0, sizeof(node_info)); 

    node_info[s].hight = vertex_num; 

    int i; 
    for(i = 0; i < vertex_num; ++i) {
        if(capacity[s][i] > 0) {
            
            flow[s][i] = capacity[s][i]; 
            flow[i][s] = -capacity[s][i]; 

            node_info[i].overplus = capacity[s][i]; 
            node_info[s].overplus -= capacity[s][i];
            
            residual[s][i] = 0; 
            residual[i][s] = capacity[s][i]; 
        
        }
    }

}

void move_node_to_front(LIST l, LIST h)
{
   LIST tmp = l; 

   while(tmp->next != h) 
       tmp = tmp->next;

   tmp->next = h->next; 
   h->next = l->next; 
   l->next = h;

}

int main() 
{
    FILE *fp = fopen("relabel_to_font.txt", "r"); 

    int vertex_num; 

    fscanf(fp, "%d\n", &vertex_num); 

    int i, j; 
    CAPACITY capacity; 
    RESIDUAL residual; 

    memset(residual, 0, sizeof(residual)); 
    for(i = 0; i < vertex_num; ++i) 
        for(j = 0; j < vertex_num; ++j){ 

            fscanf(fp, "%d", &capacity[i][j]); 
            residual[i][j] = capacity[i][j];
    }
    fclose(fp); 

    FLOW flow; 
    NODE_INFO node_info; 

    //init_flow_state
    init_flow_state(capacity, flow, residual, node_info, vertex_num);  

    //init list L and adjacnt list 
    
    LIST l = (LIST)malloc(sizeof(struct list)); 
    l->next = NULL; 

    ADJACENT_LIST adj_list; 

    for(i = 0; i < vertex_num; ++i) {
        if(i != s && i != t) { 

            LIST h = (LIST)malloc(sizeof(struct list)); 
            h->data = i; 
            h->next = l->next; 
            l->next = h; 
        
            adj_list[i] = (LIST)malloc(sizeof(struct list)); 
            adj_list[i]->next = NULL; 
        }
    }
   
    for(i = 0; i < vertex_num; ++i) {
        if(i != s && i != t) {
        
            for(j = 0; j < vertex_num; ++j) {
            
                if(capacity[i][j] > 0 || capacity[j][i] > 0) {
                    
                    LIST h  = (LIST)malloc(sizeof(struct list)); 
                    h->data = j; 
                    h->next = adj_list[i]->next; 
                    adj_list[i]->next = h; 
                }
            
            }
        }
    }


    LIST h = l->next; 
    while(h != NULL) {

        int u = h->data; 
        
        if(node_info[u].overplus > 0) {

            int old_hight = node_info[u].hight; 
            discharge(u, flow, residual, node_info, adj_list); 
            
            if( node_info[u].hight > old_hight) {
                move_node_to_front(l, h); 
            }

        }

        h = h->next;

    }

    printf("max flow=%d\n", node_info[t].overplus); 

    return 0; 
}

