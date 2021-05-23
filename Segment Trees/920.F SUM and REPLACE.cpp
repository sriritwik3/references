// link to the problem - https://codeforces.com/problemset/problem/920/F
/*First precompute no.of primary divisors of all the numbers<10^6 in nlogn time.One Keypoint to be noted is that the update
function converges so easily here. Atmax it takes 6 steps to converge. So we can use segment trees with normal range update.
Lazy propagation doesn't work here. And if any segment contains only 1 and 2 it doesn't have to be updated as no.of divisors of 1 and 2 
are q and 2 itself. So we stop the recursion whenever we encounter a segment which only contains 1 and 2. FOr achieving this, 2 segment trees
are maintained, one to keep the value of sums of segment, and other to store maximum value in a segment */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
 
 
void buildSegmentTree(ll a[],ll st[],ll mx[],ll si,ll ss, ll se){
    if(ss == se){
        st[si] = mx[si] = a[se];
        return;
    }
    ll mid = ss + (se-ss)/2;
    buildSegmentTree(a,st,mx,2*si,ss,mid);
    buildSegmentTree(a,st,mx,2*si+1,mid+1,se);
    mx[si] = max(mx[2*si],mx[2*si+1]);
    st[si] = st[2*si] + st[2*si+1];
}
 
ll segmentTreeQuery(ll st[],ll si, ll ss, ll se, ll qs,ll qe){
    if(ss > qe || qs > se) return 0;
    if(qs <= ss && qe >= se) return st[si];
    ll mid = ss + (se-ss)/2;
    return segmentTreeQuery(st,2*si,ss,mid,qs,qe) + segmentTreeQuery(st,2*si+1,mid+1,se,qs,qe);
}
 
void pointUpdateSegTree(ll a[],ll st[],ll mx[],ll divisors[],ll si,ll ss,ll se,ll ul,ll ur){
    //You have to update in the original array first
    if(ss == se){
        st[si] = mx[si] = a[ss] = divisors[a[ss]];
        return;
    }
    ll mid = ss + (se-ss)/2;
    if(ul <= mid && mx[2*si] > 2) pointUpdateSegTree(a, st,mx,divisors, 2*si, ss, mid, ul, min(mid,ur));
    if(ur > mid && mx[2*si+1] > 2) pointUpdateSegTree(a,st,mx,divisors,2*si+1,mid+1,se,max(ul,mid+1),ur);
    st[si] = min(st[2*si],st[2*si+1]);
    mx[si] = max(mx[2*si],mx[2*si+1]);
    st[si] = st[2*si] + st[2*si+1];
}
 
int32_t main()
{
    fastio;
    ll n,m;
    cin >> n >> m;
    ll a[n+1];
    for(ll i=1;i<=n;i++) cin >> a[i];
    ll divisors[1000002];
    memset(divisors,0,sizeof(divisors));
    for(ll i=1;i<=1000001;i++)
        for(ll j=i;j<=1000001;j+=i)
            ++divisors[j];
 
    ll st[4*n+4];
    ll mx[4*n+4];
    buildSegmentTree(a,st,mx,1,1,n);
    while(m--){
        ll c,l,r;
        cin >> c >>  l >> r;
        if(c==1)
            pointUpdateSegTree(a,st,mx,divisors,1,1,n,l,r);
        else
            cout << segmentTreeQuery(st,1,1,n,l,r) << '\n';
    }
    return 0;
}