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
    RB_TREE r_child = x->right; 
    RB_TREE grandson = r_child->left; 

    x->parent = r_child; 
    x->right = grandson; 

    r_child->left = x; 
    r_child->parent = parent; 

    grandson->parent = x; 

    if(parent == Nil_p) 
        *rb_tree_p = r_child; 
    else if(parent->left == x) 
        parent->left = r_child; 
    else parent->right = r_child; 


}

void right_rotate(RB_TREE *rb_tree_p, RB_TREE x) 
{
    RB_TREE parent = x->parent;
    RB_TREE l_child = x->left; 
    RB_TREE grandson = l_child->right;

    x->parent = l_child; 
    x->left = grandson; 

    l_child->right = x; 
    l_child->parent = parent; 

    grandson->parent = x; 

    if(parent == Nil_p) 
        *rb_tree_p = l_child; 
    else if(parent->left == x) 
        parent->left = l_child; 
    else parent->right = l_child;
}

void rb_tree_insert_fixup(RB_TREE *rb_tree_p, RB_TREE x)
{
    RB_TREE parent = x->parent; 
    RB_TREE uncle; 
    
    while(parent->color == RED) {
        
        if(parent->parent->left == parent) {
            uncle = parent->parent->right; 

            if(uncle->color == RED) {
                uncle->color = parent->color = BLACK;
                parent->parent->color =RED; 
                x = parent->parent; 
                parent = x->parent; 
            }
            else if(parent->right == x) {
                
                left_rotate(rb_tree_p, parent); 
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
            uncle = parent->parent->left; 

            if(uncle->color == RED) {
            
                uncle->color = parent->color = BLACK; 
                parent->parent->color = RED; 
                x = parent->parent; 
                parent = x->parent; 
            }   
            else if(parent->left == x) {

                right_rotate(rb_tree_p, parent); 
                x = x->right; 
                parent = x->parent; 
            }
            else {
                
                parent->color = BLACK; 
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
    tmp_p->parent = tmp_p->left = tmp_p->right = Nil_p; 


    RB_TREE iter = *rb_tree_p; 
    RB_TREE parent = Nil_p; 

    while(iter != Nil_p) {

        parent = iter; 
        if(tmp > iter->data) 
            iter = iter->right; 
        else 
            iter = iter->left; 
            
    }

    if(parent == Nil_p) 
        *rb_tree_p = tmp_p; 
    else if(parent->data < tmp) 
        parent->right = tmp_p; 
    else 
        parent->left = tmp_p; 

    tmp_p->parent = parent; 

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

    while(x->color == BLACK && x != *rb_tree_p) {
        
        if(parent->left == x) {
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
                if(x->color == RED) {
                    x->color = BLACK; 
                    break; 
                }
            
            }
            else if(brother->left->color == RED) {
                
                brother->left->color = BLACK; 
                brother->color = RED; 
                right_rotate(rb_tree_p, brother); 
                
            }
            else {

                brother->color = parent->color; 
                parent->color = BLACK; 
                brother->right->color = BLACK; 
                left_rotate(rb_tree_p, parent); 
                x = *rb_tree_p ;
            
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
                parent = x->parent; 
                if(x->color == RED) {
                    x->color = BLACK; 
                    break;
                }
            }
            else if(brother->right->color == RED) {
                brother->right->color = BLACK;
                brother->color = RED; 
                left_rotate(rb_tree_p, brother); 
            }
            else{
                brother->color = parent->color; 
                parent->color = BLACK; 
                brother->left->color = BLACK;
                right_rotate(rb_tree_p, parent); 
                x = *rb_tree_p; 
            }

        
        }
    }

    //x->color = BLACK;
}

void rb_tree_delete(RB_TREE *rb_tree_p, int tmp)
{
    RB_TREE tmp_p = rb_tree_search(*rb_tree_p, tmp); 

    if(tmp_p->right != Nil_p && tmp_p->left != Nil_p) {
        RB_TREE s = rb_tree_min(tmp_p->right); 
        tmp_p->data = s->data; 
        tmp_p = s; 
    }

    RB_TREE x; 
    if(tmp_p->left != Nil_p) 
        x = tmp_p->left; 
    else 
        x = tmp_p->right; 
    
    if(tmp_p->parent == Nil_p) 
        *rb_tree_p = x; 
    else if(tmp_p->parent->left == tmp_p)
        tmp_p->parent->left = x;
    else 
        tmp_p->parent->right = x; 

    x->parent = tmp_p->parent; 

    if(tmp_p->color == BLACK && x->color != RED) 
        rb_tree_delete_fixup(rb_tree_p, x); 

    else x->color = BLACK;

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

