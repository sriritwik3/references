//link to the problem - https://codeforces.com/contest/13/problem/E


#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define all(v) (v).begin(), (v).end()
typedef long long ll;
#define int long long
#define pl pair<ll,ll> 
const int maxn = 100005;

signed main()
{
    fastio;
    int n,m;
    cin >> n >> m;
    ll a[n];
    for(int i=0;i<n;i++) cin >> a[i];
    int len = sqrt(n+.0) + 1;
    ll next[n],cnt[n];

    for(ll i=n-1;i>=0;i--){
        if(i+a[i] >= n || i/len != (i+a[i])/len) next[i] = i,cnt[i] = 0;
        else next[i] = next[i+a[i]], cnt[i] = cnt[i+a[i]] + 1;
    }
  //  for(int i=0;i<n;i++) cout << next[i] << ' ' << cnt[i] << '\n';
    while(m--){
        ll ch;
        cin >> ch;
        if(ch == 0){
            ll l,r;
            cin >> l >> r;
            l--;
            a[l] = r;
            for(ll i=l;i>=0 && (i/len == l/len);i--){
                if(i+a[i] >= n || i/len != (i+a[i])/len) next[i] = i,cnt[i] = 0;
                else next[i] = next[i+a[i]], cnt[i] = cnt[i+a[i]] + 1;
            }
        }
        else{
            ll l;
            cin >> l;
            l--;
            ll last = 0, count = 0;
            for(;l<n;last = next[l],l = last + a[last]) count += cnt[l] + 1;
            cout << last+1 << ' ' << count << '\n';
        }
    }
    return 0;
}
