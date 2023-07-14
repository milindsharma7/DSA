// IMPLEMENTATION OF DINIC'S MAX FLOW ALGORITHM
// SAMPLE TEST CASE GIVEN BELOW
// PRACTICE LINK: https://www.codechef.com/problems/MAXFLOW

#include <bits/stdc++.h>
using namespace std;

class Dinic_Max_Flow{

private:
    vector <vector <long long int>> graph;
    vector <vector <long long int>> Cap;
    vector <vector <long long int>> Residual;
    vector <long long int> Level;
    long long int n;
public:
    Dinic_Max_Flow(vector <vector <long long int>> graph,vector <vector <long long int>> Cap,long long int n){
        this->n = n;
        this->graph = graph;
        this->Cap = Cap;
    }
    void findLevel(long long int source){
        Level = vector <long long int> (n+1,-1);
        Level[source] = 0;
        queue <long long int> q;
        q.push(source);
        while(!q.empty()){
            long long int node = q.front();
            q.pop();
            for(auto i:graph[node]){
                if(Level[i] == -1 && Residual[node][i] > 0){
                    Level[i] = Level[node] + 1;
                    q.push(i);
                }
            }
        }
    }
    long long int maxFlow(long long int source,long long int sink){
        Residual = Cap;
        long long flow = 0;
        vector <long long int> parent(n+1);
        function <bool(long long int)> dfs = [&](long long int node){
            if(node == sink){
                parent[sink] = node;
                return true;
            }
            bool ok = false;
            for(auto i:graph[node]){
                if(Level[i] == Level[node] + 1 && Residual[node][i] > 0){
                    if(dfs(i)){
                        parent[i] = node;
                        ok = true;
                    }
                }
            }
            return ok;
        };
        while(true){
            findLevel(source);
            if(Level[sink] == -1){
                break;
            }
            dfs(source);
            long long int current = sink;
            vector <long long int> path;
            while(current != source){
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(current);
            
            reverse(path.begin(),path.end());
            long long int BottleNeck = 1e18;
            // for(auto i:path)cout << i << " " ;cout << "\n" ;
            for(long long int i=0;i<(long long int)path.size()-1;i++){
                BottleNeck = min(BottleNeck,Residual[path[i]][path[i+1]]);
                // cout << Residual[path[i]][path[i+1]] << "\n" ;
            }
            for(long long int i=0;i<(long long int)path.size()-1;i++){
                Residual[path[i]][path[i+1]] -= BottleNeck;
            }
            flow += BottleNeck;
        }
        return flow;
    }
};

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    long long int nodes,edges;
    cin>>nodes>>edges;
    vector <vector <long long int>> graph(nodes+1),Cap(nodes+1,vector <long long int> (nodes+1));
    for(long long int i=0;i<edges;i++){
        long long int u,v,c;
        cin>>u>>v>>c;
        graph[u].push_back(v);
        Cap[u][v] = c;
    } 
    Dinic_Max_Flow MF(graph,Cap,nodes);
    long long int t;cin>>t;
    while(t--){
        long long int source,sink;
        cin>>source>>sink;
        if(source == sink){
            cout << "0\n";
            continue;
        }
        cout << MF.maxFlow(source,sink) << "\n" ;
    }
}

// Sample Test Case
// 6 9
// 1 3 6
// 1 2 4
// 1 4 10
// 2 4 11
// 4 3 8
// 5 1 12
// 5 2 12
// 3 6 12
// 4 6 12
// 1
// 5 6
// Correct Answer: 23