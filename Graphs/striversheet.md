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
SCC means - a component in which if we take any node and reachout to every other node in that component.  
![image](https://user-images.githubusercontent.com/56584349/180655974-b61c2323-2a67-4c1e-aede-190fd60483bc.png)  
We definitely cannot do DFS because we would end up visiting all nodes in a CC and couldn't find SCC.  
So we could do one thing i.e do dfs by visiting the nodes in reverse order such that there will be no way in which we go back if it's not an scc.  
For this numbering, we may need to use toposort ordering and follow it in reverse.  
- Sort all the nodes according to their topo sort(loosely based topo sort as we may have cycles here)  
- Transpose the graph i.e reverse all the edges of the graph  
- Use the topo sort or the increasing order of finishing time to find the strongly connected components using DFS.  
```cpp
#include <bits/stdc++.h>
using namespace std;
void dfs(int node, stack<int> &st, vector<int> &vis, vector<int> adj[]) {
    vis[node] = 1; 
    for(auto it: adj[node]) {
        if(!vis[it]) {
            dfs(it, st, vis, adj); 
        }
    }
    
    st.push(node); 
}
void revDfs(int node, vector<int> &vis, vector<int> transpose[]) {
    cout << node << " "; 
    vis[node] = 1; 
    for(auto it: transpose[node]) {
        if(!vis[it]) {
            revDfs(it, vis, transpose); 
        }
    }
}
int main() {
    int n=6, m=7;
	vector<int> adj[n+1]; 
	adj[1].push_back(3);
	adj[2].push_back(1);
	adj[3].push_back(2);
	adj[3].push_back(5);
	adj[4].push_back(6);
	adj[5].push_back(4);
	adj[6].push_back(5);
	stack<int> st;
	vector<int> vis(n+1, 0); 
	for(int i = 1;i<=n;i++) {
	    if(!vis[i]) {
	        dfs(i, st, vis, adj); 
	    }
	} 
	vector<int> transpose[n+1]; 
	for(int i = 1;i<=n;i++) {
	    vis[i] = 0; 
	    for(auto it: adj[i]) {
	        transpose[it].push_back(i); 
	    }
	}
	
	while(!st.empty()) {
	    int node = st.top();
	    st.pop(); 
	    if(!vis[node]) {
	        cout << "SCC: "; 
	        revDfs(node, vis, transpose); 
	        cout << endl; 
	    }
	}
	return 0;
}
```
Time Complexity: O(N+E), DFS+TopoSort  
Space Complexity: O(N+E), Transposing the graph

# 14) MST using prim's  
Spanning tree - converting a graph to a tree such that number of edges are n-1.  Every node should be reachable by every other node.  
Minimum Spanning tree(MST) is a ST for which weights of all edges is minimum.   
**Prims**  
**Intuition:** Let’s start with anyone node in our graph. As the first step, we find out all the adjacent edges connected to this node and then pick up the minimum one. Now we have 2 nodes. We further continue this process but now we would consider all the edges connected to these two nodes and pickup the minimum one. We then continue this process until all the nodes are covered.  
**Note:** It might happen that while picking up an edge we might end up forming a cycle. In that case, we would pick up the next lowest edge that doesn’t form a cycle.  
We use three arrays to achieve this -   
- **Key** : This array holds the weight/ cost of the MST(intialized to INT_MAX except the index 0 which is set with value of zero)  
- **MST** : This is a boolean array which indicates whether a node is already a part of MST or not(initialized to false except the index 0 which is true)  
- **Parent**:  This indicates the parent of a particular node in the MST(initialized to -1)  

- Assuming we start with node 0, the index 0 in the key array is initialized to zero(because it is the first node in the MST). We find the index/node in the key array which has the minimum weight. We then find all its adjacent edges and pickup the the one with minimum weight.   
- Also at the same time we mark this node as true(indicating that it is now a part of the MST) and also set it’s parent as node ‘0’.   
- After this, we would continue to find the one with minimum weight in the key array that is not a part of the MST(Notice that this is where we ensure that we pickup the node with minimum weight and we do not choose an edge that might cause a cycle)  
- We continue this process until all nodes become a part of the MST  
```cpp
int parent[N];
    int key[N]; 
    bool mstSet[N]; 
  
    for (int i = 0; i < N; i++) 
        key[i] = INT_MAX, mstSet[i] = false; 
    key[0] = 0; 
    parent[0] = -1; 
    int ansWeight = 0;
    for (int count = 0; count < N - 1; count++)
    { 
        
        int mini = INT_MAX, u; 
  
        for (int v = 0; v < N; v++) 
{
            if (mstSet[v] == false && key[v] < mini) 
                mini = key[v], u = v; 
}
                 mstSet[u] = true; 
        
        for (auto it : adj[u]) {
            int v = it.first;
            int weight = it.second;
            if (mstSet[v] == false && weight < key[v]) 
                parent[v] = u, key[v] = weight; 
        }
            
    } 
    
    
    for (int i = 1; i < N; i++) 
        cout << parent[i] << " - " << i <<" \n"; 
```
TC - O(N^2), SC - O(N)  
We can optimise this by using a min heap instead of finding the smallest every single time in linear time.  
```cpp
int parent[N]; 
    int key[N]; 
    bool mstSet[N]; 
    for (int i = 0; i < N; i++) 
        key[i] = INT_MAX, mstSet[i] = false; 
    
    priority_queue< pair<int,int>, vector <pair<int,int>> , greater<pair<int,int>> > pq;

    key[0] = 0; 
    parent[0] = -1; 
    pq.push({0, 0});

    while(!pq.empty())
    { 
        int u = pq.top().second; 
        pq.pop();       
        mstSet[u] = true; 
        for (auto it : adj[u]) {
            int v = it.first;
            int weight = it.second;
            if (mstSet[v] == false && weight < key[v]) {
                parent[v] = u;
	    key[v] = weight; 
                pq.push({key[v], v});    
            }
        }            
    } 
    
    for (int i = 1; i < N; i++) 
        cout << parent[i] << " - " << i <<" \n"; 
```
TC - O(NLOGN), SC - O(N)  

# 15) MST using Kruskal's  


# 16) Dijkstra's Algorithm  
Given a weighted, undirected, and connected graph of V vertices and E edges, Find the shortest distance of all the vertex’s from the source vertex S.  
Note: The Graph doesn’t contain any negative weight cycle.  
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n=5,m=6,source=1;
	vector<pair<int,int> > g[n+1]; 	// assuming 1 based indexing of graph
	// Constructing the graph
	g[1].push_back({2,2});
	g[1].push_back({4,1});
	g[2].push_back({1,2});
	g[2].push_back({5,5});
	g[2].push_back({3,4});
	g[3].push_back({2,4});
	g[3].push_back({4,3});
	g[3].push_back({5,1});
	g[4].push_back({1,1});
	g[4].push_back({3,3});
	g[5].push_back({2,5});
	g[5].push_back({3,1});	
	// Dijkstra's algorithm begins from here
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int>>> pq;
	vector<int> distTo(n+1,INT_MAX);//1-indexed array for calculating shortest paths
	distTo[source] = 0;
	pq.push(make_pair(0,source));	// (dist,source)
	while( !pq.empty() ){
		int dist = pq.top().first;
		int prev = pq.top().second;
		pq.pop();
		vector<pair<int,int> >::iterator it;
		for( it = g[prev].begin() ; it != g[prev].end() ; it++){
			int next = it->first;
			int nextDist = it->second;
			if( distTo[next] > distTo[prev] + nextDist){
				distTo[next] = distTo[prev] + nextDist;
				pq.push(make_pair(distTo[next], next));
			}
		}
	}
	cout << "The distances from source " << source << " are : \n";
	for(int i = 1 ; i<=n ; i++)	cout << distTo[i] << " ";
	cout << "\n";
	return 0;
}
```
Time Complexity: O((N+E) * logN). Going through N nodes and E edges and log N for priority queue  
Space Complexity: O(N). Distance array and priority queue  

# 17) Bellman-Ford algorithm  


# 18) Floyd Warshall algorithm   
The Floyd Warshall Algorithm is for solving the All Pairs Shortest Path problem. The problem is to find shortest distances between every pair of vertices in a given edge weighted directed Graph.   
We initialize the solution matrix same as the input graph matrix as a first step. Then we update the solution matrix by considering all vertices as an intermediate vertex. The idea is to one by one pick all vertices and updates all shortest paths which include the picked vertex as an intermediate vertex in the shortest path. When we pick vertex number k as an intermediate vertex, we already have considered vertices {0, 1, 2, .. k-1} as intermediate vertices. For every pair (i, j) of the source and destination vertices respectively, there are two possible cases.   
1) k is not an intermediate vertex in shortest path from i to j. We keep the value of dist[i][j] as it is.   
2) k is an intermediate vertex in shortest path from i to j. We update the value of dist[i][j] as dist[i][k] + dist[k][j] if dist[i][j] > dist[i][k] + dist[k][j]  
The following figure shows the above optimal substructure property in the all-pairs shortest path problem.  
```cpp
void floydWarshall(int graph[][V])
{
    /* dist[][] will be the output matrix
    that will finally have the shortest
    distances between every pair of vertices */
    int dist[V][V], i, j, k;
 
    /* Initialize the solution matrix same
    as input graph matrix. Or we can say
    the initial values of shortest distances
    are based on shortest paths considering
    no intermediate vertex. */
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
 
    /* Add all vertices one by one to
    the set of intermediate vertices.
    ---> Before start of an iteration,
    we have shortest distances between all
    pairs of vertices such that the
    shortest distances consider only the
    vertices in set {0, 1, 2, .. k-1} as
    intermediate vertices.
    ----> After the end of an iteration,
    vertex no. k is added to the set of
    intermediate vertices and the set becomes {0, 1, 2, ..
    k} */
    for (k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++) {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++) {
                // If vertex k is on the shortest path from
                // i to j, then update the value of
                // dist[i][j]
                if (dist[i][j] > (dist[i][k] + dist[k][j])
                    && (dist[k][j] != INF
                        && dist[i][k] != INF))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist);
}
```  
Time Complexity: O(V^3)
Auxiliary Space: O(V^2)

# Dis joint set union
https://takeuforward.org/data-structure/disjoint-set-union-by-rank-union-by-size-path-compression-g-46/

The disjoint set data structure generally provides two types of functionalities:

Finding the parent for a particular node (findPar()) 
Union (in broad terms this method basically adds an edge between two nodes) 
Union by rank 
Union by size 

### Union by rank 
The rank of a node generally refers to the distance (the number of nodes including the leaf node) between the furthest leaf node and the current node. Basically rank includes all the nodes beneath the current node. 

### Ultimate parent:  
The parent of a node generally refers to the node right above that particular node. But the ultimate parent refers to the topmost node or the root node. 

#### Initial configuration:

**rank array**: This array is initialized with zero.  

**parent array**: The array is initialized with the value of nodes i.e. parent[i] = i.  

The algorithm steps are as follows:  

Firstly, the Union function requires two nodes(let’s say u and v) as arguments. Then we will find the ultimate parent (using the findPar() function that is discussed later) of u and v. Let’s consider the ultimate parent of u is pu and the ultimate parent of v is pv.  

After that, we will find the rank of pu and pv.  

Finally, we will connect the ultimate parent with a smaller rank to the other ultimate parent with a larger rank. But if the ranks are equal, we can connect any parent to the other parent and we will increase the rank by one for the parent node to whom we have connected the other one.  

Now, if we try to find the ultimate parent(typically using recursion) of each query separately, it will end up taking O(logN) time complexity for each case. But we want the operation to be done in a constant time. This is where the **path compression** technique comes in.  

```cpp
#include <bits/stdc++.h>
using namespace std;
class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};
int main() {
    DisjointSet ds(7);
    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(6, 7);
    ds.unionBySize(5, 6);
    // if 3 and 7 same or not
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n";
    }
    else cout << "Not same\n";

    ds.unionBySize(3, 7);

    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n";
    }
    else cout << "Not same\n";
    return 0;
}
```
**Time complexity** - O(4x)  


# Kruskal's algorithm for MST

The algorithm steps are as follows:  

First, we need to extract the edge information(if not given already) from the given adjacency list in the format of (wt, u, v) where u is the current node, v is the adjacent node and wt is the weight of the edge between node u and v and we will store the tuples in an array.  

Then the array must be sorted in the ascending order of the weights so that while iterating we can get the edges with the minimum weights first.
After that, we will iterate over the edge information, and for each tuple, we will apply the  following operation:  

First, we will take the two nodes u and v from the tuple and check if the ultimate parents of both nodes are the same or not using the findUPar() function provided by the Disjoint Set data structure.  

If the ultimate parents are the same, we need not do anything to that edge as there already exists a path between the nodes and we will continue to the next tuple.  

If the ultimate parents are different, we will add the weight of the edge to our final answer(i.e. mstWt variable used in the following code) and apply the union operation(i.e. either unionBySize(u, v) or unionByRank(u, v)) with the nodes u and v. The union operation is also provided by the Disjoint Set.  

Finally, we will get our answer (in the mstWt variable as used in the following code) successfully.  

```cpp
#include <bits/stdc++.h>
using namespace std;


