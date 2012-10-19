#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>
#include <sys/time.h>

#define MAXSIZE 50000

int array[MAXSIZE]; 

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


int main() 
{
    //int *array = (int*)malloc(MAXSIZE*sizeof(int));


    FILE *fp = fopen("numbers.txt", "r");

    int len; 

    fscanf(fp, "%d\n", &len); 
    
    int i; 
    for(i = 0; i < len; ++i) 
        fscanf(fp, "%d", &array[i]); 

    fclose(fp);

    struct timeval begin_time, end_time; 

    gettimeofday(&begin_time, NULL); 
    insert_sort(0, len); 
    gettimeofday(&end_time, NULL); 

    fp = fopen("insert_sort.out", "w"); 

    for(i = 0; i < len; ++i) 
        fprintf(fp, "%d ", array[i]); 

    fprintf(fp, "\n");

    fclose(fp); 

    //free(array); 

    printf("elapsed time = %ld uSecs.\n", (end_time.tv_sec-begin_time.tv_sec)*1000000 + (end_time.tv_usec-begin_time.tv_usec)); 

    return 0; 
}

