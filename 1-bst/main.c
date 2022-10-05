#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libcompact.h"

// a.
typedef struct BSTNode {
    I32 val;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// b.
typedef struct {
    BSTNode* root;
    size_t size;
} BST;

// c.
void add_node(BST* bst, BSTNode* node) {
    BSTNode* parent = NULL;
    BSTNode* current = bst->root;
    bool side = false;
    while(current != NULL) {
        parent = current;
        side = node->val < current->val;
        current = side ? current->left : current->right;
    }
    if(parent == NULL) {
        bst->root = node;
    } else {
        if(side) parent->left = node;
        else parent->right = node;
    }
}
void add_val(BST* bst, I32 val) {
    BSTNode* node = calloc(1, sizeof *node);
    node->val = val;
    add_node(bst, node);
    bst->size++;
}

// d.
BST* make_bst(I32* arr, size_t len) {
    BST* bst = calloc(1, sizeof *bst);
    for(size_t i = 0; i < len; i++) {
        add_val(bst, arr[i]);
    }
    return bst;
}

// e. Remove a value from the tree. If possible the left child should be
// moved to the position occupied by the removed value. This may cause
// additional issues that need to be fixed. The function should return
// the number of values removed (0 or 1). Beware of memory leaks.

/*BSTNode* find_node(BST* bst, I32 val) {
    BSTNode* n = bst->root;
    while(n != NULL && n->val != val) {
        n = val < n->val ? n->left : n->right;
    }
    return n;
}*/

U8 remove_val(BST* bst, I32 val) {
    BSTNode* parent = NULL;
    BSTNode* node = bst->root;
    while(node != NULL && node->val != val) {
        parent = node;
        node = val < node->val ? node->left : node->right;
    }
    if(node == NULL) return 0;
    if(node->left != NULL) {
        if(parent == NULL) {
            bst->root = node->left;
        } else if(node == parent->right) {
            parent->right = node->left;
        } else {
            parent->left = node->left;
        }
        if(node->right != NULL) {
            add_node(bst, node->right);
        }
    } else if(node->right != NULL) {
        if(parent == NULL) {
            bst->root = node->right;
        } else if(node == parent->right) {
            parent->right = node->right;
        } else {
            parent->left = node->right;
        }
    }

    free(node);
    bst->size--;
    return 1;
}

// f.
void free_node(BSTNode* node) {
    if(node == NULL) return;
    free_node(node->left);
    free_node(node->right);
    free(node);
}
void free_bst(BST* bst) {
    free_node(bst->root);
    free(bst);
}

// Testing
void print_node(BSTNode* node) {
    if(node == NULL) {
        P("NULL");
        return;
    }
    P("( %d, left: ", node->val);
    print_node(node->left);
    P(", right: ");
    print_node(node->right);
    P(" )");
}
void print_bst(BST* bst) {
    if(bst == NULL) {
        Pn("NULL");
        return;
    }
    P("{ size: %zu, root: ", bst->size);
    print_node(bst->root);
    P(" }\n");
}

int main() {
    BST* bst = make_bst((I32[]){ 3, 8, 2, 7, 3, 10}, 6);
        print_bst(bst);
    add_val(bst, 200);
    add_val(bst, 6);
        print_bst(bst);
    remove_val(bst, 3);
        print_bst(bst);
    remove_val(bst, 8);
        print_bst(bst);
    remove_val(bst, 7);
        print_bst(bst);
    free_bst(bst);
    bst = NULL;
        print_bst(bst);
    return 0;
    // valgrind pass
}