class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};
class Solution
{
public:
    //Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // 1 - 2 wt = 5
        /// 1 - > (2, 5)
        // 2 -> (1, 5)

        // 5, 1, 2
        // 5, 2, 1
        vector<pair<int, pair<int, int>>> edges;
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                int adjNode = it[0];
                int wt = it[1];
                int node = i;

                edges.push_back({wt, {node, adjNode}});
            }
        }
        DisjointSet ds(V);
        sort(edges.begin(), edges.end());
        int mstWt = 0;
        for (auto it : edges) {
            int wt = it.first;
            int u = it.second.first;
            int v = it.second.second;

            if (ds.findUPar(u) != ds.findUPar(v)) {
                mstWt += wt;
                ds.unionBySize(u, v);
            }
        }

        return mstWt;
    }
};

int main() {

    int V = 5;
    vector<vector<int>> edges = {{0, 1, 2}, {0, 2, 1}, {1, 2, 1}, {2, 3, 2}, {3, 4, 1}, {4, 2, 2}};
    vector<vector<int>> adj[V];
    for (auto it : edges) {
        vector<int> tmp(2);
        tmp[0] = it[1];
        tmp[1] = it[2];
        adj[it[0]].push_back(tmp);

        tmp[0] = it[0];
        tmp[1] = it[2];
        adj[it[1]].push_back(tmp);
    }

    Solution obj;
    int mstWt = obj.spanningTree(V, adj);
    cout << "The sum of all the edge weights: " << mstWt << endl;
    return 0;
}
```

**Time Complexity:** O(N+E) + O(E logE) + O(E*4α*2)   where N = no. of nodes and E = no. of edges. O(N+E) for extracting edge information from the adjacency list. O(E logE) for sorting the array consists of the edge tuples. Finally, we are using the disjoint set operations inside a loop. The loop will continue to E times. Inside that loop, there are two disjoint set operations like findUPar() and UnionBySize() each taking 4 and so it will result in 4*2. That is why the last term O(E*4*2) is added.  

**Space Complexity:** O(N) + O(N) + O(E) where E = no. of edges and N = no. of nodes. O(E) space is taken by the array that we are using to store the edge information. And in the disjoint set data structure, we are using two N-sized arrays i.e. a parent and a size array (as we are using unionBySize() function otherwise, a rank array of the same size if unionByRank() is used) which result in the first two terms O(N).  


# Number of Operations to Make Network Connected  
You are given a graph with n vertices and m edges. You can remove one edge from anywhere and add that edge between any two vertices in one operation. Find the minimum number of operations that will be required to make the graph connected. If it is not possible to make the graph connected, return -1.  

- First we need to extract all the edge information (If not already given) in the form of the pair (u, v) where u = starting node and v = ending node. We should store all the edge information in an array.  
- Then we will iterate through the array selecting every pair and checking the following:  
- If the ultimate parent of u and v(checked using the findPar() method of the Disjoint set) becomes the same,  we should increase the count of extra-edges by 1.
- Because the same ultimate parent means the nodes are already connected and so we can consider the current edge as an extra edge.
- But if the ultimate parents are different, then we should apply the union(either unionBySize() or unionByRank()) method on those two nodes.
- Thus we will get the count of the extra edges. Now it’s time to count the number of components. In order to do so, we will just count the number of the nodes that are the ultimate parent of themselves.
- We will iterate over all the nodes and for each node, we will check the following:
- If the node is the ultimate parent of itself, we will increase the count of components by 1.
Otherwise, we will continue to the next node.  
This checking will be done using the parent array inside the Disjoint set.  

Finally, we will check the count of extra edges and the number of components. If the count of extra-edges is greater or the same, we will return the answer that is (number of components - 1), and otherwise, we will return -1.  

```cpp
#include <bits/stdc++.h>
using namespace std;

