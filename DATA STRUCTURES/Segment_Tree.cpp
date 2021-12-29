#include <bits/stdc++.h>

using ll = long long int;
using namespace std;

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

int main(){
    // Query -> T.query(left,right) (zero based indexing)
    // update -> T.update(position,updated number) (zero based indexing)
    
    vector <ll> v = {1,3,5,7,9,11};
    SegmentTree T(v);
    cout<<T.query(3,5)<<endl;
    cout<<T.query(0,2)<<endl;
    cout<<T.query(0,0)<<endl;
    T.update(4,10);
    cout<<T.query(3,5)<<endl;
    cout<<T.query(4,4)<<endl;
} 