#include <stdio.h> 
#include <stdlib.h>

#define RED 1
#define BLACK 2

typedef struct red_black_tree {

    int data; 
    int color;
    struct red_black_tree* left;
    struct red_black_tree* right; 
    struct red_black_tree* parent;

}*RB_TREE;

struct red_black_tree Nil = {-1, BLACK, NULL, NULL, NULL};
struct red_black_tree* Nil_p = &Nil; 

void left_rotate(RB_TREE *rb_tree_p, RB_TREE x) 
{
    RB_TREE parent = x->parent;
    RB_TREE right_child = x->right; 
    RB_TREE tmp_p = right_child->left; 

    x->parent = right_child; 
    x->right = tmp_p; 

    tmp_p->parent = x;

    right_child->left = x; 
    right_child->parent = parent; 

    if(parent->left == x) 
        parent->left = right_child;
    else
        parent->right = right_child;

    if(parent == Nil_p) 
        *rb_tree_p = right_child; 
}

void right_rotate(RB_TREE *rb_tree_p, RB_TREE x) 
{
    RB_TREE parent = x->parent; 
    RB_TREE left_child = x->left; 
    RB_TREE tmp_p = left_child->right; 

    x->parent = left_child; 
    x->left = tmp_p; 

    tmp_p->parent = x; 

    left_child->right = x; 
    left_child->parent = parent; 

    if(parent->left == x) 
        parent->left = left_child; 
    else 
        parent->right = left_child; 

    if(parent == Nil_p) 
        *rb_tree_p = left_child; 

}

void rb_tree_insert_fixup(RB_TREE *rb_tree_p, RB_TREE x)
{
    RB_TREE uncle_node; 
    RB_TREE parent = x->parent; 

    while(parent->color == RED) {
    
        if(parent->parent->left == parent) {
            uncle_node = parent->parent->right; 

            if(uncle_node->color == RED) {
                parent->color = uncle_node->color = BLACK; 
                parent->parent->color = RED; 
                x = parent->parent; 
                parent = x->parent;

            }
            else if(parent->right ==x) {
                left_rotate(rb_tree_p, x->parent); 
                x = x->left; 
                parent = x->parent;  
            }
            else {
                parent->color = BLACK; 
                parent->parent->color = RED; 
                right_rotate(rb_tree_p, parent->parent);
            }
        }
        else {
            uncle_node = parent->parent->left; 

            if(uncle_node->color == RED) {
                parent->color = uncle_node->color = BLACK;
                parent->parent->color = RED;
                x = parent->parent; 
                parent = x->parent; 
            }
            else if(parent->left == x) {
                right_rotate(rb_tree_p, x->parent); 
                x = x->right;
                parent = x->parent; 
            }
            else {
                x->parent->color = BLACK; 
                parent->parent->color = RED; 
                left_rotate(rb_tree_p, parent->parent);
            }
        
        }
        
    }

    (*rb_tree_p)->color = BLACK; 
}

void rb_tree_insert(RB_TREE *rb_tree_p, int tmp) 
{
    RB_TREE tmp_p = (RB_TREE)malloc(sizeof(struct red_black_tree)); 
    tmp_p->color = RED; 
    tmp_p->data = tmp; 
    tmp_p->left = tmp_p->right = tmp_p->parent = Nil_p; 

    RB_TREE iter_p = *rb_tree_p; 
    RB_TREE parent = iter_p; 

    while(iter_p != Nil_p) {
    
        parent = iter_p;
        if(tmp > iter_p->data) 
            iter_p = iter_p->right; 
        else 
            iter_p = iter_p->left; 
    }

    if(parent == Nil_p) 
        *rb_tree_p = tmp_p; 
    
    tmp_p->parent = parent; 

    if(parent->data > tmp) 
        parent->left = tmp_p; 
    else 
        parent->right = tmp_p; 

  
    rb_tree_insert_fixup(rb_tree_p, tmp_p); 

}

// this function is only for find the successor.
RB_TREE rb_tree_min(RB_TREE rb_tree_p) 
{
    while(rb_tree_p->left != Nil_p) 
        rb_tree_p = rb_tree_p->left; 

    return rb_tree_p; 
}

