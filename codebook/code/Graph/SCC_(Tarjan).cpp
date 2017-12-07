void tarjan(int u) {
    visit[u] = low[u] = ++t;
    stack[top++] = u;
    instack[u] = true;
 
    for (int v : G[u]) {
        // tree edge
        if (!visit[v])
            tarjan(v);
        // tree/back/forward/cross edge
        // 已經遍歷過、但是尚未形成SCC的點
        if (instack[v])
            low[u] = min(low[u], low[v]);
    }
 
    // 形成SCC，從目前的DFS forest移除它。
    // u點會是SCC裡面，最早拜訪的點。
    if (visit[u] == low[u]) {
        int v;
        do {
            v = stack[--top];
            instack[v] = false;
            contract[v] = u;
        } while (v != u);
    }
}