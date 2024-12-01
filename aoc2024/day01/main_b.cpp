
#include<iostream>
#include <bits/stdc++.h> //good for online challenges.  Not recommended for production code.

int main(int argc,char** argv){
    std::ifstream inp("../day01/input1.in");

    std::vector<size_t> interleaved((
        std::istream_iterator<size_t>(inp)),
        std::istream_iterator<size_t>()
    );

    size_t N=interleaved.size()/2;
    std::vector<size_t> a(N),b(N);
    for(size_t i=0;i<N;i++){
        a[i]=interleaved[2*i];
        b[i]=interleaved[2*i+1];
    }
    std::unordered_map<size_t,size_t> m;
    for(size_t i=0;i<N;i++){
        m.emplace(b[i],0).first->second++;
    }

    size_t total_similarity=0;
    for(size_t i=0;i<N;i++){
        total_similarity+=a[i]*m[a[i]];
    }
    std::cout << total_similarity << std::endl;

    return 0;
}