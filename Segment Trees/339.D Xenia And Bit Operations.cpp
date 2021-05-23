//Link to the question - https://codeforces.com/problemset/problem/339/D
//Normal segment trees with storing the level of the tree at each node.

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
 
 
 
void buildSegmentTree(ll a[],pair<ll,ll> st[],ll si,ll ss, ll se){
    if(ss == se){
        st[si].first = a[se];
        st[si].second = 1;
        return;
    }
    ll mid = ss + (se-ss)/2;
    buildSegmentTree(a,st,2*si,ss,mid);
    buildSegmentTree(a,st,2*si+1,mid+1,se);
    if(st[2*si].second == 1){
        st[si].second = 0;
        st[si].first = (st[2*si].first | st[2*si+1].first);
    }
    else {
        st[si].second = 1;
        st[si].first = (st[2*si].first ^ st[2*si+1].first);
    }
}
 
ll segmentTreeQuery(pair<ll,ll> st[],ll si, ll ss, ll se, ll qs,ll qe,ll level){
    if(ss > qe || qs > se) return 0;
    if(qs <= ss && qe >= se) return st[si].first;
    ll mid = ss + (se-ss)/2;
    if(level == 0)
    return (segmentTreeQuery(st,2*si,ss,mid,qs,qe,level^1) | segmentTreeQuery(st,2*si+1,mid+1,se,qs,qe,level^1));
    else
    return (segmentTreeQuery(st,2*si,ss,mid,qs,qe,level^1) ^ segmentTreeQuery(st,2*si+1,mid+1,se,qs,qe,level^1));
}
 
void pointUpdateSegTree(ll a[],pair<ll,ll> st[],ll si,ll ss,ll se,ll ui,ll level){
    //You have to update in the original array first
    if(ss == se){
        st[si].first = a[ss];
        return;
    }
    ll mid = ss + (se-ss)/2;
    if(ui <= mid) pointUpdateSegTree(a, st, 2*si, ss, mid, ui, level^1);
    else pointUpdateSegTree(a,st,2*si+1,mid+1,se,ui, level^1);
    if(level == 0) st[si].first = st[2*si].first | st[2*si+1].first;
    else  st[si].first = st[2*si].first ^ st[2*si+1].first;
}
 
 
 
 
int32_t main()
{
    fastio;
    ll n,m;
    cin >> n >> m;
    n = (ll)pow(2,n);
    ll a[n+1];
    for(ll i=1;i<=n;i++) cin >> a[i];
    pair<ll,ll> st[4*n+4];
    buildSegmentTree(a,st,1,1,n);
    //for(ll i=1;i<=2*n;i++) cout << st[i].first << ' ' << st[i].second << '\n';
    while(m--){
        ll l,r;
        cin >> l >> r;
        a[l] = r;
        pointUpdateSegTree(a,st,1,1,n,l,st[1].second);
        cout << st[1].first << '\n';
    }
    return 0;
}