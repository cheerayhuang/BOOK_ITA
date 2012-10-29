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

// define source and termination.
const int s = 0; 
const int t = 3;

int find_push_target(int i, CAPACITY c, FLOW f, NODE_INFO n) 
{
    int u; 
    int num = n[s].hight; 

    for(u = 0; u < num; ++u) {
        if(n[i].hight == n[u].hight+1 && c[i][u]-f[i][u] > 0) {
            return u; 
        }
    }

    return 0; 
}

int push(FLOW f, RESIDUAL r, CAPACITY c, NODE_INFO n) 
{
    int num = n[s].hight; 

    int i; 

    int is_pushed = 0; 

    for(i = 0; i < num; ++i) {

        int u = find_push_target(i, c, f, n);  
        if(n[i].overplus > 0 && u != 0) {
            
            int d = n[i].overplus < (c[i][u]-f[i][u]) ?  n[i].overplus : (c[i][u]-f[i][u]); 

            n[i].overplus -= d; 
            n[u].overplus += d; 

            f[i][u] += d; 
            f[u][i] -= d; 

            r[i][u] = c[i][u] - f[i][u];
            r[u][i] = c[u][i] - f[u][i]; 

            is_pushed = 1; 
            //return 1; 
        }
    
    }

    return is_pushed; 
}


int find_low_point(int i, CAPACITY c, FLOW f, NODE_INFO n) 
{
    int u; 
    int num = n[s].hight; 
    int min_hight = LONG_MAX;
    int min_point = 0; 

    for(u = 0; u < num; ++u) {
        
        if(u != s && n[u].hight >= n[i].hight && c[i][u]-f[i][u] > 0) {
            
            if(n[u].hight < min_hight) {
                min_hight = n[u].hight; 
                min_point = u; 
            }
        }
        else if(n[u].hight < n[i].hight && c[i][u]-f[i][u] > 0) {

            return 0; 
            
        }
    }

    return min_point; 
}

int relabel(FLOW f, RESIDUAL r, CAPACITY c, NODE_INFO n) 
{
    int num = n[s].hight; 
    
    int is_relabeled = 0;

    int i; 

    for(i = 0; i < num; ++i) {
        
        int u = find_low_point(i, c, f, n); 
        if(i != s && i != t && n[i].overplus > 0 && u != 0) { 
            
            n[i].hight = n[u].hight + 1; 
            is_relabeled = 1; 
            //return 1; 
        }
    }

    return is_relabeled; 
}


int main() 
{
    FILE *fp = fopen("push_relabel.txt", "r"); 

    int vertex_num; 

    fscanf(fp, "%d\n", &vertex_num); 

    int i, j; 
    CAPACITY capacity; 

    for(i = 0; i < vertex_num; ++i) 
        for(j = 0; j < vertex_num; ++j) 
            fscanf(fp, "%d", &capacity[i][j]); 

    fclose(fp); 


    FLOW flow; 
    RESIDUAL residual; 
    NODE_INFO node_info; 

    //init_flow_state

    memset(flow, 0, sizeof(flow));
    memset(residual, 0, sizeof(residual)); 
    memset(node_info, 0, sizeof(node_info)); 

    node_info[s].hight = vertex_num; 

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

    while(push(flow, residual, capacity, node_info) || 
          relabel(flow, residual, capacity, node_info)) {
    
        for(i = 0; i < 6; ++i) 
            printf("node[%d]: overplus=%d, hight=%d\n", i, node_info[i].overplus, node_info[i].hight); 
            printf("----------\n"); 

    }

    int sum = 0; 
    for(i = 0; i < vertex_num; ++i) {
        sum += flow[i][t]; 
    }

    printf("max flow = %d\n", sum); 

    return 0; 
}

