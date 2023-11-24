//
// Created by Dustin Burda on 11/20/23.
//

#ifndef RASTERIZATIONENGINE_MATRIX_H
#define RASTERIZATIONENGINE_MATRIX_H

#include <cstdlib>
#include <array>
#include <vector>

/*
 * TODO:
 *  constructor single number --> DONE
 *  constructor array of data --> DONE
 *  constructor vector of data --> DONE
 *  subscript --> DONE
 *  negate --> DONE
 *  plus equal/minus equal matrix --> DONE
 *  times equal/divide equal scalar
 *  inverse/invert
 *  determinant
 *  ========================================
 *  operator ==
 *  multiply/divide by scalar
 *  add/subtract matrix
 *  multiply matrix
 *  multiply vector
 *
 *  MATRIX FOR_EACH
 * */


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

    Matrix& operator-() {
        for(int i = 0; i < R; i++) {
            for(int j = 0; j < C; j++) {
                data_ *= -1;
            }
        }
        return (*this);
    }




    size_t num_rows() const { return R; }
    size_t num_cols() const { return C; }


private:
    std::array<std::array<float, C>, R> data_;
};


#endif //RASTERIZATIONENGINE_MATRIX_H