//User function Template for C++
class DisjointSet {
public:
    vector<int> rank, parent, size;
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};
class Solution {
public:
    int Solve(int n, vector<vector<int>>& edge) {
        DisjointSet ds(n);
        int cntExtras = 0;
        for (auto it : edge) {
            int u = it[0];
            int v = it[1];
            if (ds.findUPar(u) == ds.findUPar(v)) {
                cntExtras++;
            }
            else {
                ds.unionBySize(u, v);
            }
        }
        int cntC = 0;
        for (int i = 0; i < n; i++) {
            if (ds.parent[i] == i) cntC++;
        }
        int ans = cntC - 1;
        if (cntExtras >= ans) return ans;
        return -1;
    }
};

int main() {

    int V = 9;
    vector<vector<int>> edge = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {2, 3}, {4, 5}, {5, 6}, {7, 8}};

    Solution obj;
    int ans = obj.Solve(V, edge);
    cout << "The number of operations needed: " << ans << endl;
    return 0;
}
```

# Account merge

Given: N = 6
accounts [ ] =
[["John","j1@com","j2@com","j3@com"],
["John","j4@com"],
["Raj",”r1@com”, “r2@com”],
["John","j1@com","j5@com"],
["Raj",”r2@com”, “r3@com”],
["Mary","m1@com"]]

- Here we will perform the disjoint set operations on the indices of the accounts considering them as the nodes. 
- As in each account, the first element is the name, we will start iterating from the second element in each account to visit only the emails sequentially.  
The algorithm steps are the following:  

- First, we will create a map data structure. Then we will store each email with the respective index of the account(the email belongs to) in that map data structure.
- While doing so, if we encounter an email again(i.e. If any index is previously assigned for the email), we will perform union(either unionBySize() or unionByRank()) of the current index and the previously assigned index.
- After completing step 2, now it’s time to merge the accounts. For merging, we will iterate over all the emails individually and find the ultimate parent(using the findUPar() method) of the assigned index of every email. Then we will add the email of the current account to the index(account index) that is the ultimate parent. Thus the accounts will be merged.
  
Finally, we will sort the emails for every account separately and store the final results in the answer array accordingly.  
```cpp
#include <bits/stdc++.h>
using namespace std;
//User function Template for C++
class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>> &details) {
        int n = details.size();
        DisjointSet ds(n);
        sort(details.begin(), details.end());
        unordered_map<string, int> mapMailNode;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < details[i].size(); j++) {
                string mail = details[i][j];
                if (mapMailNode.find(mail) == mapMailNode.end()) {
                    mapMailNode[mail] = i;
                }
                else {
                    ds.unionBySize(i, mapMailNode[mail]);
                }
            }
        }

        vector<string> mergedMail[n];
        for (auto it : mapMailNode) {
            string mail = it.first;
            int node = ds.findUPar(it.second);
            mergedMail[node].push_back(mail);
        }

        vector<vector<string>> ans;

        for (int i = 0; i < n; i++) {
            if (mergedMail[i].size() == 0) continue;
            sort(mergedMail[i].begin(), mergedMail[i].end());
            vector<string> temp;
            temp.push_back(details[i][0]);
            for (auto it : mergedMail[i]) {
                temp.push_back(it);
            }
            ans.push_back(temp);
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};


int main() {

    vector<vector<string>> accounts = {{"John", "j1@com", "j2@com", "j3@com"},
        {"John", "j4@com"},
        {"Raj", "r1@com", "r2@com"},
        {"John", "j1@com", "j5@com"},
        {"Raj", "r2@com", "r3@com"},
        {"Mary", "m1@com"}
    };


    Solution obj;
    vector<vector<string>> ans = obj.accountsMerge(accounts);
    for (auto acc : ans) {
        cout << acc[0] << ":";
        int size = acc.size();
        for (int i = 1; i < size; i++) {
            cout << acc[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
```

**Time Complexity:** O(N+E) + O(E*4ɑ) + O(N*(ElogE + E)) where N = no. of indices or nodes and E = no. of emails. The first term is for visiting all the emails. The second term is for merging the accounts. And the third term is for sorting the emails and storing them in the answer array.

**Space Complexity:** O(N)+ O(N) +O(2N) ~ O(N) where N = no. of nodes/indices. The first and second space is for the ‘mergedMail’ and the ‘ans’ array. The last term is for the parent and size array used inside the Disjoint set data structure.
