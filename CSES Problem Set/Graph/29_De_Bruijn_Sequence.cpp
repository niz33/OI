#include<iostream>
#include<vector>
#include<set>
using namespace std;
int n,m;
vector<int> s[200005];
void hei(int x){
    while(s[x].size()){
        int y=s[x][s[x].size()-1];
        s[x].pop_back();
        hei(y);
    }
    cout<<x%2;
}
int main(){
    cin>>n;
    if(n==1){
        cout<<"01";
        return 0;
    }
    for(int i=0;i<(1<<(n-1));i++){
        s[(i<<1)%(1<<(n-1))].push_back(i);
        s[((i<<1)+1)%(1<<(n-1))].push_back(i);
    }
    for(int i=1;i<n-1;i++){
        cout<<0;
    }
    hei(0);
}