//link to the problem - https://codeforces.com/problemset/problem/1234/D

//didn't use a segment tree approach but still we can use persistent segment tree to solve this problem.
/* Store all the indices in which each alphabet occur in a vector of sets. Whenever you have to update, remove the old index from the set
and add the new one. For querying, iterate through all alphabets and find whether each alphabet's index appears to be in the range of l to r
using lower_bound. */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
 
int32_t main()
{
    fastio;
    string s;
    vector<set<ll> > segtree(26);
    cin >> s;
    for(ll i=0;i<s.size();i++) segtree[s[i] - 'a'].insert(i);
    ll q;
    cin >> q;
    while(q--){
        ll c,l;
        cin >> c >> l;
        if(c==1){
            char r;
            cin >> r;
            segtree[s[--l] - 'a'].erase(l);
            s[l] = r;
            segtree[s[l] - 'a'].insert(l);
        }else {
            ll r;
            cin >> r;
            ll count = 0;
            --l,--r;
            for(ll i=0;i<26;i++){
                auto it = segtree[i].lower_bound(l);
                if(it!=segtree[i].end() && *it<=r) count++;
            }
            cout << count << '\n';
        }
    }
    return 0;
}