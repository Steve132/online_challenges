#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>
#include<ranges>
#include<numeric>
#include<algorithm>

struct Game{
    enum class Hand{
        ROCK=0,PAPER,SCISSORS
    };
    Hand theirs,mine;
    
    int score() const{
        int value=static_cast<int>(mine)+1;
        int match=(static_cast<int>(theirs)-static_cast<int>(mine)+3) % 3;
        
        switch(match){
            case 0: return 3+value;
            case 1: return 0+value;
            case 2: return 6+value;
        };
        return 0;
    }
    
};

std::istream& operator>>(std::istream& inp,Game& g){
    std::string mstr,tstr;
    inp >> tstr >> mstr;
    int tselect=static_cast<int>(tstr[0]-'A'),
    mselect=static_cast<int>(mstr[0]-'X');


    
    g={static_cast<Game::Hand>(tselect),static_cast<Game::Hand>(mselect)};
    return inp;
}

std::ostream& operator<<(std::ostream& out,const Game& g){
   
    return out;
}

const std::string INPUTFILE="../day02/input.in";
const std::string TESTFILE="../day02/test.in";

int main(int argc,char** argv){
    std::ifstream input(INPUTFILE);
    std::istream_iterator<Game> ing(input),end;
    auto tot=std::accumulate(ing,end,0,[](int tot,const Game& g){
        return tot+g.score();
    });   
    std::cout << tot << std::endl;
    return 0;
}