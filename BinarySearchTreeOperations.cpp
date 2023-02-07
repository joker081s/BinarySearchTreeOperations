#include<iostream>
#include<stdlib.h>
#include<stack>
using namespace std;

struct node* createNode(int);
void insertNode(struct node **, int);
struct node* searchNode(struct node **, int);
void deleteNode(struct node **, int);
void operations();
void preOrderTraversal(struct node**);

struct node {
    int data;
    struct node *right;
    struct node *left;
};

int main() {

    // creation of eight nodes;
    struct node *a = createNode(60);
    struct node *b = createNode(80);
    struct node *c = createNode(40);
    struct node *d = createNode(20);
    struct node *e = createNode(50);
    struct node *f = createNode(70);
    struct node *g = createNode(10);
    struct node *h = createNode(30);

    // assigning child nodes to root node (a);
    a->right = b;
    a->left = c;

    // assigning child nodes to c node;
    c->left = d;
    c->right = e;

    // assigning child node to b node;
    b->left = f;

    // assigning child nodes to d node;
    d->left = g;
    d->right = h;

    cout<<"=========================================================\n";

    int n, data;
    operations();
    while(1) {
        cout<<"Enter your choice : ";
        cin>>n;
        if (n == 5) {
            cout<<"Exiting program...\n";
            break;
        }
        switch(n) {
            case 0 : operations(); break;
            case 1 :
                cout<<"Enter the data to insert in the node : ";
                cin>>data;
                insertNode(&a, data);
                break;
            case 2 :
                cout<<"Enter the data to search in the tree : ";
                cin>>data;
                struct node *temp;
                temp = searchNode(&a, data);
                if (temp != NULL) {
                    cout<<"Parent Node have data : "<<temp->data<<endl;
                } else if (temp == NULL && data == a->data) {
                    cout<<"Data found but it doesn't have parent node\n";
                } else {
                    cout<<"Data isn't found in the tree\n";
                }
                cout<<"=========================================================\n";
                break;
            case 3 :
                cout<<"Enter the data to delete in the tree : ";
                cin>>data;
                deleteNode(&a, data);
                cout<<"=========================================================\n";
                break;
            case 4 :
                cout<<"Traversing the tree :\n";
                preOrderTraversal(&a);
                break;
            default :
                cout<<"There is no such operation available\n";
                cout<<"=========================================================\n";
                break;
        }
    }

    cout<<"=========================================================\n";

    return 0;

}

struct node* createNode(int i) {
    struct node *z;
    z = (struct node *) malloc(sizeof(struct node));
    z->data = i;
    z->right = z->left = NULL;
    return z;
}

void insertNode(struct node **i, int info) {
    struct node *temp, *z;
    temp = *i;
    z = (struct node*) malloc(sizeof(struct node));
    z->data = info;
    z->left = z->right = NULL;
    while(temp != NULL) {
        if (temp->data == info) {
            cout<<"Insertion of node isn't possible due to duplication of data."<<endl;
            cout<<"=========================================================\n";
            return;
        }
        if (info < temp->data) {
            if (temp->left == NULL) {
                temp->left = z;
                cout<<"Insertion of node is successful\nParent node of inserting node has data : "<<temp->data<<"\nNode inserted at left of parent node"<<endl;
                cout<<"=========================================================\n";
                return;
            }
            temp = temp->left;
        } else {
            if (temp->right == NULL) {
                temp->right = z;
                cout<<"Insertion of node is successful\nParent node of inserting node has data : "<<temp->data<<"\nNode inserted at right of parent node"<<endl;
                cout<<"=========================================================\n";
                return;
            }
            temp = temp->right;
        }
    }
    cout<<"Code must not be reached here\n";
    cout<<"=========================================================\n";
}

struct node* searchNode(struct node **i, int info) {
    struct node *z, *parNode;
    z = *i;
    parNode = NULL;
    if (z == NULL) {
        cout<<"Searching isn't possible\nTree is empty!!"<<endl;
        return NULL;
    }
    while(z != NULL) {
        if (info == z->data) {
            cout<<"Data found (data : "<<info<<")"<<endl;
            return parNode;
        }
        parNode = z;
        if (info < z->data) {
            z = z->left;
        } else {
            z = z->right;
        }
    }
    cout<<"Data not found :("<<endl;
    return NULL;
}

