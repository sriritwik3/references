# Graphs  
## Striver sheet  

# 1) Clone a graph  
Given a reference of a node in a connected undirected graph.  
Return a deep copy (clone) of the graph.  
Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.  
```
class Node {
    public int val;
    public List<Node> neighbors;
}
```  
To clone a graph, you will need to traverse it. Both BFS and DFS are for this purpose. But that is not all you need. To clone a graph, you need to have a copy of each node and you need to avoid copying the same node for multiple times. So you still need a mapping from an original node to its copy.  
### Using DFS  
```cpp
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) {
            return NULL;
        }
        if (copies.find(node) == copies.end()) {
            copies[node] = new Node(node -> val, {});
            for (Node* neighbor : node -> neighbors) {
                copies[node] -> neighbors.push_back(cloneGraph(neighbor));
            }
        }
        return copies[node];
    }
private:
    unordered_map<Node*, Node*> copies;
};
```  
### Using BFS  
```cpp
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) {
            return NULL;
        }
        Node* copy = new Node(node -> val, {});
        copies[node] = copy;
        queue<Node*> todo;
        todo.push(node);
        while (!todo.empty()) {
            Node* cur = todo.front();
            todo.pop();
            for (Node* neighbor : cur -> neighbors) {
                if (copies.find(neighbor) == copies.end()) {
                    copies[neighbor] = new Node(neighbor -> val, {});
                    todo.push(neighbor);
                }
                copies[cur] -> neighbors.push_back(copies[neighbor]);
            }
        }
        return copy;
    }
private:
    unordered_map<Node*, Node*> copies;
};
```

# 2) DFS  
Depth First Traversal is a traversal technique/algorithm, used to traverse through all the nodes in the given graph.   
It starts traversal through any one of its neighbour nodes and explores the farthest possible node in each path/branch and then starts Back-tracking.  
Backtracking happens when the DFS algorithm reaches a particular node that has no neighbours to visit further, once it reaches that node with no neighbours to be visited it’ll backtrack to its previous node (say N) and from this node N algorithm will start searching for unvisited neighbour nodes and starts visiting them.  
```cpp
class Solution {
    void dfs(int node, vector<int> &vis, vector<int> adj[], vector<int> &storeDfs) {
        storeDfs.push_back(node); 
        vis[node] = 1; 
        for(auto it : adj[node]) {
            if(!vis[it]) {
                dfs(it, vis, adj, storeDfs); 
            }
        }
    }
public:
	vector<int>dfsOfGraph(int V, vector<int> adj[]){
	    vector<int> storeDfs; 
	    vector<int> vis(V+1, 0); 
      for(int i = 1;i<=V;i++) {
        if(!vis[i]) dfs(i, vis, adj, storeDfs); 
      }
	    return storeDfs; 
	}
};
```
Time complexity: O(N+E), Where N is the time taken for visiting N nodes and E is for travelling through adjacent nodes.  
Space Complexity:O(N+E)+O(N)+O(N) , Space for adjacency list, Array,Auxiliary space.  
Also exists an iterative solution using stack.  

# 3) BFS  
An Undirected Graph will be given. Return a vector of all the nodes of the Graph by Breadth-First Search ( BFS ) Technique.  
We use a queue of pairs with the parent element also being inserted.  
```cpp
class Solution {
  public:
    vector < int > bfsOfGraph(int V, vector < int > adj[]) {
      vector < int > bfs;
      vector < int > vis(V, 0);
      queue < int > q;
      q.push(0);
      vis[0] = 1;
      while (!q.empty()) {
        int node = q.front();
        q.pop();
        bfs.push_back(node);

        for (auto it: adj[node]) {
          if (!vis[it]) {
            q.push(it);
            vis[it] = 1;
          }
        }
      }

      return bfs;
    }
};
```
Time Complexity : O(N+E)  
N = Nodes , E = travelling through adjacent nodes  
Space Complexity : O(N+E) + O(N) + O(N)   
Space for adjacency list, visited array, queue data structure  

