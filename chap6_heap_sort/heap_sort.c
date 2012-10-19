#include <stdio.h> 
#include <stdlib.h>

#define MAXSIZE 50000

#define PARENT(x) ((x)/2)
#define L_CHILD(x) (2*(x))
#define R_CHILD(x) (2*(x)+1)

void build_max_heap(int array[], int len) 
{
    int i; 

    for(i = len / 2; i >= 0; --i) {
        keep_heap_properties(array, i, len);  
    }
}

void keep_heap_properties(int array[], int root_pos,  int len) 
{
    int next_root_pos = root_pos; 

    if(next_root_pos == len

    if(array[next_root_pos] < array[L_CHILD(root_pos)]) {
        next_root_pos = L_CHILD(root_pos); 
    }

    if(array[next_root_pos] < array[R_CHILD(root_pos)]) { 
        next_root_pos = R_CHILD(root_pos); 
    }

    if(next_root_pos != root_pos) {
        
        int tmp = a[next_root_pos]; 
        a[next_root_pos] = a[root_pos]; 
        a[root_pos] = a[next_root_pos]; 
    
        keep_heap_properties(array, next_root_pos, len); 

    }
}

void heap_sort(int array[], int len) 
{
    int rear = len; 

    int result[MAXSIZE]; 

    memset(result, 0, sizeof(int)*MAXSIZE);


    while(rear > 0) {
        
        // output to result in ascent order. 
        result[--rear] = array[0];

        array[0] = array[rear]; 
        keep_heap_properties(array, 0, rear); 

    }
}

int main() 
{
    int array[MAXSIZE]; 

    FILE *fp = fopen("numbers.txt", "r"); 

    int len;
    fscanf(fp, "%d\n", &len); 

    int i = 0; 
    for(; i < len; ++i) 
        fscanf(fp, "%d", &array[i]); 

    fclose(fp); 

    heap_sort(array, len); 

    return 0; 
}

