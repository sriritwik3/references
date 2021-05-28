/* Given a list of integers, write a function that returns the largest sum of non-adjacent numbers. Numbers can be 0 or negative.
For example, [2, 4, 6, 2, 5] should return 13, since we pick 2, 6, and 5. [5, 1, 1, 5] should return 10, since we pick 5 and 5
Follow-up: Can you do this in O(N) time and constant space? */

//store the max until (i-1)'th element and (i-2)'th element for each element in the array.
//https://divyabiyani.medium.com/daily-coding-problem-february-24th-2020-given-a-list-of-integers-write-a-function-that-89b68076b0fb


#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

int32_t main()
{ 
    ll n;
    cin >> n;
    ll a[n+1];
    for(ll i=1;i<=n;i++) cin >> a[i];
    ll nminus1 = a[1],nminus2 = 0;
    for(ll i=2;i<=n;i++){
        ll new2 = max(nminus1,nminus2);
        nminus1 = a[i] + nminus2;
        nminus2 = new2;
    }
    cout <<  max(nminus2,nminus1) << '\n';
    return 0;
}
