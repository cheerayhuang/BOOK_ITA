#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 

#define MAXSIZE 100

int main()
{

    FILE *fp = fopen("martrix_chain_order.txt", "r"); 

    int len; 

    fscanf(fp, "%d\n", &len); 

    int i = 0; 
    int a[MAXSIZE]; 
    int s[MAXSIZE][MAXSIZE]; 
    
    for(i = 0; i < len; ++i) {
        s[i][i] = 0; 
        fscanf(fp, "%d", &a[i]); 
    }

    int l; 
    int n = len - 1; 

    for(l = 2; l <= n; ++l) {

        for(i = 0; i < n; ++i) {
            int j = i + l - 1;

            if(j >= n) break; 
            
            s[i][j] = LONG_MAX; 

            int k;
            for(k = i; k <= j; ++k) {

                int q = s[i][k] + s[k+1][j] + a[i]*a[j+1]*a[k+1]; 
                if(q < s[i][j]) s[i][j] = q; 
            }    
        
        }
    
    }

    printf("min time of multiplication is %d\n", s[1][4]); 
    
    return 0; 

}