void deleteNode(struct node **i, int info) {
    struct node *z, *parNode, *ptr;
    z = *i;

    parNode = searchNode(i, info);

    // if parent node is null but data to be deleted in root node
    if (parNode == NULL && info == z->data) {
        if (z->right == NULL && z->left == NULL) {
            *i = NULL;
            cout<<"Tree is now empty!!\n";
            return;
        }
        if (z->right == NULL && z->left != NULL) {
            *i = z->right;
            cout<<"Root Node deleted successfully with data ("<<info<<")\n";
            return;
        }
        if (z->right != NULL && z->left == NULL) {
            *i = z->left;
            cout<<"Root Node deleted successfully with data ("<<info<<")\n";
            return;
        }
        if (z->right != NULL && z->left != NULL) {
            struct node *tempPtr;
            tempPtr = z->right;
            while(tempPtr->left != NULL) {
                tempPtr = tempPtr->left;
            }
            tempPtr->left = z->left;
            cout<<"Root Node deleted successfully with data ("<<info<<")\n";
            return;
        }
    }
    if (parNode == NULL) {       // if parent node is null
        cout<<"Can't able to delete the node"<<endl;
        return;
    }

    // parent node is not null then set the ptr variable to the data to be deleted
    if (parNode != NULL)
        ptr = (info < parNode->data) ? parNode->left : parNode->right;

    // if left and right of ptr both have null value
    if (ptr->left == NULL && ptr->right == NULL) {
        if (info < parNode->data) {
            parNode->left = NULL;
        } else {
            parNode->right = NULL;
        }
        cout<<"Data deleted successfully\nData deleted : "<<info<<"\nParent Node of data deleted have data : "<<parNode->data<<endl;
        return;
    }

    // if left of ptr have null but right of ptr is not null
    if (ptr->left == NULL && ptr->right != NULL) {
        if (info < parNode->data) {
            parNode->left = ptr->right;
        } else {
            parNode->right = ptr->right;
        }
        cout<<"Data deleted successfully\nData deleted : "<<info<<"\nParent Node of data deleted have data : "<<parNode->data<<endl;
        return;
    }

    // if right of ptr have null but left of ptr is not null
    if (ptr->left != NULL && ptr->right == NULL) {
        if (info < parNode->data) {
            parNode->left = ptr->left;
        } else {
            parNode->right = ptr->left;
        }
        cout<<"Data deleted successfully\nData deleted : "<<info<<"\nParent Node of data deleted have data : "<<parNode->data<<endl;
        return;
    }

    // if left and right of ptr both have not null 
    if (ptr->left != NULL && ptr->right != NULL) {
        if (info < parNode->data) {
            parNode->left = ptr->right;
        } else {
            parNode->right = ptr->right;
        }
        struct node *temp;
        temp = ptr->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        temp->left = ptr->left;
        cout<<"Data deleted successfully\nData deleted : "<<info<<"\nParent Node of data deleted have data : "<<parNode->data<<endl;
        return;
    }
    cout<<"Code must not be reached here\n";
}

void preOrderTraversal(struct node **i) {
    struct node *z;
    z = *i;

    stack<struct node*> stack;
    stack.push(NULL);

    while(z != NULL) {
        cout<<"\t\t     "<<z->data<<endl;
        if (z->right != NULL) {
            stack.push(z->right);
        }
        if (z->left != NULL) {
            z = z->left;
        } else {
            z = stack.top();
            stack.pop();
        }
    }

    cout<<"=========================================================\n";

}

void operations() {
    cout<<"Operations : \n\t0 -> to print operations\n\t1 -> to insert node\n\t2 -> to search data\n\t3 -> to delete node\n\t4 -> to traversal the tree\n\t5 -> to exit from program"<<endl;
    cout<<"=========================================================\n";
}