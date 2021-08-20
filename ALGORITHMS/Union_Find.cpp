#include <bits/stdc++.h>
using namespace std;

void Make_Set(vector<pair<int,int>> &dsu,int u){

    if(dsu[u].first==u)
        return;
    dsu[dsu[u].first].second+=1;
    Make_Set(dsu,dsu[u].first);
}

int Find(vector<pair<int,int>> &dsu,int u){

    if(dsu[u].first==u)
        return u;
    return Find(dsu,dsu[u].first);
}

int Union(vector<pair<int,int>> &dsu,int u,int v){

    int f1=Find(dsu,u);
    int f2=Find(dsu,v);
    
    if(dsu[f2].second>=dsu[f1].second)
    {
        dsu[f1].first=f2;
        Make_Set(dsu,u);
    }
}

int main(){
    cout<<"Enter number of edges and vertices in graph"<<endl;
    int n; cin>>n;
    cout<<"Enter number of edges"<<endl;
    int m;cin>>m;
    cout<<"Enter all the edges"<<endl;

    vector<pair<int,int>> dsu(n+1); 

    for(int i=0;i<n+1;i++)
    {   
        dsu[i].first=i;
        dsu[i].second=0;
    }

    for(int i=0;i<m;i++)
    {

    }
    return 0;
}