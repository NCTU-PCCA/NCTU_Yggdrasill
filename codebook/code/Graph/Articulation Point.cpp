void tarjan(int u, int p)
{   // u 為當前點, p 為當前點之母節點
	// cnt 為 DFS 次序
    low[u] = dfn[u] = ++cnt;
    for (int v : G[u]) {
        if (u == rt && !dfn[v]) ++c;
        if (!dfn[v]) {
        	// (u, v) 為 Tree Edge
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            // To check if u is AP or not.
            if (dfn[u] <= low[v] && u != rt) ge[u] = 1;
        }
        // 注意不可以同一條邊走兩次，且根節點特判
        if (v != p && p != -1)
            low[u] = min(low[u], dfn[v]);
    }
}