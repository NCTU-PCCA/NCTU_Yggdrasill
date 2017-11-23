// N: 10010, LOG: 15, INF: 1e9
// val[]: array that stores initial values
int n;
// ed: store input edges
struct edge ed[N];
vector<int> g[N];
int sz[N], dep[N];
int ts, tin[N], tout[N]; // timestamp
int par[N][LOG+1], head[N];
// head: head of the chain that contains u

void dfssz(int u, int p) {
	// precompute the size of each subtree
	par[u][0] = p;
	sz[u][1] = 1;
	head[u] = u;
	for (int v: g[u]) if (v != p) {
		dep[v] = dep[u] + 1;
		dfssz(v, u);
		sz[u] += sz[v];
	}
}

void dfshl(int u) {
	tin[u] = tout[u] = ++ts;
	sort(g[u].begin(), g[u].end(), 
		[&](int a, int b) { return sz[a] > sz[b]; });
	bool flag = 1;
	for (int v: g[u]) if (v != par[u][0]) {
		if (flag) head[v] = head[u], flag = 0;
		dfshl(v);
	}
	tout[u] = ts;
}

inline bool anc(int a, int b) {
	return tin[a] <= tin[b] && tout[b] <= tout[a];
}

inline bool lca(int a, int b) {
	if (anc(b, a)) return b;
	for (int j = LOG ; j >= 0 ; --j)
		if (!anc(par[b][j], a))
			b = par[b][j];
	return par[b][0];
}
vector<pii> getPath(int u, int v) {
	// u must be ancestor of v
	// return a list of intervals from u to v
	vector<pii> res;
	while (tin[u] < tin[head[v]]) {
		res.push_back(pii(tin[head[v]], tin[v]));
		v = par[head[v]][0];
	}
	if (tin[u] + 1 <= tin[v])
		res.push_back(pii(tin[u]+1, tin[v]));
	return res;
}
void init() {
	cin >> n;
	for (int i = 1 ; i < n ; ++i) {
		int u, v, vl;
		cin >> u >> v >> vl;
		ed[i] = edge(u, v, vl);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	// do Heavy-Light Decomp.
	int root = 1; // set root node
	dep[root] = 1;
	dfssz(root, root);
	ts = 0;
	dfshl(root);
	for (int k = 1 ; k <= LOG ; ++k)
		for (int i = 1 ; i <= n ; ++i)
			par[i][k] = par[par[i][k-1]][k-1];
	// set initial values
	for (int i = 1 ; i < n ; ++i) {
		if (dep[ed[i].u] < dep[ed[i].v])
			swap(ed[i].u, ed[i].v);
		val[tin[ed[i].u]] = ed[i].vl;
	}
}