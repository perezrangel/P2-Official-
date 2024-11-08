#ifndef BSTNODE_HPP
#define BSTNODE_HPP

#include <iostream>
using namespace std;

template <typename T>
class BSTNode {
public:
    T data;
    BSTNode<T>* left;
    BSTNode<T>* right;
    BSTNode<T>* parent;

    // Default constructor
    BSTNode();

    // Copy constructor
    BSTNode(const BSTNode<T>& other);

    // Assignment operator
    BSTNode<T>& operator=(const BSTNode<T>& other);

    // Methods
    BSTNode<T>* treeMin();
    BSTNode<T>* treeMax();
    void printPreOrderTraversal() const;
    void printInOrderTraversal() const;
    void printPostOrderTraversal() const;
};

#include "BSTNode.cpp"  // Include implementation for template class

#endif // BSTNODE_HPP
