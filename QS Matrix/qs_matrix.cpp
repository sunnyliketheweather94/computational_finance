#ifndef __QS_MATRIX_CPP__
#define __QS_MATRIX_CPP__

#include "qs_matrix.hpp"
#include <vector>
#include <algorithm>
#include <fstream>

// constructor
template <typename Type>
QSMatrix<Type>::QSMatrix(const unsigned rows_, const unsigned cols_, const Type& val) {
    matrix.resize(rows_);

    for(unsigned i = 0; i < matrix.size(); ++i) {
        matrix[i].resize(cols_, val);
    }

    n_rows = rows_;
    n_cols = cols_;
}

// copy constructor
template <typename Type>
QSMatrix<Type>::QSMatrix(const QSMatrix<Type>& rhs) {
    matrix = rhs.matrix;
    n_rows = rhs.get_rows();
    n_cols = rhs.get_cols();
}

// destructor
template <typename Type>
QSMatrix<Type>::~QSMatrix() {
    // do nothing
}

// overloaded mathematical operators
template <typename Type>
QSMatrix<Type>& QSMatrix<Type>::operator=(const QSMatrix<Type> rhs) {
    if(this == &rhs) { // handling self-assignment
        return *this;
    }

    unsigned new_rows = rhs.get_rows();
    unsigned new_cols = rhs.get_cols();

    matrix.resize(new_rows);
    for(unsigned i = 0; i < matrix.size(); ++i) {
        matrix[i].resize(new_cols);
    }

    for(unsigned i = 0; i < new_rows; ++i) {
        for(unsigned j = 0; j < new_cols; ++j) {
            matrix[i][j] = rhs(i, j);
        }
    }

    n_rows = new_rows;
    n_cols = new_cols;

    return *this;
}

// matrix-matrix operations

// addition (WITHOUT ASSIGNMENT) - create new matrix to store result of operation
template <typename Type>
QSMatrix<Type>  QSMatrix<Type>::operator+(const QSMatrix<Type>& rhs) {
    QSMatrix<Type> result(n_rows, n_cols, Type());

    for(unsigned i = 0; i < n_rows; ++i) {
        for(unsigned j = 0; j < n_cols; ++j) {
            result(i, j) = matrix[i][j] + rhs(i, j);
        }
    }

    return result;
}

template <typename Type>
QSMatrix<Type>& QSMatrix<Type>::operator+=(const QSMatrix<Type>& rhs) {
    for(unsigned i = 0; i < rhs.get_rows(); ++i) {
        for(unsigned j = 0; j < rhs.get_cols(); ++j) {
            matrix[i][j] += rhs(i, j);
        }
    }

    return *this;
}

template <typename Type>
QSMatrix<Type>  QSMatrix<Type>::operator- (const QSMatrix<Type>& rhs) {
    QSMatrix<Type> result(n_rows, n_cols, Type());

    for(unsigned i = 0; i < n_rows; ++i) {
        for(unsigned j = 0; j < n_cols; ++j) {
            result[i][j] = matrix[i][j] - rhs(i, j);
        }
    }

    return result;
}

template <typename Type>
QSMatrix<Type>& QSMatrix<Type>::operator-=(const QSMatrix<Type>& rhs) {
    unsigned new_rows = rhs.get_rows();
    unsigned new_cols = rhs.get_cols();

    for(unsigned i = 0; i < new_rows; ++i) {
        for(unsigned j = 0; j < new_cols; ++j) {
            matrix[i][j] -= rhs(i, j);
        }
    }

    return *this;
}

template <typename Type>
QSMatrix<Type>  QSMatrix<Type>::operator* (const QSMatrix<Type>& rhs) {
    unsigned new_rows = rhs.get_rows();
    unsigned new_cols = rhs.get_cols();

    QSMatrix<Type> result(new_rows, new_cols, Type());

    for(unsigned i = 0; i < new_rows; ++i) {
        for(unsigned j = 0; j < new_cols; ++j) {
            for(unsigned k = 0; k < new_rows; ++k) {
                result[i][j] = matrix[i][k] + rhs(k, j);
            }
        }
    }

    return result;
}

