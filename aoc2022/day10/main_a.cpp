#include <aoc2022/headers.hpp>
#include <aoc2022/vector2d.hpp>
#include <aoc2022/coord2i.hpp>



struct Command {
    std::string opcode;
    int argument;
    size_t waited;
};

std::istream& operator>>(std::istream& inp,Command& f){
    std::string opcode;
    int argument=0;
    inp >> opcode;
    if(opcode != "noop"){
        inp >> argument;
    }
    f=Command{opcode,argument,0};
    return inp;
}
std::ostream& operator<<(std::ostream& out,const Command& f){
    return out << f.opcode << "_" << f.argument;
}

class Device{
    std::vector<Command> rprogram;
    size_t timestamp=0;
    int X=1;
private:
    bool execute(const Command& cmd){
        
        if(cmd.opcode=="noop") return true;
        if(cmd.opcode=="addx") {
            if(cmd.waited==1){
                X+=cmd.argument;
                return true;
            }
        }
        return false;
    }
public:
    template<class Iter>
    Device(Iter b,Iter e):
        rprogram(b,e)
    {
        std::reverse(rprogram.begin(),rprogram.end());
    }
    bool tick(){
        timestamp++;
        
        if(rprogram.empty()) return false;
        
        auto& ncmd=rprogram.back();

        if(execute(ncmd)){
            rprogram.pop_back();
            std::cout << "ts: " << clock() << " executed " << ncmd << " X:" << value() << std::endl; 
        }
        else{
            ncmd.waited++;
        }
        return !rprogram.empty();

    };
    int value() const {
        return X;
    }
    size_t clock() const {
        return timestamp-1;
    }
};


const std::string INPUTFILE="../day10/input.in";
const std::string TESTFILE="../day10/test2.in";

int main(int argc,char** argv){
    std::ifstream input(TESTFILE);

    std::istream_iterator<Command> inmoves(input),endmoves;
    Device dev{inmoves,endmoves};

    for(size_t c=0;dev.tick();c++){
        if(c % 40 == 18){
            std::cout << "X[" << c << "]==" << dev.value() << std::endl;
        }
    }
    
    return 0;
}