# 4) cycle in UDG using BFS  
```cpp
class Solution
{
public:
    bool checkForCycle(int s, int V, vector<int> adj[], vector<int> &visited)
    {
        // Create a queue for BFS
        queue<pair<int, int>> q;
        visited[s] = true;
        q.push({s, -1});
        while (!q.empty())
        {
            int node = q.front().first;
            int par = q.front().second;
            q.pop();
 
            for (auto it : adj[node])
            {
                if (!visited[it])
                {
                    visited[it] = true;
                    q.push({it, node});
                }
                else if (par != it)
                    return true;
            }
        }
        return false;
    }
    bool isCycle(int V, vector<int> adj[])
    {
        vector<int> vis(V - 1, 0);
        for (int i = 1; i <= V; i++)
        {
            if (!vis[i])
            {
                if (checkForCycle(i, V, adj, vis))
                    return true;
            }
        }
    }
};
```
Time Complexity: O(N+E),  N is the time taken and E is for traveling through adjacent nodes overall.   
Space Complexity: O(N+E) +  O(N) + O(N) , space for adjacent list , array and queue  

# 5) cycle in UDG using DFS  
Also pass the parent element to the recursive call.  
```cpp
class Solution {
  public:
    bool checkForCycle(int node, int parent, vector < int > & vis, vector < int > adj[]) {
      vis[node] = 1;
      for (auto it: adj[node]) {
        if (!vis[it]) {
          if (checkForCycle(it, node, vis, adj))
            return true;
        } else if (it != parent)
          return true;
      }

      return false;
    }
  public:
    bool isCycle(int V, vector < int > adj[]) {
      vector < int > vis(V + 1, 0);
      for (int i = 0; i < V; i++) {
        if (!vis[i]) {
          if (checkForCycle(i, -1, vis, adj)) return true;
        }
      }

      return false;
    }
};
```

