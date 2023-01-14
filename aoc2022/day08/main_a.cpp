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
#include<ranges>

template<class T>
struct vector2d: public std::vector<std::vector<T>>{
private:
    using base=std::vector<std::vector<T>>;
public:
    size_t rows() const{
        return base::size();
    }
    size_t columns() const{
        return base::operator[](0).size();
    }
    auto& operator[](size_t i){
        return base::operator[](i);
    }
    const auto& operator[](size_t i) const{
        return base::operator[](i);

    }
};

struct Forest: vector2d<int>{
    
};

std::istream& operator>>(std::istream& inp,Forest& f){
    std::istream_iterator<std::string> is(inp),end;
    
    std::vector<int> row;
    f=Forest{};
    for(auto& s : std::ranges::subrange(is,end)){
        row.resize(s.size());
        f.reserve(s.size());
        for(size_t i=0;i<s.size();i++){
            
            row[i]=s[i]-'0';
        }
        f.push_back(row);
    }
    return inp;
}
std::ostream& operator<<(std::ostream& out,const Forest& f){
    for(size_t i=0;i<f.rows();i++)
    {
        for(size_t j=0;j<f.columns();j++){
            out << f[i][j];
        }
        out << '\n';
    }
    return out;
}

const std::string INPUTFILE="../day08/input.in";
const std::string TESTFILE="../day08/test.in";

int main(int argc,char** argv){
    std::ifstream input(TESTFILE);
    Forest f;
    input >> f;
    std::cout << f;

    return 0;
}