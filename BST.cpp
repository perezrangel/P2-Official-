//==============================================================
// Names: Aisha Barry, Omar Perez, Amaya Joshi
// Class: CS 271-01
// Date: 11/07/2024
// About: BST.cpp contains the implementations for
// the BST class. Handling tree-wide structure and management
//==============================================================
#include "BST.hpp"

template <typename T>
BST<T>::BST() : root(nullptr), nodeCount(0) {}

template <typename T>
BST<T>::BST(const BST<T>& other) : root(nullptr), nodeCount(0) {
    copyTree(this->root, other.root);
    this->nodeCount = other.nodeCount;
}

template <typename T>
BST<T>::~BST() {
    destroyTree(root);
}

template <typename T>
BST<T>& BST<T>::operator=(const BST<T>& other) {
    if (this != &other) {
        destroyTree(this->root);
        this->root = nullptr;
        copyTree(this->root, other.root);
        this->nodeCount = other.nodeCount;
    }
    return *this;
}

// Helper function to copy the tree
template <typename T>
void BST<T>::copyTree(BSTNode<T>*& thisRoot, BSTNode<T>* otherRoot) {
    if (otherRoot == nullptr) {
        thisRoot = nullptr;
    } else {
        thisRoot = new BSTNode<T>();
        thisRoot->data = otherRoot->data;
        copyTree(thisRoot->left, otherRoot->left);
        if (thisRoot->left != nullptr) {
            thisRoot->left->parent = thisRoot;
        }
        copyTree(thisRoot->right, otherRoot->right);
        if (thisRoot->right != nullptr) {
            thisRoot->right->parent = thisRoot;
        }
    }
}

// Helper function to destroy the tree
template <typename T>
void BST<T>::destroyTree(BSTNode<T>* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Helper functions to print traversals
template <typename T>
void BST<T>::printPreOrder(BSTNode<T>* node) const {
    if (node != nullptr) {
        cout << node->data << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}

template <typename T>
void BST<T>::printInOrder(BSTNode<T>* node) const {
    if (node != nullptr) {
        printInOrder(node->left);
        cout << node->data << " ";
        printInOrder(node->right);
    }
}

template <typename T>
void BST<T>::printPostOrder(BSTNode<T>* node) const {
    if (node != nullptr) {
        printPostOrder(node->left);
        printPostOrder(node->right);
        cout << node->data << " ";
    }
}

// Methods implementations

template <typename T>
void BST<T>::transplant(BSTNode<T>* oldNode, BSTNode<T>* newNode) {
    if (oldNode->parent == nullptr) {
        root = newNode;
    } else if (oldNode == oldNode->parent->left) {
        oldNode->parent->left = newNode;
    } else {
        oldNode->parent->right = newNode;
    }
    if (newNode != nullptr) {
        newNode->parent = oldNode->parent;
    }
}

template <typename T>
bool BST<T>::isEmpty() const {
    return root == nullptr;
}

template <typename T>
long BST<T>::size() const {
    return nodeCount;
}


/*
insert
Omar Perez
This method inserts a new node with the specified value into the Binary Search Tree.
It creates a new node, finds the appropriate position for the node within the tree, 
and adjusts parent and child pointers to maintain structure.

Parameters:
value

Return value:
A pointer to the newly inserted node.

*/
template <typename T>
BSTNode<T>* BST<T>::insert(T value) {
    BSTNode<T>* y = nullptr;
    BSTNode<T>* x = root;
    BSTNode<T>* z = new BSTNode<T>();
    z->data = value;

    while (x != nullptr) {
        y = x;
        if (value < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == nullptr) {
        root = z;
    } else if (value < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }

    nodeCount++;
    return z;
}




template <typename T>
void BST<T>::remove(T value) {
    BSTNode<T>* z = search(value);
    if (z == nullptr) {
        throw ValueNotInTreeException();
    }

    if (z->left == nullptr) {
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        transplant(z, z->left);
    } else {
        BSTNode<T>* y = z->right->treeMin();
        if (y->parent != z) {
            transplant(y, y->right);
            y->right = z->right;
            if (y->right != nullptr) {
                y->right->parent = y;
            }
        }
        transplant(z, y);
        y->left = z->left;
        if (y->left != nullptr) {
            y->left->parent = y;
        }
    }

    delete z;
    nodeCount--;
}


/*
search
Omar Perez
This method searches for a node with the specified value in the BST.
Starting from the root, it traverses the tree based on comparisons with the node values
to find the target node.

Parameters:
value

Return value:
A pointer to the node containing the  value if it exists in the tree; else it 
returns a nullptr.
*/
template <typename T>
BSTNode<T>* BST<T>::search(T value) const {
    BSTNode<T>* x = root;
    while (x != nullptr && x->data != value) {
        if (value < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

template <typename T>
BSTNode<T>* BST<T>::treeMin() const {
    if (isEmpty()) {
        throw EmptyTreeException();
    }
    BSTNode<T>* x = root;
    while (x->left != nullptr) {
        x = x->left;
    }
    return x;
}

template <typename T>
BSTNode<T>* BST<T>::treeMax() const {
    if (isEmpty()) {
        throw EmptyTreeException();
    }
    BSTNode<T>* x = root;
    while (x->right != nullptr) {
        x = x->right;
    }
    return x;
}

/*
printPreOrderTraversal
Omar Perez
This method initiates the pre-order traversal of the entire Binary Search Tree,
starting from the root node. It prints the values of all nodes in pre-order 
sequence (root, left, right) to standard output.

Parameters: None

Return value: None
*/
template <typename T>
void BST<T>::printPreOrderTraversal() const {
    printPreOrder(root);
    cout << endl;
}

template <typename T>
void BST<T>::printInOrderTraversal() const {
    printInOrder(root);
    cout << endl;
}

template <typename T>
void BST<T>::printPostOrderTraversal() const {
    printPostOrder(root);
    cout << endl;
}
