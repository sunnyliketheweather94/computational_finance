#ifndef __SIMPLE_MATRIX_CPP__
#define __SIMPLE_MATRIX_CPP__

#include "simple_matrix.h"
#include <iomanip>
#include <vector>
#include <utility>
#include <fstream>


// default constructor
template <typename T>
SimpleMatrix<T>::SimpleMatrix() {
    // do nothing as the vector created will use the std::vector's default c'tor
}

// constructor
template <typename T>
SimpleMatrix<T>::SimpleMatrix(const int& rows, const int& cols, const T& val) {
    std::vector<T> col(cols, val); // create a row of all entries = val

    for(int i = 0; i < rows; ++i) {
        mat.push_back(col);
    }
}

// copy constructor
template <typename T>
SimpleMatrix<T>::SimpleMatrix(const SimpleMatrix<T>& rhs) {
    mat = rhs.get_matrix();
}

// assignment operator being overloaded for this class
template <typename T>
SimpleMatrix<T>& SimpleMatrix<T>::operator=(const SimpleMatrix<T>& rhs) {
    if(this == &rhs) { // if the two are the same
        return *this;
    }

    mat = rhs.get_matrix();
    return *this;
}

// overloading the addition operator
template <typename T>
SimpleMatrix<T> SimpleMatrix<T>::operator+(const SimpleMatrix<T>& other) {
    std::vector<std::vector<T> > result;
    std::pair<int, int> p = get_dim(); // obtain dimensions of matrix

    for(int i = 0; i < p.first; ++i) {
        std::vector<T> temp;
        for(int j = 0; j < p.second; ++j) {
            temp.push_back(std::move(value(i, j) + other.value(i, j)));
        }

        result.push_back(temp);
    }
}

// overloading the subtraction operator
template <typename T>
SimpleMatrix<T> SimpleMatrix<T>::operator-(const SimpleMatrix<T>& other) {
    std::vector<std::vector<T> > result;
    std::pair<int, int> p = get_dim(); // obtain dimensions of matrix

    for(int i = 0; i < p.first; ++i) {
        std::vector<T> temp;
        for(int j = 0; j < p.second; ++j) {
            temp.push_back(std::move(value(i, j) - other.value(i, j)));
        }

        result.push_back(temp);
    }
}

// destructor
template <typename T>
SimpleMatrix<T>::~SimpleMatrix() {
    // vector class handles it so no need to write anything!
}

// member function 1: return the matrix
template <typename T>
std::vector<std::vector<T> > SimpleMatrix<T>::get_matrix() const {
 return mat;
}

// member function 2: return element at (i, j)th position of matrix
// don't add const after the function in prototype because
// the value MAY get modified (it's ok!)
template <typename T>
T& SimpleMatrix<T>::value(const int& row, const int& col) {
    return (mat.at(row)).at(col);
}

// overloading the std::cout
template <typename T>
std::ostream& operator<<(std::ostream& os, SimpleMatrix<T>& other) {
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