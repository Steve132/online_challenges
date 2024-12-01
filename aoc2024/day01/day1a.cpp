#include<iostream>


int main(int argc,char** argv){
    std::ifstream inp("../test1.in");
    unsigned int ctotal=0;
    unsigned int cmax[3]={0,0,0};
    //unsigned int cmini=

    while(inp){
        unsigned int c;
        inp >> c;
        
        ctotal+=c;
        int cmini=-1;
        for(int i=0;i<3;i++)
        {
            if(ctotal > cmax[i]){
                cmaxi=i;
            }
        }
        if(cmaxi >=0 ){
            cmax[i] = ctotal;
        }

        inp.ignore();
        if(inp.peek()=='\n') {
            ctotal=0;
        }
    }
    cout << "the max is " << cmax << std::endl;    

    return 0;
}