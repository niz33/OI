#include<iostream>
#include<vector>
using namespace std;

class AdjacencyMatrix{
public:
    static const int vertexCnt=505;
    bool edges[vertexCnt][vertexCnt];
    bool directed=false;
    void add_edge(int u,int v){
        edges[u][v]=1;
        if(!directed){
            edges[v][u]=1;
        }
    }
};

template<typename T> class WeightedAdjacencyMatrix{
public:
    static const int vertexCnt=505;
    bool edges[vertexCnt][vertexCnt];
    T weights[vertexCnt][vertexCnt];
    bool directed=false;
    void add_edge(int u,int v,T w){
        edges[u][v]=1;
        weights[u][v]=w;
        if(!directed){
            edges[v][u]=1;
            weights[v][u]=w;
        }
    }
};

class AdjacencyList{
public:
    static const int vertexCnt=505;
    vector<int> edges[vertexCnt];
    bool directed=false;
    void add_edge(int u,int v){
        edges[u].push_back(v);
        if(!directed){
            edges[v].push_back(u);
        }
    }
};

template<typename T> class WeightedAdjacencyList{
public:
    static const int vertexCnt=505;
    vector<tuple<int,T>> edges[vertexCnt];
    bool directed=false;
    void add_edge(int u,int v,T w){
        edges[u].push_back(make_tuple(v,w));
        if(!directed){
            edges[v].push_back(make_tuple(u,w));
        }
    }
};