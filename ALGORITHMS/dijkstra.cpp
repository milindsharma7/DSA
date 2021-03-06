/*
    MILIND SHARMA
    22-08-2021
    12:46 AM
    DIJKSTRA
*/

/*
    NOTE:-
    1) Dijkstra can be implemented using priority queue also, just declare it in reverse order.
    2) There is no need of visited array since we might need to apply bfs on a node which we have already visited to relax the node more than once.
    3) This solution is based on codeforces problemset :- https://codeforces.com/contest/20/problem/C
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> shortest_path;

void dijkstra(vector<vector<pair<int,int>>> &graph,vector<long long int> &distance,vector<int> &path)
{
    set<pair<int,int>> s;
    s.insert({distance[1],1});

    while (!s.empty())
    {
        pair<int,int> tmp= *s.begin();
        s.erase(tmp);
        for(int i=0;i<graph[tmp.second].size();i++)
        {
            if(distance[graph[tmp.second][i].second]>distance[tmp.second]+graph[tmp.second][i].first)
            {
                distance[graph[tmp.second][i].second]=distance[tmp.second]+graph[tmp.second][i].first;
                path[graph[tmp.second][i].second]=tmp.second;
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
    cout<<"Enter the number of vertices in the graph"<<endl;
    cin>>n;

    int m;
    cout<<"Enter the number of edges in the graph"<<endl;
    cin>>m;

    vector<vector<pair<int,int>>> graph(n+1);
    vector<long long int> distance(n+1,LLONG_MAX);
    vector<int> path(n+1);
    distance[1]=0;

    cout<<"Enter the edge and weight u,v,w"<<endl;

    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        graph[u].push_back({w,v});
        graph[v].push_back({w,u});
    }

    dijkstra(graph,distance,path);

    bool f1=false;

    if(distance[n]==LLONG_MAX)f1=true;

    (f1==false)?find_path(path,n):shortest_path.push_back(-1);

    if(f1==false)shortest_path.push_back(1);

    for(int i=shortest_path.size()-1;i>=0;i--)
    {
        cout<<shortest_path[i]<<" ";
    }

    return 0;
}