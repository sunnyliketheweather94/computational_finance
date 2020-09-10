#ifndef __SIMPLE_MATRIX_H__
#define __SIMPLE_MATRIX_H__


#include <vector>
#include <fstream>
#include <utility>

template <typename T = double> // default data type is double.
class SimpleMatrix {
private:
    std::vector<std::vector<T> > mat;

public:
    SimpleMatrix(); // default constructor
    SimpleMatrix(const int& rows, const int& cols, const T& val); // fills entire matrix with val
    SimpleMatrix(const SimpleMatrix<T>& rhs_); // copy constructor
    SimpleMatrix<T>& operator=(const SimpleMatrix<T>& rhs_); // assignment operator
    SimpleMatrix<T>  operator+(SimpleMatrix<T>& other); // overloading the addition operator
    SimpleMatrix<T>  operator-(SimpleMatrix<T>& other); // overloading the addition operator
    virtual ~SimpleMatrix(); // virtual destructor

    // member functions
    std::vector<std::vector<T> > get_matrix() const; // returns the matrix
    T& value(const int& row, const int& col); // returns element at a given pair of indices
    std::pair<int, int> get_dim() const;
    friend std::ostream& operator<<(std::ostream& os, SimpleMatrix<T>& other);
};


#include "simple_matrix.cpp"

#endif