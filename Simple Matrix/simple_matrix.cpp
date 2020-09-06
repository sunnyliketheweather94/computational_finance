#ifndef __SIMPLE_MATRIX_CPP__
#define __SIMPLE_MATRIX_CPP__

#include "simple_matrix.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>



// default constructor
template <typename Type>
SimpleMatrix<Type>::SimpleMatrix() {
    // do nothing as the vector created will use the std::vector's default c'tor
    std::cout << "Hiii // inside the default constructor.\n";
}

// constructor
template <typename Type>
SimpleMatrix<Type>::SimpleMatrix(const int& rows, const int& cols, const Type& val) {
    std::vector<Type> col(cols, val); // create a row of all entries = val

    for(int i = 0; i < rows; ++i) {
        mat.push_back(col);
    }

    std::cout << "Hiii // inside the regular constructor.\n";
}

// copy constructor
template <typename Type>
SimpleMatrix<Type>::SimpleMatrix(const SimpleMatrix<Type>& rhs) {
    mat = rhs.get_matrix();
    std::cout << "hiiii // inside the copy constructor.\n";
}

// assignment operator being overloaded for this class
template <typename Type>
SimpleMatrix<Type>& SimpleMatrix<Type>::operator=(const SimpleMatrix<Type>& rhs) {
    if(this == &rhs) { // if the two are the same
        return *this;
    }

    mat = rhs.get_matrix();
    return *this;
}

// overloading the addition operator
template <typename Type>
SimpleMatrix<Type> SimpleMatrix<Type>::operator+(const SimpleMatrix<Type>& other) {
    std::vector<std::vector<Type> > result;
    std::pair<int, int> p = get_dim(); // obtain dimensions of matrix

    for(int i = 0; i < p.first; ++i) {
        std::vector<Type> temp;
        for(int j = 0; j < p.second; ++j) {
            temp.push_back(value(i, j) + other.value(i, j));
        }

        result.push_back(temp);
    }
}

// overloading the subtraction operator
template <typename Type>
SimpleMatrix<Type> SimpleMatrix<Type>::operator-(const SimpleMatrix<Type>& other) {
    std::vector<std::vector<Type> > result;
    std::pair<int, int> p = get_dim(); // obtain dimensions of matrix

    for(int i = 0; i < p.first; ++i) {
        std::vector<Type> temp;
        for(int j = 0; j < p.second; ++j) {
            temp.push_back(value(i, j) - other.value(i, j));
        }

        result.push_back(temp);
    }
}

// destructor
template <typename Type>
SimpleMatrix<Type>::~SimpleMatrix() {
    // vector class handles it so no need to write anything!
    std::cout << "Byeeee // in the destructor.\n";
}

// member function 1: return the matrix
template <typename Type>
std::vector<std::vector<Type> > SimpleMatrix<Type>::get_matrix() const {
 return mat;
}

// member function 2: return element at (i, j)th position of matrix
// don't add const after the function in prototype because
// the value MAY get modified (it's ok!)
template <typename Type>
Type& SimpleMatrix<Type>::value(const int& row, const int& col) {
    return (mat.at(row)).at(col);
}


// member function 3: return the dimensions of the matrix
template <typename Type>
std::pair<int, int> SimpleMatrix<Type>::get_dim() const {
    int n_rows = mat.size();
    int n_cols = (mat.at(0)).size();

    std::pair<int, int> p(n_rows, n_cols);

    return p;
}

// overloading the std::cout
template <typename Type>
std::ostream& operator<<(std::ostream& os, SimpleMatrix<Type>& other) {
    std::pair<int, int> p = other.get_dim(); // obtain dimensions

    for(int i = 0; i < p.first; ++i) {
        for(int j = 0; j < p.second; ++j) {
            os << std::setprecision(2) << other.value(i, j) << " ";
        }

        os << std::endl;
    }

    return os;
}

#endif