template <typename Type>
QSMatrix<Type>& QSMatrix<Type>::operator*=(const QSMatrix<Type>& rhs) {
    QSMatrix<Type> temp = (*this) * rhs;
    *this = temp;

    return *this;
}

template <typename Type>
QSMatrix<Type>  QSMatrix<Type>::transpose() {
    QSMatrix<Type> result(n_cols, n_rows, Type());

    for(unsigned i = 0; i < n_rows; ++i) {
        for(unsigned j = 0; j < n_cols; ++j) {
            result(j, i) = matrix[i][j];
        }
    }

    return result;
}

// matrix-scalar operations

// elementwise-addition
template <typename Type>
QSMatrix<Type> QSMatrix<Type>::operator+(const Type& rhs) {
    QSMatrix<Type> result(n_rows, n_cols, Type());

    for(unsigned i = 0; i < n_rows; ++i) {
        for(unsigned j = 0; j < n_cols; ++j) {
            result(i, j) = matrix[i][j] + rhs;
        }
    }

    return result;
}

// elementwise-subtraction
template <typename Type>
QSMatrix<Type> QSMatrix<Type>::operator-(const Type& rhs) {
    QSMatrix<Type> result(n_rows, n_cols, Type());

    for(unsigned i = 0; i < n_rows; ++i) {
        for(unsigned j = 0; j < n_cols; ++j) {
            result(i, j) = matrix[i][j] - rhs;
        }
    }

    return result;
}

// elementwise-multiplication
template <typename Type>
QSMatrix<Type> QSMatrix<Type>::operator*(const Type& rhs) {
    QSMatrix<Type> result(n_rows, n_cols, Type());

    for(unsigned i = 0; i < n_rows; ++i) {
        for(unsigned j = 0; j < n_cols; ++j) {
            result(i, j) = matrix[i][j] * rhs;
        }
    }

    return result;
}

// elementwise-division
template <typename Type>
QSMatrix<Type> QSMatrix<Type>::operator/(const Type& rhs) {
    QSMatrix<Type> result(n_rows, n_cols, Type());

    for(unsigned i = 0; i < n_rows; ++i) {
        for(unsigned j = 0; j < n_cols; ++j) {
            result(i, j) = matrix[i][j] / rhs;
        }
    }

    return result;
}

// matrix-vector operations

// (right) matrix-vector multiplication
template <typename Type>
std::vector<Type> QSMatrix<Type>::operator*(const std::vector<Type> rhs) {
    std::vector<Type> result(rhs.get_rows(), Type());

    for(unsigned i = 0; i < n_rows; ++i) {
        for(unsigned j = 0; j < n_cols; ++j) {
            result(i, j) += matrix[i][j] * rhs[j];
        }
    }

    return result;
}

template <typename Type>
std::vector<Type> QSMatrix<Type>::diag_vec() {
    unsigned min_index = std::min(n_rows, n_cols);
    std::vector<Type> result(min_index, Type());

    for(unsigned i = 0; i < min_index; ++i) {
        result.push_back(matrix[i][i]);
    }

    return result;
}

// access individual elements
template <typename Type>
Type& QSMatrix<Type>::operator()(const unsigned& row, const unsigned& col) {
    return matrix[row][col];
}

template <typename Type>
const Type& QSMatrix<Type>::operator()(const unsigned& row, const unsigned& col) const {
    return matrix[row][col];
}

// get dimensions
template <typename Type>
unsigned QSMatrix<Type>::get_rows() const {
    return n_rows;
}

template <typename Type>
unsigned QSMatrix<Type>::get_cols() const {
    return n_cols;
}

// template <typename Type>
// std::ostream& operator<<(std::ostream& os, const QSMatrix<Type> rhs) {
//     for(unsigned i = 0; i < 10; ++i) {
//         for(unsigned j = 0; j < 10; ++j) {
//             os << rhs(i, j) << " ";
//         }

//         os << std::endl;
//     }

//     return os;
// }

#endif