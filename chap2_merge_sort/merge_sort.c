#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>
#include <sys/time.h>

#define MAXSIZE 50000

int array[MAXSIZE]; 

/*
void insert_sort(int begin, int end)
{

    int i; 
    int j; 

    for(i = begin+1; i < end; ++i) {
        
        int key = array[i]; 
        j = i-1; 

        while(j >= 0) {
            if(array[j] > key) {
                array[j+1] = array[j]; 
                j--; 
            }
            else {
                break; 
            }
        }

        array[j+1] = key; 
       
   
    }
        
}
*/

void merge_sort(int begin, int end)
{

    int step = (end-begin) / 2;

    if(end-begin > 1) {
        merge_sort(begin, begin+step); 
        merge_sort(begin+step, end); 
    }
  /*  else {
        // use insert sort for 100 size part. 

        insert_sort(begin, begin+step); 
        insert_sort(begin+step, end); 
    }*/

    int i, left_len, right_len; 
    int left[MAXSIZE], right[MAXSIZE]; 

    left_len = 0; 
    for(i = begin; i < begin+step; ++i, ++left_len) 
        left[left_len] = array[i]; 

    right_len = 0; 
    for(i = begin+step; i < end; ++i, ++right_len) 
        right[right_len] = array[i]; 

    left[left_len] = right[right_len] = LONG_MAX; 

    i = begin;
    int j = 0; 
    int k = 0; 

    while(i < end) {
        if(left[j] <= right[k]) { 
            array[i] = left[j++];
        }
        else { 
            array[i] = right[k++]; 
        }

        i++;
    }
        
}


int main() 
{
    //int *array = (int*)malloc(MAXSIZE*sizeof(int));


    printf("%d\n", sizeof(array)); 

    FILE *fp = fopen("numbers.txt", "r");

    int len; 

    fscanf(fp, "%d\n", &len); 
    
    int i; 
    for(i = 0; i < len; ++i) 
        fscanf(fp, "%d", &array[i]); 

    fclose(fp);

    struct timeval begin_time, end_time; 

    gettimeofday(&begin_time, NULL); 
    merge_sort(0, len); 
    gettimeofday(&end_time, NULL); 

    fp = fopen("merge_sort.out", "w"); 

    for(i = 0; i < len; ++i) 
        fprintf(fp, "%d ", array[i]); 

    fprintf(fp, "\n");
    fclose(fp); 
    //free(array); 

    printf("elapsed time = %ld uSecs.\n", (end_time.tv_sec-begin_time.tv_sec)*1000000 + (end_time.tv_usec-begin_time.tv_usec));

    return 0; 
}

