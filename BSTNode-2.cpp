//==============================================================
// Names: Aisha Barry, Amaya Joshi, Omar Perez
// Class: CS 271-01
// Date:11/07/2024
// About: BSTNode.cpp includes implementations for the BSTNode 
// class
//==============================================================
#include "BSTNode.hpp"


/*
Constructor
Omar Perez
Creates node in the subtree rooted at this node 
Parameters: None
Return value: None
*/
template <typename T>
BSTNode<T>::BSTNode() : data(T()), left(nullptr), right(nullptr), parent(nullptr) {}



/*
Copy Constructor
Omar Perez
do this later
Parameters: None
Return value: None
*/
template <typename T>
BSTNode<T>::BSTNode(const BSTNode<T>& other) : data(other.data), left(nullptr), right(nullptr), parent(nullptr) {
    if (other.left) {
        left = new BSTNode<T>();
        *left = *other.left;
        left->parent = this;
    }
    if (other.right) {
        right = new BSTNode<T>();
        *right = *other.right;
        right->parent = this;
    }
}


template <typename T>
BSTNode<T>& BSTNode<T>::operator=(const BSTNode<T>& other) {
    if (this != &other) {
        data = other.data;

        // Delete existing left and right subtrees
        delete left;
        delete right;

        // Copy left subtree
        if (other.left) {
            left = new BSTNode<T>();
            *left = *other.left;
            left->parent = this;
        } else {
            left = nullptr;
        }

        // Copy right subtree
        if (other.right) {
            right = new BSTNode<T>();
            *right = *other.right;
            right->parent = this;
        } else {
            right = nullptr;
        }
    }
    return *this;
}



/*
BSTNode<T>* treeMin()
treeMin
Omar Perez
This function returns a pointer to the node with the minimal value 
on the tree rooted at 'this'
Parameters:
Return Value: pointer to node
*/
template <typename T>
BSTNode<T>* BSTNode<T>::treeMin() {
    BSTNode<T>* current = this;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

template <typename T>
BSTNode<T>* BSTNode<T>::treeMax() {
    BSTNode<T>* current = this;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
}


/*
printPreOrderTraversal
Omar Perez
This method prints the stdout of the pre-order traversal for the subtree 
that starts at this node.
Parameters: None
Return value: None
*/
template <typename T>
void BSTNode<T>::printPreOrderTraversal() const {
    cout << data << " ";
    if (left)
        left->printPreOrderTraversal();
    if (right)
        right->printPreOrderTraversal();
}

template <typename T>
void BSTNode<T>::printInOrderTraversal() const {
    if (left)
        left->printInOrderTraversal();
    cout << data << " ";
    if (right)
        right->printInOrderTraversal();
}

template <typename T>
void BSTNode<T>::printPostOrderTraversal() const {
    if (left)
        left->printPostOrderTraversal();
    if (right)
        right->printPostOrderTraversal();
    cout << data << " ";
}
