#ifndef BST_HPP
#define BST_HPP

#include "BSTNode.hpp"
#include <iostream>
#include <exception>

using namespace std;

template <typename T>
class BST {
private:
    BSTNode<T>* root;
    long nodeCount;

    // Helper functions
    void copyTree(BSTNode<T>*& thisRoot, BSTNode<T>* otherRoot);
    void destroyTree(BSTNode<T>* node);
    void printPreOrder(BSTNode<T>* node) const;
    void printInOrder(BSTNode<T>* node) const;
    void printPostOrder(BSTNode<T>* node) const;

public:
    // Default constructor
    BST();

    // Copy constructor
    BST(const BST<T>& other);

    // Destructor
    ~BST();

    // Assignment operator
    BST<T>& operator=(const BST<T>& other);

    // Methods
    void transplant(BSTNode<T>* oldNode, BSTNode<T>* newNode);
    bool isEmpty() const;
    long size() const;
    BSTNode<T>* insert(T value);
    void remove(T value);
    BSTNode<T>* search(T value) const;
    BSTNode<T>* treeMin() const;
    BSTNode<T>* treeMax() const;
    void printPreOrderTraversal() const;
    void printInOrderTraversal() const;
    void printPostOrderTraversal() const;

    // Exceptions
    class ValueNotInTreeException : public exception {
        public:
            virtual const char* what() const throw() {
                return "Value not in tree exception";
            }
    };

    class EmptyTreeException : public exception {
        public:
            virtual const char* what() const throw() {
                return "Empty tree exception";
            }
    };
};

#include "BST.cpp"  // Include implementation for template class

#endif // BST_HPP
