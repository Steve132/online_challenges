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
    struct Segment{
        Coord2i position;
        std::unordered_map<Coord2i,unsigned int> locations;
        Segment(const Coord2i& start=Coord2i{})
        {
            position=start;
            locations[position]=1;
        }
        void update(const Coord2i& head){
            Coord2i vec=head-position;
            if(std::abs(vec.x) <= 1 && std::abs(vec.y)<=1) return;

            vec.x=sign(vec.x);
            vec.y=sign(vec.y);
            position=position+vec;
            std::cout << position << std::endl;
            locations[position]=1;
        }
    };
public:

    std::vector<Segment> segments;
    SimulatedRope(const Coord2i& start=Coord2i{}):segments(10,start)
    {

    }
    void update(const Movement& m){
        
        size_t amount=std::max(std::abs(m.x),std::abs(m.y));
        Coord2i direction{sign(m.x),sign(m.y)};
        for(size_t i=0;i<amount;i++){
            segments[0].position=segments[0].position+direction;
            segments[0].locations[segments[0].position]=1;
            update_all();
        }
    }
protected:
    void update_all(){

        for(size_t i=1;i<segments.size();i++){
            const Segment& head=segments[i-1];
            Segment& next=segments[i];
            next.update(head.position);
        }
    }
};

const std::string INPUTFILE="../day09/input.in";
const std::string TESTFILE="../day09/test2.in";

int main(int argc,char** argv){
    std::ifstream input(INPUTFILE);

    std::istream_iterator<Movement> inmoves(input),endmoves;
    SimulatedRope rope;
    for_each(inmoves,endmoves,[&rope](const Movement& m){
        std::cout << m << std::endl;
        rope.update(m);
        std::cout << "H:" << rope.segments[0].position << " T: " << rope.segments[1].position << std::endl;
    });

    std::cout << "Total locations:" << rope.segments.back().locations.size() << std::endl;
    
    return 0;
}