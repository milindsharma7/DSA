/*..............OVERKILL..................*/

#include <bits/stdc++.h>

using namespace std;
using ll = long long int;
#define MAX 21

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

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
            if(k<0)return node;
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

class LazySegmentTree{

    private:
        vector <ll> Tree;
        vector <ll> Lazy;
        vector <ll> arr;
    public:
        LazySegmentTree()
        {
            
        }
        LazySegmentTree(vector <ll> arr){
            this->arr = arr;
            Tree.resize(4*arr.size(),0);
            Lazy.resize(4*arr.size(),0);
            construct(1,0,arr.size()-1);
        }
        void propagate(ll i,ll l,ll r){
            if(l==r){
                Tree[i] += Lazy[i];
                Lazy[i] = 0;
            }
            else{
                Tree[i] += (r-l+1)*Lazy[i];
                Lazy[2*i] += Lazy[i];
                Lazy[2*i+1] += Lazy[i];
                Lazy[i] = 0;
            }
        }
        void construct(ll i,ll l,ll r){
            if(l==r){
                Tree[i] = arr[l];
                return;
            }
            ll mid = (l+r)/2;   
            construct(2*i,l,mid);
            construct(2*i+1,mid+1,r);
            Tree[i] = Tree[2*i] + Tree[2*i+1];
        }
        void update(ll i,ll l,ll r,ll l1,ll r1,ll val){
            ll mid = (l+r)/2;
            propagate(i,l,r);
            if(l1>r || r1<l){
                return;
            }
            if(l1<=l && r1>=r){
                Lazy[i] += val;
                propagate(i,l,r);    
            }
            else{
                update(2*i,l,mid,l1,r1,val);
                update(2*i+1,mid+1,r,l1,r1,val);
                Tree[i] = Tree[2*i] + Tree[2*i+1];
            }
        }
        void update(ll l,ll r,ll val){
            update(1,0,arr.size()-1,l,r,val);
        }
        long long int query(ll i,ll l,ll r,ll l1,ll r1){
            ll mid = (l+r)/2;
            propagate(i,l,r);
            if(l1>r || r1<l){
                return 0;
            }
            else if(l1<=l && r1>=r){
                return Tree[i];
            }
            ll left = query(2*i,l,mid,l1,r1);
            ll right = query(2*i+1,mid+1,r,l1,r1);

            return left + right;
        }
        long long int query(ll l,ll r){
            return query(1,0,arr.size()-1,l,r);
        }
};

class HLD{
    private:
        vector <ll> Subtree;
        
