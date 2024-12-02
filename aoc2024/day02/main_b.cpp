
#include<iostream>
#include <bits/stdc++.h> //good for online challenges.  Not recommended for production code.
#include <sstream>

struct report{
    std::vector<int> entries;    
    bool safe() const;
};

std::istream& operator >> (std::istream& is, report& r){
    std::istringstream iss;
    std::string line;  
    std::getline(is,line);
    iss.str(line);
    r.entries=std::vector<int>(
        (std::istream_iterator<int>(iss)),
        std::istream_iterator<int>()
    );
    if(r.entries.size()==0){
        is.setstate(std::ios_base::failbit);
    }
    return is;
}


int main(int argc,char** argv){
    std::ifstream inp("../day02/input1.in");
    
    int z=std::accumulate(
        std::istream_iterator<report>(inp),
        std::istream_iterator<report>(),
        (int)0,
        [](int acc, const report& r){
            return acc + (int)r.safe();
        }
    );

    std::cout << "Number reports safe: " << z << std::endl;


    return 0;
}


bool report::safe() const{
    std::vector<int> diff_report=this->entries;

    auto single_safe=[&diff_report](const std::vector<int>& v){
        diff_report=v;
        std::cout << "{";
        for(int i=0;i<v.size();i++){
            std::cout << v[i] << " ";
        }
        std::cout << "}" << std::endl;
        std::adjacent_difference(
            v.begin(),
            v.end(),
            diff_report.begin()
        );
        
        bool direction=diff_report.back()>0;
        bool monotonic_and_safe=std::all_of(
            std::next(diff_report.begin()),
            diff_report.end(),
            [direction](int x){
                return (x > 0) == direction &&
                        abs(x) >= 1 && abs(x) <= 3;
            }
        );
        return monotonic_and_safe;
    };

    std::cout << "<<<<>>>>" << std::endl;
    if(single_safe(entries)) return true;
    std::vector<int> entries_copy(entries);
    entries_copy.pop_back();

    for(int i=0;i<entries.size();i++){
        std::copy(
            entries.begin(),
            entries.begin()+i,
            entries_copy.begin());
        std::copy(
            entries.begin()+i+1,
            entries.end(),
            entries_copy.begin()+i);
        if(single_safe(entries_copy)) return true;
    }
    return false;
}