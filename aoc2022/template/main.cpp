#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>
#include<ranges>
#include<numeric>
#include<algorithm>

struct Elf{
   
};

std::istream& operator>>(std::istream& inp,Elf& elf){
   
    return inp;
}

std::ostream& operator<<(std::ostream& out,const Elf& elf){
   
    return out;
}

const std::string INPUTFILE="../day02/input.in"
const std::string TESTFILE="../day02/input.in"

int main(int argc,char** argv){
    std::ifstream input(INPUTFILE);
   
    return 0;
}