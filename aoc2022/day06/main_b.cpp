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

template<size_t N>
struct stream_queue{
    std::array<char,N> fifo;
    size_t consumed_so_far=0;
    void insert(char c){
        consumed_so_far++;
        uint_fast8_t vlast=fifo[N-1];
        uint_fast8_t vnew=c-'a';
        std::shift_right(fifo.begin(),fifo.end(),1);
        fifo[0]=vnew;
    }
    bool unique() const {
        std::bitset<26> reg{0};
        for(char c : fifo){
            reg[c]=true;
        }
        return consumed_so_far >= N && reg.count()==N;
    }
};



const std::string INPUTFILE="../day06/input.in";
const std::string TESTFILE="../day06/test.in";

int main(int argc,char** argv){
    std::ifstream input(INPUTFILE);
    std::istream_iterator<char> instream(input),end;

    stream_queue<14> sq;
    for(size_t i=0;instream!=end;i++){
        sq.insert(*instream++);
        if(i >= 14 && sq.unique()){
            std::cout << i+1 << std::endl;
            break;
        }
    }
    return 0;
}