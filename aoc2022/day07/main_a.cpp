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

struct Directory{
    size_t size;
    std::string name;
    std::vector<Directory> children;
    bool is_file;

    Directory(std::string nm,size_t sz):
        size(sz),
        name(nm),
        is_file(true)
    {}
    template<class Iter>
    Directory(std::string nm,Iter a,Iter b):
        size(0),
        name(nm),
        children{a,b},
        is_file(false)
    {
        for(const auto& c : children){
            size+=c.size;
        }
    }
};



Directory parse_child(std::istream& inp,const std::string& name){
    std::string dolla,cmd,drop;
    inp >> dolla >> cmd;
    std::vector<Directory> children;

    while(inp){
        size_t sz;
        inp >> sz;
        if(!inp.fail()){
            std::string name;
            inp >> name;
            children.emplace_back(name,sz);
            continue;
        }
        inp.clear();
        inp >> dolla;
        if(dolla == "dir") {
            inp >> drop;
            continue;
        }
        if(dolla=="$"){
            std::string next_name;
            inp >> drop >> next_name;
            if(next_name == "..") break;
            auto child=parse_child(inp,next_name);
            children.emplace_back(child);
        }
    }

    return Directory{name,children.begin(),children.end()};
}

Directory parse(std::istream& inp){
    
    std::string dolla,cmd,name;
    inp >> dolla >> cmd >> name; //root is beginning of file.
    return parse_child(inp,name);

}

std::ostream& operator<<(std::ostream& out,const Directory& d){
    
    std::string n=d.name;
    if(n=="/") n="__root__"; 
    
    auto namesize=[&](std::ostream& out){
        out << "name=\"" << n << "\" size=\"" << d.size << "\"";
    };

    if(d.is_file) {
        out << "<file ";
        namesize(out);
        out << "/>";
    }
    else{
        out << "<dir ";
        namesize(out);
        out << ">";
        for(const auto& ch : d.children){
            out << ch;
        }
        out << "</dir>";
    }
    return out;
}

const std::string INPUTFILE="../day07/input.in";
const std::string TESTFILE="../day07/test.in";

int main(int argc,char** argv){
    std::ifstream input(TESTFILE);




    Directory d=parse(input);
    std::cout << d << std::endl;
    return 0;
}