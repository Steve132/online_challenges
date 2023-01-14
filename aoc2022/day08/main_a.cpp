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
struct vector2d: public std::vector<T>{
private:
    using base=std::vector<T>;
    size_t r=0;
    size_t c=0;


    size_t index(size_t i,size_t j) const{
        return i*c+j;
    }

public:
    vector2d()=default;
    vector2d(size_t tr,size_t tc):r{tr},c{tc},base(tr*tc,T{})
    {}
    size_t rows() const{
        return r;
    }
    size_t columns() const{
        return c;
    }
    auto row(size_t i) const{
        return std::ranges::subrange(base::begin()+i*c,base::begin()+(i+1)*c);
    }
    auto row(size_t i) {
        return std::ranges::subrange(base::begin()+i*c,base::begin()+(i+1)*c);
    }
    T& operator()(size_t i,size_t j) {
        return base::operator[](index(i,j));
    }
    const T& operator()(size_t i,size_t j) const {
        return base::operator[](index(i,j));
    }

    //Not used but cool anyway.
    auto column(size_t ci) {
        auto crange=std::views::iota(size_t(0),c) |
        std::views::transform([ci,this](size_t ri) -> T& {
            return operator()(index(ri,ci));
        });
        return crange;
    }
    auto column(size_t ci) const {
        auto crange=std::views::iota(size_t(0),c) |
        std::views::transform([ci,this](size_t ri) -> const T& {
            return operator()(index(ri,ci));
        });
        return crange;
    }
};

struct Forest: vector2d<int> {
    enum class Visibility: uint32_t{
        LEFT=0x01,
        TOP=0x02,
        RIGHT=0x04,
        BOTTOM=0x08
    };
    using VisibilityMask=uint32_t;
private:
    vector2d<VisibilityMask> visible;
    

public:
    Forest()=default;
    Forest(const vector2d<int>& heights):vector2d<int>{heights}
    {
        visible=vector2d<VisibilityMask>{heights.rows(),heights.columns()};
        std::fill(visible.begin(),visible.end(),0);

        std::vector<int> vert_max(heights.columns(),0);
        int horiz_max=0;
        for(size_t i=0;i<rows();i++){
            for(size_t j=0;j<columns();j++){
                int v=heights(i,j);
                if(v > horiz_max){
                    horiz_max=v;
                    visible(i,j) |= (VisibilityMask)Visibility::LEFT;
                }
                if(v > vert_max[j]){
                    vert_max[j]=v;
                    visible(i,j) |= (VisibilityMask)Visibility::TOP;
                }
            }
        }
        horiz_max=0;
        std::fill(vert_max.begin(),vert_max.end(),0);
        for(size_t i=0;i<rows();i++){
            size_t rev_i=rows()-i-1;
            for(size_t j=0;j<columns();j++){
                size_t rev_j=columns()-j-1;
                int v=heights(rev_i,rev_j);
                if(v > horiz_max){
                    horiz_max=v;
                    visible(rev_i,rev_j) |= (VisibilityMask)Visibility::RIGHT;
                }
                if(v > vert_max[rev_j]){
                    vert_max[rev_j]=v;
                    visible(rev_i,rev_j) |= (VisibilityMask)Visibility::BOTTOM;
                }
            }
        }
    }
};
    

std::istream& operator>>(std::istream& inp,Forest& f){
    std::istream_iterator<std::string> is(inp),end;
    
    std::vector<int> row;
    
    std::vector<std::vector<int>> hv;
    for(auto& s : std::ranges::subrange(is,end)){
        row.resize(s.size());
        hv.reserve(s.size());
        for(size_t i=0;i<s.size();i++){
            
            row[i]=s[i]-'0';
        }
        hv.push_back(row);
    }
    vector2d<int> hv2{hv.size(),hv[0].size()};
    for(size_t i=0;i<hv2.rows();i++)
    for(size_t j=0;j<hv2.columns();j++){
        hv2(i,j)=hv[i][j];
    }

    f=Forest{hv2};
    return inp;
}

template<class T>
std::ostream& operator<<(std::ostream& out,const vector2d<T>& f){
    for(size_t i=0;i<f.rows();i++)
    {
        for(size_t j=0;j<f.columns();j++){
            out << f(i,j);
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