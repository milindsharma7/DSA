#include <bits/stdc++.h>
using namespace std;

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

    if(dsu[f1].second>dsu[f2].second)
    {
        dsu[f2].first=f1;
    }

    else if(dsu[f1].second==dsu[f1].second)
    {
        dsu[f2].first=dsu[f1].first;
        dsu[f1].second++;
    }

    else
    { 
        dsu[f1].first=f2;
    }
    return false;
}

int main(){

    cout<<"Enter number of vertices in the graph"<<endl;

    int n;cin>>n;

    cout<<"Enter the number of edges in the graph"<<endl;

    int m;cin>>m;

    vector<pair<int,pair<int,int>>> graph;

    vector<pair<int,int>> dsu(n+1);

    for(int i=0;i<n+1;i++)
    {
        dsu[i].first=i;
        dsu[i].second=0;
    }

    cout<<"Enter the edges of the graph along with the weight"<<endl;

    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        graph.push_back({w,{u,v}});
    }

    // lambda function convenient to sort
    sort(graph.begin(),graph.end(),[](pair<int, pair<int,int>> a,pair<int, pair<int,int>> b){
        return a.first<b.first;
    });

    vector<pair<int,pair<int,int>>> ans;

    for(int i=0;i<m;i++)
    {
        if(Union(dsu,graph[i].second.first,graph[i].second.second)==false)
        {
            ans.push_back(graph[i]);
        }
    }

    cout<<"Minimum spanning tree:"<<endl;

    for(int i=0;i<ans.size();i++)
    {
        cout<<"Edge: "<<ans[i].second.first<<" "<<ans[i].second.second<<" "<<"Weight: "<<ans[i].first<<endl;
    }

    return 0;
}