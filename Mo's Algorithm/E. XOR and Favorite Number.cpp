// link to the problem - https://codeforces.com/problemset/problem/617/E

#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define all(v) (v).begin(), (v).end()
#define int long long
#define pl pair<ll,ll> 
const int maxn = 100005;
//const int maxel = 1000005;

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct Query{
	int l, r, idx;
	int64_t ord;
 
	inline void calcOrder() {
		ord = gilbertOrder(l, r, 21, 0);
	}
};

inline bool operator<(const Query &a, const Query &b) {
	return a.ord < b.ord;
}

Query qry[maxn];
int cnt[maxn];
int a[maxn];
int ans[maxn];
int k;
int store = 0;

void add(int i){
    store += cnt[k ^ i];
    cnt[i]++;
}

void removee(int i){
    cnt[i]--;
    store -= cnt[k ^ i];
}

signed main()
{
    fastio;
    int n,t;
    cin >> n >> t >> k;
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<t;i++){
        int l,r;
        cin >> l >> r;
        --l; 
        qry[i].l = l;
        qry[i].r = r;
        qry[i].idx = i;
        qry[i].calcOrder();
    }
    sort(qry,qry+t);
    int cl = 0, cr = -1;
    int prefix[n+1];
    prefix[0] = 0;
    for(int i=1;i<=n;i++) prefix[i] = prefix[i-1] ^ a[i-1];
    for(int i=0;i<t;i++){
        while( cr < qry[i].r ) add(prefix[++cr]);
        while( cr > qry[i].r ) removee(prefix[cr--]);
        while( cl < qry[i].l ) removee(prefix[cl++]);
        while( cl > qry[i].l ) add(prefix[--cl]);
        ans[qry[i].idx] = store; 
    }
    for(int i=0;i<t;i++) cout << ans[i] << '\n';
    return 0;
}
