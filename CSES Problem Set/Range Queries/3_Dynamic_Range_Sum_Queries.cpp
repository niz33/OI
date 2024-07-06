#include<iostream>
using namespace std;
long long sum[200005];
class SegmentTree{
    public:
    static const int size=200005;
    long long rSum[size*2];
    long long rLazyAdd[size*2];
    long long rLazySet[size*2];

    void maintain(int r,int rl,int rr){
        int rm=(rl+rr)/2;
        if(rLazySet[r]){
            rLazySet[r*2]=rLazySet[r*2+1]=rLazySet[r];
            rSum[r*2]=(rm-rl)*rLazySet[r];
            rSum[r*2+1]=(rr-rm)*rLazySet[r];
            rLazyAdd[r*2]=rLazyAdd[r*2+1]=0;
            rLazySet[r]=0;
        }
        else if(rLazyAdd[r]){
            if(rLazySet[r*2]){
                rLazySet[r*2]+=rLazyAdd[r];
                rLazyAdd[r*2]=0;
            }
            else{
                rLazyAdd[r*2]+=rLazyAdd[r];
            }
            if(rLazySet[r*2+1]){
                rLazySet[r*2+1]+=rLazyAdd[r];
                rLazyAdd[r*2+1]=0;
            }
            else{
                rLazyAdd[r*2+1]+=rLazyAdd[r];
            }
            rSum[r*2]+=(rm-rl)*rLazyAdd[r];
            rSum[r*2+1]+=(rr-rm)*rLazyAdd[r];
            rLazyAdd[r]=0;
        }
        
    }
     
    void add(int al,int ar,long long v,int r,int rl,int rr){
        if(ar<=rl||al>=rr){
            return;
        }
        if(al<=rl&&ar>=rr){
            rSum[r]+=v*(rr-rl);
            if(rLazySet[r]){
                rLazySet[r]+=v;
            }
            else{
                rLazyAdd[r]+=v;
            }
            return;
        }
        int rm=(rl+rr)/2;
        maintain(r,rl,rr);
        add(al,ar,v,r*2,rl,rm);
        add(al,ar,v,r*2+1,rm,rr);
        rSum[r]=rSum[r*2]+rSum[r*2+1];
    }

    void set(int sl,int sr,long long v,int r,int rl,int rr){
        if(sr<=rl||sl>=rr){
            return;
        }
        if(sl<=rl&&sr>=rr){
            rSum[r]=v*(rr-rl);
            rLazySet[r]=v;
            rLazyAdd[r]=0;
            return;
        }
        int rm=(rl+rr)/2;
        maintain(r,rl,rr);
        set(sl,sr,v,r*2,rl,rm);
        set(sl,sr,v,r*2+1,rm,rr);
        rSum[r]=rSum[r*2]+rSum[r*2+1];
    }

    long long query(int ql,int qr,int r,int rl, int rr){
        if(qr<=rl||ql>=rr){
            return 0;
        }
        if(ql<=rl&&qr>=rr){
            return rSum[r];
        }
        maintain(r,rl,rr);
        int rm=(rl+rr)/2;
        return query(ql,qr,r*2,rl,rm)+query(ql,qr,r*2+1,rm,rr);

    }
};

SegmentTree s;

int main(){
    
    int n,q;
    long long t,a,b,x;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>x;
        s.set(i,i+1,x,1,1,n+1);
    }
    for(int i=1;i<=q;i++){
        cin>>t;
        if(t==1){
            cin>>a>>b>>x;
            s.add(a,b+1,x,1,1,n+1);
        }
        if(t==2){
            cin>>a>>b>>x;
            s.set(a,b+1,x,1,1,n+1);
        }
        if(t==3){
            cin>>a>>b;
            cout<<s.query(a,b+1,1,1,n+1)<<endl;
        }
        for(int i=1;i<=n;i++){
            //cout<<query
        }
    }
}