/* Given an array of integers, return a new array such that each element at index i of the new array is the product of all the numbers in the original array except the one at i.
For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be [2, 3, 6].
Follow-up: what if you can't use division? */


//First things first, we should not use a division operator.
//Some intital thoughts - maintain two arrays one called left and other right
//such that left[i] is the multiplication of all the elements from left[i] to left[i-1]
// and right[i] is the multiplication of all the elements from right[i+1] to right[n]
//ans[i] will simply be multiplication of left[i] and right[i]

//Improving on this, We can just use 1 array(right) to reduce the space we use. And just use one variable to maintain all the muliplication of
//elements to the left.
//In the first traversal we fill the array right[n]
//In next traversal while we itearte from 1 to n we update our left variable in each iteration

#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    ll a[n+1];
    for(ll i=1;i<=n;i++) cin >> a[i];
    ll right[n+1],left=1;
    memset(right,1,sizeof(right));
    for(ll i=n-1;i>=1;i--)
        right[i] *= (a[i+1] * right[i+1]);
    for(ll i=1;i<=n;i++){
        cout << left*right[i] << '\n';
        left *= a[i];
    }
    return 0;
}





