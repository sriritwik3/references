//link to the problem - https://www.spoj.com/problems/KQUERY/

// Normal implementation of mergesort tree would be sufficient.

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
 
//mrt must be initialised as vector<ll> mrt[N];
 
void buildMergeSortTree(ll a[],vector<ll> mrt[],ll si,ll ss,ll se){
    if(ss == se){
        mrt[si].push_back(a[ss]);
        return;
    }
    ll mid = ss + (se-ss)/2;
    buildMergeSortTree(a,mrt,2*si,ss,mid);
    buildMergeSortTree(a,mrt,2*si+1,mid+1,se);
    ll i=0,j=0;
    while(i < mrt[2*si].size() && j < mrt[2*si+1].size()){
        if(mrt[2*si][i] <= mrt[2*si+1][j]){
            mrt[si].push_back(mrt[2*si][i]);
            i++;
        }
        else mrt[si].push_back(mrt[2*si+1][j]), j++;
    }
    while(i<mrt[2*si].size()) 
        mrt[si].push_back(mrt[2*si][i]),i++;
    while(j<mrt[2*si+1].size())
        mrt[si].push_back(mrt[2*si+1][j]),j++;
}
 
ll queryMergeSortTree(vector<ll> mrt[],ll si,ll ss,ll se,ll qs,ll qe,ll k){
    if(qe < ss || qs > se) return 0;
    if(ss >= qs && qe >= se)
        return (mrt[si].end() - upper_bound(mrt[si].begin(),mrt[si].end(),k));
    ll mid = ss + (se-ss)/2;
    return queryMergeSortTree(mrt,2*si,ss,mid,qs,qe,k) + queryMergeSortTree(mrt,2*si+1,mid+1,se,qs,qe,k);
}
 
 
int32_t main()
{
    fastio;
    ll n;
    cin >> n;
    ll a[n+1];
    for(ll i=1;i<=n;i++) cin >> a[i];
    vector<ll> st[4*n+4];
    buildMergeSortTree(a,st,1,1,n);
    ll q;
    cin >> q;
    while(q--){
        ll l,r,k;
        cin >>  l >> r >> k;
        cout << queryMergeSortTree(st,1,1,n,l,r,k) << '\n';
    }
    return 0;
}