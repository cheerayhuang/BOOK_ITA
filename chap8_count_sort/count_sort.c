#include <stdio.h> 
#include <stdlib.h> 
#include <memory.h> 
#include <sys/time.h> 

#define MAXSIZE 50000


void count_number(int array[], int count[], int len) 
{
    int i = 0; 
    int tmp;
    for(; i < len; ++i) {
        count[array[i]]++;
    }

    tmp = 0; 
    for(i = 0; i < len; ++i) {
        
        if(count[i] > 0) {
            tmp += count[i]; 
            count[i] = tmp; 
        }
    }

}

void count_sort(int array[], int result[], int count[], int len)
{

    int i; 

    // use "downto" to keep sorting stable. 
    for(i = len-1; i >= 0; --i) {
        result[count[array[i]]-1] = array[i]; 
        count[array[i]]--; 

    }
}

int main() 
{
    FILE* fp = fopen("numbers.txt", "r"); 

    int len; 
    int array[MAXSIZE]; 

    fscanf(fp, "%d\n", &len); 
    
    int i; 
    for(i = 0; i < len; ++i) 
        fscanf(fp, "%d", &array[i]);

    fclose(fp);

    // count the total of appearance for each number.

    int count[MAXSIZE]; // in this example, the value of input numbers are all less than 50000. 
    memset(count, 0, sizeof(int)*MAXSIZE); 

    struct timeval begin_time, end_time; 
    gettimeofday(&begin_time, NULL);
    count_number(array, count, len);

    //count sort. 

    int result[MAXSIZE]; // the total of numbers is not more than 50000. 
    count_sort(array, result, count, len); 
    gettimeofday(&end_time, NULL); 

    fp = fopen("count_sort.out", "w"); 


    for(i = 0; i < len; ++i) 
        fprintf(fp, "%d\n", result[i]); 

    fclose(fp); 

    printf("elapsed time = %ld uSecs.\n", (end_time.tv_sec-       begin_time.tv_sec)*1000000 + (end_time.tv_usec-begin_time.tv_usec));

    return 0; 
}
