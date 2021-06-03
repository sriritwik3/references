/* There exists a staircase with N steps, and you can climb up either 1 or 2 steps at a time.
 Given N, write a function that returns the number of unique ways you can climb the staircase. The order of the steps matters.
For example, if N is 4, then there are 5 unique ways:
1, 1, 1, 1
2, 1, 1
1, 2, 1
1, 1, 2
2, 2
What if, instead of being able to climb 1 or 2 steps at a time, you could climb any number from a set of positive integers X?
For example, if X = {1, 3, 5}, you could climb 1, 3, or 5 steps at a time. */


//Use dp where dp[i] represent no.of ways to climb the staircase upto i steps.
//if a is an array which represents all possible steps, we initialise dp[a[j]] to be 1 for j in [1,m].
//dp[i] += dp[i-a[j]] for j in 1 to m if i > a[j]

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)


int32_t main()
{ 
    fastio;
    ll n,m;
    cin >> n >> m;
    ll a,dp[n+1];
    unordered_set<ll> s;
    memset(dp,0,sizeof(dp));
    for(ll i=1;i<=m;i++) cin >> a, s.insert(a), dp[a] = 1;
    for(ll i=1;i<=n;i++){
        for(auto it = s.begin();it!= s.end();it++){
            if(*it < i)
            dp[i] += dp[i-*it];
        }
    }
    cout << dp[n] << '\n';
    return 0;
}
