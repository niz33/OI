#include<iostream>
using namespace std;
int n[4]={4,6,8,9};
int main(){
    for(int a=0;a<4;a++){
        for(int b=0;b<4;b++){
            for(int c=0;c<4;c++){
                for(int d=0;d<4;d++){
                    if(n[a]+n[b]+n[c]+n[d]==20){
                        cout<<n[a]<<" "<<n[b]<<" "<<n[c]<<" "<<n[d]<<endl;
                    }
                }
            }
        }
    }
}