#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>
#include<ranges>
#include<numeric>
#include<algorithm>
#include<unordered_set>
#include<array>

struct Rucksack{
    std::array<std::unordered_set<char>,2> compartments;
    Rucksack(){}
    Rucksack(const std::string& init):
        compartments{
            std::unordered_set<char>{init.begin(),init.begin()+init.size()/2},
            std::unordered_set<char>{init.begin()+init.size()/2,init.end()}
        }
    {}
    char common() const{
        for(const char& a : compartments[0]){
            if(compartments[1].count(a)){
                return a;
            }
        }
        return 0;
    }

    int score() const{
        char c=common();
        if(isupper(c))
            return (c-'A')+27;
        else 
            return (c-'a')+1;
    }
};

std::istream& operator>>(std::istream& inp,Rucksack& g){
    std::string mstr;
    inp >> mstr;
    g=Rucksack(mstr);
    return inp;
}

std::ostream& operator<<(std::ostream& out,const Rucksack& g){
    out << std::string(g.compartments[0].begin(),g.compartments[0].end());
    out << "|";
    out << std::string(g.compartments[1].begin(),g.compartments[1].end());
    return out;
}

const std::string INPUTFILE="../day03/input.in";
const std::string TESTFILE="../day03/test.in";

int main(int argc,char** argv){
    std::ifstream input(INPUTFILE);
    std::istream_iterator<Rucksack> ing(input),end;
    auto tot=std::accumulate(ing,end,0,[](int tot,const Rucksack& g){
        return tot+g.score();
    });   
    std::cout << tot << std::endl;
    return 0;
}