#include "RBTree.hpp"

template <typename T>
RBTree<T>::RBTree() : root(nullptr), nodeCount(0) {
    // Initialize the NIL sentinel node
    nil = new RBTreeNode<T>();
    nil->color = BLACK;
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;  // Important to initialize
    root = nil;
}

template <typename T>
RBTree<T>::RBTree(const RBTree<T>& other) : root(nullptr), nodeCount(0) {
    // Initialize the NIL sentinel node
    nil = new RBTreeNode<T>();
    nil->color = BLACK;
    root = nil;
    copyTree(this->root, other.root, other.nil);
    this->nodeCount = other.nodeCount;
}

template <typename T>
RBTree<T>::~RBTree() {
    destroyTree(root);
    delete nil;
}

template <typename T>
RBTree<T>& RBTree<T>::operator=(const RBTree<T>& other) {
    if (this != &other) {
        destroyTree(this->root);
        this->root = nil;
        copyTree(this->root, other.root, other.nil);
        this->nodeCount = other.nodeCount;
    }
    return *this;
}

// Helper function to copy the tree
template <typename T>
void RBTree<T>::copyTree(RBTreeNode<T>*& thisRoot, RBTreeNode<T>* otherRoot, RBTreeNode<T>* otherNil) {
    if (otherRoot == otherNil) {
        thisRoot = nil;
    } else {
        thisRoot = new RBTreeNode<T>(*otherRoot);
        thisRoot->left = nil;
        thisRoot->right = nil;
        thisRoot->parent = nil;
        thisRoot->color = otherRoot->color;

        if (otherRoot->left != otherNil) {
            copyTree(thisRoot->left, otherRoot->left, otherNil);
            thisRoot->left->parent = thisRoot;
        } else {
            thisRoot->left = nil;
        }

        if (otherRoot->right != otherNil) {
            copyTree(thisRoot->right, otherRoot->right, otherNil);
            thisRoot->right->parent = thisRoot;
        } else {
            thisRoot->right = nil;
        }
    }
}

// Helper function to destroy the tree
template <typename T>
void RBTree<T>::destroyTree(RBTreeNode<T>* node) {
    if (node != nil) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

template <typename T>
void RBTree<T>::leftRotate(RBTreeNode<T>* x) {
    RBTreeNode<T>* y = x->right;
    if (y == nil) {
        return; // Cannot perform left rotate on a node with nil right child
    }
    x->right = y->left;
    if (y->left != nil)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}


template <typename T>
void RBTree<T>::rightRotate(RBTreeNode<T>* y) {
    RBTreeNode<T>* x = y->left;
    if (x == nil) {
        return; // Cannot perform right rotate on a node with nil left child
    }
    y->left = x->right;
    if (x->right != nil)
        x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == nil) {
        root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}


// Insert fix-up
template <typename T>
void RBTree<T>::insertFixup(RBTreeNode<T>* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBTreeNode<T>* y = z->parent->parent->right;
            if (y->color == RED) {
                // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            // Symmetric to the above
            RBTreeNode<T>* y = z->parent->parent->left;
            if (y->color == RED) {
                // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // Case 2
                    z = z->parent;
                    rightRotate(z);
                }
                // Case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template <typename T>
void RBTree<T>::deleteFixup(RBTreeNode<T>* x) {
    while (x != root && x->color == BLACK) {
        if (x->parent == nullptr || x->parent == nil) {
            break;
        }
        if (x == x->parent->left) {
            RBTreeNode<T>* w = x->parent->right;
            if (w == nullptr || w == nil) {
                break;
            }
            if (w->color == RED) {
                // Case 1
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                // Case 2
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    // Case 3
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                // Case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            // Symmetric code for x == x->parent->right
            RBTreeNode<T>* w = x->parent->left;
            if (w == nullptr || w == nil) {
                break;
            }
            if (w->color == RED) {
                // Case 1
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                // Case 2
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    // Case 3
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                // Case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}





// Transplant method
template <typename T>
void RBTree<T>::transplant(RBTreeNode<T>* u, RBTreeNode<T>* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent; // This should be safe since nil->parent is initialized
}



template <typename T>
bool RBTree<T>::isEmpty() const {
    return root == nil;
}

template <typename T>
long RBTree<T>::size() const {
    return nodeCount;
}

template <typename T>
RBTreeNode<T>* RBTree<T>::insert(T value) {
    RBTreeNode<T>* z = new RBTreeNode<T>();
    z->data = value;
    z->left = nil;
    z->right = nil;
    z->color = RED;

    RBTreeNode<T>* y = nil;
    RBTreeNode<T>* x = root;

    while (x != nil) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == nil) {
        root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }

    nodeCount++;
    insertFixup(z);
    return z;
}

template <typename T>
void RBTree<T>::remove(T value) {
    RBTreeNode<T>* z = search(value);
    if (z == nil) {
        throw ValueNotInTreeException();
    }

    RBTreeNode<T>* y = z;
    RBTreeNode<T>* x;
    Color yOriginalColor = y->color;

    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    } else {
        // Use your existing treeMin method in RBTreeNode
        y = z->right->treeMin();
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            x->parent = y; // x might be nil; ensure nil->parent is initialized
        } else {
            transplant(y, y->right);
            y->right = z->right;
            if (y->right != nil) {
                y->right->parent = y;
            }
        }

        transplant(z, y);
        y->left = z->left;
        if (y->left != nil) {
            y->left->parent = y;
        }
        y->color = z->color;
    }

    delete z;
    nodeCount--;

    if (yOriginalColor == BLACK) {
        deleteFixup(x);
    }
}


template <typename T>
RBTreeNode<T>* RBTree<T>::search(T value) const {
    RBTreeNode<T>* x = root;
    while (x != nil && x->data != value) {
        if (value < x->data)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

template <typename T>
RBTreeNode<T>* RBTree<T>::treeMin() const {
    if (isEmpty()) {
        throw typename RBTree<T>::ValueNotInTreeException();
    }
    RBTreeNode<T>* x = root;
    while (x->left != nil) {
        x = x->left;
    }
    return x;
}

template <typename T>
RBTreeNode<T>* RBTree<T>::treeMax() const {
    if (isEmpty()) {
        throw typename RBTree<T>::ValueNotInTreeException();
    }
    RBTreeNode<T>* x = root;
    while (x->right != nil) {
        x = x->right;
    }
    return x;
}

// Traversal helper functions
template <typename T>
void RBTree<T>::printPreOrder(RBTreeNode<T>* node) const {
    if (node != nil) {
        cout << node->data << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}

template <typename T>
void RBTree<T>::printInOrder(RBTreeNode<T>* node) const {
    if (node != nil) {
        printInOrder(node->left);
        cout << node->data << " ";
        printInOrder(node->right);
    }
}

template <typename T>
void RBTree<T>::printPostOrder(RBTreeNode<T>* node) const {
    if (node != nil) {
        printPostOrder(node->left);
        printPostOrder(node->right);
        cout << node->data << " ";
    }
}

template <typename T>
void RBTree<T>::printPreOrderTraversal() const {
    printPreOrder(root);
    cout << endl;
}

template <typename T>
void RBTree<T>::printInOrderTraversal() const {
    printInOrder(root);
    cout << endl;
}

template <typename T>
void RBTree<T>::printPostOrderTraversal() const {
    printPostOrder(root);
    cout << endl;
}
