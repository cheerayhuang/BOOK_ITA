#include <stdio.h> 
#include <stdlib.h> 

typedef struct Tree {

    struct Tree* parent, *left, *right; 
    int data;

}*TREE;

TREE max_node(TREE tree_p) 
{
    while(tree_p->right != NULL) 
        tree_p = tree_p->right;

    return tree_p; 
        
}

TREE min_node(TREE tree_p) 
{
   while(tree_p->left != NULL)
       tree_p = tree_p->left; 

   return tree_p; 
}

TREE successor(TREE tree_p) 
{
    if(tree_p->right != NULL) 
        return min_node(tree_p->right); 

    while(tree_p->parent->right == tree_p) 
        tree_p = tree_p->parent; 

    return tree_p->parent;

}

TREE predecessor(TREE tree_p) 
{
    if(tree_p->left != NULL)
        return max_node(tree_p->left); 

    while(tree_p->parent->left == tree_p)
        tree_p = tree_p->parent; 

    return tree_p->parent; 
}

void inorder_iterate(TREE tree_p)
{
    if(tree_p != NULL) {
        inorder_iterate(tree_p->left); 
        printf("%d ", tree_p->data); 
        inorder_iterate(tree_p->right); 
    }
}

/*
void insert(TREE *tree_p, int tmp)
{
    TREE parent = NULL; 
    TREE tmp_tree; 
    
    tmp_tree = (TREE)malloc(sizeof(struct Tree)); 
    tmp_tree->data = tmp; 
    tmp_tree->left = tmp_tree->right = NULL; 
    tmp_tree->parent = NULL; 


    TREE x = *tree_p; 

    while(x != NULL) {
        if(tmp > x->data) { 
            parent = x;
            x = x->right;
        }    
        else {
            parent = x;
            x = x->left; 
        }
    }

    tmp_tree->parent = parent; 

    if(parent == NULL) {
        *tree_p = tmp_tree;
        return ;
    }
    
    if(parent->data > tmp) 
        parent->left = tmp_tree; 
    else 
        parent->right = tmp_tree; 
    

    return ;
}
*/ 

// a new insert version
void insert(TREE tree_p, int tmp) 
{
    TREE parent = NULL; 
    TREE tmp_tree; 
    
    tmp_tree = (TREE)malloc(sizeof(struct Tree)); 
    tmp_tree->data = tmp; 
    tmp_tree->left = tmp_tree->right = NULL; 
    tmp_tree->parent = NULL; 


    while(tree_p != NULL) {
        if(tmp > tree_p->data) { 
            parent = tree_p;
            tree_p = tree_p->right;
        }    
        else {
            parent = tree_p;
            tree_p = tree_p->left; 
        }
    }

    tmp_tree->parent = parent; 

    if(parent->data > tmp) 
        parent->left = tmp_tree; 
    else 
        parent->right = tmp_tree; 
    

    return ;

}

TREE search(TREE tree_p, int i)
{
    while(i != tree_p->data) {
        if(i > tree_p->data) 
            tree_p = tree_p->right; 
        else 
            tree_p = tree_p->left; 
    }

    return tree_p;

}

void delete(TREE tree_p, int i) 
{
    TREE tmp = search(tree_p, i);
    TREE x, y;

    if(tmp->right != NULL && tmp->left != NULL) {
        y = successor(tmp); 
        tmp->data = y->data; 
        tmp = y; 
    }

    if(tmp->right != NULL) 
        x = tmp->right; 
    else 
        x = tmp->left; 

    if(tmp->parent->left == tmp) 
        tmp->parent->left =x; 
    else 
        tmp->parent->right = x; 

    free(tmp); 

}

int main()
{
    TREE tree = NULL; 

    FILE* fp = fopen("binary_search_tree.txt", "r"); 

    int len; 

    fscanf(fp, "%d\n", &len); 
    
    /*
    int i; 
    for(i = 0; i < len; ++i) {
        int tmp; 

        fscanf(fp, "%d", &tmp);

        
        insert(&tree, tmp); 
    } */

    // use "&tree", since when insert the first node, I need alloc some memory for it. freak..
    // so I read the first elemet, and insert the rest of data.

    
    int i; 
    int tmp; 

    fscanf(fp, "%d", &tmp); 

    tree = (TREE)malloc(sizeof(struct Tree)); 
    tree->data = tmp; 
    tree->left = tree->right = tree->parent = NULL; 

    for(i = 1; i < len; ++i) {
        fscanf(fp, "%d", &tmp); 
        insert(tree, tmp); 
    }

    printf("delete 13:\n");
    delete(tree, 13); 
    inorder_iterate(tree); 
    printf("\n");

    printf("delete 16:\n"); 
    delete(tree, 16); 
    inorder_iterate(tree); 
    printf("\n"); 

    printf("delete 5:\n"); 
    delete(tree, 5); 
    inorder_iterate(tree); 
    printf("\n"); 

    return 0; 
}

