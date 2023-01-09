#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>
#include<ranges>
#include<numeric>
#include<algorithm>

struct Elf{
    std::vector<unsigned int> calories;
    unsigned int total(){
        return std::accumulate(calories.begin(),calories.end(),0);
    }
};

std::istream& operator>>(std::istream& inp,Elf& elf){
    elf=Elf();
    while(inp){
        unsigned int c;
        inp >> c;
        elf.calories.push_back(c);
        inp.ignore();
        if(inp.peek()=='\n') break;
    }
    return inp;
}

std::ostream& operator<<(std::ostream& out,const Elf& elf){
    bool first=true;
    for(auto x : elf.calories){
        
        out << (!first ? "," : "") << x;
        first=false;
    }
    return out;
}


//O(n log n) <-- n! -> 1   log(n!) -> n log n
//O(n) Bucket Sort
///O(n log n)  <--- 1/log(n)   n=1000000-> O(n log n)=n log n / n -> log(n) -> log(1000000)->20 > 20x

//binary mergeselect using binary representation of trees (does this work? no?)


int main(int argc,char** argv){
    std::ifstream input("../aoc2022/input1.in");
    auto input_b=std::istream_iterator<Elf>(input),input_e=std::istream_iterator<Elf>();
    std::vector<Elf> elves(input_b,input_e);

    for(auto& e : elves){
        std::cout << "Elf: " << e << std::endl;
    }

    std::vector<unsigned int> totals(elves.size());

    std::transform(elves.begin(),elves.end(),totals.begin(),
    [](auto& elf){
        return elf.total();
    });



    size_t N=6;
    auto mid=totals.begin()+totals.size()-N;
    std::nth_element(totals.begin(),mid,totals.end());

    std::for_each(mid,totals.end(),[](auto x){
        std::cout << "The top are " << x << std::endl;
    });

    std::cout << "The total is " << std::accumulate(mid,totals.end(),0) << std::endl;


    return 0;
}