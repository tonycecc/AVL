#include <iostream>
using namespace std;
// Anthony Cecchini 

// In this project, implement an AVL tree with one function
// -- AVL_Insert: insert a new node into AVL tree
//
// In the main function, we will insert 10 nodes into AVL
// Then, we will enumarate these nodes based on in-order traverse
// The enumeration function has been implemented for you


class Node {

public:

    int SID = 0;

    Node* left = NULL;

    Node* right = NULL;

    Node* parent = NULL;

    //int balanceFactor = 0;

    int height = -1;

};


class AVL {

public:


    void AVL_Enumerate(); // enumerate nodes based on in-order traverse

    void AVL_Insert(Node* x); // insert a new node x into AVL tree

    void rebalance(Node* x);

    Node* rightRotate(Node* x); // Rotate right

    Node* leftRotate(Node* x); // Rotate left

private:

    Node* root = NULL;
};
// Get the height of the node
int height(Node* x){
    // if x is null then the height is -1
    if(x == NULL){
        return -1;

    } else {
        // return the height of x
        return x->height;
    }
}

// Update the height of the node
void updateHeight(Node* x){
    // height of x left >= height of x right
    if(height(x->left) >= height(x->right)){
        // update the height of x with the height of x->left + 1
        x->height = height(x->left)+ 1;

    } else {
        // update the height of x with the height of x->right +1
        x->height = height(x->right) + 1;
    }


}

// Rotation right
Node* AVL::rightRotate(Node* x){
    // Create node y that is x's left child
    Node *y = x->left;
    // the parent of y is the parent of x
    y->parent = x->parent;
    // is the parent null?
    if(y->parent == NULL){
        // If the parent of y is null then the root is y
        root = y;
    } else {
        // check if the parent left is x
        if(y->parent->left == x){
            // if so then y's parents left child is y
            y->parent->left = y;
        } else if(y->parent->right == x){
            // y's parents right child is y
            y->parent->right = y;
        }

    }
    // rotates
    // x's left child is y's right child
    x->left = y->right;
    // if x's left is null then x's left parent is its self
    if(x->left != NULL){
        x->left->parent = x;
    }
    // y's right is x
    y->right = x;
    // x's parent is y
    x->parent = y;


    // Update the heights of the nodes
    updateHeight(y);
    updateHeight(x);

    // Return new root which is y
    return y;
}

Node* AVL::leftRotate(Node* x){
    // Create node y that is x's right child
    Node* y = x->right;
    // y's parent is equal to x's parent
    y->parent = x->parent;
    // If the parent of y is null then it is the root
    if(y->parent == NULL){
        // update the root
        root = y;
    } else {  // if it is not the root then
        // if y's parents left child is x then y's parents left child will be y
        if(y->parent->left == x){
            // update y's parents left child is y
            y->parent->left = y;
        } else if(y->parent->right == x){  // if y's parents right child is x
            // then y's parents right child is y
            y->parent->right = y;
        }
    }
    // rotate
    // x's right is y's left
    x->right = y->left;
    // if the right is null then the parent will be x
    if(x->right != NULL){
        // x's right parent is x;
        x->right->parent = x;
    }
    // y's left child is x
    y->left = x;
    // x's parent is y
    x->parent = y;

     // update the heights
    updateHeight(x);

   updateHeight(y);
    // return new root
    return y;
}



void enumerate(Node* ptr) { // in-order traverse

    if (ptr->left != NULL) {

        enumerate(ptr->left);

    }
    cout << ptr->SID << ' ';

    if (ptr->right != NULL) {

        enumerate(ptr->right);
    }
}

void AVL::AVL_Enumerate() {

    enumerate(root);
}
Node* insert(Node* root, Node* x) { // insert a node to a tree with root
    // if the root is null then the node x is the root
    if (root == NULL) {
        root = x;
    }
    else {
        // x's parent is the root
        x->parent = root;
        // if the SID of x is smaller then the roots SID then insert at the left of the parent
        if (x->SID <= root->SID) {
            // recursively insert to the left
            root->left = insert(root->left, x);
        }
        else {
            // Recursively insert to the right
            root->right = insert(root->right, x);
        }
    }
    // return the updated root
    return root;
}

void AVL::rebalance(Node* x) {
    // Rebalanced while x isn't null
    while(x != NULL){
        // x has been inserted and now the height will be updated
        updateHeight(x);
        // Check the Height of the left and right
        if((height(x->left)) >= (2 + height(x->right))){
            // if the height of the left left child is bigger then the child of the left right
            // They will need to be swapped
            if((height(x->left->left)) >= (height(x->left->right))){
                // Update the node x with a right rotation of the sub tree
               x = rightRotate(x);
            } else {
                // if the left->left child is smaller than the left right child then the left child sub-tree will be corrected
                // with a left rotate
               x->left = leftRotate(x->left);
               // then x will be updated with a right rotate
                x = rightRotate(x);
            }
            // else if the height of the right child is greater than the height of the left child
        } else if((height(x->right)) >= (2 + height(x->left))){
            // check if the right->right child is greater than the right left child
            if(height(x->right->right) >= (height(x->right->left))){
                // update x with a left rotate of x
               x =  leftRotate(x);
            } else {
                // else we need to rotate the right child with a right rotate of the x->right
               x->right = rightRotate(x->right);
               // then rotate x with a left rotate of x
                x = leftRotate(x);
            }
        }
        // update x parent
        x = x->parent;
    }

}
void AVL::AVL_Insert(Node *x) {
    // Insert at the root
    root = insert(root,x);
    // rebalanced on the x node
    rebalance(x);
}

int main()
{
    Node tmp[10];

    for (int i = 0; i < 10; i++) {

        cin >> tmp[i].SID;
    }

    AVL x;

    for (int i = 0; i < 10; i++) {

        x.AVL_Insert(&tmp[i]);
    }

    int operationChoice ;

    cin >> operationChoice;

    if (operationChoice == 1) { // enumerate key

        x.AVL_Enumerate();
    }
    else {

        cout << "Enter a valid choice";
    }

    return 0;
}

