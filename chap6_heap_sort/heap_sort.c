#include <stdio.h> 
#include <stdlib.h>
#include <memory.h> 
#include <sys/time.h> 

#define MAXSIZE 50000

#define L_CHILD(x) (2*((x)+1)-1)
#define R_CHILD(x) (2*((x)+1))

void keep_heap_properties(int [], int, int); 

void build_max_heap(int array[], int len) 
{
    int i;
    
    len--; 

    if(len % 2 == 0) 
        i = len / 2 - 1; 
    else 
        i = len / 2; 

    for(; i >= 0; --i) {
        keep_heap_properties(array, i, len);  
    }
}

void keep_heap_properties(int array[], int root_pos,  int len) 
{
    int next_root_pos = root_pos; 

    if(next_root_pos == len) 
        return; 

    if(L_CHILD(root_pos) <= len && array[next_root_pos] < array[L_CHILD(root_pos)]) {
        next_root_pos = L_CHILD(root_pos); 
    }

    if(R_CHILD(root_pos) <= len && array[next_root_pos] < array[R_CHILD(root_pos)]) { 
        next_root_pos = R_CHILD(root_pos); 
    }

    if(next_root_pos != root_pos) {
        
        int tmp = array[next_root_pos]; 
        array[next_root_pos] = array[root_pos]; 
        array[root_pos] = tmp; 
    
        keep_heap_properties(array, next_root_pos, len); 

    }
}

int* heap_sort(int array[], int len) 
{
    int rear = len; 

    int *result = (int*)malloc(sizeof(int)*len); 

    memset(result, 0, sizeof(int)*len);


    while(rear > 0) {
        
        // output to result in ascent order. 
        result[--rear] = array[0];

        array[0] = array[rear]; 
        keep_heap_properties(array, 0, rear-1); 

    }

    return result;  
}

int main() 
{
    int array[MAXSIZE]; 
    int *result; 

    FILE *fp = fopen("numbers.txt", "r"); 

    int len;
    fscanf(fp, "%d\n", &len); 

    int i = 0; 
    for(; i < len; ++i) 
        fscanf(fp, "%d", &array[i]); 

    fclose(fp); 

    struct timeval begin_time, end_time; 

    gettimeofday(&begin_time, NULL); 
    build_max_heap(array, len); 
    result = heap_sort(array, len);
    gettimeofday(&end_time, NULL); 

    fp = fopen("heap_sort.out", "w"); 

    for(i = 0; i < len; ++i) 
        fprintf(fp, "%d ", result[i]); 
    fclose(fp); 

    free(result);

    printf("elapsed time = %ld uSecs.\n", (end_time.tv_sec-begin_time.tv_sec)*1000000 + (end_time.tv_usec-begin_time.tv_usec));

    return 0; 
}

