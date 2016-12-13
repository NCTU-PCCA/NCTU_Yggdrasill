#define maxnode (1000+10) 
#define maxedge (40000+10)
#define INF 1023456789
#include<bits/stdc++.h>
using namespace std;
int node, src, dest, nedge; 
int head[maxnode], point[maxedge], nxt[maxedge], flow[maxedge], capa[maxedge], wt[maxedge]; 
int dist[maxnode], in[maxnode], from[maxnode], mf[maxnode]; 
//set number of node, source, and destination (one base)
void init(int _node, int _src, int _dest) { 
    node = _node; 
    src = _src; 
    dest = _dest; 
    nedge = 0; 
    memset(point, -1, sizeof(point)); 
    for (int i = 1; i <= node; i++) head[i] = -1; 
    nedge = 0; 
} 
void add_edge(int u, int v, int c1, int w) { 
    point[nedge] = v, capa[nedge] = c1, flow[nedge] = 0, nxt[nedge] = head[u], wt[nedge]=w, head[u] = (nedge++); 
    point[nedge] = u, capa[nedge] = 0, flow[nedge] = 0, nxt[nedge] = head[v], wt[nedge]=-w, head[v] = (nedge++); 
} 
int sp(int &left){
	for(int i=1;i<=node;i++) dist[i]=INF;
	queue<int> que;
	que.push(src);
	in[src]=1;
	mf[src]=left;
	dist[src]=0;
	while(!que.empty()){
		int u=que.front();
		que.pop();
		in[u]=0;
		if(dist[u]>=dist[dest]) continue;
		for(int v=head[u];v!=-1;v=nxt[v]){
			if(flow[v]==capa[v]) continue;
			if(dist[u]+wt[v]<dist[point[v]]){
				dist[point[v]]=dist[u]+wt[v];
				from[point[v]]=v;
				mf[point[v]]=min(mf[u],capa[v]-flow[v]);
				if(!in[point[v]]){
					in[point[v]]=1;
					que.push(point[v]);
				}
			}
		}
	}
	left-=mf[dest];
	if(dist[dest]<INF){
		for(int u=dest;u!=src;u=point[from[u]^1]){
			flow[from[u]]+=mf[dest];
			flow[from[u]^1]-=mf[dest];
		}
	}
	return dist[dest];
}
int min_cost_flow(){
	int res=0,tmp,maxflow=2;
	while(maxflow&&(tmp=sp(maxflow))<INF) res+=tmp;
	return res;
}
int main(){
	int n,m,x,y,z;
	while(scanf("%d%d",&n,&m)==2){
		init(n,1,n);
		for(int i=0;i<m;i++){
			scanf("%d%d%d",&x,&y,&z);
			add_edge(x,y,1,z);
			add_edge(y,x,1,z); //undirected
		}
		printf("%d\n",min_cost_flow());
	}
	return 0;
}
