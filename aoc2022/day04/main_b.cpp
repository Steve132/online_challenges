#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>
#include<ranges>
#include<numeric>
#include<algorithm>
#include<unordered_set>
#include<array>
#include<bit>



int score(char c){
    if(isupper(c))
        return int(c-'A')+26+1;
    else 
        return int(c-'a')+1;
}
char unscore(size_t c){
    if(c >= 27) return 'A'+(c-26-1);
    return 'a'+(c-1);
}
struct Compartment{
    std::uint64_t items;
    Compartment():items(0){}

    template<class I>
    Compartment(I b,I e){
        items=0;
        for(;b!=e;++b){
            char c=*b;
            items|= (1ULL) << (score(c)-1);
        }
    }

    char firstElement() const{
        auto c=std::countr_zero(items);
        return unscore(c+1);
    }
    Compartment operator&(const Compartment& c) const {
        Compartment out;
        out.items=c.items & items;
        return out;
    }
    Compartment operator|(const Compartment& c) const {
        Compartment out;
        out.items=c.items | items;
        return out;
    }
};
std::ostream& operator<<(std::ostream& outp,const Compartment& g){
    for(size_t i=0;i<54;i++){
        if((g.items >> i) & 1){
            outp << unscore(i+1);
        }
    }
    return outp;
}

struct Rucksack{
    std::array<Compartment,2> compartments;
    Rucksack(){}
    Rucksack(const std::string& init):
        compartments{
            Compartment{init.begin(),init.begin()+init.size()/2},
            Compartment{init.begin()+init.size()/2,init.end()}
        }
    {}
    
};

template<class T,size_t n>
std::istream& operator>>(std::istream& inp,std::array<T,n>& out){
    for(size_t i=0;i<n;i++){
        inp >> out[i];
    }
    return inp;
}
std::istream& operator>>(std::istream& inp,Rucksack& g){
    std::string mstr;
    inp >> mstr;
    g=Rucksack(mstr);
    return inp;
}
std::ostream& operator<<(std::ostream& out,const Rucksack& g){
    
    return out << g.compartments[0] << "|" << g.compartments[1];
}
const std::string INPUTFILE="../day03/input.in";
const std::string TESTFILE="../day03/test.in";

int main(int argc,char** argv){
    std::ifstream input(INPUTFILE);
    std::istream_iterator<std::array<Rucksack,3>> ing(input),end;
    auto tot=std::accumulate(ing,end,0,[](int tot,const std::array<Rucksack,3>& g){
        size_t sc=0;
        Compartment c;
        c.items=~uint64_t(0);
        for(int i=0;i<3;i++){
            std::cout << g[i] << std::endl;
            auto c1=g[i].compartments[0] | g[i].compartments[1];
            c=c1 & c; 
        }
        std::cout << c << std::endl;

        return tot+score(c.firstElement());
    });   
    std::cout << tot << std::endl;
    return 0;
}