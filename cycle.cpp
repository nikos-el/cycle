#include <vector>  
#include <list>  
  
using namespace std;  
  
class Graph{  
  public:  
    Graph(int N): V(N), adj(N) {}  
    ~Graph() {}  
    void addEdge(int u, int v) { adj[u].push_back(v); }  
  
    bool cycle(vector<int> &path) const{  
      int node1=-1, node2=-1;  
      vector<state> status(V, unvisited);  
      vector<int> p(V, -1);  
      bool isCyclic = false;  
      for (int i=0; i<V; ++i)  
        if(status[i]==unvisited)  
          if (dfs_visit(i, status, p, node1, node2)) { isCyclic=true; break; }  
  
      if (isCyclic){  
        list<int> path_l;  
        path_l.push_front(node2); path_l.push_front(node1);  
        int x=p[node1];  
        while(!isEdge(node2,x)){  
          path_l.push_front(x);  
          x=p[x];  
        }  
        path_l.push_front(x);  
        for (int i: path_l) path.push_back(i);  
      }  
      return isCyclic;  
    }  
  
  private:  
    enum state {unvisited, visited, seen};  
    int V;  
    vector<list<int>> adj;  
  
    bool dfs_visit(int u, vector<state> &status, vector<int> &p, int &node1, int &node2) const{  
      status[u]=seen; node1=u;  
      for(int v: adj[u]){  
        p[v]=u;  
        if (status[v]==seen) { node2=v;  return true; }  
        if (status[v]==unvisited && dfs_visit(v, status, p, node1, node2))  
          return true;  
      }  
      status[u]=visited;  
      return false;  
    }  
  
    bool isEdge(int u, int v) const{  
      for (int i: adj[u])  
        if (i==v) return true;  
      return false;  
    }  
};  
