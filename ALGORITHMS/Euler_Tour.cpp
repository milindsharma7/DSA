// https://cses.fi/problemset/task/1137

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

class SegmentTree{

    private:
        vector <ll> Tree;
        vector <ll> arr;
    public:
        SegmentTree(vector <ll> arr){
            this->arr = arr;
            Tree.resize(4*arr.size(),0);
            construct(1,0,arr.size()-1);
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

        void update(ll i,ll pos,ll l,ll r,ll number){
            ll mid = (l+r)/2;
            if(l==r){
                Tree[i] = number;
                return;
            }
            else if(pos<=mid){
                update(2*i,pos,l,mid,number);
            }
            else{
                update(2*i+1,pos,mid+1,r,number);
            }

            Tree[i] = Tree[2*i] + Tree[2*i+1];
        }

        void update(ll pos,ll number){
            update(1,pos,0,arr.size()-1,number);
        }

        long long int query(ll i,ll l,ll r,ll l1,ll r1){
            ll mid = (l+r)/2;
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

ll Time = 0;
vector <ll> Tin,Tout,FlatTree,value;
vector <vector<ll>> tree;
vector <bool> visited;

void dfs(ll node){
    visited[node] = true;
    Tin[node] = Time;
    FlatTree[Time++] = value[node];
    for(ll i=0;i<tree[node].size();i++){
        if(visited[tree[node][i]]==false){
            visited[tree[node][i]] = true;
            dfs(tree[node][i]);
        }
    }
    Tout[node] = Time;
    FlatTree[Time++] = value[node];
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    ll n,q;cin>>n>>q;
    Tin.resize(n+1),Tout.resize(n+1),value.resize(n+1),tree.resize(n+1),visited.resize(n+1),FlatTree.resize(2*n);
    for(ll i=1;i<=n;i++)cin>>value[i];
    for(ll i=0;i<n-1;i++){
        ll u,v;cin>>u>>v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(1LL);
    SegmentTree T(FlatTree);
    while(q--){
        ll t,s;cin>>t>>s;
        if(t==1){
            ll a;cin>>a;
            T.update(Tin[s],a);
            T.update(Tout[s],a);
        }
        else{
            cout<<T.query(Tin[s],Tout[s])/2<<"\n";
        }
    }
    return 0;
}