#include <stdio.h> 
#include <stdlib.h> 
#include <sys/time.h> 

#define MAXSIZE 1024000 



/*int * compute_pattern_prefix(char p_str[], int l_pattern)
{

    int *prefix = (int*)malloc(sizeof(int)*MAXSIZE); 

    prefix[0] = -1; 

    int i = 1;
    int j; 
    
    while(i < l_pattern) {

        j = prefix[i-1]; 
        while(p_str[i] != p_str[j+1] ) {
            if(j == -1) { 
                j = -2; 
                break; 
            }
            j = prefix[j];
        }
        prefix[i] = j+1; 
        i++;    
    }

    return prefix; 
}*/

void simple_match(char alphabet_str[], int l_alpha, char p_str[], int l_pattern)
{

    int i = 0; 
    int j = 0; 

    while(i < l_alpha) {
        
        int k = i; 
        j = 0; 

        while(j < l_pattern) {
            
            if(alphabet_str[k] != p_str[j]) break; 
            
            j++; 
            k++; 

        }
        
        if(j == l_pattern) 
            break; 

        i++;
        
    }

    // print
    /*
    for( j = 0; j < l_alpha; ++j) {
        if(j == i-l_pattern+1) 
            printf("\"");

        printf("%c", alphabet_str[j]);

        if(j == i) 
            printf("\""); 
    }

    printf("\n"); */ 

    printf("the str from %d to %d is matched!\n", i, i+l_pattern-1); 

}

int main() 
{
    
    char alphabet_str[MAXSIZE]; 
    char p_str[MAXSIZE]; 

    int len_alphabet, len_pattern; 

    FILE* fp = fopen("alphabet_str.txt", "r"); 
   
    // read alphabet and pattern. 
    fscanf(fp, "%d\n", &len_alphabet); 
    fread(alphabet_str, 1, len_alphabet, fp);
    fclose(fp); 

    fp = fopen("pattern_str.txt", "r"); 
    fscanf(fp, "%d\n", &len_pattern); 
    fread(p_str, 1, len_pattern, fp); 
    fclose(fp); 

    struct timeval time_begin, time_end; 

    gettimeofday(&time_begin, NULL); 

    simple_match(alphabet_str, len_alphabet, p_str, len_pattern); 

    gettimeofday(&time_end, NULL); 

    // count time
    printf("elapsed time = %ld uSecs.\n", (time_end.tv_sec-time_begin.tv_sec)*1000000 +(time_end.tv_usec - time_begin.tv_usec)); 


    
    return 0; 
}


