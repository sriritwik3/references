//link to the problem - https://codeforces.com/contest/1187/problem/E

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
const int N = 2000005;
 
vector<ll> adj[N];
vector<ll> dp(N), sz(N), a(N);
ll temp,answer;
 
void dfs(ll u,ll par){
    sz[u] = 1;
    dp[u] = 0;
    for(auto v:adj[u]){
        if(v == par) continue;
        dfs(v,u);
        sz[u] += sz[v];
        dp[u] += dp[v];
    }
    dp[u] += sz[u];
}
 
void dfs1(ll u, ll par){
    answer = max(dp[u], answer);
    for(auto v:adj[u]){
        if(v == par) continue;
        dp[u] -= dp[v];
        dp[u] -= sz[v];
        sz[u] -= sz[v];
        sz[v] += sz[u];
        dp[v] += dp[u];
        dp[v] += sz[u];
        dfs1(v,u);
        dp[v] -= (dp[u] + sz[u]);
        sz[v] -= sz[u];
        sz[u] += sz[v];
        dp[u] += (dp[v] + sz[v]);
    }
}
 
signed main(){
    fastio;
    ll n;
    cin >> n;
    for(ll i=1;i<n;i++){
        ll c,b;
        cin >> c >> b;
        adj[b].push_back(c);
        adj[c].push_back(b);
    }
    dfs(1,-1);
    dfs1(1,-1);
  //  for(ll i=1;i<=n;i++) cout << sz[i] << ' ' << dp[i] << '\n';
    cout << answer << endl;
    return 0;
}
