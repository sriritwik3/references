[source](https://youtu.be/tyB0ztf0DNY)

> Those who cannot remember the past are condemned to repeat it. 

1. Tabulation - Bottom-up
2. Memoization - Top-down  

## Fibonacci Numbers
0 1 1 2 3 5 8 13 21 .....  
f(n) = f(n-1) + f(n-2)  

**recursion code**
```
f(n){  
  if(n <=1) return n;  
  return f(n-1) + f(n-2);  
}
```
If you look at the recursion tree, f(n) calls for f(n-1) first which indeed call f(n-2) first and so on. We are calling for the same function many times.  
![image](https://user-images.githubusercontent.com/56584349/177520234-392f5be7-d4f0-418f-9462-fecca948f0cf.png)

This is called as an overlapping subproblem. This is where memoization comes in - we tend to store the value of the subproblem in a map/table.  
Here, maximum number of sub problems can be n+1 i.e f(0), f(1)....f(n). so, we use an array of size n+1. Initialise the array with -1.  

```
initialise dp array with -1 of size n+1
f(n){
  if(n <= 1) return n;
  if(dp[n] != -1) return dp[n];
  return dp[n] = f(n-1) + f(n-2);
}
```
 
TC - O(N), SC - O(N) ARRAY + O(N) RECURSION STACK SPACE  

### To solve the same problem using tabulation,  
Start with the base case first. Similar to the previous approach, initialise a dp array with all -1.
`dp[0] = 0, dp[1] = 1`  
From the recurrence relation, wkt we only need i-1 and i-2'th result to compute i'th problem. So we can go to build upon this.

```
for(int i=2;i<=n;i++){
  dp[i] = dp[i-1] + dp[i-2];
}
```

TC - O(N), SC - O(N)  

To also eliminate that extra O(N) space, we can try using only 2 variables which stores the results of i-1 and i-2 sub problems instead of storing everything.  

```
int i1 = 1, i2 = 0, ans = -1;
//If you want the answer for nth fibonacci number
for(int i=2;i<=n;i++){
  ans = i1 + i2;
  i2 = i1;
  i1 = ans;
}
```
Now SC - O(1)

