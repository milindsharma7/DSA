#include <bits/stdc++.h>

using ll = long long int;
using namespace std;

class LazySegmentTree{

    private:
        vector <ll> Tree;
        vector <ll> Lazy;
        vector <ll> arr;
    public:
        LazySegmentTree(vector <ll> arr){
            this->arr = arr;
            Tree.resize(4*arr.size(),0);
            Lazy.resize(4*arr.size(),0);
            construct(1,0,arr.size()-1);
        }
        void propogate(ll i,ll l,ll r){
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
            propogate(i,l,r);
            if(l1>r || r1<l){
                return;
            }
            if(l1<=l && r1>=r){
                Lazy[i] += val;
                propogate(i,l,r);    
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
            propogate(i,l,r);
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

int main(){
    // Query -> T.query(left,right) (zero based indexing)
    // update -> T.update(left,right,number to be added to the range) (zero based indexing)
    
    ll n; cin>>n;
    vector <ll> v(n);ll i;
    for(ll i=0;i<n;i++){
        cin>>v[i];
    }
    ll q;cin>>q;
    LazySegmentTree T(v);
    while(q--){
        ll a,l,r;
        cin>>a>>l>>r;
        if(a==0){
            cout<<T.query(l,r)<<"\n";
        }
        else{
            ll val;cin>>val;
            T.update(l,r,val);
        }
    }
} 

