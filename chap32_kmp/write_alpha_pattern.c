#include <stdio.h> 
#include <stdlib.h> 

#define MAXSIZE 1000000
#define STEP 10000

int main() 
{
    FILE *fp = fopen("alphabet_str.txt", "w"); 
    
    int i = 0; 

    fprintf(fp, "%d\n", MAXSIZE);  
    while(i++ < MAXSIZE-1) 
        putc('a', fp); 
   
    putc('b', fp); 

    fclose(fp); 

    i = 0; 
    fp = fopen("pattern_str.txt", "w"); 
    fprintf(fp, "%d\n", STEP); 
    while( i++ < STEP-1) 
        putc('a', fp); 

    putc('b', fp); 

    fclose(fp); 

    return 0; 
}
