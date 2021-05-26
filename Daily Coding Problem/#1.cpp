#include<bits/stdc++.h>
using namespace std;

/*Given a list of numbers and a number k, return true whether any two numbers from the list add up to k. */



// One approach is to use an unordered set and push a[i] into the set each time we traverse the array. And check whether k - a[i] is already 
//present in the array. If it was, just simply return true.
// Time Complexity - O(n) 
int solve_set(int a[],int n,int k){
    unordered_set<int> s;
    for(ll i=1;i<=n;i++){
        if(s.find(k-a[i]) != s.end()) return true;
        s.insert(a[i]);
    }
    return false;
}


//Another method is to use 2 pointer technique after sorting the array. Our left will be a[1] and right will be a[n]
//check for their sum if it's less than k, increment l else decrement r(as the array is sorted).
//Time complexity  - O(nlogn) as the array sorted
int solve_2pointers(int a[],int n,int k){
    sort(a,a+n);
    int l = a[1], r = a[n];
    while(l < r){
        if(l+r == k) return true;
        else if(l+r < k) l++;
        else r--;
    }
    return false;
} 


//Yet there is another method to solve this, keep the frequency of all numbers which are less than k in one iteration. 
//Iterate again from 1 to k/2 and find if there exist k-i for any i. If i == k/2, there should be two elements.
//Time Complexity - O(n+k)
int solve_freq(int a[],int n,int k){
    int freq[k+1];
    memset(freq,0,sizeof(freq));
    for(ll i=1;i<=n;i++) freq[a[i]]++;
    if(k&1){
        for(ll i=1;i<=k/2;i++){
            if(freq[i] > 0 && freq[k-i] > 0) return true;
        }
    }
    else{
        for(ll i=1;i<=k/2;i++){
            if(i==k/2) if(freq[i] >= 2) return true;
            if(freq[i] > 0 && freq[k-i] > 0) return true;
        }
    }
    return false;
}


int main(){
    int n,k;
    cin >> n >> k;
    int a[n+1];
    a[0] = 0;
    for(ll i=1;i<=n;i++) cin >> a[i];
    //cout << solve(a,n,k) << '\n';
    return 0;
}