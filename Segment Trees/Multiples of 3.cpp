//link to the problem - https://www.codechef.com/problems/MULTQ3

//normal lazy propagation with storing the count of the remainders when divided by 3. One key point to be noticed is that
//when we flip the values in all 3 nodes, it's just sufficient to do that pending%3 times. as it's a cyclic shift.

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

struct node{
    ll rem[3];
};

node st[400004];

void buildSegmentTree(ll si,ll ss, ll se){
    if(ss == se){
        st[si].rem[0] = 1;
        st[si].rem[1] = 0;
        st[si].rem[2] = 0;
        return;
    }
    ll mid = ss + (se-ss)/2;
    buildSegmentTree(2*si,ss,mid);
    buildSegmentTree(2*si+1,mid+1,se);
    st[si].rem[0] = st[2*si].rem[0] + st[2*si+1].rem[0];
    st[si].rem[1] = st[2*si].rem[1] + st[2*si+1].rem[1];
    st[si].rem[2] = st[2*si].rem[2] + st[2*si+1].rem[2];
}


ll lazyPropQuery(ll lazy[],ll si, ll ss, ll se, ll qs,ll qe){
    //lazy array must be initialised to 0
    if(lazy[si] != 0 ){
        ll add = lazy[si];
        lazy[si] = 0;
        for(ll i=0;i<add%3;i++){
            ll temp = st[si].rem[2];
	        st[si].rem[2] = st[si].rem[1];
	        st[si].rem[1] = st[si].rem[0];
	        st[si].rem[0] = temp;
        }
        if(se != ss) lazy[2*si] += add, lazy[2*si+1] += add;
    }
    if(ss > qe || qs > se) return 0;
    if(qs <= ss && qe >= se) return st[si].rem[0];
    ll mid = ss + (se-ss)/2;
    return lazyPropQuery(lazy,2*si,ss,mid,qs,qe) + lazyPropQuery(lazy,2*si+1,mid+1,se,qs,qe);
}

void rangeUpdateSegTree(ll lazy[],ll si,ll ss,ll se,ll qs,ll qe){
    //You have to update in the original array first
    if(lazy[si] != 0 ){
        ll ad = lazy[si];
        lazy[si] = 0;
        for(ll i=0;i<ad%3;i++){
            ll temp = st[si].rem[2];
	        st[si].rem[2] = st[si].rem[1];
	        st[si].rem[1] = st[si].rem[0];
	        st[si].rem[0] = temp;
        }
        if(se != ss) lazy[2*si] += ad, lazy[2*si+1] += ad;
    }
    if(ss > qe || qs > se) return;
    if(ss >= qs && se <= qe){
        ll temp = st[si].rem[2];
	        st[si].rem[2] = st[si].rem[1];
	        st[si].rem[1] = st[si].rem[0];
	        st[si].rem[0] = temp;
        if(ss != se) lazy[2*si] += 1, lazy[2*si+1] += 1;
        return;
    }
    ll mid = ss + (se-ss)/2;
    rangeUpdateSegTree( lazy,  2*si, ss,mid,qs,qe);
    rangeUpdateSegTree(lazy,2*si+1,mid+1,se,qs,qe);
    st[si].rem[0] = st[2*si].rem[0] + st[2*si+1].rem[0];
    st[si].rem[1] = st[2*si].rem[1] + st[2*si+1].rem[1];
    st[si].rem[2] = st[2*si].rem[2] + st[2*si+1].rem[2];
}



int32_t main()
{
    fastio;
    ll n,q;
    cin >> n >> q;
    buildSegmentTree(1,1,n);
    ll lazy[400004];
    memset(lazy,0,sizeof(lazy));
    while(q--){
        ll c,l,r;
        cin >> c >> l >> r;
        if(c==0)
            rangeUpdateSegTree(lazy,1,1,n,l+1,r+1);
        else cout << lazyPropQuery(lazy,1,1,n,l+1,r+1) << '\n';
    }
    return 0;
}
