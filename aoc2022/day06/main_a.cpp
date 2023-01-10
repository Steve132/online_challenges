#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>
#include<ranges>
#include<numeric>
#include<algorithm>
#include<unordered_set>
#include<array>
#include<stack>
#include<string>
#include<bitset>

struct stream_queue{
    std::uint32_t fifo4=0;
    void insert(char c){
        uint_fast8_t vlast=(fifo4 >> 24) & 0xFF;
        uint_fast8_t vnew=c-'a';
        std::cout << (int)vnew << std::endl;
        fifo4 = (fifo4 << 8) + vnew;
    }
    bool unique() const {
        std::bitset<32> reg{0};
        reg[(fifo4 >> 0) & 0xFF]=true;
        reg[(fifo4 >> 8) & 0xFF]=true;
        reg[(fifo4 >> 16) & 0xFF]=true;
        reg[(fifo4 >> 24) & 0xFF]=true;
        return reg.count()==4;
    }
};



const std::string INPUTFILE="../day06/input.in";
const std::string TESTFILE="../day06/test.in";

int main(int argc,char** argv){
    std::ifstream input(INPUTFILE);
    std::istream_iterator<char> instream(input),end;

    stream_queue sq;
    for(size_t i=0;instream!=end;i++){
        sq.insert(*instream++);
        if(i >= 4 && sq.unique()){
            std::cout << i+1 << std::endl;
            break;
        }
    }
    return 0;
}