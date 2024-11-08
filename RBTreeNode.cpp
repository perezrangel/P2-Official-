//==============================================================
// Names: Aisha Barry, Amaya Joshi, Omar Perez
// Class: CS 271-01
// Date:11/07/2024
// About: RBTreeNode.cpp includes implementations for the 
// RBTreeNode class
//==============================================================

#include "RBTreeNode.hpp"
#include <iostream>
using namespace std;

/*
Constructor
Omar Perez
Creates node in the subtree rooted at this node 
Parameters: None
Return value: None
*/
template <typename T>
RBTreeNode<T>::RBTreeNode()
    : data(T()), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}



/*
Copy Constructor
Omar Perez
do this later
Parameters: None
Return value: None
*/
template <typename T>
RBTreeNode<T>::RBTreeNode(const RBTreeNode<T>& other)
    : data(other.data), left(nullptr), right(nullptr), parent(nullptr), color(other.color) {
    if (other.left) {
        left = new RBTreeNode<T>(*other.left);
        left->parent = this;
    }
    if (other.right) {
        right = new RBTreeNode<T>(*other.right);
        right->parent = this;
    }
}


//==============================================================
// Destructor
// Aisha Barry
// This destructor recursively deletes all nodes in the subtree 
// rooted at this node to prevent memory leaks.
// PARAMETERS: None
// Return value: None
//==============================================================
template <typename T>
RBTreeNode<T>& RBTreeNode<T>::operator=(const RBTreeNode<T>& other) {
    if (this != &other) {
        data = other.data;
        color = other.color;

        // Delete existing left and right subtrees
        if (left) {
            delete left;
            left = nullptr;
        }
        if (right) {
            delete right;
            right = nullptr;
        }

        // Copy left subtree
        if (other.left) {
            left = new RBTreeNode<T>(*other.left);
            left->parent = this;
        }

        // Copy right subtree
        if (other.right) {
            right = new RBTreeNode<T>(*other.right);
            right->parent = this;
        }
    }
    return *this;
}



/*
treeMin
Omar Perez
This function returns a pointer to the node with the minimal value 
on the tree rooted at 'this'
Parameters:
Return Value: pointer to node
*/
template <typename T>
RBTreeNode<T>* RBTreeNode<T>::treeMin() {
    RBTreeNode<T>* current = this;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

template <typename T>
RBTreeNode<T>* RBTreeNode<T>::treeMax() {
    RBTreeNode<T>* current = this;
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
void RBTreeNode<T>::printPreOrderTraversal() const {
    cout << data << " ";
    if (left)
        left->printPreOrderTraversal();
    if (right)
        right->printPreOrderTraversal();
}

//==============================================================
// printInOrderTraversal
// Aisha Barry
// This function prints the values of the nodes in the Red-Black 
// Tree in ascending order using in-order traversal, starting 
// from the node on which this function is called.
// PARAMETERS: None
// Return value: None
//==============================================================
template <typename T>
void RBTreeNode<T>::printInOrderTraversal() const {
    if (left)
        left->printInOrderTraversal();
    cout << data << " ";
    if (right)
        right->printInOrderTraversal();
}

template <typename T>
void RBTreeNode<T>::printPostOrderTraversal() const {
    if (left)
        left->printPostOrderTraversal();
    if (right)
        right->printPostOrderTraversal();
    cout << data << " ";
}
