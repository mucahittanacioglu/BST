#include <stdio.h>
#include <stdlib.h>
typedef struct BinarySearchTree BST;
struct BinarySearchTree{
    int key;
    BST* left;
    BST* right;

};

void addToTree(int temp, BST **pTree);

int main() {
    int temp;
    BST* root=NULL;

    while(temp!= -1){
        scanf("%d",&temp);
        getchar();
        if(temp == -1)
            break;
        addToTree(temp,&root);
    }
    return 0;
}

void addToTree(int key, BST **root) {
    BST *iter= *root;
    if((*root)==NULL){
        (*root)=malloc(sizeof(BST));
        (*root)->key=key;
        (*root)->left=NULL;
        (*root)->right=NULL;
        return;
    }
    while(key < iter->key && iter->left != NULL )
        iter = iter->left;
    while(key > iter->key && iter->right != NULL )
        iter=iter->right;
    if(key < iter->key) {
        iter->left = malloc(sizeof(BST));
        iter->left->key=key;
        iter->left->left=NULL;
        iter->left->right=NULL;
        return;
    }
    if(key > iter->key) {
        iter->right = malloc(sizeof(BST));
        iter->right->key=key;
        iter->right->left=NULL;
        iter->right->right=NULL;
    }
}
