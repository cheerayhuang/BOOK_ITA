#include <stdio.h> 
#include <stdlib.h>
#include <memory.h> 
#include <sys/time.h> 

#define MAXSIZE 50000

void insert_sort(int array[], int begin, int end) 
{

    int i; 
    int j; 

    for(i = begin+1; i <= end; ++i) {
        
        int key = array[i]; 
        for(j = i-1; j >= 0 && array[j] > key; --j)
            array[j+1] = array[j]; 

        array[j+1] = key; 
    
    }
}

int locate(int array[], int begin, int end) 
{
    // randomize quick sort, get a sign value in a random pos. 
    int rand_pos = rand() % (end-begin+1) + begin; 
    int sign_value = array[rand_pos];
    array[rand_pos] = array[begin]; 
    array[begin] = sign_value; 

    int i = begin, j = end+1; 
/*
    for(; j <= end; ++j) {
    
        if(array[j] < sign_value) {
            i++; 
            int tmp = array[i]; 
            array[i] = array[j]; 
            array[j] = tmp; 
        }
    }

    array[begin] = array[i]; 
    array[i] = sign_value; 
*/

    while(1) {
        
        do{ 
            i++; 
        } while(i <= end && array[i] < sign_value);
        
        do{ 
            j--; 
        } while(array[j] > sign_value); 

        if(j < i) 
            break; 

        int tmp = array[i]; 
        array[i] = array[j]; 
        array[j] = tmp; 
    
    }

    array[begin] = array[j]; 
    array[j] = sign_value; 
    
    return j; 
}

void quick_sort(int array[], int begin, int end)
{
    if(end-begin + 1 > 7) {
        int mid = locate(array, begin, end); 
        quick_sort(array, begin, mid-1);
        quick_sort(array, mid+1, end); 
    }
    else {
        // use insert sort for it. 

        insert_sort(array, begin, end); 
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

    struct timeval begin_time, end_time; 

    gettimeofday(&begin_time, NULL); 
    
    // set random seed 
    srand(begin_time.tv_sec); 
    quick_sort(array, 0, len);

    gettimeofday(&end_time, NULL); 

    fp = fopen("quick_sort.out", "w"); 

    for(i = 0; i < len; ++i) 
        fprintf(fp, "%d ", array[i]); 
    fclose(fp); 

    printf("elapsed time = %ld uSecs.\n", (end_time.tv_sec-begin_time.tv_sec)*1000000 + (end_time.tv_usec-begin_time.tv_usec));

    return 0; 
}

