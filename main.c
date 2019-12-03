#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    int data; //node will store an integer
    struct node *right_child; // right child
    struct node *left_child; // left child
};

struct node* search(struct node *root, int x)
{
    if(root==NULL || root->data==x) //if root->data is x then the element is found
        return root;
    else if(x>root->data) // x is greater, so we will search the right subtree
        return search(root->right_child, x);
    else //x is smaller than the data, so we will search the left subtree
        return search(root->left_child,x);
}
int total=0;//variable to hold how many different same numbers sequence will yield same BST
int sizeOfBst=0;//variable that holds how many key BST have.
int keys1[1000]={0};//keys1 and keys2 holds given key sequence to calculate permutations.
int keys2[1000]={0};
int indexForKeys = 0;//to dynamicially change keys arrays
//this function checks whether given 2 input sequence will yield same BST
int isSameBST(int *permutedSequence, int *originalSequence, int n)
{

    // if no element is present in the array, return true
    if (n == 0)
        return 1;

    // if root differs,
    // return false
    if (permutedSequence[0] != originalSequence[0])
        return 0;

    // if array contains only one key, return true
    if (n == 1)
        return 1;

    // take four auxiliary arrays of size n-1 each (as maximum
    // keys in left or right subtree can be n-1)
    int leftPermutedSequence[n - 1], rightPermutedSequence[n - 1], leftOriginalSequence[n - 1], rightOriginalSequence[n - 1];

    int k = 0, l = 0, m = 0, o = 0;


    // process remaining keys and divide them into two groups
    for (int i = 1; i < n; i++)
    {
        // leftPermutedSequence[] will contain left subtree of permutedSequence
        if (permutedSequence[i] < permutedSequence[0])
            leftPermutedSequence[k++] = permutedSequence[i];

            // rightPermutedSequence[] will contain right subtree of permutedSequence
        else
            rightPermutedSequence[l++] = permutedSequence[i];

        // leftOriginalSequence[] will contain left subtree of originalSequence
        if (originalSequence[i] < originalSequence[0])
            leftOriginalSequence[m++] = originalSequence[i];

            // rightOriginalSequence[] will contain right subtree of originalSequence
        else
            rightOriginalSequence[o++] = originalSequence[i];
    }


    // return false if number of nodes in left subtree of both sequence differs
    if (k != m)
        return 0;


    // return false if number of nodes in right subtree of both sequence differs
    if (l != o)
        return 0;

    // check left subtree and right subtree recursively
    return isSameBST(leftPermutedSequence, leftOriginalSequence, k) &&
           isSameBST(rightPermutedSequence, rightOriginalSequence, l);
}

void print(int *num, int n)
{
    int i;
    for ( i = 0 ; i < n ; i++)
        printf("%d ", num[i]);
    printf("\n");
}
//simple function that swaps the value pointed by x-y
void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
//this function generates all the permutation of originalSequence sequence
void permute(int *permuteSequence, int swapVal, int r, int * originalSequence,int flag)
{
    int i;
    if (swapVal == r) {
        if(isSameBST(originalSequence, permuteSequence, sizeOfBst)){
            if(flag)
                print(permuteSequence, sizeOfBst);
            total++;
        }

    }else
    {
        for (i = swapVal; i <= r; i++)
        {
            swap((permuteSequence + swapVal), (permuteSequence + i));

            permute(permuteSequence, swapVal + 1, r, originalSequence,flag);

            swap((permuteSequence + swapVal), (permuteSequence + i));
        }
    }
}


//function to find the minimum value in a node
struct node* find_minimum(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left_child != NULL) // node with minimum value will have no left child
        return find_minimum(root->left_child); // left most element will be minimum
    return root;
}

//function to create a node
struct node* new_node(int x)
{
    struct node *tempNode;
    tempNode = malloc(sizeof(struct node));
    tempNode->data = x;
    tempNode->left_child = NULL;
    tempNode->right_child = NULL;

    return tempNode;
}
//function to insert node
struct node* insert(struct node *root, int x)
{

    //searching for the place to insert
    if(root==NULL)
        return new_node(x);
    else if(x>root->data) // x is greater. Should be inserted to right
        root->right_child = insert(root->right_child, x);
    else // x is smaller should be inserted to left
        root->left_child = insert(root->left_child,x);
    return root;
}