        vector <ll> Parent;
        vector <ll> Heavy;
        vector <ll> Head;
        vector <ll> LinearTree;
        vector <ll> Position;
        vector <ll> Value;
        vector <bool> visited;
        LazySegmentTree T;
        ll idx;
    public:
        vector <ll> Depth;
        HLD(vector <vector<ll>> &tree,ll root){
            Subtree.resize(tree.size(),1);
            Depth.resize(tree.size());
            Parent.resize(tree.size(),root);
            Heavy.resize(tree.size());
            Head.resize(tree.size());
            iota(Head.begin(),Head.end(),0);
            Value.resize(tree.size());
            LinearTree.resize(tree.size());
            Position.resize(tree.size());
            visited.resize(tree.size(),false);
            dfs(tree,root,1);
            visited.clear();
            visited.resize(tree.size(),false);idx = 1;
            dfsHLD(tree,root,root);
            
            T = LazySegmentTree(LinearTree);
        }
        void dfs(vector <vector<ll>> &tree,ll node,ll depth){
            visited[node] = true;ll mx = 0;ll heavy = 0;
            for(ll i=0;i<tree[node].size();i++){
                if(!visited[tree[node][i]]){
                    visited[tree[node][i]] = true;
                    Parent[tree[node][i]] = node;
                    Depth[tree[node][i]] = depth;
                    dfs(tree,tree[node][i],depth+1);
                    Subtree[node] += Subtree[tree[node][i]];
                    if(Subtree[tree[node][i]]>mx){
                        mx = Subtree[node];
                        heavy = tree[node][i];
                    }
                }
                Heavy[node] = heavy;
            }
        }
        void dfsHLD(vector <vector<ll>> &tree,ll node,ll chain){
            // debug(node);
            visited[node] = true;
            LinearTree[idx] = Value[node];
            Head[node] = chain;
            Position[node] = idx;
            idx++;
            if(Heavy[node]!=0){
                dfsHLD(tree,Heavy[node],chain);
            }
            for(ll i=0;i<tree[node].size();i++){
                if(Heavy[node]!=tree[node][i] && visited[tree[node][i]]==false){
                    visited[tree[node][i]] = true;
                    dfsHLD(tree,tree[node][i],tree[node][i]);
                }
            }
        }
        ll LCA(ll u,ll v){
            while(Head[u]!=Head[v]){
                if(Depth[Head[u]]<Depth[Head[v]]){
                    swap(u,v);
                }
                u = Parent[Head[u]];
            }
            if(Depth[u]>Depth[v]){
                swap(u,v);
            }
            return u;
        }
        void LCAUpdate(ll u,ll v){
            // debug(Head,Depth,Parent,Heavy);
            while(Head[u]!=Head[v]){
                if(Depth[Head[u]]<Depth[Head[v]]){
                    swap(u,v);
                }
                T.update(Position[Head[u]],Position[u],1);
                u = Parent[Head[u]];
                // debug(u,v);
            }
            // debug(u,v);
            if(Depth[u]>Depth[v]){
                swap(u,v);
            }
            T.update(Position[u],Position[v],1);
        }
        ll LCAQuery(ll u,ll v){
            debug(Position,u,v);
            // for(ll i=0;i<LinearTree.size();i++){debug(T.query(i,i));}
            // debug(Head,Depth,Parent,Heavy);
            ll sum = 0;
            while(Head[u]!=Head[v]){
                if(Depth[Head[u]]<Depth[Head[v]]){
                    swap(u,v);
                }
                sum += T.query(Position[Head[u]],Position[u]);
                u = Parent[Head[u]];
                // debug(u,v);
            }
            // debug(u,v);
            if(Depth[u]>Depth[v]){
                swap(u,v);
            }
            sum += T.query(Position[u],Position[v]);
            return sum;
        }
};


int main(){
    ll n;cin>>n;
    vector<vector<ll>> tree(n+1);
    vector <pair<ll,ll>> edges;
    for(ll i=1;i<=n-1;i++){
        ll u,v;cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
        edges.push_back({u,v});
    }
    HLD hld(tree,1);
    BinaryLiftingTable T(tree,1);
    ll k;cin>>k;
    while(k--){
        ll u,v;cin>>u>>v;ll lca = hld.LCA(u,v);
        ll d1 = hld.Depth[u];
        ll d2 = hld.Depth[v];
        ll dLCA = hld.Depth[lca];
        if(lca==u || lca==v){
            if(lca!=v)swap(u,v),swap(d1,d2); // v = lca
            ll NodeJustbelowLCA1 = T.query(u,d1-dLCA-1);
            // debug(d1,d2,dLCA,NodeJustbelowLCA1);
            hld.LCAUpdate(u,NodeJustbelowLCA1-1);
            continue;
        }
        ll NodeJustbelowLCA1 = T.query(u,d1-dLCA-1);
        ll NodeJustbelowLCA2 = T.query(v,d2-dLCA-1);
        // debug(d1,d2,dLCA,NodeJustbelowLCA1,NodeJustbelowLCA2);
        hld.LCAUpdate(u,NodeJustbelowLCA1);
        hld.LCAUpdate(v,NodeJustbelowLCA2);
    }
    cout<<hld.LCAQuery(1,n)<<endl;
    for(ll i=0;i<n-1;i++){
        cout<<hld.LCAQuery(edges[i].first,edges[i].second)<<" ";
    }
    return 0;
}