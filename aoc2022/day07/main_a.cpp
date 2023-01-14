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

    template<class F>
    void walk(F&& f) {
        f(*this);
        for(auto& ch : children){
            ch.walk(f);
        }
    };
    template<class F>
    void walk(F&& f) const {
        f(*this);
        for(const auto& ch : children){
            ch.walk(f);
        }
    };
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
    struct inner{
        static std::ostream& print_indent(std::ostream& out,int level){
            for(int i=0;i<level;i++) out << "\t";
            return out;
        }
        static void pprint(std::ostream& out,const Directory& d,int level){
            std::string n=d.name;
            if(n=="/") n="__root__"; 
            
            auto namesize=[&](std::ostream& out){
                out << "name=\"" << n << "\" size=\"" << d.size << "\"";
            };

            if(d.is_file) {
                print_indent(out,level) << "<file ";
                namesize(out);
                out << "/>\n";
            }
            else{
                print_indent(out,level) << "<dir ";
                namesize(out);
                out << ">\n";
                for(const auto& ch : d.children){
                    pprint(out,ch,level+1);
                }
                print_indent(out,level) << "</dir>\n";
            }
        }
    };
    inner::pprint(out,d,0);
    return out;
}

const std::string INPUTFILE="../day07/input.in";
const std::string TESTFILE="../day07/test.in";

int main(int argc,char** argv){
    std::ifstream input(INPUTFILE);




    Directory root=parse(input);
    std::cout << root << std::endl;

    size_t tot=0;
    root.walk([&tot](const Directory& d){
        if(d.size <=100000 && !d.is_file ){
            std::cout << d.name << std::endl;
            tot+=d.size;
        }
    }
    );
    std::cout << tot << std::endl;
    return 0;
}