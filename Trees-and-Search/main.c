//
//  main.c
//  Trees and Search
//
//  Created by A Philipeit on 08/12/2016.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

typedef struct Node{
    char data;
    struct Node * left;
    struct Node * right;
}Node;

//Tree operations:
Node * tree_search(Node * root, char data);
void tree_insert(Node * root, char data);
void tree_delete(Node * root);
void tree_print_sorted(Node * root);

Node * tree_generate_from_array(char data[], int dataC);

int main(int argc, const char * argv[]) {
    char data[] = {'A','B','C','D','E','F','G','H','I','J','K'};
    
    Node * root = tree_generate_from_array(data, 11);
    
    if (tree_search(root, 'F') != NULL) {
        printf("Tree contains F\n");
    }else{
        printf("Tree does not contain F\n");
    }
    
    if (tree_search(root, 'X') != NULL) {
        printf("Tree contains X\n");
    }else{
        printf("Tree does not contain X\n");
    }
    
    tree_insert(root, 'P');
    tree_insert(root, 'Q');
    tree_insert(root, 'R');
    
    tree_print_sorted(root);
    
    printf("\n");
    
    tree_delete(root);
    
    return 0;
}

//Recursively searches through the tree,
//deciding "which way to go" at each node
//Complexity grows with number of levels in tree,
//Tree contains n elements -> O(log n)
Node * tree_search(Node * root, char data) {
    assert(root != NULL);
    
    if (root->data == data) {
        return root;
    }else if (root->data > data) {
        if (root->left != NULL) {
            return tree_search(root->left, data);
        }else{
            return NULL;
        }
        
    }else if (root->data < data) {
        if (root->right != NULL) {
            return tree_search(root->right, data);
        }else{
            return NULL;
        }
    }
    
    return NULL;
}

//Similar to search function, tries to find location for data
//Recursion to decide "which way to go" at each node
void tree_insert(Node * root, char data) {
    assert(root != NULL);
    
    if (root->data == data) {
        //Data already in the tree
        return;
        
    }else if (root->data > data) {
        if (root->left != NULL) {
            //Need to insert somewhere in left subtree
            return tree_insert(root->left, data);
        }else{
            //No left subtree, creating new leaf for data
            Node * node = (Node *) malloc(sizeof(Node));
            
            node->data = data;
            node->left = NULL;
            node->right = NULL;
            
            root->left = node;
        }
        
    }else if (root->data < data) {
        if (root->right != NULL) {
            //Need to insert somewhere in right subtree
            return tree_insert(root->right, data);
        }else{
            //No right subtree, creating new leaf for data
            Node * node = (Node *) malloc(sizeof(Node));
            
            node->data = data;
            node->left = NULL;
            node->right = NULL;
            
            root->right = node;
        }
    }
}

//Recursively delete all children and then root
void tree_delete(Node * root) {
    assert(root != NULL);
    
    if (root->left != NULL) {
        tree_delete(root->left); //Delete left subtree
        root->left = NULL;
    }
    
    if (root->right != NULL) {
        tree_delete(root->right); //Delete right subtree
        root->right = NULL;
    }
    
    free(root); //Finally delete root
}

//Traversal order: Left Visit Right (recursively)
//Leave space between data
void tree_print_sorted(Node * root) {
    assert(root != NULL);
    
    if (root->left != NULL) {
        tree_print_sorted(root->left);
        
        printf(" ");
    }
    
    printf("%c", root->data);
    
    if (root->right != NULL) {
        printf(" ");
        
        tree_print_sorted(root->right);
    }
}

//Need to find optimal order to insert items into tree:
//Sort array (Function is faster if already sorted)
//Make middle element root
//Repeat recursively for left and right subarray
Node * tree_generate_from_array(char data[], int dataC) {
    //Sort array (could be much more efficient):
    for (int i = 1; i < dataC; i++) {
        char d1 = data[i - 1];
        char d2 = data[i];
        
        if (d1 <= d2) continue;
        
        data[i - 1] = d2;
        data[i] = d1;
        
        if (i > 1) i -= 2;
    }
    
    //Generate root node:
    Node * root = (Node *) malloc(sizeof(Node));
    root->data = data[(int) floor(dataC / 2.0)]; //Pick middle of sorted array for root
    
    //Add left and right child:
    if (dataC > 1) {
        root->left = tree_generate_from_array(data, floor(dataC / 2.0));
    }else{
        root->left = NULL;
    }
    
    if (dataC > 2) {
        root->right = tree_generate_from_array(data + sizeof(char) * (int)ceil(dataC / 2.0), floor(dataC / 2.0));
    }else{
        root->right = NULL;
    }
    
    
    return root;
}
