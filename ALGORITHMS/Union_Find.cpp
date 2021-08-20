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

bool Union(vector<pair<int,int>> &dsu,int u,int v){

    int f1=Find(dsu,u);
    int f2=Find(dsu,v);

    if(f1==f2)
        return true;
    
    if(dsu[u].second>=dsu[v].second)
    {
        dsu[v].first=u;
        Make_Set(dsu,v);
    }
    else
    {
        dsu[u].first=v;
        Make_Set(dsu,u);
    }

    return false;
}

int main(){
    cout<<"Enter number vertices in graph"<<endl;
    int n;cin>>n;
    cout<<"Enter number of edges"<<endl;
    int m;cin>>m;
    cout<<"Enter all the edges"<<endl;

    vector<pair<int,int>> dsu(n+1); 

    for(int i=0;i<n+1;i++)
    {   
        dsu[i].first=i;
        dsu[i].second=0;
    }

    bool contains_cycle=false;
    for(int i=0;i<m;i++)
    {
        int u,v;cin>>u>>v;
        if(Union(dsu,u,v))
            contains_cycle=true;
    }

    if(contains_cycle)cout<<"Graph contains cycle"<<endl;
    else cout<<"Graph does not contain cycle"<<endl;
    
    return 0;
}