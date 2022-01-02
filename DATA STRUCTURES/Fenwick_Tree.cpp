#include <bits/stdc++.h>

using namespace std;
using ll = long long int;

class FenwickTree{
    private:
        vector <ll> Tree;
    public:
        FenwickTree(vector <ll> &arr){
            ll n = arr.size();
            Tree.resize(n+1,0);
            for(ll i=0;i<n;i++){
                build(i+1,arr[i]);
            }
        }
        void build(ll idx,ll num){
            ll sum = 0;
            while(idx<Tree.size()){
                Tree[idx] += num;
                idx += (idx&-idx);
            }
        }
        long long int prefix(ll idx){
            ll sum = 0;
            while(idx>0){
                sum += Tree[idx];
                idx -= (idx&-idx);
            }
            return sum;
        }
        long long int query(ll l,ll r){
            return prefix(r) - prefix(l-1);
        }
        void update(ll idx,ll num){
            ll old = query(idx,idx);
            ll delta = num - old;
            build(idx,delta);
        }
};

int main(){
    /*      FENWICK TREE/BINARY INDEXED TREE
            1)  QUERY(l,r) -> return sum of the range (l,r) (one based indexing)
            2)  UPDATE(idx,num) -> updates the number at idx with num (one based indexing)
    */
    vector <ll> v = {1,2,3,4,5};
    FenwickTree F(v);
    cout<<F.query(1,2)<<endl;
    cout<<F.query(3,3)<<endl;
    cout<<F.query(2,5)<<endl;
    F.update(4,69);
    cout<<F.query(3,5)<<endl;
    F.update(2,420);
    cout<<F.query(1,5)<<endl;
    return 0;
}