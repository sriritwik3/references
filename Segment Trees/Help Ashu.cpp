//link to the problem - https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/help-ashu-1/

//normal segment trees with point updates

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

void buildSegmentTree(ll a[],ll st[],ll si,ll ss, ll se){
    //cout << si << ss <<  se << st[si] << a[ss] <<  '\n';
    if(ss == se){
        if(a[ss]%2 == 0) st[si]++;
        return;
    }
    ll mid = ss + (se-ss)/2;
    buildSegmentTree(a,st,2*si,ss,mid);
    buildSegmentTree(a,st,2*si+1,mid+1,se);
    st[si] = st[2*si] + st[2*si+1];
}

ll query(ll st[],ll si, ll ss, ll se, ll qs,ll qe){
    if(ss > qe || qs > se) return 0;
    if(qs <= ss && qe >= se) return st[si];
    ll mid = ss + (se-ss)/2;
    return query(st,2*si,ss,mid,qs,qe) + query(st,2*si+1,mid+1,se,qs,qe);
}


void pointUpdateSegTree(ll a[],ll st[],ll si,ll ss,ll se,ll ui,ll add){
    //You have to update in the original array first
    if(ss == se){
        st[si] += add;
        return;
    }
    ll mid = ss + (se-ss)/2;
    if(ui <= mid) pointUpdateSegTree(a, st, 2*si, ss, mid, ui, add);
    else pointUpdateSegTree(a,st,2*si+1,mid+1,se,ui, add);
    st[si] = st[2*si] + st[2*si+1];
}


int32_t main()
{
    fastio;
    ll n;
    cin >> n;
    ll a[n+1];
    for(ll i=1;i<=n;i++) cin >> a[i];
    ll q;
    cin >> q;
    ll st[4*n+4];
    memset(st,0,sizeof(st));
    buildSegmentTree(a,st,1,1,n);
    //for(ll i=1;i<=15;i++) cout << st[i] << ' ';
    while(q--){
        ll f,l,r;
        cin >> f >> l >> r;
        if(f == 0){
            if(a[l]%2 != r%2){
                if(a[l]&1) pointUpdateSegTree(a,st,1,1,n,l,1);
                else pointUpdateSegTree(a,st,1,1,n,l,-1);
                a[l] = r;
            }
        }
        else if(f == 1) cout << query(st,1,1,n,l,r) << '\n';
        else cout << (r-l+1) - query(st,1,1,n,l,r) << '\n';
    }
    return 0;
}
