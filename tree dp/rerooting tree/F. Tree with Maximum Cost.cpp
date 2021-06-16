// Link to the problem - https://codeforces.com/contest/1092/problem/F

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
const int N = 2000005;
 
vector<ll> adj[N];
vector<ll> dp(N), ans(N), a(N);
ll temp,answer;
 
void dfs(ll u,ll par , ll h){
    temp += (1ll * h * a[u]);
    dp[u] = a[u];
    for(auto v:adj[u]){
        if(v == par) continue;
        dfs(v,u,h+1);
        dp[u] += dp[v];
    }
}
 
void dfs1(ll u, ll par){
    answer = max(temp, answer);
    for(auto v:adj[u]){
        if(v == par) continue;
        temp -= dp[v];
        dp[u] -= dp[v];
        dp[v] += dp[u];
        temp += dp[u];
        dfs1(v,u);
        temp -= dp[u];
        dp[v] -= dp[u];
        dp[u] += dp[v];
        temp += dp[v];
    }
}
 
signed main(){
    fastio;
    ll n;
    cin >> n;
    for(ll i=1;i<=n;i++){
        cin >> a[i];
    } 
    for(ll i=1;i<n;i++){
        ll c,b;
        cin >> c >> b;
        adj[b].push_back(c);
        adj[c].push_back(b);
    }
    dfs(1,-1,0);
    dfs1(1,-1);
    cout << answer << endl;
    return 0;
}
