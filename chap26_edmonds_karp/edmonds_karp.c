#include <stdio.h> 
#include <stdlib.h> 
#include <memory.h> 
#include <limits.h> 

#define MAXSIZE 100 


typedef int CAPACITY[MAXSIZE][MAXSIZE];
typedef CAPACITY FLOW; 
typedef CAPACITY RESIDUAL; 


void generate_shortest_path(int p[], int i, int *path) 
{
    int k = 0; 
    int min = INT_MAX; 

    while(i != 0) {
        path[k++] = i; 
        i = p[i]; 
    }

    path[k] = i; 
}

int* bfs(RESIDUAL r, int vertex_num, int t) 
{

    enum {WHITE, BLACK} color[MAXSIZE]; 
    int parent[MAXSIZE]; 

    int queue[MAXSIZE]; 
    int head = 0, tail = 1; 

    queue[0] = 0;
    color[0] = BLACK; 

    int i; 
    for(i = 1; i < vertex_num; ++i) 
        color[i] = WHITE; 

    while(head != tail) {
        
        // don't handle the circle for queue. 
        int h = queue[head++]; 
        color[h] = BLACK; 

        for(i = 0; i < vertex_num; ++i) {
            
            if(r[h][i] > 0 && color[i] == WHITE) {

                // don't handle the circle for queue. 
                queue[tail++] = i; 

                parent[i] = h; 
                if(i == t) {
                    
                    int *path = (int*)malloc(sizeof(int)*vertex_num);

                    generate_shortest_path(parent, i, path); 
                    return path; 
                }
            }
        }
    }

    return NULL; 
}

void print_all_flow(FLOW f, int vertex_num) 
{
    int i, j; 

    for(i = 0; i < vertex_num; ++i) { 
        for(j = 0; j < vertex_num; ++j) 
            printf("%d ", f[i][j]);
        printf("\n"); 
    }

    printf("\n"); 

}

void edmonds_karp(CAPACITY c, RESIDUAL residual, int vertex_num) 
{
    FLOW flow; 
    //RESIDUAL residual; 

    int t = 3; // in this case, the end point is 3. 

    memset(flow, 0, sizeof(flow)); 

    int *path; 
    path = bfs(residual, vertex_num, t);

    while(path != NULL) {
        
        int k = 0; 
        int min_weight = INT_MAX; 

        while(path[k] != 0) {
            if(residual[path[k+1]][path[k]] < min_weight) min_weight = residual[path[k+1]][path[k]]; 
            k++; 
        }
        
        k = 0; 
        while(path[k] != 0) {
            flow[path[k+1]][path[k]] += min_weight; 
            residual[path[k+1]][path[k]] -= min_weight; 
            //residual[path[k]][path[k+1]] += min_weight; 
            k++; 
        }

        free(path); 

        print_all_flow(flow, vertex_num); 


        print_all_flow(residual, vertex_num); 

        path = bfs(residual, vertex_num, t); 
    
    };  

    int i, sum = 0; 
    for(i = 0; i < vertex_num; ++i) 
        sum += flow[i][t]; 

    printf("max flow = %d\n", sum);
}

int main() 
{
    FILE *fp = fopen("edmonds_karp.txt", "r"); 


    CAPACITY capacity; 
    RESIDUAL residual; 

    int i, j, vertex_num; 

    fscanf(fp, "%d\n", &vertex_num);

    memset(residual, 0, sizeof(residual)); 
    for(i = 0; i < vertex_num; ++i) 
        for(j = 0; j < vertex_num; ++j) { 
            fscanf(fp, "%d", &capacity[i][j]); 

            residual[i][j] = capacity[i][j]; 

    }

    edmonds_karp(capacity, residual, vertex_num); 
    
    fclose(fp); 

    return 0; 
}

