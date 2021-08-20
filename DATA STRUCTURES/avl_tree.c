/*
    MILIND SHARMA
    1:00 AM
    21-07-2021
*/

#include <stdio.h>
#include <stdlib.h>

struct node{
   int data;
   int height;
   struct node* right;
   struct node* left;
};

struct node* create(int data)
{
    struct node* temp;
    temp=(struct node*)malloc(sizeof(struct node));
    temp->right=NULL;
    temp->left=NULL;
    temp->height=0;
    temp->data=data;
    return temp;
}

int max(int a,int b)
{
    if(a>=b)return a;
    return b;
}

int height(struct node* temp)
{
    if(temp==NULL)return -1;
    else return temp->height;
}

int balance(struct node* temp)
{
    return height(temp->left)-height(temp->right);
}

struct node* inorder_succ(struct node* root)
{
    if(root->right!=NULL)
    {
        struct node* temp=root->right;
        while(temp->left!=NULL)
        {
            temp=temp->left;
        }
        root=temp;
    }
    return root;
}

struct node* LL(struct node* temp)
{
    struct node* x=temp->left;
    struct node* y=x->right;
    x->right=temp;
    temp->left=y;

    temp->height=1+max(height(temp->right),height(temp->left));
    x->height=1+max(height(x->right),height(x->left));

    return x;
}

struct node* RR(struct node* temp)
{
    struct node* x=temp->right;
    struct node* y=x->left;
    x->left=temp;
    temp->right=y;

    temp->height=1+max(height(temp->right),height(temp->left));
    x->height=1+max(height(x->right),height(x->left));

    return x; 
}

struct node* RL(struct node* temp)
{
    temp->right=LL(temp->right);
    temp=RR(temp);
    return temp;
}

struct node* LR(struct node* temp)
{
    temp->left=RR(temp->left);
    temp=LL(temp);
    return temp;
}

struct node* insert(int data,struct node* root)
{
    if(root==NULL)
    {
        root=create(data);
    }

    else if(data>root->data)
    {
        root->right=insert(data,root->right);
    }

    else if(data<root->data)
    {
        root->left=insert(data,root->left);
    }

    root->height=1+max(height(root->left),height(root->right));
    
    if(balance(root)>1 && root->left->data>data)
    {
        root=LL(root);
    }

    else if(balance(root)>1 && root->left->data<data)
    {
        
        root=LR(root);
    }

    else if(balance(root)<-1 && root->right->data<data)
    {
        root=RR(root);
    }

    else if(balance(root)<-1 && root->right->data>data)
    {
        root=RL(root);
    }

    return root;
}

struct node* delete(int data,struct node* root)
{
    if(root==NULL)
        printf("The element does not exist or the tree is empty........\n");
    else if(data>root->data)
        root->right=delete(data,root->right);
    else if(data<root->data)
        root->left=delete(data,root->left);
    else
    {
        if(root->right==NULL && root->left==NULL)
        {
            struct node* temp=root;
            root=NULL;
            free(temp);
        }

        else if(root->right==NULL || root->left==NULL)
        {
            struct node* temp=(root->left==NULL)?root->right:root->left;
            *root=*temp;
            free(temp);
        }
        else
        {
            struct node* temp=inorder_succ(root);
            root->data=temp->data;
            root->right=delete(root->data,root->right);
        }
    }
    if(root==NULL)return root;

    root->height=1+max(height(root->left),height(root->right));

    if(balance(root)>1 && balance(root->left)>=0)
        root=LL(root);
    else if(balance(root)>1 && balance(root->left)<0)
        root=LR(root);
    else if(balance(root)<-1 && balance(root->right)<=0)
        root=RR(root);
    else if(balance(root)<-1 && balance(root->right)>0)
        root=RL(root);
    
    return root;
}

void inorder(struct node* temp)
{
    if(temp==NULL)return;
    inorder(temp->left);
    printf("%d HEIGHT(%d), ",temp->data,temp->height);
    inorder(temp->right);
}

void preorder(struct node* temp)
{
    if(temp==NULL)return;
    printf("%d HEIGHT(%d), ",temp->data,temp->height);
    inorder(temp->left);
    inorder(temp->right);
}

void choice()
{
    printf("AVL TREE MENU:\n");
    printf("Enter 1 to create a new tree\n");
    printf("Enter 2 to add an element to the tree\n");
    printf("Enter 3 to delete an element from the tree\n");
    printf("Enter 4 to print inorder traversal of the tree\n");
    printf("Enter 5 to print preorder travelsal of the tree\n");
    printf("Enter 6 to exit\n");
}

int main(){

    struct node* root=NULL;
    int select;
    while(1)
    {
        choice();
        printf("Enter your choice:\n");
        scanf("%d",&select);
        if(select==1)
        {
            root=NULL;
            int n;
            printf("Enter the number of elements in the AVL tree:\n");
            scanf("%d",&n);
            printf("Enter the elements of the tee:\n");
            for(int i=1;i<=n;i++)
            {
                int temp;
                scanf("%d",&temp);
                root=insert(temp,root);
            }
        }
        else if(select==2)
        {
            printf("Enter the element you want to add to the tree:\n");
            int temp;
            scanf("%d",&temp);
            root=insert(temp,root);
        }
        else if(select==3)
        {
            printf("Enter the element you want to delete from the tree:\n");
            int temp;
            scanf("%d",&temp);
            root=delete(temp,root);
        }
        else if(select==4)
        {
            inorder(root);
            printf("\n");
        }
        else if(select==5)
        {
            preorder(root);
            printf("\n");
        }
        else if(select==6)
        {
            printf("Exiting...\n");
            break;
        }
        else
        {
            printf("Enter a valid choice between [1-6]\n");
        }
    }
return 0;
}