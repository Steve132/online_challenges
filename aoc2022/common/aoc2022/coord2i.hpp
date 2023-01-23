#ifndef AOC2022_COORD2I_HPP
#define AOC2022_COORD2I_HPP

#include "headers.hpp"

namespace aoc2022{

struct Coord2i{
    ssize_t x,y;

    Coord2i operator+(const Coord2i& c) const {
        return {x+c.x,y+c.y};
    }
    Coord2i operator-(const Coord2i& c) const {
        return {x-c.x,y-c.y};
    }

    bool operator==(const Coord2i& c) const = default;
    auto operator<=>(const Coord2i& c) const = default;
};

std::istream& operator>>(std::istream& inp,Coord2i& f){
    return inp >> f.x >> f.y;
}
std::ostream& operator<<(std::ostream& out,const Coord2i& f){
    return out << "(" << f.x << "," << f.y << ")";
}

}

static inline ssize_t l1norm(const aoc2022::Coord2i c){
    return std::abs(c.x)+std::abs(c.y);
}

template<>
struct std::hash<aoc2022::Coord2i>{
    size_t operator()(const aoc2022::Coord2i& c) const noexcept{
        size_t cx=(size_t)c.x;
        size_t cy=(size_t)c.y;
        static const unsigned int NB=sizeof(size_t)*8/2;
        return cx+(cy << NB)+(cy >> NB);
    }
};



#endif