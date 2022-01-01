#include <bits/stdc++.h>

using namespace std;
using ll = long long int;

class SparseTable{
    private:
        vector<vector<ll>> Table;
        vector<ll> log;
    public:
        SparseTable(vector<ll> arr){
            ll n = arr.size();
            ll k = log2(n);
            Table.resize(k+1,vector<ll>(n,0));
            log.resize(n+1);
            Table[0] = arr;
            for(ll i=1;i<=k;i++){
                for(ll j=0;j<=n-(1LL<<i);j++){
                    Table[i][j] = min(Table[i-1][j],Table[i-1][j+(1LL<<(i-1LL))]);
                }
            }
            for(ll i=1;i<=n;i++){
                log[i] = log2(i);
            }
        }
        long long int query(ll l,ll r){
            ll k = log[r-l+1];
            return min(Table[k][l-1],Table[k][r-(1LL<<k)]);
        }
};

int main(){
    /*              SPARSE TABLE 
       ANSWER MIN/MAX/GCD RANGE QUERY IN O(1) TIME
           INPUT QUERY IN 1 BASED INDEXING
    */
    vector<ll> v = {6,5,4,3,2,1};
    SparseTable S(v);
    cout<<S.query(1,6)<<endl;
    cout<<S.query(2,4)<<endl;
    cout<<S.query(3,6)<<endl;
    cout<<S.query(1,5)<<endl;
    cout<<S.query(3,3)<<endl;
    return 0;
}