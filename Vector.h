//
// Created by Dustin Burda on 11/19/23.
//

#ifndef RASTERIZATIONENGINE_VECTOR_H
#define RASTERIZATIONENGINE_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <array>
#include <vector>

template<std::size_t N>
class Vec {
public:
    explicit Vec() {
        data_.fill(0);
    };

    explicit Vec(const std::vector<float>& list) {
        assert(list.size() == N);
        for(int i = 0; i < N; i++) {
            data_[i] = list[i];
        }
    }

    explicit Vec(float num) {
        data_.fill(num);
    }

    float operator[](size_t i) const {
        if(i >= N)
            throw std::logic_error("Index must be within bounds!\n");
        return data_[i];
    }

    float& operator[](size_t i) {
        if(i >= N)
            throw std::logic_error("Index must be within bounds!\n");
        return data_[i];
    }

    Vec<N> operator-() const {
        Vec<N> neg = *this;
        std::for_each(neg.data_.begin(), neg.data_.end(), [](float& elem){
            elem *= -1;
        });
        return neg;
    }

    Vec& operator+=(const Vec<N>& other) {
        for(int i = 0; i < N; i++) {
            data_[i] += other[i];
        }
        return *this;
    }

    Vec<N>& operator-=(const Vec<N>& other) {
        return (*this += -other);
    }

    Vec<N>& operator*=(float t) {
        std::for_each(data_.begin(), data_.end(), [&t](float& elem) {
            elem *= t;
        });
        return *this;
    }

    Vec<N>& operator/=(float t) {
        return (*this *= (1/t));
    }

    Vec<N>& normalize() {
        (*this) /= magnitude();
        return *this;
    }

    float magnitude() {
        float length_squared = 0;
        for(int i = 0; i < N; i++) {
            length_squared += data_[i]*data_[i];
        }
        return std::sqrt(length_squared);
    }

    Vec<N> normal() {
        return (*this)/(magnitude());
    };

private:
    std::array<float, N> data_;
};

template<std::size_t N>
static bool operator==(const Vec<N>& v1, const Vec<N> v2) {
    for(int i = 0; i < N; i++) {
        if(v1[i] != v2[i])
            return false;
    }
    return true;
}

template<std::size_t N>
static Vec<N> operator+(const Vec<N>& v1, const Vec<N> v2) {
    Vec<N> ret;
    for(int i = 0; i < N; i++) {
        ret[i] = v1[i] + v2[i];
    }
    return ret;
}

template<std::size_t N>
static Vec<N> operator-(const Vec<N>& v1, const Vec<N> v2) {
    return v1 + (-v2);
}

template<std::size_t N>
static Vec<N> operator*(const Vec<N>& v1, float t) {
    Vec<N> ret;
    for(int i = 0; i < N; i++) {
        ret[i] = v1[i] *t;
    }
    return ret;
}

template<std::size_t N>
static Vec<N> operator*(float t, const Vec<N>& v1) {
    return v1 * t;
}

template<std::size_t N>
static Vec<N> operator/(const Vec<N>& v1, float t) {
    return v1 * (1/t);
}

template<std::size_t N>
static float dot(const Vec<N>& v1, const Vec<N>& v2) {
    float dot_product = 0;
    for(int i = 0; i < N; i++) {
        dot_product += v1[i] * v2[i];
    }
    return dot_product;
}

static Vec<3> cross(const Vec<3>& v1, const Vec<3>& v2) {
    Vec<3> ret;
    ret[0] = v1[1] * v2[2] - v2[1] * v1[2];
    ret[1] = v2[0] * v1[2] - v1[0] * v2[2];
    ret[2] = v1[0] * v2[1] - v2[0] * v1[1];
    return ret;
}


#endif //RASTERIZATIONENGINE_VECTOR_H
