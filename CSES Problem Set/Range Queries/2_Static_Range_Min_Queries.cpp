#include<iostream>
using namespace std;
long long sum[200005];
class SegmentTree{
    static const int size=200005;
    long long rMin[size*2];
    long long rLazy[size*2];

    void maintain(int r,int rl,int rr){
        if(!rLazy[r]){
            return;
        }
        int rm=(rl+rr)/2;
        rMin[r]=min(rMin[r],rLazy[r]);
        
    }
    
    void 
};