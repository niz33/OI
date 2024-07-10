#include<iostream>
using namespace std;
int n,U;
string st;
class matrix{
public:
    matrix(){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                v[i][j]=0;
            }
        }
    }
    long long v[8][8];
    matrix operator*(matrix m){
        matrix res;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                for(int k=0;k<8;k++){
                    res.v[i][j]+=v[i][k]*m.v[k][j];
                }
            }
        }
        return res;
    }
};
matrix b,e,s,ii,id,t[800000];
void init(){
    for(int i=0;i<8;i++){
        b.v[i][i]=1;
        e.v[i][i]=1;
        s.v[i][i]=1;
        ii.v[i][i]=1;
        id.v[i][i]=1;
    }
    b.v[0][0]=0;
    b.v[0][1]=1;
    b.v[7][1]=1;
    e.v[5][0]=1;
    e.v[1][2]=1;
    e.v[1][1]=0;
    e.v[5][5]=0;
    e.v[7][0]=1;
    s.v[2][2]=0;
    s.v[3][3]=0;
    s.v[2][3]=1;
    s.v[3][4]=1;
    s.v[7][0]=1;
    ii.v[7][0]=1;
    ii.v[4][4]=0;
    ii.v[4][5]=1;
    id.v[7][0]=1;
}
void build(int x,int l,int r){
    if(l==r){
        switch(st[l]){
            case 'b':t[x]=b;break;
            case 'e':{t[x]=e;t[x].v[5][6]=n-l;break;}
            case 's':t[x]=s;break;
            case 'i':t[x]=ii;break;
            default:t[x]=id;break;
        }
        return;
    }
    int m=(l+r)/2;
    build(2*x,l,m);
    build(2*x+1,m+1,r);
    t[x]=t[2*x]*t[2*x+1];
}
void update(int p,int v,int x,int l,int r){
    if(l==r){
        switch(v){
            case 'b':t[x]=b;break;
            case 'e':{t[x]=e;t[x].v[5][6]=n-l;break;}
            case 's':t[x]=s;break;
            case 'i':t[x]=ii;break;
            default:t[x]=id;break;
        }
        return;
    }
    int m=(l+r)/2;
    if(p<=m) update(p,v,2*x,l,m);
    else update(p,v,2*x+1,m+1,r);
    t[x]=t[2*x]*t[2*x+1];
}
int main(){
    cin>>st;
    n=st.size();
    init();
    build(1,0,n-1);
    cout<<t[1].v[7][6]<<endl;
    cin>>U;
    for(int i=0;i<U;i++){
        int p;
        char v;
        cin>>p>>v;
        update(p-1,v,1,0,n-1);
        cout<<t[1].v[7][6]<<endl;
    }
}