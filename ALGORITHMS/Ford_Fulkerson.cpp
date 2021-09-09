#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<vector<ll>> adj;

bool bfs(ll source, ll sink, ll v,vector<ll> &parent){
    vector <bool> visited(v,false);
    vector<vector<ll>> residual_graph = adj;
    queue <ll> q;
    q.push(source);
    visited[source]=true;
    while(!q.empty()){
        ll temp = q.front();
        q.pop();
        for(ll i=0;i<=v;i++)
        {
            if(visited[i]==false && residual_graph[temp][i]>0)
            {
                q.push(i);
                visited[i]=true;
                parent[i]=temp;
            }
        }
    }
    if(visited[sink]==true)return true;
    return false;
}

ll Ford_Fulkerson(ll source, ll sink,ll v){
    ll max_flow=0;
    vector<ll> parent(v);
    
    while(bfs(source,sink,v,parent)){

        ll bottleneck_capacity=LLONG_MAX;
        ll temp = sink;
        while(temp!=source){
            bottleneck_capacity=min(bottleneck_capacity,adj[parent[temp]][temp]);
            temp = parent[temp];
        }
        temp = sink;
        while(temp!=source){
            adj[parent[temp]][temp]-=bottleneck_capacity;
            temp = parent[temp];
        }
        max_flow+=bottleneck_capacity;
    }

    return max_flow;
}

int main(){
    ll v,e,i;
    cin>>v>>e;
    adj.resize(v+1,vector<ll>(v+1,0));
    for(i=0;i<e;i++)
    {
        ll u,v,w;
        cin>>u>>v>>w;
        adj[u][v]=w;
    }
    cout<<"Max Flow: "<<Ford_Fulkerson(0LL,5LL,5LL);
    // Replace 0 and 5 with source and sink respectively and v with number of vertices.
return 0;
}

// Sample Input -->
// 5 10
// 0 1 16
// 0 2 13
// 1 2 10
// 1 3 12
// 2 1 4
// 2 4 14
// 3 2 9
// 3 5 20
// 4 3 7
// 4 5 4
// Sample Output
// 23