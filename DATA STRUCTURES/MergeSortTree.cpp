/*
    IF MEMORY LIMIT IS NOT TIGHT, YOU CAN USE MERGE SORT TREE TO FIND
    NUMBER OF ELEMENTS SMALLER THAN K FOR SEVERAL QUERIES IN A RANGE
*/

#include <bits/stdc++.h>

using namespace std;
using ll = long long int;

class MergeSortTree{

    private:
        vector <vector<ll>> Tree;
        vector <ll> arr;
    public:
        MergeSortTree(vector <ll> arr){
            this->arr = arr;
            Tree.resize(4*arr.size());
            construct(1,0,arr.size()-1);
        }
        void merge(ll i){
            ll n1 = Tree[2*i].size(), n2 = Tree[2*i+1].size();
            ll x = 0, y = 0;

            while(x<n1 && y<n2){
                if(Tree[2*i][x]<Tree[2*i+1][y]){
                    Tree[i].push_back(Tree[2*i][x++]);
                }
                else Tree[i].push_back(Tree[2*i+1][y++]);
            }
            while(x<n1)Tree[i].push_back(Tree[2*i][x++]);
            while(y<n2)Tree[i].push_back(Tree[2*i+1][y++]);
        }
        void construct(ll i,ll l,ll r){
            if(l==r){
                Tree[i].push_back(arr[l]);
                return;
            }
            ll mid = (l+r)/2;   
            construct(2*i,l,mid);
            construct(2*i+1,mid+1,r);
            merge(i);
        }

        long long int query(ll i,ll l,ll r,ll l1,ll r1,ll k){
            ll mid = (l+r)/2;
            if(l1>r || r1<l){
                return 0;
            }
            else if(l1<=l && r1>=r){
                return lower_bound(Tree[i].begin(),Tree[i].end(),k)-Tree[i].begin();
            }
            ll left = query(2*i,l,mid,l1,r1,k);
            ll right = query(2*i+1,mid+1,r,l1,r1,k);

            return left + right;
        }

        long long int query(ll l,ll r,ll k){
            return query(1,0,arr.size()-1,l,r,k);
        }
};

int main(){
    
    return 0;
}