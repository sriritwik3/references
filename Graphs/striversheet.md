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

# 3) BFS  
An Undirected Graph will be given. Return a vector of all the nodes of the Graph by Breadth-First Search ( BFS ) Technique.  
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

# 7) cycle in DG using BFS  

# 8) Topological sort BFS  

# 9) Topological sort DFS  

# 10) Number of Islands  

# 11) Bipartite check using DFS  

# 12) Bipartite check using BFS  

# 13) Strongly connected components(using kosaraju algo)  

# 14) MST using prim's  

# 15) MST using Kruskal's  

# 16) Dijkstra's Algorithm  

# 17) Bellman-Ford algorithm  

# 18) Floyd Warshall algorithm  
