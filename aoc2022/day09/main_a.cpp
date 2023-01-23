#include <aoc2022/headers.hpp>
#include <aoc2022/vector2d.hpp>
#include <aoc2022/coord2i.hpp>

using Coord2i=aoc2022::Coord2i;

struct Movement : public Coord2i{
};

std::istream& operator>>(std::istream& inp,Movement& f){
    std::string dir;int amount;
    inp >> dir >> amount;
    char ch=dir[0];
    switch(ch){
        case 'U':
        case 'u':
            f={0,amount}; break;
        case 'D':
        case 'd':
            f={0,-amount}; break;
        case 'L':
        case 'l':
            f={-amount,0}; break;
        case 'R':
        case 'r':
            f={amount,0}; break;
    }
    return inp;
}

static inline ssize_t sign(ssize_t x){
    if(x==0) return 0;
    if(x < 0) return -1;
    return 1; 
}


struct SimulatedRope{
    Coord2i head,tail;
    std::unordered_map<Coord2i,unsigned int> tail_locations;
    SimulatedRope(const Coord2i& start=Coord2i{})
    {
        head=tail=start;
        tail_locations[tail]=1;
    }
    void update(const Movement& m){
        
        size_t amount=std::max(std::abs(m.x),std::abs(m.y));
        Coord2i direction{sign(m.x),sign(m.y)};
        for(size_t i=0;i<amount;i++){
            head=head+direction;
            Coord2i vec=head-tail;
            if(std::abs(vec.x) <= 1 && std::abs(vec.y)<=1) continue;

            vec.x=sign(vec.x);
            vec.y=sign(vec.y);
            tail=tail+vec;
            tail_locations[tail]=1;
            std::cout << "TM: " << tail << std::endl;
        }
    }
};

const std::string INPUTFILE="../day09/input.in";
const std::string TESTFILE="../day09/test.in";

int main(int argc,char** argv){
    std::ifstream input(TESTFILE);

    std::istream_iterator<Movement> inmoves(input),endmoves;
    SimulatedRope rope;
    for_each(inmoves,endmoves,[&rope](const Movement& m){
        std::cout << m << std::endl;
        rope.update(m);
        std::cout << "H:" << rope.head << " T: " << rope.tail << std::endl;
    });

    std::cout << "Total locations:" << rope.tail_locations.size() << std::endl;
    
    return 0;
}