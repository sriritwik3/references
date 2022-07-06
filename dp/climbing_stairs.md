# Climbing Stairs  

##### Initially You are at step 0 and you have to reach step n. Each time you can climb up one stair or two stairs. Total number of ways to reach nth stair.  

First try to write the recurrence relation. To reach stair n, only possible way is to reach it from stair n-1 or from stair n-2. So the recurrence would become f(n) = f(n-1) + f
(n-2), given we handle the edge cases.  
**This is just same as fibonacci problem**

But if the constraints are too tight i.e upto 10e18 dp approach wouldn't work. We have to do it in O(logN) for which we need to use matrix exponentiation.  
![image](https://user-images.githubusercontent.com/56584349/177543591-0dc7522c-2e35-4b81-aaed-b7a91df38254.png)

If we simplify that we get,  

![image](https://user-images.githubusercontent.com/56584349/177543917-3239e905-8b5e-4652-9bb0-5fab09b55554.png)

So, to get n'th fibonacci number, we can find the value of matrix  
1 1  
1 0  
raised to the power of n-1.  

To achieve the same in O(logn), we use binary exponentiation i.e A^n = A^(n/2) * A^(n/2) if n is even, A^(n/2) * A^(n/2) * A if it's odd.  

## Code  

```cpp
// Fibonacci Series using Optimized Method
#include <bits/stdc++.h>
using namespace std;
 
void multiply(int F[2][2], int M[2][2]);
void power(int F[2][2], int n);
 
// Function that returns nth Fibonacci number
int fib(int n)
{
    int F[2][2] = {{1, 1}, {1, 0}};
    if (n == 0)
        return 0;
    power(F, n - 1);
 
    return F[0][0];
}
 
// Optimized version of power() in method 4
void power(int F[2][2], int n)
{
    if(n == 0 || n == 1)
       return;
    int M[2][2] = {{1, 1}, {1, 0}};
     
    power(F, n / 2);
    multiply(F, F);
     
    if (n % 2 != 0)
        multiply(F, M);
}
 
void multiply(int F[2][2], int M[2][2])
{
    int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
     
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}
 
// Driver code
int main()
{
    int n = 9;
     
    cout << fib(9);
    getchar();
     
    return 0;
}
 
// This code is contributed by Nidhi_biet
```
