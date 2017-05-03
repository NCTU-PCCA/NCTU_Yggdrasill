#include<bits/stdc++.h>
#define V 20100
#define inf 0x3f3f3f3f
int mx[V],my[V],dis[V],que[V];
bool vis[V];
vector<int> g[V];
bool DFS(int u){
	vis[u]=true;
	for(int i=0;i<g[u].size();i++){
		int v=my[g[u][i]];
		if(v==-1||!vis[v]&&dis[v]==dis[u]+1&&DFS(v)){
			mx[u]=g[u][i];
			my[g[u][i]]=u;
			return true;
		}
	}
	return false;
}
// n is the size of left hand side
int Hopcroft_Karp(int n){
	int matching=0,qt,qf,sp,i,u,v;
	bool flag=true;
	memset(mx,-1,sizeof(mx));
	memset(my,-1,sizeof(my));
	while(flag){
		flag=false;
		qt=qf=0;
		sp=inf;
		for(i=0;i<n;i++){
			if(mx[i]==-1){
				dis[i]=0;
				que[qt++]=i;
			}
			else dis[i]=inf;
		}
		while(qf<qt){
			u=que[qf++];
			if(dis[u]>=sp) continue;
			for(i=0;i<g[u].size();i++){
				v=my[g[u][i]];
				if(v==-1){
					if(dis[u]+1<sp){
						sp=dis[u]+1;
						flag=true;
					}
				}
				else if(dis[u]+1<dis[v]){
					dis[v]=dis[u]+1;
					que[qt++]=v;
				}
			}
		}
		if(flag){
			memset(vis,0,sizeof(vis));
			for(i=0;i<n;i++){
				if(dis[i]==0&&DFS(i)) matching++;
			}
		}
	}
	return matching;
}
