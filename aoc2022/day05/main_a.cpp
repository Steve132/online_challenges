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

struct Crane{
    std::vector<std::vector<char>> stacks;
};



std::istream& operator>>(std::istream& inp,Crane& crane){
    crane=Crane();
    
    struct inner{
        static std::string readFour(std::istream& inp){
            std::string out="aaaa";
            for(int i=0;i<4;i++) out[i]=inp.get();        
            return out;
        }

        static bool readOneLine(Crane& crane,std::istream& inp){
            for(int i=0;true;i++){
                auto g=readFour(inp);
                if(g=="    "){
                    continue;
                }
                if(g=="   \n"){
                    return true;
                }
                if(g[0]=='['){
                    if(i >= crane.stacks.size()){
                        crane.stacks.resize(i+1);
                    }
                    crane.stacks[i].push_back(g[1]);
                    continue;
                }
                return false;
            }
        }
    };

    while((inner::readOneLine(crane,inp))){}
    std::string tmp;
    getline(inp,tmp);
    for(auto& st : crane.stacks){
        std::reverse(st.begin(),st.end());
    }
    
    return inp;
}
std::ostream& operator<<(std::ostream& out,const Crane& crane){
    
    size_t stackHeight=std::accumulate(crane.stacks.begin(),crane.stacks.end(),0,
        [](size_t T,const std::vector<char>& st)
        { 
            return std::max(T,st.size());
        });
    

    for(size_t h=stackHeight;h>0;h--){
        for(size_t i=0;i<crane.stacks.size();i++){
            if((h-1) < crane.stacks[i].size()){
                out << "[" << crane.stacks[i][h-1] << "] ";
            }
            else {
                out << "    ";
            }
        }
        out << "\n";
    }

    return out;
}


const std::string INPUTFILE="../day05/input.in";
const std::string TESTFILE="../day05/test.in";

int main(int argc,char** argv){
    std::ifstream input(TESTFILE);
    Crane crane;
    input >> crane;
    std::cout << crane;
    return 0;
}