#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <string>

using namespace std;

struct Edge {
    int to;
    double bandwidth;
};

struct Node {
    int id;
    vector<Edge> edges;
};

class RoutingEngine {
private:
    vector<unique_ptr<Node>> nodes;
    int numNodes;

    bool dfs(int curr, int dest, double minBW, vector<bool>& visited, vector<int>& path) {
        visited[curr] = true;
        path.push_back(curr);

        if (curr == dest) {
            return true;
        }

        for (const auto& edge : nodes[curr]->edges) {
            if (!visited[edge.to] && edge.bandwidth >= minBW) {
                if (dfs(edge.to, dest, minBW, visited, path)) {
                    return true;
                }
            }
        }

        path.pop_back();
        return false;
    }

public:
    RoutingEngine(int n) : numNodes(n) {
        for (int i = 0; i < n; i++) {
            auto node = make_unique<Node>();
            node->id = i;
            nodes.push_back(move(node));
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);

        if (!file) {
            cerr << "Error: Could not open file '" << filename << "'." << endl;
            return;
        }

        int u, v;
        double bw;

        while (file >> u >> v >> bw) {
            if (u >= 0 && u < numNodes && v >= 0 && v < numNodes) {
                nodes[u]->edges.push_back({v, bw});
            } else {
                cerr << "Warning: Skipping invalid edge " << u << " -> " << v << endl;
            }
        }

        file.close();
    }

    void printGraph() const {
        for (const auto& node : nodes) {
            cout << "Node " << node->id << ": ";
            for (const auto& e : node->edges) {
                cout << "-(" << e.bandwidth << ")-> " << e.to << " ";
            }
            cout << endl;
        }
    }

    vector<int> findPath(int source, int dest, double minBW) {
        vector<bool> visited(numNodes, false);
        vector<int> path;

        if (source < 0 || source >= numNodes || dest < 0 || dest >= numNodes) {
            cout << "Invalid source or destination." << endl;
            return path;
        }

        if (dfs(source, dest, minBW, visited, path)) {
            cout << "Path found (min BW >= " << minBW << "): ";
            for (size_t i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i < path.size() - 1) {
                    cout << " -> ";
                }
            }
            cout << endl;
        } else {
            cout << "No feasible path found." << endl;
        }

        return path;
    }
};

int main() {
    RoutingEngine engine(6);

    engine.loadFromFile("network.txt");

    cout << "=== Network Topology ===" << endl;
    engine.printGraph();

    cout << endl;
    cout << "=== Finding paths ===" << endl;
    engine.findPath(0, 5, 50);
    engine.findPath(0, 5, 100);
    engine.findPath(0, 5, 200);

    return 0;
}