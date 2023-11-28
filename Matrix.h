//
// Created by Dustin Burda on 11/20/23.
//

#ifndef RASTERIZATIONENGINE_MATRIX_H
#define RASTERIZATIONENGINE_MATRIX_H

#include <cstdlib>
#include <array>
#include <vector>
#include "Vector.h"
#include "util.h"

// R - number of rows/column length
// C - number of cols/row length
template<std::size_t R, std::size_t C, typename T>
class Matrix {
public:
//    Matrix() = default;

    explicit Matrix(T num) {
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                data_[i][j] = num;
            }
        }
    }

    explicit Matrix(std::array<std::array<T, C>, R>& data) : data_{data} {}

    explicit Matrix(std::array<T, R*C>& data) {
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                data_[i][j] = data[i*R + j];
            }
        }
    }

    explicit Matrix(std::vector<std::vector<T>>& data) {
        assert(data.size() == R && data[0].size() == C);
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                data_[i][j] = data[i][j];
            }
        }
    }
    explicit Matrix(std::vector<T>& data) {
        assert(data.size() == R*C);
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                data_[i][j] = data[i*R + j];
            }
        }
    }

    const std::array<T, C>& operator[](size_t i) const {
        if(i >= R)
            throw std::logic_error("");
        return data_[i];
    }

    std::array<T, C>& operator[](size_t i) {
        if(i >= R)
            throw std::logic_error("");
        return data_[i];
    }

    Matrix<R,C, T> operator-() const {
        Matrix<R,C, T> ret = (*this);
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                ret[i][j] *= -1;
            }
        }
        return ret;
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

    Matrix<C,R, T> transpose() const {
        Matrix<C,R, T> ret(0);
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                ret[j][i] = (*this)[i][j];
            }
        }
        return ret;
    }

    double determinant() const {
        if(R != C)
            throw std::logic_error("Determinant of non-square matrix does not exist!");
        Matrix<R,C, T> copy = (*this);

        for(int r = 0; r < R; r++) {
            for(int r_next = r + 1; r_next < R; r_next++) {
                double f = copy[r_next][r] / copy[r][r];
                for(int c = r; c < R; c++) {
                    copy[r_next][c] -= f * copy[r][c];
                }
            }
        }

        double det = 1;
        for(int i = 0; i < R; i++)
            det *= copy[i][i];

        return det;
    }

    bool invertible() const {
        return determinant() != 0;
    }


    size_t num_rows() const { return R; }
    size_t num_cols() const { return C; }


private:
    std::array<std::array<T, C>, R> data_;
};

template<size_t N, typename T>
Matrix<N,N, T> Id() {
    Matrix<N,N, T> ret(0);
    for(int i = 0; i < N; i++) {
        ret[i][i] = 1;
    }

    return ret;
}


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
static bool operator!=(const Matrix<R,C, T>& m1, const Matrix<R,C, T>& m2) {
    return !(m1 == m2);
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
    Matrix<R,C, T> ret(0);
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

template<std::size_t N, typename T>
Matrix<N, N, T> inverse(Matrix<N,N, T>& m) {
    Matrix<N,2*N, T> augmented(0);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            augmented[i][j] = m[i][j];
        }
    }

    for(int i = 0; i < N; i++)
        augmented[i][i+N] = 1;
    for(int i = 0; i < N -1; i++) {
        for(int  j = 2*N -1; j >= 0; j--) {
            augmented[i][j] /= augmented[i][i];
        }
        for(int k = i + 1; k < N; k++) {
            float coeff = augmented[k][i];
            for(int j = 0; j < 2*N; j++) {
                augmented[k][j] -= augmented[i][j] * coeff;
            }
        }
    }

    for(int j = 2*N -1; j >= N - 1; j--)
        augmented[N-1][j] /= augmented[N-1][N-1];
    // second pass
    for (int i = N -1; i > 0; i--) {
        for (int k= i -1; k >= 0; k--) {
            float coeff = augmented[k][i];
            for (int j=0; j < 2*N; j++) {
                augmented[k][j] -= augmented[i][j] * coeff;
            }
        }
    }

    Matrix<N,N, T> inverse(0);

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            inverse[i][j] = augmented[i][j + N];
        }
    }

    return inverse;
}


#endif //RASTERIZATIONENGINE_MATRIX_H
