// Kosaraju - Find SCC by twice dfs, and the SCC DAG is in the Topology
// ordering.
// Owner: samsam2310
//
#include <bits/stdc++.h>
#define N 300002 // Maximum number of vertices
using namespace std;
vector<int> forward_graph[N];  // original graph
vector<int> backward_graph[N]; // reverse graph
vector<int> dag_graph[N];      // result dag graph(graph of scc)
int scc[N];                    // SCC index of a vertex
bool visit[N];
void init() {
    fill(forward_graph, forward_graph + N, vector<int>());
    fill(backward_graph, backward_graph + N, vector<int>());
    fill(dag_graph, dag_graph + N, vector<int>());
}
void dfs(vector<int> &graph, int now, int scc_id,
         stack<int> *leave_order = NULL) {
    visit[now] = true;
    if (scc != -1) {
        scc[now] = scc_id;
    }
    for (int v : graph[now]) {
        if (!visit[v]) {
            dfs(graph, v, scc_id, leave_order);
        }
    }
    if (leave_order) {
        leave_order->push(now);
    }
}
int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    init();
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b; // edge of a -> b
        cin >> a >> b;
        forward_graph[a].push_back(b);
        backward_graph[b].push_back(a);
    }
    // Find the SCC.
    memset(visit, 0, sizeof(visit));
    stack<int> leave_order;
    for (int i = 0; i < n; ++i) {
        if (!visit[i]) {
            dfs(forward_graph, i, -1, &leave_order);
        }
    }
    memset(visit, 0, sizeof(visit));
    int scc_id = 0;
    while (!leave_order.empty()) {
        int v = leave_order.top();
        leave_order.pop();
        if (!visit[v]) {
            dfs(backward_graph, i, scc_id, NULL);
            ++scc_id;
        }
    }
    // Build the SCC DAG.
    for (int i = 0; i < n; ++i) {
        for (int v : forward_graph[i]) {
            if (scc[i] != scc[v]) {
                dag_graph[scc[i]].push_back(scc[v]);
            }
        }
    }
    return 0;
}
