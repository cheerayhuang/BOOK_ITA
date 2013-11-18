#include <stdio.h> 
#include <stdlib.h>

typedef struct b_tree{

    int is_leaf;
    int count; 
    int key[5]; 
    struct b_tree* child[6];
}b_tree;

b_tree* create_b_tree()
{
    b_tree *new_node = (b_tree*)malloc(sizeof(b_tree));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->is_leaf = 1;
    new_node->count = 0; 
    
    return new_node;
}

static int split_child(b_tree *root, int i, b_tree *child) 
{
    b_tree *new_node = (b_tree*)malloc(sizeof(b_tree));
    if (root == NULL) {
        return -1;
    }

    new_node->is_leaf = child->is_leaf; 

    int j = 0; 
    for (j = 0; j < 2; ++j) {
        new_node->key[j] = child->key[3+j]; 
    }

    if (!child->is_leaf) {
        
        for (j = 0; j <= 2; ++j) {
            new_node->child[j] = child->child[3+j]; 
        }
    }

    child->count = new_node->count = 2;

    for (j = root->count-1; j >= i; --j) {
        root->key[j+1] = root->key[j];
    }
    root->key[i] = child->key[2];

    for (j = root->count; j >= i+1; --j) {
        root->child[j+1] = root->child[j];
    }
    root->child[i+1] = new_node;
    root->count++;

    return 0;
}

static int insert_not_full(b_tree *root, int k) 
{
    int j = 0; 
    while (j < root->count && k > root->key[j]) {
        ++j;        
    }

    if (root->is_leaf) {
        int i = 0; 
        for(i = root->count-1; i >= j; --i) {
            root->key[i+1] = root->key[i];
        }
        root->key[j] = k; 
        ++root->count;
    }
    else {
        b_tree *tmp_node = root->child[j]; 
        if (tmp_node->count == 5) {
            split_child(root, j, tmp_node);
            if (k > root->key[j]) {
                ++j;
                tmp_node = root->child[j];
            }
        }
        insert_not_full(tmp_node, k);
    }

    return 0;
}


int insert_b_tree(b_tree **root, int k) 
{
    if (*root == NULL) {
        return -1;
    }

    int count = (*root)->count; 
    if (count == 5) {
        b_tree *new_node = create_b_tree();
        if (new_node == NULL) {
            return -1;
        }

        new_node->count = 0;
        new_node->is_leaf = 0;
        new_node->child[0] = *root;
        *root = new_node;
        split_child(*root, 0, (*root)->child[0]);
        insert_not_full(*root, k);
    }
    else {
        insert_not_full(*root, k);
    }

    return 0;
}

static int merge_node(b_tree *root, int pos) 
{
    int cur_count = root->child[pos]->count; 
    int next_count = root->child[pos+1]->count;

    root->child[pos]->key[cur_count] = root->key[pos];

    int i = cur_count+1; 
    int j = 0; 
    for (; j < next_count; ++j) {
        root->child[pos]->key[i+j] = root->child[pos+1]->key[j];
        root->child[pos]->child[i+j] = root->child[pos+1]->child[j];
    }
    root->child[pos]->child[i+j+1] = root->child[pos+1]->child[next_count];
    root->child[pos]->count = cur_count+next_count+1;

    free(root->child[pos+1]);
    i = pos+1; 
    for (; i < root->count; ++i) {
        root->child[i] = root->child[i+1];
        root->key[i-1] = root->key[i];
    }
    
    --root->count;

    return 0;
}

int delete_b_tree(b_tree *root, int k) 
{
    int j = 0; 
    while (j < root->count && k > root->key[j]) {
        ++j;
    }

    if (root->is_leaf) {
        if (k == root->key[j]) {
            int i = j; 
            for(; i < root->count-1; ++i) {
                root->key[i] = root->key[i+1];
            }
            --root->count;
        }
        else {
            return -1;
        }
    }
    else {
        if (k == root->key[j]) {
            if (root->child[j]->count >= 3) {
                int predecessor = root->child[j]->key[root->child[j]->count-1];
                delete_b_tree(root->child[j], predecessor);
                root->key[j] = predecessor;
            }
            else if (root->child[j+1]->count >= 3) {
                int successor = root->child[j+1]->key[0];
                delete_b_tree(root->child[j+1], successor);
                root->key[j] = successor;
            }
            else {
               merge_node(root, j); 
               delete_b_tree(root->child[j], k);
            }
        }
        else {
            if (root->child[j]->count >= 3) {
                delete_b_tree(root->child[j], k);
            }
            else if (root->child[j+1]->count >= 3) {
                // move up a key to root from root->child[j+1]
                // and move down a key to root->child[j] from root
                
                root->child[j]->key[root->child[j]->count] = root->key[j];
                root->key[j] = root->child[j+1]->key[0];

                root->child[j]->child[root->child[j]->count+1] = root->child[j+1]->child[0];

                int i = 0; 
                for (; i < root->child[j+1]->count-1; ++i) {
                    root->child[j+1]->key[i] = root->child[j+1]->key[i+1];
                    root->child[j+1]->child[i] = root->child[j+1]->child[i+1];
                }
                root->child[j+1]->child[root->child[j+1]->count-1] = root->child[j+1]->child[root->child[j+1]->count];

                --root->child[j+1]->count; 
                ++root->child[j]->count;

                delete_b_tree(root->child[j], k);
            }
            else if (j-1 >= 0 && root->child[j-1]->count >= 3) {
                // move up a key to root from root->child[j-1]
                // and move down a key to root->child[j] from root

                int i = root->child[j]->count; 
                for (; i > 0; --i) {
                    root->child[j]->key[i] = root->child[j]->key[i-1];
                    root->child[j]->child[i+1] = root->child[j]->child[i];
                }
                root->child[j]->child[1] = root->child[j]->child[0];
                root->child[j]->child[0] = root->child[j-1]->child[root->child[j-1]->count];
                root->child[j]->key[0] = root->key[j];
                root->key[j] = root->child[j-1]->key[root->child[j-1]->count-1];

                --root->child[j+1]->count; 
                ++root->child[j]->count;

                delete_b_tree(root->child[j], k);
            }
            else {
                merge_node(root, j);
                delete_b_tree(root->child[j], k);
            }
        }
    }

    return 0;
}

int main() 
{
    b_tree *root = NULL;
    root = create_b_tree();
    if (root == NULL) {
        fprintf(stderr, "malloc memory faild.\n"); 
        return 0;
    }

    int i = 1; 
    for(; i <= 15; ++i) {
        insert_b_tree(&root, i);
    }
    
    return 0;
}

