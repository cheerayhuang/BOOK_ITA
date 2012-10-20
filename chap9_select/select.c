#include <stdio.h> 
#include <stdlib.h> 
#include <memory.h> 
#include <sys/time.h> 

#define MAXSIZE 50000

int position(int array[], int begin, int end) 
{
    int sign_value = array[begin]; 

    int i = begin; 
    int j = end+1;

    while(1) {
        
        do{ 
            i++; 
        }while(i <= end && array[i] < sign_value); 

        do{ 
            j--; 
        }while(array[j] > sign_value); 

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

int select_number(int array[], int maxth, int begin, int end)
{
    int p = position(array, begin, end); 

    int len = p-begin+1;
    
    if(len == maxth) 
        return array[p]; 

    int result; 

    if(len < maxth) 
        result = select_number(array, maxth-len, p+1, end); 
    else 
        result = select_number(array, maxth, begin, p-1); 

    return result;
}

int main() 
{
    FILE* fp = fopen("numbers.txt", "r"); 

    int len; 
    int maxth; // the xth number in order you want to select.
    int array[MAXSIZE]; 

    fscanf(fp, "%d %d\n", &len, &maxth); 
    
    int i; 
    for(i = 0; i < len; ++i) 
        fscanf(fp, "%d", &array[i]);

    fclose(fp);

    struct timeval begin_time, end_time; 
    gettimeofday(&begin_time, NULL);
    
    int result = select_number(array, maxth, 0, len-1); 

    gettimeofday(&end_time, NULL); 

    printf("the No.%d is %d\n", maxth, result); 

    printf("elapsed time = %ld uSecs.\n", (end_time.tv_sec-       begin_time.tv_sec)*1000000 + (end_time.tv_usec-begin_time.tv_usec));

    return 0; 
}