// function to delete a node
struct node* delete(struct node *root, int x)
{
    //searching for the item to be deleted
    if(root==NULL)
        return NULL;
    if (x>root->data)
        root->right_child = delete(root->right_child, x);
    else if(x<root->data)
        root->left_child = delete(root->left_child, x);
    else
    {
        //No Children
        if(root->left_child==NULL && root->right_child==NULL)
        {
            free(root);
            return NULL;
        }

            //One Child
        else if(root->left_child==NULL || root->right_child==NULL)
        {
            struct node *temp;
            if(root->left_child==NULL)
                temp = root->right_child;
            else
                temp = root->left_child;
            free(root);
            return temp;
        }

            //Two Children
        else
        {
            struct node *temp = find_minimum(root->right_child);
            root->data = temp->data;
            root->right_child = delete(root->right_child, temp->data);
        }
    }
    return root;
}
void updateKey(int x){
    keys1[indexForKeys]=x;
    keys2[indexForKeys]=x;
    indexForKeys++;
}
void updateKeysWithNewTree(struct node *root,int indexFrom){
    if(root!=NULL) // checking if the root is not null
    {
        updateKey(root->data);
        updateKeysWithNewTree(root->left_child,++indexFrom);
        updateKeysWithNewTree(root->right_child,++indexFrom);

    }
}

void updateKeys(int *key1,int* key2,struct node *root){
    memset(key1,0,1000);
    memset(key2,0,1000);
    updateKeysWithNewTree(root,0);
}

//function that prints tree in order
void inorder(struct node *root)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left_child); // visiting left child
        printf(" %d ", root->data); // printing data at root
        inorder(root->right_child);// visiting right child
    }
}

int main()
{

    struct node *root=NULL;
    int temp =11,temp2=0;
    int initRoot = 0;
    int keyIndex = 0;//variable to store input sequence.
    printf("Please Enter Sequence(To finish enter -1):\n ");
    while(temp != -1){

        scanf("%d",&temp);
        getchar();

        keys1[keyIndex]=temp;// here we save sequence in 2 different array to find permutations
        keys2[keyIndex]=temp;

        keyIndex++;
        sizeOfBst++;

        if(initRoot == 0){
            root = new_node(temp);//for first item addition.
            initRoot=1;
            continue;
        }
        if(temp == -1)
            break;
       sizeOfBst++;
        insert(root,temp);
    }
    sizeOfBst = sizeOfBst/2;
    temp=0;

    while(temp!= 7){
        printf("\nPlease select a property below:\n1.)Delete a key.\n2.)Insert new key\n3.)Print list inorder\n4.)Find the sequences that yields same BST\n5.)Print number of sequences that yields same BST(Its slow on high number of key)\n6.)See current assumed input sequences(it can find option 4-5 in runtime)\n7.)Exit.\n");
        scanf("%d",&temp);
        getchar();
        switch(temp){
            case 1:{
                printf("Enter key to delete:");
                scanf("%d",&temp2);
                getchar();
                root =  delete(root,temp2);
                printf("%d deleted succesfully.\n",temp2);

                sizeOfBst--;
                updateKeys(keys1,keys2,root);//updating keys to dynamically find how many different sequences yields same bst
                indexForKeys=0;
                break;
            }
            case 2:{
                printf("Enter key to insert:");
                scanf("%d",&temp2);
                getchar();
                if(insert(root,temp2) != NULL)
                    printf("%d succesfully added.",temp2);
                else
                    printf("Couldn't add new key:%d",temp2);

                sizeOfBst++;
                updateKeys(keys1,keys2,root);//updating keys to dynamically find how many different sequences yields same bst
                indexForKeys=0;
                break;
            }
            case 3:{
                inorder(root);
                break;
            }
            case 4:{
                permute(keys1,0,sizeOfBst-1,keys2,1);
                total=0;
                break;
            }
            case 5:{
                permute(keys1,0,sizeOfBst-1,keys2,0);
                printf("%d number of differrent sequences yields same BST.\n",total);
                total=0;
                break;
            }
            case 6:{
                printf("Sizeof BSt:%d\nCurrent assumed sequence:",sizeOfBst);
                print(keys1,sizeOfBst);
                printf("\n");
            }
            default:
                continue;
        }
    }










    return 0;
}