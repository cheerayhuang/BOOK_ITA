#include <stdio.h> 
#include <stdlib.h> 

#define MAXSIZE 50000

typedef struct stack{ 
    int top; 
    int data[MAXSIZE]; 
}STACK; 



int pop_up(STACK *stack_p) 
{
    return stack_p->data[--stack_p->top]; 
}

int push_down(STACK *stack_p, int i) 
{
    stack_p->data[stack_p->top++] = i; 
    return i;
}

int empty(STACK *stack_p) 
{
    return (stack_p->top == 0); 
}


int main() 
{
    // build a stack; 
    STACK data_stack; 
    data_stack.top = 0; 

    
    FILE *fp = fopen("for_stack_array_test.txt", "r");
    int i = 0; 
    int len; 

    fscanf(fp, "%d", &len); 
    for(; i < len; ++i) { 
        int tmp; 
        fscanf(fp, "%d", &tmp); 
        push_down(&data_stack, tmp); 
    }

    fclose(fp); 

    fp = fopen("stack_array.out", "w"); 
    for(i = 0; i < len; ++i) 
        fprintf(fp, "%d\n", pop_up(&data_stack)); 

    if(empty(&data_stack)) 
        printf("Now, the stack is empty!\n"); 
    
    fclose(fp); 
    
    return 0; 
}

