#include<iostream>
using namespace std;
int main(){
    int a,b;
    cin>>a>>b;
    while(b!=0){
        cout<<a<<" "<<b<<"*"<<a/b<<"+"<<a%b<<endl;
        int c;
        c=b;
        b=a%b;
        a=c;
    }
}