# 6) cycle in DG using DFS   
Normal approach wouldn't work. Eg below  
![image](https://user-images.githubusercontent.com/56584349/180603631-db708cf3-c2a6-4ed4-a2ca-3174a4a6e93a.png)  
To tackle this, we use 2 visited arrays.  One is normal visited and other is dfs visited. We mark both as one as same time. But whenever a recursive call is done 
for a particular node(i.e it no longer have any neighbours left) we mark it again to 0.  
So ideally, if we reach a node in the current dfs call which is already visited we can guarantee that there exists a cycle.  
```cpp
class Solution {
  private:
    bool checkCycle(int node, vector < int > adj[], int vis[], int dfsVis[]) {
      vis[node] = 1;
      dfsVis[node] = 1;
      for (auto it: adj[node]) {
        if (!vis[it]) {
          if (checkCycle(it, adj, vis, dfsVis)) return true;
        } else if (dfsVis[it]) {
          return true;
        }
      }
      dfsVis[node] = 0;
      return false;
    }
  public:
    bool isCyclic(int N, vector < int > adj[]) {
      int vis[N], dfsVis[N];
      memset(vis, 0, sizeof vis);
      memset(dfsVis, 0, sizeof dfsVis);
      for (int i = 0; i < N; i++) {
        if (!vis[i]) {
          // cout << i << endl; 
          if (checkCycle(i, adj, vis, dfsVis)) {
            return true;
          }
        }
      }
      return false;
    }
};
```
Time Complexity: O(V + E), since in its whole, it is a DFS implementation, V – vertices; E – edges;  
Space Complexity: O(V), because, apart from the graph, we have 2 arrays of size V, to store the required information

# 7) cycle in DG using BFS  
We know that toposort exists only for acyclic graphs. So if topo sort ordering doesn't exists the graph is cyclic.   

# 8) Topological sort DFS  
linear ordering of vertices such that if there is an edge from u->v, u appears before v in that ordering.  It's only possible for DAG.  
- For Undirected graphs ,only u->v is not applicable . It cannot be sure whether the edge is between u to v or v to u ( u-v ) .  
- In a cyclic graph there will always be a dependency factor . You cannot make sure that you can have linear ordering of vertices.  
 Just because there was an edge from u to v. Dfs call will go from u to v. The 1st dfs (v) will get over first and then dfs(u). Here we are making sure that if u->v, then we will first push v into the stack and then u will be pushed. This is how Topological order is maintained in the Stack.  
```cpp
class Solution {
  void findTopoSort(int node, vector < int > & vis, stack < int > & st, vector < int > adj[]) {
    vis[node] = 1;

    for (auto it: adj[node]) {
      if (!vis[it]) {
        findTopoSort(it, vis, st, adj);
      }
    }
    st.push(node);
  }
  public:
    vector < int > topoSort(int N, vector < int > adj[]) {
      stack < int > st;
      vector < int > vis(N, 0);
      for (int i = 0; i < N; i++) {
        if (vis[i] == 0) {
          findTopoSort(i, vis, st, adj);
        }
      }
      vector < int > topo;
      while (!st.empty()) {
        topo.push_back(st.top());
        st.pop();
      }
      return topo;

    }
};
```
Time Complexity: O(N+E)  
N = Number of node , E = Number of Edges  
Space Complexity: O(N) + O(N)   
Visited Array and Stack data structure. Both will be using O(N).  
Auxiliary Space Complexity:  O(N)   
Recursion call of DFS  

# 9) Topological sort BFS  
**Intuition:**  
The question states that if there is an edge between u and v then u should appear before v, Which means we have to start this question from a node that doesn’t have any previous edges. But how to find that node that has no edge before if? Here, we use the concept of in-degree (Number of edges pointing toward a node). We find an in-degree which has indegree=0 and we start from this. We use the Indegree concept to find topological sorting. Let’s see how.  

**Approach:**  

- In order to maintain the In-degree of each and every node, we take an array of size v( where v is the number of nodes).  
- Find in-degree of all nodes and fill them in an array
- Now take Queue data structure and add nodes that have in-degree is 0 (as we discussed in the intuition), and simply apply bfs on queue with some condition.
- Take the top/peek node from Queue ( let the popped node be x), add this x to our answer. (If you can observe clearly the above step is nothing but Normal BFS traversal).  
	- We’ll apply some conditions to the BFS:
	- Now take neighbour nodes of popped nodes and reduce their in-degree by 1.
- Check if any of the popped element nodes in degree becomes 0, after reducing in-degree by 1 if it happens then add this neighbour element to the queue for which the in-degree became zero.
- Repeat step 4 till the queue becomes empty.  
```cpp
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
	vector<int> topo(int N, vector<int> adj[]) {
        queue<int> q; 
	    vector<int> indegree(N, 0); 
	    for(int i = 0;i<N;i++) {
	        for(auto it: adj[i]) {
	            indegree[it]++; 
	        }
	    }
	    
	    for(int i = 0;i<N;i++) {
	        if(indegree[i] == 0) {
	            q.push(i); 
	        }
	    }
	    vector<int> topo;
	    while(!q.empty()) {
	        int node = q.front(); 
	        q.pop(); 
	        topo.push_back(node);
	        for(auto it : adj[node]) {
	            indegree[it]--;
	            if(indegree[it] == 0) {
	                q.push(it); 
	            }
	        }
	    }
	    return topo;
	}
};
```
Time Complexity: O(N+E)  
Space complexity: O(N)+O(N)  

# 10) Number of Islands  
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.  
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.  
As said in the question, a group of 1's is an Island. So try to eliminate a group of 1 using BSF and increment the counter meanwhile    

```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0, islands = 0, offsets[] = {0, 1, 0, -1, 0};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    islands++;
                    grid[i][j] = '0';
                    queue<pair<int, int>> todo;
                    todo.push({i, j});
                    while (!todo.empty()) {
                        pair<int, int> p = todo.front();
                        todo.pop();
                        for (int k = 0; k < 4; k++) {
                            int r = p.first + offsets[k], c = p.second + offsets[k + 1];
                            if (r >= 0 && r < m && c >= 0 && c < n && grid[r][c] == '1') {
                                grid[r][c] = '0';
                                todo.push({r, c});
                            }
                        }
                    }
                }
            }
        }
        return islands;
    }
};
```
Using DFS  
```cpp
class Solution {
public:
    void DFS(vector<vector<char>>& grid, int i, int j) {
        // boundary checking
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return;
        // return if current position is of water or is already visited
        if(grid[i][j] == '2' || grid[i][j] == '0')
            return;
        
        // mark the current as visited
        grid[i][j] = '2';
        
        // do DFS in all 4 directions
        DFS(grid, i+1, j);
        DFS(grid, i, j-1);
        DFS(grid, i-1, j);
        DFS(grid, i, j+1);
    }
    
    int numIslands(vector<vector<char>>& grid) {
        // We can treat the matrix grid as a grid. Each Island is a
        // connected component. The task is to find no. of disconnectedd components
        // in the graph.
        
        int islands = 0;
        // We make each 1 as 2 in when it is visited
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                // do DFS in case has not been visited and there is land
                if(grid[i][j] == '1') {
                    DFS(grid, i, j);
                    ++islands;
                } 
            }
        }
        return islands;
    }
};
```
TC - O(V^2)  

# 11) Bipartite check using DFS   
Given is a 2D adjacency list representation of a graph. Check whether the graph is Bipartite graph. (Note: In a Bipartite graph, one can color all the nodes with exactly 2 colors such that no two adjacent nodes have the same color)  
Normally except for the case where there is an odd length cycle in the graph, every time it's bipartite.  
If the current neighbor is already colored, we check its color and the variable, node’s color. We know that they are adjacent nodes, if the colors are the same, we can infer that it is not a Bipartite graph, so returning false, else returning true.  
```cpp
class Solution {
public:
    bool dfs(vector<vector<int>> &graph,int node, vector<int> &visited){
        for(auto i:graph[node]){
            if(visited[i] == -1){
                visited[i] = 1 ^ visited[node];
                if(dfs(graph, i, visited)) 
                    return true;
            } else if(visited[i] == visited[node])
                return true;
        }
        return false;
    }
    
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> visited(n, -1);
        for(int i=0;i<n;i++){
            if(visited[i] == -1){
                visited[i] = 1;
                if(dfs(graph, i, visited))
                    return false;
            }
        }
        return true;
    }
};
```
Time Complexity: O(V + E), since in its whole, it is a DFS implementation, V – vertices; E – edges;  
Space Complexity: O(V), because, apart from the graph, we maintain a color array.  

# 12) Bipartite check using BFS   
```cpp
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> colors(n, 0);
        queue<int> q;
        
        for (int i = 0; i < n; i++) {
            if (colors[i]) continue;
            
            colors[i] = 1;
            q.push(i);
            
            while (!q.empty()) {
                int temp = q.front();
                
                for (auto neighbor : graph[temp]) {
                    
					// Color neighbor with opposite color
                    if (!colors[neighbor]){
                        colors[neighbor] = -colors[temp];
                        q.push(neighbor);
                    }
                    
					// If the neighbor has the same color - can't bipartite.
                    else if (colors[neighbor] == colors[temp]) 
                        return false;
                }
                q.pop();
            }
        }
        return true;
    }
};
```

# 13) Strongly connected components(using kosaraju algo)  


# 14) MST using prim's  

# 15) MST using Kruskal's  

# 16) Dijkstra's Algorithm  

# 17) Bellman-Ford algorithm  

# 18) Floyd Warshall algorithm  
