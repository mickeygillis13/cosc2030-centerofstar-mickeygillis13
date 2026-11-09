#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <stdexcept>

using namespace std;

class Graph {
private:
    int numVertices;              // Number of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix

public:
    // Constructor to initialize graph with a given number of vertices
    Graph(int vertices) {
        numVertices = vertices;
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0)); // Initialize with 0 (no edges)
    }

    // Destructor
    ~Graph() {}

    // Add an edge from vertex u to vertex v (directed)
    void addEdge(int u, int v) {
        if (u >= numVertices || v >= numVertices || u < 0 || v < 0) {
            throw out_of_range("Vertex index out of bounds.");
        }
        adjMatrix[u][v] = 1; // Directed edge from u to v
    }

    // Remove an edge from vertex u to vertex v
    void removeEdge(int u, int v) {
        if (u >= numVertices || v >= numVertices || u < 0 || v < 0) {
            throw out_of_range("Vertex index out of bounds.");
        }
        adjMatrix[u][v] = 0; // Remove edge from u to v
    }

    // Check if there is an edge between vertex u and vertex v
    bool isEdge(int u, int v) const {
        if (u >= numVertices || v >= numVertices || u < 0 || v < 0) {
            throw out_of_range("Vertex index out of bounds.");
        }
        return adjMatrix[u][v] == 1;
    }

    // Display the adjacency matrix
    void displayMatrix() const {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Breadth-First Search (BFS) traversal
    void bfs(int start) const {
        if (start >= numVertices || start < 0) {
            throw out_of_range("Vertex index out of bounds.");
        }

        vector<bool> visited(numVertices, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ": ";

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            // Visit all the neighbors
            for (int i = 0; i < numVertices; ++i) {
                if (adjMatrix[v][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    // Non-recursive Depth-First Search (DFS) traversal
    void dfs(int start) const {
        if (start >= numVertices || start < 0) {
            throw out_of_range("Vertex index out of bounds.");
        }

        vector<bool> visited(numVertices, false);
        stack<int> s;

        // Start from the given vertex
        s.push(start);

        cout << "DFS starting from vertex " << start << ": ";

        while (!s.empty()) {
            int v = s.top();
            s.pop();

            if (!visited[v]) {
                visited[v] = true;
                cout << v << " ";
            }

            // Push all unvisited neighbors onto the stack
            for (int i = numVertices - 1; i >= 0; --i) {
                // Check if there's an edge and if the neighbor hasn't been visited
                if (adjMatrix[v][i] == 1 && !visited[i]) {
                    s.push(i);
                }
            }
        }
        cout << endl;
    }

    // Get the number of vertices in the graph
    int getNumVertices() const {
        return numVertices;
    }

    // Get all edges in the graph
    vector<pair<int, int>> getEdges() const {
        vector<pair<int, int>> edges;
        for (int i = 0; i < numVertices; i++){
            for (int j = 0; j < numVertices; j++){
                if(adjMatrix[i][j] == 1){
                    edges.push_back({i, j});
                }
            }
        }
        return edges;
    }

    // Function to find the center of a star graph
    int findCenterOfStar(const Graph& g) {
        vector<pair<int,int>> edges = g.getEdges();
        if(edges.size() < 2){
            return -1; // Not enough edges to determine a center
        }
        if(edges[0].first == edges[1].first || edges[0].first == edges[1].second){
            return edges[0].first;
        }
        if(edges[0].second == edges[1].first || edges[0].second == edges[1].second){
            return edges[0].second;
        }
        return -1; 
    }
};

int main() {
    // Create a graph with 5 vertices (0 to 4)
    Graph g(5);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(4, 0);

    // Display the adjacency matrix
    cout << "Example Adjacency Matrix:" << endl;
    g.displayMatrix();

    // Perform BFS and DFS starting from vertex 0
    g.bfs(0);  // BFS traversal starting from vertex 0
    g.dfs(0);  // DFS traversal starting from vertex 0
    cout << "------------------------------------" << endl;

    // Star graph example
    Graph starGraph(5); 
    starGraph.addEdge(2, 3); 
    starGraph.addEdge(1, 2); 
    starGraph.addEdge(2, 4); 
    starGraph.addEdge(0, 2); 
    cout << "Star graph Adjacency Matrix: " << endl;  
    starGraph.displayMatrix(); 
    cout << "Center of graph: " << starGraph.findCenterOfStar(starGraph) << endl; 

    return 0;
}