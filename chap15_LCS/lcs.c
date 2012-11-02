#include <stdio.h> 
#include <stdlib.h> 

#define MAXSIZE 100 


int main() 
{
    int m, n; 

    char x[MAXSIZE]; 
    char y[MAXSIZE]; 

    int s[MAXSIZE][MAXSIZE];

    FILE* fp = fopen("lcs.txt", "r"); 

    fscanf(fp, "%d\n", &m);  
    fgets(x, m+1, fp); 

    fscanf(fp, "%d\n", &n); 
    fgets(y, n+1, fp); 
    
    int i, j; 

    printf("%s\n", x); 
    printf("%s\n", y); 

    
    for(i = 0; i <= n; ++i) s[0][i] = 0; 
    for(i = 0; i <= m; ++i) s[i][0] = 0; 

    for(i = 1; i <= m; ++i) 
        for(j = 1; j <= n; ++j) {
            
            if(x[i-1] == y[j-1]) 
                s[i][j] = s[i-1][j-1] + 1; 

            else {
                
                s[i][j] = s[i-1][j] > s[i][j-1] ? s[i-1][j] : s[i][j-1]; 
            }
        
        }

    fclose(fp); 
     
    printf("the length is %d.\n", s[m][n]); 

    return 0; 
}

