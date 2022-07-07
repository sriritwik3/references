# Ninjas Training  
## Intro to 2d DP  

A Ninja has a ‘N’ Day training schedule.
He has to perform one of these three activities (Running, Fighting Practice, or Learning New Moves) each day.
There are merit points associated with performing an activity each day. The same activity can’t be performed on two consecutive days.
We need to find the maximum merit points the ninja can attain in N Days.  
We are given a 2D Array POINTS of size ‘N*3’ which tells us the merit point of specific activity on that particular day.
Our task is to calculate the maximum number of merit points that the ninja can earn.  

## Solution
[link](https://takeuforward.org/data-structure/dynamic-programming-ninjas-training-dp-7/)  
**step1 -express the problem in terms of indices.**  
f(day, last) - Maximum points till given day with last option on previous day.  
**step2 - try all possible choices at given index**.  
![image](https://user-images.githubusercontent.com/56584349/177719412-e6486dfb-4a46-4641-8a06-f876c69fecb6.png)  
This is for base case, day = 0. And for others we recurse.  
**step3 - take max of all the choices.**  
![image](https://user-images.githubusercontent.com/56584349/177719871-e2ddc15c-2067-4d24-9e3c-0503aa62dfe0.png)  

## Memoization  
```cpp
#include <bits/stdc++.h>
using namespace std;

int f(int day, int last, vector<vector<int>> &points,vector<vector<int>> &dp) {
  if (dp[day][last] != -1) return dp[day][last];
  if (day == 0) {
    int maxi = 0;
    for (int i = 0; i <= 2; i++) {
      if (i != last)
        maxi = max(maxi, points[0][i]);
    }
    return dp[day][last] = maxi;
  }

  int maxi = 0;
  for (int i = 0; i <= 2; i++) {
    if (i != last) {
      int activity = points[day][i] + f(day - 1, i, points, dp);
      maxi = max(maxi, activity);
    }
  }
  return dp[day][last] = maxi;
}

int ninjaTraining(int n, vector < vector < int > > & points) {

  vector < vector < int > > dp(n, vector < int > (4, -1));
  return f(n - 1, 3, points, dp);
}

int main() {

  vector < vector < int > > points = {{10,40,70},
                                      {20,50,80},
                                      {30,60,90}};
  int n = points.size();
  cout << ninjaTraining(n, points);
}
```
Time Complexity: O(N * 4 * 3)  
Reason: There are N * 4 states and for every state, we are running a for loop iterating three times.  
Space Complexity: O(N) + O(N * 4)  
Reason: We are using a recursion stack space(O(N)) and a 2D array (again O(N * 4)). Therefore total space complexity will be O(N) + O(N) ≈ O(N).  

## Tabulation  
First initialise the base conditions. 

```cpp
#include <bits/stdc++.h>
using namespace std;

int ninjaTraining(int n, vector < vector < int > > & points) {
  vector < vector < int > > dp(n, vector < int > (4, 0));
  dp[0][0] = max(points[0][1], points[0][2]);
  dp[0][1] = max(points[0][0], points[0][2]);
  dp[0][2] = max(points[0][0], points[0][1]);
  dp[0][3] = max(points[0][0], max(points[0][1], points[0][2]));
  for (int day = 1; day < n; day++) {
    for (int last = 0; last < 4; last++) {
      dp[day][last] = 0;
      for (int task = 0; task <= 2; task++) {
        if (task != last) {
          int activity = points[day][task] + dp[day - 1][task];
          dp[day][last] = max(dp[day][last], activity);
        }
      }
    }
  }
  return dp[n - 1][3];
}

int main() {
  vector<vector<int> > points = {{10,40,70},
                                 {20,50,80},
                                 {30,60,90}};
  int n = points.size();
  cout << ninjaTraining(n, points);
}
```
Time Complexity: O(N * 4 * 3)  
Reason: There are three nested loops  
Space Complexity: O(N * 4)  
Reason: We are using an external array of size ‘N * 4’’.  

## Space optimised  

dp[day][last] =  max(dp[day][last],points[day][task] + dp[day-1][task])  

Here the task can be anything from 0 to 3 and day-1 is the previous stage of recursion.
So in order to compute any dp array value, we only require the last row to calculate it.  
- So rather than storing the entire 2D Array of size N*4, we can just store values of size 4(say prev).  
- We can then take a dummy array, again of size 4 (say temp) and calculate the next row’s value using the array we stored in step 1.  
- After that whenever we move to the next day, the temp array becomes our prev for the next step.  
- At last prev[3] will give us the answer.  

```cpp
#include <bits/stdc++.h>
using namespace std;

int ninjaTraining(int n, vector < vector < int > > & points) {
  vector < int > prev(4, 0);
  prev[0] = max(points[0][1], points[0][2]);
  prev[1] = max(points[0][0], points[0][2]);
  prev[2] = max(points[0][0], points[0][1]);
  prev[3] = max(points[0][0], max(points[0][1], points[0][2]));
  for (int day = 1; day < n; day++) {
    vector < int > temp(4, 0);
    for (int last = 0; last < 4; last++) {
      temp[last] = 0;
      for (int task = 0; task <= 2; task++) {
        if (task != last) {
          temp[last] = max(temp[last], points[day][task] + prev[task]);
        }
      }
    }
    prev = temp;
  }
  return prev[3];
}

int main() {
  vector<vector<int> > points = {{10,40,70},
                                 {20,50,80},
                                 {30,60,90}};
  int n = points.size();
  cout << ninjaTraining(n, points);
}
```

TC - O(N * 4 * 3) , SC - O(4)
