//
// Created by Dustin Burda on 11/19/23.
//

#ifndef RASTERIZATIONENGINE_VECTOR_H
#define RASTERIZATIONENGINE_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <array>

template<std::size_t N>
class Vec {
    explicit Vec(float nums[N]) {
        for(int i = 0; i  < N; i++) {
            data_[i] = nums[i];
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

    Vec<N> operator-() const {
        Vec<N> neg = *this;
        std::for_each(neg.begin(), neg.end(), [](float& elem){
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

private:
    std::array<float, N> data_;
};

template<std::size_t N>
Vec<N> operator+(const Vec<N>& v1, const Vec<N> v2) {

}

template<std::size_t N>
Vec<N> operator-(const Vec<N>& v1, const Vec<N> v2) {

}

template<std::size_t N>
Vec<N> operator*(const Vec<N>& v1, float t) {

}

template<std::size_t N>
Vec<N> operator*(float t, const Vec<N>& v1) {

}

template<std::size_t N>
Vec<N> operator/(const Vec<N>& v1, float t) {

}

template<std::size_t N>
static float dot(const Vec<N>& v1, const Vec<N>& v2) {

}


static Vec<3> cross(const Vec<3>& v1, const Vec<3>& v2) {

}


#endif //RASTERIZATIONENGINE_VECTOR_H
