# Time Complexity  
**Run time analysis**  - process of determining how processing time of a problem increases as the size of the problem (input size) increases.  
**Rate of growth** - rate at which running time increases as a function of input.  So we can ignore the low order terms that are relatively insignificant.  

## Asymptotic Notations  
**Big-O Notation** - It gives the tight upper bound of the given function.  Generally, it is represented as f(n)=O(g(n)). That means at larger values of N the upperbound of a f(n) is g(n).  
![image](https://user-images.githubusercontent.com/56584349/180781624-de4f4279-8dea-4f30-8c3f-ff6cb010636d.png)  
O(g(n)) = {f(n): there exists positive constants c and n0 such that 0 <= f(n) <= c* g(n) for all n > n0 }  
Our objective is to give the smallest rate of growth g(n) which is greater than or equal to the given algorithm’s rate of growth.  

**Omega-Ω Notation**  - Similar to Big - O, this gives the tight lower bound of the given function.  
Ω(g(n)) = {f(n): there exists positive constants c and n0 such that 0 <= cg(n) <= f(n) for all n > n0 }.  
![image](https://user-images.githubusercontent.com/56584349/180782052-0ab1633b-5eac-44aa-8fda-e879b2a37aba.png)  
Our objective is to give the largest rate of growth g(n) which is less than or equal to the given algorithms’ rate of growth.  

**Theta-Θ Notation**  
Θ-notation is defined as  
Θ(g(n)) = {f(n): there exists positive constants c and n0 such that 0 <= c1g(n) <= f(n) <= c2g(n) for all n > n0 }  
![image](https://user-images.githubusercontent.com/56584349/180783912-4616a45f-7f08-4785-b167-0fc7d8f7962c.png)  

**Note:** In the analysis, we generally focus on the upper bound(O) because knowing the lower bound(Ω) of an algorithm is of no practical importance, and we use the Θ notation if the upper bound(O) and lower bound(Ω) are the same .   

## Recurrence relations  
A recurrence relation is an equation that recursively defines a sequence where the next term of the sequence is a function of the previous terms. In other words we
express the nth term of the sequence(Fn) as a function of the previous terms Fi(i<n).  
Eg: fibonacci(i) = fibonacci(i-1) + fibonacci(i-2)  
Binary search can also be denoted as a recurrence relation. In every iteration we are reducing the search space by half and we're doing constant operations in each iteration.  
So, we can write **T(N) = T(N/2) + 1** where T(1) = 1.   

# Masters Theorem  
We use Masters Theorem to solve for the recurrence relations and calculate the final run time.  
Masters theorem can be used for recurrence relations of type : T(n) = a.T(n/b) + f(n) a>=1, b>1  
- n: The size of the problem.
- a: The number of subproblems in the recursion.
- n/b: The size of each subproblem.(It is assumed that the size of all the subproblems are
the same)
- f(n): The cost of work done outside the recursive calls, which basically includes the cost
of dividing the problem and merging the solutions of the subproblems.  
**Note:** Here ‘a’ and ‘b’ are constants and f(n) is asymptotically a positive function. In other words, for sufficiently large input size ‘n’, f(n) > 0 and T(n) is a monotonically increasing function.  

The solution of recurrence relations of the form T(n) = a.T(n/b) + f(n) as given by Master’s
theorem where the whole idea is based upon the comparison of f(n) and n^(logba) and
determining which of them is the dominating factor  
logba - log a to the base b.  
-  Case 1: If f(n) = O(n^(logba - ε)), for some ε > 0, then T(n) = Θ(n^(logba)).
This case can be interpreted as the worst case of f(n) is n^(logba - ε), which is less than
n^(logba) so n^(logba) takes more time and dominates.
-  Case 2: If f(n) = Θ(n^(logba)), then T(n) = Θ(n^(logba) * logn).
If f(n) is also Θ(n^(logba)), then the time taken will be Θ(n^(logba) * logn).
-  Case 3: If f(n) = Ω(n^(logba + ε)), for some ε > 0, and if a.f(n/b) <= c.f(n) for some c < 1 and
all sufficiently large ‘n’, then T(n) = Θ(f(n)).
Since the best case of f(n) is n^(logba - ε), so the best case of f(n) is greater than n^(logba),
hence f(n) dominates.  

**Limitations of Master’s Theorem**
- We cannot use Master’s theorem if T(n) is not monotone, for example T(n) = sin(n).  
- f(n) must be a polynomial  
- If a is not a constant, for example a = 2 * n, or b cannot be expressed as a constant, for
example T(n) = T(√n), then the master's theorem cannot be applied.  

## Space Complexity  
Space complexity is a measure of the total amount of memory including the space of input
values with respect to the input size, that an algorithm needs to run and produce the result.  
Whereas **Auxiliary Space** is the temporary or extra space used by an algorithm apart from the
input size in order to solve a problem.  
Space complexity = Auxiliary Space + Space taken by the input size   



