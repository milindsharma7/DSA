/*
    BINARY LIFTING - Kth ANCESTOR OF A NODE IN A TREE IN Log(K) TIME WITH PREPROCESSING N*Log(N);
    1) TAKE INPUT OF TREE IN GRAPH FORM THEN CONVERT TO PARENT ARRAY USING DFS FUNCTION
    2) IF PARENT ARRAY IS ALREADY AVAILABLE IN THE PROBLEM THEN NO NEED OF DFS
    3) MAX = MAXIMUM NUMBER OF BITS IN K, ADJUST ACCORDINGLY
    4) NODES ARE ASSUMED TO BE NUMBERED FROM 1 TO N IF THERE IS A ZERO NODE THEN MAKE CHANGES ACCORDINGLY IN LOOP
*/

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define MAX 18

class BinaryLiftingTable{
    private:
        vector<vector<ll>> Table;
        vector<ll> Parent;
        vector<bool> visited;
    public:
        BinaryLiftingTable(vector<vector<ll>> &tree,ll root){
            Table.resize(MAX,vector<ll>(tree.size(),0));
            Parent.resize(tree.size());
            visited.resize(tree.size(),false);
            dfs(tree,root,root);
            build();
        }
        void build(){
            Table[0] = Parent;
            for(ll i=1;i<MAX;i++){
                for(ll j=1;j<Table[i].size();j++){
                    Table[i][j] = Table[i-1][Table[i-1][j]];
                }
            }
        }
        ll query(ll node,ll k){
            ll ans = node;
            for(ll i=0;i<MAX;i++){
                if(k&(1<<i)){
                    ans = Table[i][ans];
                }
            }
            return ans;
        }
        void dfs(vector<vector<ll>> &tree,ll node,ll parent){
            visited[node] = true;
            Parent[node] = parent;
            for(auto i:tree[node]){
                if(visited[i]==false){
                    visited[i] = true;
                    dfs(tree,i,node);
                }
            }
        }
};

int main(){
    ll nodes,edges;
    cin>>nodes>>edges;
    vector<vector<ll>> tree(nodes+1);
    for(ll i=0;i<edges;i++){
        ll u,v;cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    BinaryLiftingTable BT(tree,1);
    ll q;cin>>q; // QUERIES
    while(q--){
        ll k,node;cin>>node>>k;
        cout<<BT.query(node,k)<<endl;
    }
    return 0;
}