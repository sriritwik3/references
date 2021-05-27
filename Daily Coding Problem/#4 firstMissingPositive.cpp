/* Given an array of integers, find the first missing positive integer in linear time and constant space.
 In other words, find the lowest positive integer that does not exist in the array. The array can contain duplicates and negative numbers as well.
For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.
You can modify the input array in-place. */



#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)


//Time complexity should be O(n) and space complexity should be O(1). So we cannnot sort the array as it takes O(nlogn) time.
//We cannot use hashing as it takes some extra space.
//Only thing we are left with is to modify the input array in place.
//One approach is to swap the number we get in each iteration to it's original place. 
//Next time we traverse the array we can find the first number which is not in it's place.

ll firstMisssingPos(ll a[],ll n){
    for(ll i=1;i<=n;i++)
        if(a[i] >= 1 && a[i] <= n && a[a[i]] != a[i]) swap(a[i],a[a[i]]);
    for(ll i=1;i<=n;i++){
        if(a[i] != i){
            return i;
        }
    }
    return n+1;
}

//Another excellent approach is to first make all the negative elements in the array to 0. As we have nothing to do with negative numbers.
//In next traversal, in each iteration if we find any a[i] which is in [1,n] mark a[a[i]] as -1. It indicates we encoutered a[i] somewhere in the 
//array. Hence if a[i] = -1, it mean i is present in the array. 
//In next traversal, iterate from i=1 to n. If a[i] != -1 it means that i is not present in the array. Hence i is the smallest missing positive
//number in the array. If all 1 to n numbers are present in the array, then smp will be n+1.

int32_t main()
{
    fastio;
    ll  n;
    cin >> n;
    ll a[n+1];
    for(ll i=1;i<=n;i++) {
        cin >> a[i];
        if(a[i] < 0) a[i] = 0;   
    }
    for(ll i=1;i<=n;i++){
        if(a[i] <= n && a[i] >= 1){
            if(a[a[i]] >= 0) a[a[i]] = -1;
        }
    }
    for(ll i=1;i<=n;i++){
        if(a[i] >= 0){
            cout << "first missing positive number is " << i << '\n';
            return 0;
        }    
    }
    cout << "first missing positive number is " << n+1 << '\n';
    return 0;
}