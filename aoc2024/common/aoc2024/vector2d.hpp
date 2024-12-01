#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "headers.hpp"

namespace aoc2022
{
template<class T>
struct vector2d: public std::vector<T>{
private:
    using base=std::vector<T>;
    size_t r=0;
    size_t c=0;


    size_t index(size_t i,size_t j) const{
        return i*c+j;
    }

public:
    vector2d()=default;
    vector2d(size_t tr,size_t tc):r{tr},c{tc},base(tr*tc,T{})
    {}
    size_t rows() const{
        return r;
    }
    size_t columns() const{
        return c;
    }

    T& operator()(size_t i,size_t j) {
        return base::operator[](index(i,j));
    }
    const T& operator()(size_t i,size_t j) const {
        return base::operator[](index(i,j));
    }


};
}

#endif