RB_TREE rb_tree_search(RB_TREE rb_tree_p, int tmp) 
{
    while(tmp != rb_tree_p->data) {
        if(tmp > rb_tree_p->data) 
            rb_tree_p = rb_tree_p->right; 
        else 
            rb_tree_p = rb_tree_p->left; 
    }

    return rb_tree_p;

}

void rb_tree_delete_fixup(RB_TREE* rb_tree_p, RB_TREE x)
{
    RB_TREE parent = x->parent; 
    RB_TREE brother; 

    while (x->color == BLACK && x != *rb_tree_p) {
        
        if(x == parent->left) {
            brother = parent->right; 

            if(brother->color == RED) {
                parent->color = RED; 
                brother->color = BLACK; 
                left_rotate(rb_tree_p, parent); 
            }
            else if(brother->left->color == BLACK && 
                    brother->right->color == BLACK) {
                
                brother->color = RED; 
                x = x->parent; 
                parent = x->parent; 
            }
            else if(brother->left->color == RED) {
                brother->color = RED; 
                brother->left->color = BLACK; 
                right_rotate(rb_tree_p, brother); 
                brother = brother->parent; 
            }
            else {
                brother->color = parent->color; 
                brother->right->color = BLACK; 
                parent->color = BLACK; 
                left_rotate(rb_tree_p, parent);
                x = *rb_tree_p; 
            }
        
        }
        else {
            brother = parent->left; 

            if(brother->color == RED) {
                parent->color = RED; 
                brother->color = BLACK; 
                right_rotate(rb_tree_p, parent); 
            }
            else if(brother->left->color == BLACK &&
                    brother->right->color == BLACK) {
                
                brother->color = RED; 
                x = x->parent; 
            }
            else if(brother->right->color == RED) {
                brother->color = RED; 
                brother->right->color = BLACK; 
                left_rotate(rb_tree_p, brother); 
                brother = brother->parent; 
            }
            else {
               brother->color = parent->color; 
               parent->color = BLACK; 
               brother->left->color = BLACK; 

               right_rotate(rb_tree_p, parent); 
               x = *rb_tree_p; 

            }
        
        }
    }

    x->color = BLACK; 
}

void rb_tree_delete(RB_TREE *rb_tree_p, int tmp)
{
    RB_TREE search_result = rb_tree_search(*rb_tree_p, tmp); 
    

    if(search_result->left != Nil_p && search_result->right != Nil_p) {
        RB_TREE y = rb_tree_min(search_result->right); 
        search_result->data = y->data; 
        search_result = y; 
    }

    RB_TREE x; 

    if(search_result->left != Nil_p) 
        x = search_result->left; 
    else 
        x = search_result->right; 

    if(search_result->parent->left == search_result)
        search_result->parent->left = x; 
    else 
        search_result->parent->right = x; 

    x->parent = search_result->parent; 

    if(search_result->parent == Nil_p) 
        *rb_tree_p = x; 

    if(search_result->color == BLACK) 
        rb_tree_delete_fixup(rb_tree_p, x); 

    free(search_result); 
}

void rb_tree_inorder_iterate(RB_TREE rb_tree_p)
{
   if(rb_tree_p != Nil_p) {
       rb_tree_inorder_iterate(rb_tree_p->left);
       if(rb_tree_p->color == RED) 
           printf("%dR ", rb_tree_p->data); 
       else 
           printf("%dB ", rb_tree_p->data); 
       rb_tree_inorder_iterate(rb_tree_p->right); 
    }
}

int main() 
{
    RB_TREE rb_tree = Nil_p; 

    FILE *fp = fopen("red_black_tree.txt", "r"); 
    freopen("rb_tree_insert.out", "w", stdout); 

    int len; 
    int tmp[100]; 
    fscanf(fp, "%d\n", &len); 

    // insert
    int i; 
    for(i = 0; i < len; ++i) {
        fscanf(fp, "%d", &tmp[i]); 
        rb_tree_insert(&rb_tree, tmp[i]); 
        rb_tree_inorder_iterate(rb_tree); 
        printf("\n"); 
    }

    // delete
    freopen("rb_tree_delete.out", "w", stdout); 
    printf("\ndelete: \n"); 
    for(i = 0; i < len; ++i) {
        rb_tree_delete(&rb_tree, tmp[i]); 
        rb_tree_inorder_iterate(rb_tree);
        printf("\n"); 
    }
    
    fclose(fp); 

    return 0; 
}

