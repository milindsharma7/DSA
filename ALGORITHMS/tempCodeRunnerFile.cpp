#include <bits/stdc++.h>
using namespace std;

vector<int> shortest_path;

void dijkstra(vector<vector<pair<int,int>>> &graph,vector<bool> &visited,vector<long long int> &distance,vector<int> &path)
{
    set<pair<int,int>> s;
    s.insert({distance[1],1});

    while (!s.empty())
    {
        pair<int,int> tmp= *s.begin();
        s.erase(tmp);
        visited[tmp.second]=true;

        for(int i=0;i<graph[tmp.second].size();i++)
        {
            if(distance[graph[tmp.second][i].second]>distance[tmp.second]+graph[tmp.second][i].first)
            {
                distance[graph[tmp.second][i].second]=distance[tmp.second]+graph[tmp.second][i].first;
                path[graph[tmp.second][i].second]=tmp.second;
            }
            if(visited[graph[tmp.second][i].second]==false){
                s.insert({graph[tmp.second][i].first,graph[tmp.second][i].second});
            }
        }
    }
    
}

void find_path(vector<int> &path,int i)
{
    shortest_path.push_back(i);

    if(path[i]==1)return;

    find_path(path,path[i]);
}

int main(){

    int n;
    // cout<<"Enter the number of vertices in the graph"<<endl;
    cin>>n;

    int m;
    // cout<<"Enter the number of edges in the graph"<<endl;
    cin>>m;

    vector<vector<pair<int,int>>> graph(n+1);
    vector<bool> visited(n+1,false);
    vector<long long int> distance(n+1,INT32_MAX);
    vector<int> path(n+1);
    distance[1]=0;

    // cout<<"Enter the edge and weight u,v,w"<<endl;

    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        graph[u].push_back({w,v});
        graph[v].push_back({w,u});
    }

    dijkstra(graph,visited,distance,path);

    bool f1=false;

    for(int i=1;i<distance.size();i++)
        if(distance[i]==INT32_MAX)f1=true;

    (f1==false)?find_path(path,n):shortest_path.push_back(-1);

    if(f1==false)shortest_path.push_back(1);

    for(int i=shortest_path.size()-1;i>=0;i--)
    {
        cout<<shortest_path[i]<<" ";
    }

    return 0;
}