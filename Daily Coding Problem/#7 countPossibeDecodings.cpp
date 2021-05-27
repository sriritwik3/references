/* Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, count the number of ways it can be decoded.
For example, the message '111' would give 3, since it could be decoded as 'aaa', 'ka', and 'ak'
You can assume that the messages are decodable. For example, '001' is not allowed. */

//We should get an initial thought that we should solve this question using dp just by seeing the question.
//dp[i] be the no.of ways we can decode the string upto i'th position.
//dp[i] = no.of ways we count the decoding upto (i-1)'th position + (i-2)'th position if both are valid
//dp[i] = dp[i-1](if the character at i'th position is not 0) + dp[i-2](if the characters at i-1'th and i'th positions are valid i.e lies in [10,26])
//for eg let's take '325'
//If we want to calculate dp[3] it will be equal to dp[1](no. of ways we decode for '3' as here we can take '25' as y) + dp[2](no. of ways we decode '32' as here we can take '5' as e)
//Thus each value depends on it's previous values and we write our basecases for 0 and 1.


#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

int32_t main()
{
    fastio;
    string s;
    cin >> s;
    ll n = s.size();
    ll dp[n+1];
    memset(dp,0,sizeof(dp));
    dp[0] = 1;
    dp[1] = 1 ? s[0] != '0' : 0;
    for(ll i=2;i<=n;i++){
        ll one = s[i-1] - '0';
        ll two = stoi(s.substr(i-2,2)); //changes last 2 chars from string to a integer
        if(one >= 1 && one <= 9) dp[i] += dp[i-1]; //checks whether the last character is valid or not
        if(two >= 10 && two <= 26) dp[i] += dp[i-2]; //checks whether last two characters are valid or not
    }
    cout << dp[n] << '\n';
    return 0;
}
