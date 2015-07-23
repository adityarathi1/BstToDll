#include<iostream.h>
#include<stdlib.h>
#define BUFSIZE 1024
#define NALLOC(n,type) ((type*)malloc(n*sizeof(type)))

struct node {

    short data;
    struct node *left;
    struct node *right;
};
typedef struct node Node;

/*
building a hardcoded tree as

              15
            /   \
          10     25
         /  \    / \
        4    12 20  30
                   / \
                  29 31

15 10 25 4 12 20 30 13 29 31
*/


void buid_specific_tree(Node **root,short data){
    if( NULL == *root){
        (*root) = NALLOC(1,Node);
        (*root)->data = data;
        (*root)->left = NULL;
        (*root)->right = NULL;
        
    }else{

        if((*root)->data > data){
            buid_specific_tree(&(*root)->left,data);
        }else{
            buid_specific_tree(&(*root)->right,data);
        }
    }
}
void convert(Node *root){
    static Node * prev;
    if(NULL == root){
        return ;
    }
    convert(root->left);
    convert(root->right);

    if(NULL != prev){
        prev->right = root;
        root->left = prev;
    }
    
    prev = root;
}
Node *tree2DLL(Node *root){
    convert(root);
    root->right = NULL;
    while(root->left){
        
        root = root->left;
    }
    return root;
}
void preorder (Node * root){
    if (NULL == root){
        return ;
    }
    std::cout<<root->data<<"=>";
    preorder(root->left);
    preorder(root->right);

}
int main(int argc, char **argv){

    Node *root = NULL;;
    int data,i;
    Node *buffer[BUFSIZE];
    for(int i =1;i < argc ;){
        data = (short)atoi(argv[i++]);
        buid_specific_tree(&root,data);
    }
    preorder(root);
    Node *ListHead ;
    ListHead = tree2DLL(root);
    Node *ListTail = NULL;
    std::cout<<"\nPrint List";
    while((ListHead != NULL) || (ListTail != NULL)){
        if(ListHead != NULL){
            std::cout<<ListHead->data<<"=>";
            ListTail = ListHead;
            ListHead = ListHead->right;
        }else{
            std::cout<<ListTail->data<<"<=";
            ListTail = ListTail->left;
        }
    }
    return 0;
}
