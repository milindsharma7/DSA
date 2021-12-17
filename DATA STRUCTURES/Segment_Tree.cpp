#include <bits/stdc++.h>

using ll = long long int;
using namespace std;

class SegmentTree{

    private:
        vector <ll> Tree = vector <ll>(1000000,0);
        vector <ll> arr;
    public:
        SegmentTree(vector <ll> arr){
            this->arr = arr;
        }
        void construct(ll i,ll l,ll r){
            if(l==r){
                Tree[i] = arr[l-1];
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
                Tree[l] = number;
            }
            else if(pos<=mid){
                update(2*i,pos,l,mid,number);
            }
            else{
                update(2*i+1,pos,mid+1,r,number);
            }

            Tree[i] = Tree[2*i] + Tree[2*i+1];
        }
        int query(ll i,ll l,ll r,ll l1,ll r1){
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
};

int main(){
    vector <ll> v = {1,3,5,7,9,11};
    SegmentTree T(v);
    T.construct(1,1,6);
    cout<<T.query(1,1,6,4,6)<<endl;
    cout<<T.query(1,1,6,1,3)<<endl;
    cout<<T.query(1,1,6,1,1)<<endl;
} 