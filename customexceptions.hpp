//==============================================================
// Names: Aisha Barry, Amaya Joshi, Omar Perez
// Class: CS 271-01
// Date: 11/07/2024
// About: customexceptions.hpp contains the declarations of
// and implementations of our custom exceptions.
//==============================================================

#ifndef CUSTOMEXCEPTIONS_HPP
#define CUSTOMEXCEPTIONS_HPP

#include <exception>

// Exception class for empty tree
class EmptyTreeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "The tree is empty.";
    }
};

// Exception class for value not found in tree
class ValueNotInTreeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "The value is not in the tree.";
    }
};

#endif // CUSTOMEXCEPTIONS_HPP
