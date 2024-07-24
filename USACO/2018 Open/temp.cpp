#include<bits/stdc++.h>
using namespace std;
 
#define REP(i, n) for (int i = 0; i < n; ++i)
#define REP2(i, l, r) for (int i = l; i < r; ++i)
#define FOR(i, n) for (int i = n - 1; i >= 0; --i)
#define FOR2(i, l, r) for (int i = r; i > l; --i)
#define ll long long
#define p pair<int, int>
#define x first
#define y second
#define mp make_pair
//#define MOD 998244353
#define V vector
#define all(v) begin(v), end(v)

/*Solution
initially, root the tree and initialise the binary lifting structure

for each additional edge:
    its weight is c and connect l and r, with depth[l] <= depth[r]
    let anc = lca(l, r)
    if anc = r:
        this edge can only be used to patch any edge on the path from l to r
    else:
        this edge can only patch edges belong to subtree of anc, but not subtree of l and r
-> for any main edge, we can generate a set of possible replacements, and choose the minimum 
However, it is unnecessary to update the list if we already know the minimum
->  sort all additional edges in increasing order of weitght
    iterate over them, with each:
    update all the main edges, and put a flag on them, so that they are fixed

let ans[i] denotes the answer for the main edge which connects i and par[i][0]
to travel the tree faster, we maintain an array of high[N], 
in which high[i] = i, if ans[i] = 0, we say i is unprocessed
                   lowest unprocessed ancestor of i, otherwise
for each iteration:
    update ans[i] for all unprocessed i on the path from l/r to anc, but not anc
    update high[i] for all i on the path from l/r to anc
    psuedo code:
        additional edge -> extract l, r, c;
        get anc = lca(l, r);
        _l = high[l];
        recursively update nodes (from _l to anc):
*/

#define N 50000
#define L 16
int n;
V<int> depth, deg, ans, high;
V<V<int>> adj, par;

int findCenter(){
    queue<int> q;
    bitset<N + 1> vis(0);
    for (int i = 1; i <= n; ++i){
        if (deg[i] == 1){
            q.push(i);
            vis[i] = 1;
        }
    }
    while (q.size() > 1){
        int v = q.front();
        q.pop();
        for (int u : adj[v]){
            if (!vis[u]){
                if (--deg[u] == 1){
                    q.push(u);
                    vis[u] = 1;
                }
            }
        }
    }
    return q.front();
}

void dfs(int v){
    for (int u : adj[v]){
        if (u == par[v][0]){continue;}
        par[u][0] = v;
        depth[u] = depth[v] + 1;
        dfs(u);
    }
}

void sparseTable(){
    for (int i = 1; i < L; ++i){
        for (int j = 1; j <= n; ++j){
            int anc = par[j][i - 1];
            if (!anc){continue;}
            par[j][i] = par[anc][i - 1];
        }
    }
}

int kthAncestor(int t, int k){
    int cnt = 0;
    while (k > 0 && t > 0){
        if (k & 1){
            t = par[t][cnt];
        }
        k >>= 1;
        ++cnt;
    }
    return t;
}

int lca(int l, int r){
    if (depth[r] > depth[l]){swap(l, r);}
    int delta = depth[l] - depth[r];
    l = kthAncestor(l, delta);
    if (l == r){return r;}
    int d = log2(depth[r]);
    int ans, a, b;
    while (d >= 0){
        a = par[l][d];
        b = par[r][d];
        if (a != b){
            l = a;
            r = b; 
        }else{ans = a;}
        --d;
    }
    return ans;
}

int nxt(int node){
    if (high[node] == node){return node;}
    // node is unprocessed, so return it

    else{return high[node] = nxt(high[node]);}
    // path compression -> update high lazily
}

void proces(int srt, int des, int c){
    // if we go beyond the subtree of anc(des in function), terminate
    if (depth[srt] <= depth[des]){return;}

    // else, srt denote the unprocessed node -> update this node
    ans[srt] = c;

    // go to the next unprocessed node   
    high[srt] = par[srt][0]; 
    proces(nxt(srt), des, c);
    /*
    because high[srt] = srt, since srt is previously unprocessed
    we go to precessdor p of srt
        if p is unprocessed, then high[p] = p -> p = new srt
        else, go to high[p], update high[srt] (in nxt function)
    */
}

void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	//freopen((name+".in").c_str(),"r",stdin);
	//freopen((name+".out").c_str(),"w",stdout);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setIO("disrupt");
    int q, l, r, c;
    cin>>n>>q;
    V<p> edges(n - 1);

    ans.resize(n + 1);
    high.resize(n + 1);
    adj.resize(n + 1);
    par.resize(n + 1);
    depth.resize(n + 1);
    deg.resize(n + 1);
    REP2(i, 1, n + 1){
        par[i].resize(L);
    }
    REP(i, n - 1){
        cin>>l>>r;
        adj[l].push_back(r);
        adj[r].push_back(l);
        ++deg[l];
        ++deg[r];
        edges[i] = {l, r};
    }
    int cen = findCenter();
    depth[cen] = 0;
    par[cen][0] = 0;
    dfs(cen);
    sparseTable();

    V<pair<int, p>> add(q);
    REP(i, q){
        cin>>l>>r>>c;
        add[i] = pair<int, p>(c, {l, r});
    }
    sort(all(add));

    REP2(i, 1, n + 1){
        ans[i] = -1;
        high[i] = i;
    }
    int i = 0;
    REP(i, q){
        l = add[i].y.x; 
        r = add[i].y.y;
        c = add[i].x;
        if (depth[l] < depth[r]){swap(l, r);}
        int anc = lca(l, r);
        proces(nxt(l), anc, c);
        proces(nxt(r), anc, c);
    }

    REP(i, n - 1){
        l = edges[i].x; r = edges[i].y;
        if (depth[r] > depth[l]){swap(l, r);}
        cout<<ans[l]<<'\n';
    }
    return 0;
}