#include <stdio.h> 
#include <stdlib.h>
#include <memory.h> 
#include <sys/time.h> 

enum 
{
    MAX_SIZE = 50000
};

/*
 * get_middle - get the middle number from numbers as sign value 
 * return: return the middle number 
 * array(in): an array to store the nubmers.  
 * begin(in): the beginning of the array. 
 * mid(in): the middle of the array. 
 * end(in): the tail of the array. 
 */
int get_middle(int array[], int begin, int mid, int end) 
{
    return (array[begin] < array[mid]) ? (array[mid] < array[end] ? mid : (array[begin] < array[end] ? end : begin)) : (array[mid] > array[end] ? mid : (array[begin] < array[end] ? begin : end));

}

/*
 * insert_sort - insert sort algorithm. 
 * return: none.
 * array(in/out): an array to store the numbers. 
 * begin(in): the beginning of the array. 
 * end(in): the tail of the array. 
 */
void insert_sort(int array[], int begin, int end) 
{

    int i; 
    int j; 
    int key; 

    key = 0; 

    for(i = begin+1; i <= end; ++i) 
    {
        
        key = array[i]; 
        for(j = i-1; j >= begin && array[j] > key; --j)
        {
            array[j+1] = array[j]; 
        }
        array[j+1] = key; 
    
    }
}

/*
 * locate - get the sign value position, while arranging numbers according to the sign value. 
 * return: return the sign value position.
 * array(in/out): an array to store the numbers. 
 * begin(in): the beginning of the array. 
 * end(in): the tail of the array. 
 */
int locate(int array[], int begin, int end) 
{

    int len;
    int mid;
    int step; 
    int sign_value;
    int tmp; 
    int b, e, i, j; 

    len = end - begin + 1;
    mid = begin + (len / 2); 
    b = begin; 
    e = end; 
    i = begin; 
    j = begin+1; 
    
    /*
     * use the middle number as sign value instead of fixed position or random position 
     * in order that optimize the locate funciton.
     */
    if( len > 64) 
    {
        step = len / 8; 

        b = get_middle(array, begin, begin+step, begin+step*2);
        mid = get_middle(array, begin+step*3, begin+step*4, begin+step*5); 
        e = get_middle(array, begin+step*6, begin+step*7, end); 
    }
    mid = get_middle(array, b, mid, e);

    sign_value = array[mid]; 
    array[mid] = array[begin]; 
    array[begin] = sign_value; 

    for(; j <= end; ++j) 
    {
        if(array[j] < sign_value) 
        {
            i++; 
            tmp = array[i]; 
            array[i] = array[j]; 
            array[j] = tmp; 
        }
    }

    array[begin] = array[i]; 
    array[i] = sign_value; 

    return i; 
}

/*
 * quick_sort - quick sort algorithm.
 * return: none. 
 * array(in/out): an array to store the numbers. 
 * begin(in): the beginning of the array. 
 * end(in): the tail of the array. 
 */
void quick_sort(int array[], int begin, int end)
{

    int mid; 

    mid = 0; 

    if(end-begin+1 > 7) 
    {
        mid = locate(array, begin, end); 
        quick_sort(array, begin, mid-1);
        quick_sort(array, mid+1, end); 
    }
    else 
    {
        /* as to the small scale data, use insert sort directly. */
        insert_sort(array, begin, end); 
    }
}

int main() 
{
    int array[MAX_SIZE]; 
    int len; 
    int i; 

    FILE *fp;

    struct timeval begin_time, end_time; 

    i = 0; 
    len = 0; 

    fp = fopen("numbers.txt", "r"); 
    if (fp == NULL) 
    {
        perror("open numbers.txt failed.\n"); 
        exit(EXIT_FAILURE); 
    }

    fscanf(fp, "%d\n", &len); 
    for(i = 0; i < len; ++i)
    {
        fscanf(fp, "%d", &array[i]); 
    }
    fclose(fp); 

    gettimeofday(&begin_time, NULL); 
    
    quick_sort(array, 0, len);

    gettimeofday(&end_time, NULL); 

    fp = fopen("quick_sort.out", "w"); 
    if (fp == NULL) 
    {
        perror("open quick_sort.out file failed.\n"); 
        exit(EXIT_FAILURE); 
    }

    for(i = 0; i < len; ++i)
    {
        fprintf(fp, "%d ", array[i]); 
    }
    fclose(fp); 

    printf("elapsed time = %ld uSecs.\n", (end_time.tv_sec-begin_time.tv_sec)*1000000 + (end_time.tv_usec-begin_time.tv_usec));

    return EXIT_SUCCESS; 
}

