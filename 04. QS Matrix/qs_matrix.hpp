#ifndef __QS_MATRIX_HPP__
#define __QS_MATRIX_HPP__

#include <vector>
#include <fstream>
#include <iomanip>

template <typename Type>
class QSMatrix {
private:
    std::vector<std::vector<Type> > matrix;
    unsigned n_rows;
    unsigned n_cols;

public:
    QSMatrix(const unsigned rows_, const unsigned cols_, const Type& val);
    QSMatrix(const QSMatrix<Type>& rhs);
    virtual ~QSMatrix();

    // overloaded mathematical operators
    QSMatrix<Type>& operator=(const QSMatrix<Type> rhs);

    // matrix-matrix operations
    QSMatrix<Type>  operator+ (const QSMatrix<Type>& rhs);
    QSMatrix<Type>& operator+=(const QSMatrix<Type>& rhs);
    QSMatrix<Type>  operator- (const QSMatrix<Type>& rhs);
    QSMatrix<Type>& operator-=(const QSMatrix<Type>& rhs);
    QSMatrix<Type>  operator* (const QSMatrix<Type>& rhs);
    QSMatrix<Type>& operator*=(const QSMatrix<Type>& rhs);
    QSMatrix<Type>  transpose();

    // matrix-scalar operations
    QSMatrix<Type> operator+(const Type& rhs);
    QSMatrix<Type> operator-(const Type& rhs);
    QSMatrix<Type> operator*(const Type& rhs);
    QSMatrix<Type> operator/(const Type& rhs);

    // matrix-vector operations
    std::vector<Type> operator*(const std::vector<Type> rhs);
    std::vector<Type> diag_vec ();

    // access individual elements
    Type& operator()(const unsigned& row, const unsigned& col);
    const Type& operator()(const unsigned& row, const unsigned& col) const;

    // get dimensions
    unsigned get_rows() const;
    unsigned get_cols() const;

    // overloading << operator
    friend std::ostream& operator<<(std::ostream& os, const QSMatrix<Type> rhs) {
        unsigned n_rows = rhs.get_rows();
        unsigned n_cols = rhs.get_cols();
        
        for(unsigned i = 0; i < n_rows; ++i) {
            for(unsigned j = 0; j < n_cols; ++j) {
                os << std::setprecision(2) << rhs(i, j) << " ";
            }

            os << std::endl;
        }

        return os;
    }

};

#include "qs_matrix.cpp"

#endif