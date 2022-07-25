# Sorting algorithms  
**In place and not inplace**  
An in-place sorting algorithm uses constant space for producing the output (modifies the given array only). It sorts the list only by modifying the order of the elements within the list. For example, Insertion Sort and Selection Sorts are in-place sorting algorithms as they do not use any additional space for sorting the list and a typical implementation of Merge Sort is not in-place, also the implementation for counting sort is not an in-place sorting algorithm. so the auxiliary space complexity of non-in-place sorting algorithms is increased by O(N).  

**Stability in sorting**  
Stability in sorting means that - if two same keys are there in the array after sorting, they must retain their positions.  
Bubble Sort, Insertion Sort, Merge Sort, Count Sort are stable by nature.   
Counting Sort maintain stability by ensuring that the Sorted Array is filled in a reverse order so that elements with equivalent keys have the same relative position.  
Some sorts such as Radix Sort depend on another sort, with the only requirement that the other sort should be stable.  
Quick sort, heap sort are unstable.  But they can also be made stable.  
Any sorting algo which is not stable can be made stable.  

**Complexities of all sorting algorithms**  
![image](https://user-images.githubusercontent.com/56584349/180709942-99132140-a728-4077-be10-8105275040e2.png)  


# Bubble sort   
repeatedly swapping the adjacent elements if they are in the wrong order.  To know when to stop the iterations, maintain a boolean variable and if there are no swaps, 
break the loop.    
void bubbleSort(int arr[], int n)
{
   int i, j;
   bool swapped;
   for (i = 0; i < n-1; i++)
   {
     swapped = false;
     for (j = 0; j < n-i-1; j++)
     {
        if (arr[j] > arr[j+1])
        {
           swap(arr[j], arr[j+1]);
           swapped = true;
        }
     }
     if (swapped == false)
        break;
   }
}  
### Recursive bubble sort  
```cpp
void bubbleSort(int arr[], int n)
{
    // Base case
    if (n == 1)
        return;
  
    int count = 0;
    // One pass of bubble sort. After
    // this pass, the largest element
    // is moved (or bubbled) to end.
    for (int i=0; i<n-1; i++)
        if (arr[i] > arr[i+1]){
            swap(arr[i], arr[i+1]);
            count++;
        }
  
      // Check if any recursion happens or not
      // If any recursion is not happen then return
      if (count==0)
           return;
  
    // Largest element is fixed,
    // recur for remaining array
    bubbleSort(arr, n-1);
}
```
Worst case occurs when elements are in decreasing order.n-1 operations in 1st iteration, n-2 in 2nd and so on. Thus it takes O(n*(n-1)/2). And the worst and average cases take O(n^2) time.   
Best case is when the array is already sorted and it takes O(n) time.  
In this if we think carefully in ith iteration ith largest element goes to it's place.  It is in place and it is stable.  

# Selection sort  
The selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) from unsorted part and putting it at the beginning.   The algorithm maintains two subarrays in a given array.  

- The subarray which is already sorted.   
- Remaining subarray which is unsorted. 
In every iteration of selection sort, the minimum element (considering ascending order) from the unsorted subarray is picked and moved to the sorted subarray.   
```cpp
void selectionSort(int arr[], int n) 
{ 
    int i, j, min_idx; 
    for (i = 0; i < n-1; i++) 
    { 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
        if (arr[j] < arr[min_idx]) 
            min_idx = j; 
        swap(&arr[min_idx], &arr[i]); 
    } 
} 
```
TC - O(N^2), SC - O(1)  
It is inplace. By default it is not stable but we can make it stable.  
Selection sort makes O(n) swaps which is quite minimum .  
To make it stable, instead of swapping we could just follow the idea of insertion sort by placing the element at it's position and pushing all elements to thr right by one position.  
```cpp
void stableSelectionSort(int a[], int n)
{
    // Iterate through array elements
    for (int i = 0; i < n - 1; i++)
    {
 
        // Loop invariant : Elements till a[i - 1]
        // are already sorted.
 
        // Find minimum element from
        // arr[i] to arr[n - 1].
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (a[min] > a[j])
                min = j;
 
        // Move minimum element at current i.
        int key = a[min];
        while (min > i)
        {
            a[min] = a[min - 1];
            min--;
        }
        a[i] = key;
    }
}
```

# Insertion sort  

![image](https://user-images.githubusercontent.com/56584349/180758000-e3c3dd89-0c2d-4edd-badb-9db2cf92c412.png)  
- Iterate from arr[1] to arr[N] over the array. 
- Compare the current element (key) to its predecessor. 
- If the key element is smaller than its predecessor, compare it to the elements before. Move the greater elements one position up to make space for the swapped element.  
```cpp
void insertionSort(int arr[], int n) 
{ 
    int i, key, j; 
    for (i = 1; i < n; i++)
    { 
        key = arr[i]; 
        j = i - 1; 
  
        // Move elements of arr[0..i-1],  
        // that are greater than key, to one 
        // position ahead of their 
        // current position
        while (j >= 0 && arr[j] > key)
        { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 
} 
```
Insertion sort takes maximum time to sort if elements are sorted in reverse order. And it takes minimum time (Order of n) when elements are already sorted.    
It is inplace and stable.  Insertion sort is used when number of elements is small. It can also be useful when input array is almost sorted, only few elements are misplaced in complete big array.  
We can use binary search to reduce the number of comparisons in normal insertion sort. Binary Insertion Sort uses binary search to find the proper location to insert the selected item at each iteration. In normal insertion, sorting takes O(i) (at ith iteration) in worst case. We can reduce it to O(logi) by using binary search.  
**Recursive insertion sort**  
```cpp
void insertionSortRecursive(int arr[], int n)
{
    // Base case
    if (n <= 1)
        return;
  
    // Sort first n-1 elements
    insertionSortRecursive( arr, n-1 );
  
    // Insert last element at its correct position
    // in sorted array.
    int last = arr[n-1];
    int j = n-2;
  
    /* Move elements of arr[0..i-1], that are
    greater than key, to one position ahead
    of their current position */
    while (j >= 0 && arr[j] > last)
    {
        arr[j+1] = arr[j];
        j--;
    }
    arr[j+1] = last;
}
```

# Quick sort  
QuickSort is a Divide and Conquer algorithm. It picks an element as a pivot and partitions the given array around the picked pivot.  
pivot can be chosen in many possible ways - starting element, last element, random element, median element.  
The target of partitions is, given an array and an element x of an array as the pivot, put x at its correct position in a sorted array and put all smaller elements (smaller than x) before x, and put all greater elements (greater than x) after x. All this should be done in linear time.  
 ![image](https://user-images.githubusercontent.com/56584349/180763548-1309f3a9-0f43-4477-9da4-97d637ebf629.png)  


# Merge sort  

# Bucket sort   


# Counting sort  


# Heap sort   

# Radix sort   

# 3 way merge sort    

# 3 way quick sort (Dutch National Flag)    

# Quick sort on singly linked list    

# Quick sort on DLL  

# Merge sort on singly linked list    
 
# Merge sort on DLL  

# Count inversions in an array  

# Sorting using a comparator in c++

# Questions and comparisions of all sorting algorithms for interview  
https://www.geeksforgeeks.org/sorting-algorithms/ - Misc
