//
// Created by Dustin Burda on 11/20/23.
//

#ifndef RASTERIZATIONENGINE_MATRIX_H
#define RASTERIZATIONENGINE_MATRIX_H

#include <cstdlib>
#include <array>
#include <vector>
#include "Vector.h"

/*
 * TODO:
 *  constructor single number --> DONE
 *  constructor array of data --> DONE
 *  constructor vector of data --> DONE
 *  subscript --> DONE
 *  negate --> DONE
 *  plus equal/minus equal matrix --> DONE
 *  times equal/divide equal scalar --> DONE
 *  inverse/invert
 *  determinant
 *  ========================================
 *  operator ==  --> DONE
 *  multiply/divide by scalar --> DONE
 *  add/subtract matrix --> DONE
 *  multiply matrix --> DONE
 *  multiply vector --> DONE
 *
 *  MATRIX FOR_EACH
 *  TESTTTTTTTTTTTTTTT
 * */

static constexpr float epsilon = 10e-5;


// R - number of rows/column length
// C - number of cols/row length
template<std::size_t R, std::size_t C, typename T>
class Matrix {
public:
    explicit Matrix(T num) {
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                data_[i][j] = num;
            }
        }
    }

    Matrix(std::array<std::array<float, C>, R>& data) : data_{data} {}

    Matrix(std::vector<std::vector<float>>& data) {
        assert(data.size() == R && data[0].size() == C);
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                data_[i][j] = data[i][j];
            }
        }
    }
    Matrix(std::vector<float>& data) {
        assert(data.size() == R*C);
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                data_[i][j] = data[i*R + j];
            }
        }
    }

    std::array<float, C>& operator[](size_t i) const {
        if(i >= R)
            throw std::logic_error("");
        return data_[i];
    }

    std::array<float, C>& operator[](size_t i) {
        if(i >= R)
            throw std::logic_error("");
        return data_[i];
    }

    Matrix<R,C, T>& operator-() {
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                data_[i][j] *= -1;
            }
        }
        return (*this);
    }

    Matrix<R,C, T>& operator+=(const Matrix<R,C, T>& other) {
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                data_[i][j] += other[i][j];
            }
        }

        return (*this);
    }

    Matrix<R,C, T>& operator-=(const Matrix<R,C, T>& other) {
        return (*this) += -other;
    }

    Matrix<R,C, T>& operator*=(float t) {
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                data_[i][j] *= t;
            }
        }

        return (*this);
    }

    Matrix<R,C, T>& operator/=(float t) {
        (*this) *= (1/t);
        return (*this);
    }



    size_t num_rows() const { return R; }
    size_t num_cols() const { return C; }


private:
    std::array<std::array<float, C>, R> data_;
};

template<std::size_t R, std::size_t C, typename T>
static bool operator==(const Matrix<R,C, T>& m1, const Matrix<R,C, T>& m2) {
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(std::abs(m1[i][j] - m2[i][j]) > epsilon)
                return false;
        }
    }
    return true;
}

template<std::size_t R, std::size_t C, typename T>
Matrix<R,C, T> operator*(const Matrix<R,C, T>& m1, float t) {
    Matrix<R,C, T> ret = m1;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            ret[i][j] *= t;
        }
    }
    return ret;
}

template<std::size_t R, std::size_t C, typename T>
Matrix<R,C, T> operator*(float t, const Matrix<R,C, T>& m1) {
    return m1 * t;
}

template<std::size_t R, std::size_t C, typename T>
Matrix<R,C, T> operator/(const Matrix<R,C, T>& m1, float t) {
    return m1 * (1/t);
}

template<std::size_t R, std::size_t C, typename T>
Matrix<R,C, T> operator+(const Matrix<R,C, T>& m1, const Matrix<R,C, T>& m2) {
    Matrix<R,C, T> ret;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            ret[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return ret;
}

template<std::size_t R, std::size_t C, typename T>
Matrix<R,C, T> operator-(const Matrix<R,C, T>& m1, const Matrix<R,C, T>& m2) {
    return m1 + (-m2);
}


template<std::size_t R1, std::size_t C, std::size_t R2, typename T>
Matrix<R1,R2, T> operator*(const Matrix<R1,C, T>& m1, const Matrix<C,R2, T>& m2) {
    Matrix<R1,R2, T> ret (0);
    for(int i = 0; i < R1; i++) {
        for(int j = 0; j < R2; j++) {
            T dot = 0;
            for(int k = 0; k < C; k++) {
                dot += m1[i][k] * m2[k][j];
            }
            ret[i][j] = dot;
        }
    }
    return ret;
}

template<std::size_t R, std::size_t C, typename T>
Vec<R, T> operator*(const Matrix<R,C, T>& m1, const Vec<C, T>& v1) {
    Vec<R, T> ret;
    for(int i = 0; i < R; i++) {
        T dot = 0;
        for(int j = 0; j < C; j++) {
            dot += v1[j] * m1[i][j];
        }
        ret[i] = dot;
    }

    return ret;
}


#endif //RASTERIZATIONENGINE_MATRIX_H
