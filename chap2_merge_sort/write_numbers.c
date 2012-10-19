#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>
#include <time.h> 

#define MAXSIZE 100000

int main() 
{

    FILE *fp = fopen("numbers.txt", "w");

    fprintf(fp, "%d\n", MAXSIZE); 

    time_t seed; 

    seed = time(NULL); 
    srand(seed); 

    int i = 0; 

    while(i < MAXSIZE) {
        
        int k = rand() % 2000000; 
        fprintf(fp, "%d ", k); 
        i++;
    }

    fclose(fp); 


    return 0; 
}

