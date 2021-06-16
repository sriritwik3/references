// Link to the problem - https://codeforces.com/contest/1324/problem/F

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
const int N = 2e5 + 4;
 
vector<ll> adj[N];
vector<ll> dp(N), ans(N), a(N);
 
void dfs(ll u,ll par = -1){
    dp[u] = a[u];
    for(auto v:adj[u]){
        if(v == par) continue;
        dfs(v,u);
        dp[u] += max(0ll,dp[v]);
    }
}
 
void dfs1(ll u, ll par = -1){
    ll temp = ans[par] - max(0ll,dp[u]);
    ans[u] = max(0ll,temp) + dp[u];
    for(auto v:adj[u]) if(v!=par) dfs1(v,u);
}
 
signed main(){
    fastio;
    ll n;
    cin >> n;
    for(ll i=1;i<=n;i++){
        cin >> a[i];
        if(a[i] == 0) a[i] = -1;
    } 
    for(ll i=1;i<n;i++){
        ll c,b;
        cin >> c >> b;
        adj[b].push_back(c);
        adj[c].push_back(b);
    }
    dfs(1);
    ans[1] = dp[1];
    for(auto child:adj[1]) dfs1(child,1);
    for(ll i=1;i<=n;i++) cout << ans[i] << ' ';
    cout << endl;
    return 0;
}
