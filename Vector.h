//
// Created by Dustin Burda on 11/19/23.
//

#ifndef RASTERIZATIONENGINE_VECTOR_H
#define RASTERIZATIONENGINE_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <array>
#include <vector>
#include "util.h"

template<std::size_t N, typename T>
class Vec {
public:
    explicit Vec() {
        data_.fill(0);
    };

    explicit Vec(const std::vector<T>& list) {
        assert(list.size() == N);
        for(int i = 0; i < N; i++) {
            data_[i] = list[i];
        }
    }

    explicit Vec(double num) {
        data_.fill(num);
    }

    T operator[](size_t i) const {
        if(i >= N)
            throw std::logic_error("Index must be within bounds!\n");
        return data_[i];
    }

    T& operator[](size_t i) {
        if(i >= N)
            throw std::logic_error("Index must be within bounds!\n");
        return data_[i];
    }

    Vec<N, T> operator-() const {
        Vec<N, T> neg = *this;
        std::for_each(neg.data_.begin(), neg.data_.end(), [](T& elem){
            elem *= -1;
        });
        return neg;
    }

    Vec& operator+=(const Vec<N, T>& other) {
        for(int i = 0; i < N; i++) {
            data_[i] += other[i];
        }
        return *this;
    }

    Vec<N, T>& operator-=(const Vec<N, T>& other) {
        return (*this += -other);
    }

    Vec<N, T>& operator*=(double t) {
        std::for_each(data_.begin(), data_.end(), [&t](T& elem) {
            elem *= t;
        });
        return *this;
    }

    Vec<N, T>& operator/=(double t) {
        return (*this *= (1/t));
    }

    Vec<N, T>& normalize() {
        (*this) /= magnitude();
        return *this;
    }

    double magnitude() const {
        double length_squared = 0;
        for(int i = 0; i < N; i++) {
            length_squared += data_[i]*data_[i];
        }
        return std::sqrt(length_squared);
    }

    Vec<N, T> normal() const {
        return (*this)/(magnitude());
    };

    Vec<N+1, T> homogenize_vector() const {
        Vec<N+1, T> ret;
        for(int i = 0; i < N; i++) {
            ret[i] = (*this)[i];
        }
        ret[N] = 1;
        return ret;
    }

    Vec<N-1, T> dehomogenize_vector() {
        if(N == 0)
            throw std::logic_error("Cant de-homogenize 0 dimensional vector!");
        if((*this)[N-1] == 0)
            throw std::logic_error("Can't dehomogenize vector with 0 homogenous coordinate");
        Vec<N-1, T> ret;
        for(int i = 0; i < N - 1; i++) {
            ret[i] = (*this)[i] / (*this)[N-1];
        }
        return ret;
    }

    Vec<N+1, T> homogenize_normal() const {
        Vec<N+1, T> ret;
        for(int i = 0; i < N; i++) {
            ret[i] = (*this)[i];
        }
        ret[N] = 0;
        return ret;
    }

    Vec<N-1, T> dehomogenize_normal() {
        if(N == 0)
            throw std::logic_error("Cant de-homogenize 0 dimensional normal!");
        Vec<N-1, T> ret;
        for(int i = 0; i < N - 1; i++) {
            ret[i] = (*this)[i];
        }
        return ret;
    }

private:
    std::array<T, N> data_;
};

template<std::size_t N, typename T>
bool operator==(const Vec<N, T>& v1, const Vec<N, T>& v2) {
    for(int i = 0; i < N; i++) {
        if(!equal(v1[i], v2[i]))
            return false;
    }
    return true;
}

template<std::size_t N, typename T>
Vec<N, T> operator+(const Vec<N, T>& v1, const Vec<N, T> v2) {
    Vec<N,T> ret;
    for(int i = 0; i < N; i++) {
        ret[i] = v1[i] + v2[i];
    }
    return ret;
}

template<std::size_t N, typename T>
Vec<N, T> operator-(const Vec<N, T>& v1, const Vec<N, T> v2) {
    return v1 + (-v2);
}

template<std::size_t N, typename T>
Vec<N, T> operator*(const Vec<N, T>& v1, double t) {
    Vec<N, T> ret;
    for(int i = 0; i < N; i++) {
        ret[i] = v1[i] *t;
    }
    return ret;
}

template<std::size_t N, typename T>
Vec<N, T> operator*(double t, const Vec<N, T>& v1) {
    return v1 * t;
}

template<std::size_t N, typename T>
Vec<N, T> operator/(const Vec<N, T>& v1, double t) {
    return v1 * (1/t);
}

template<std::size_t N, typename T>
double dot(const Vec<N, T>& v1, const Vec<N, T>& v2) {
    double dot_product = 0;
    for(int i = 0; i < N; i++) {
        dot_product += v1[i] * v2[i];
    }
    return dot_product;
}

template<typename T>
Vec<3, T> cross(const Vec<3, T>& v1, const Vec<3, T>& v2) {
    Vec<3, T> ret;
    ret[0] = v1[1] * v2[2] - v2[1] * v1[2];
    ret[1] = v2[0] * v1[2] - v1[0] * v2[2];
    ret[2] = v1[0] * v2[1] - v2[0] * v1[1];
    return ret;
}

using ScreenPoint = Vec<2, int>;
using WorldCoord = Vec<3, double>;
using Light = Vec<3, double>;


#endif //RASTERIZATIONENGINE_VECTOR_H
