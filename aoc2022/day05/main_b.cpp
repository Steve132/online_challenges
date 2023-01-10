#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>
#include<ranges>
#include<numeric>
#include<algorithm>
#include<unordered_set>
#include<array>

struct Range{
    size_t start,finish;

    bool contains(const Range& r) const{
        return start <= r.start && r.finish <= finish; 
    }
    bool overlap(const Range& r) const{
        return start <= r.finish && finish >= r.start;
    }
};
struct Assignment: public std::array<Range,2>
{

};
std::istream& operator>>(std::istream& inp,Range& g){
    size_t a,b;
    std::string m;
    inp >> a;
    inp.ignore();
    inp >> b;
    g=Range{a,b};
    return inp;
}
std::ostream& operator<<(std::ostream& out,const Range& g){
    return out << g.start << "-" << g.finish;
}
std::istream& operator>>(std::istream& inp,Assignment& a){
    inp >> a[0];
    inp.ignore();
    inp >> a[1];
    return inp;
}

const std::string INPUTFILE="../day04/input.in";
const std::string TESTFILE="../day04/test.in";

int main(int argc,char** argv){
    std::ifstream input(INPUTFILE);
    std::istream_iterator<Assignment> ing(input),end;
    auto tot=std::accumulate(ing,end,0,[](int tot,const Assignment& g){
        size_t sus=g[0].overlap(g[1]) || g[1].overlap(g[0]);
        return tot+=sus;
    });   
    std::cout << tot << std::endl;
    return 0;
}