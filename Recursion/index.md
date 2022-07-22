# Recursion  
When a function calls itself until a specified condition is met.  
All these recursive calls will placed into a stack and when there is no base condition of when to terminate a recursive call it would cause stack overflow.  
Entire process of recursion is just like a tree and we call that tree as recursion tree.  
stack space usually stores the functions(calls) which are yet to be completed but made another call and waiting for that call's result.  

### Parameterised recursion.  
Let's say we need to print the sum of firs n natural numbers using recursion.  parameterised recursion for that would be  
```
f(i, sum){
    if(i < 1){
        return sum;
    }
    return f(i-1, sum+i);
}
```  

### Functional recursion for the same  
```
f(i){
    if(i == 0) return 0;
    return (n + f(i-1));
}
```
