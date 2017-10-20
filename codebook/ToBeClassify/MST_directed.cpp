#include<cstdio>
#include<vector>
#include<algorithm>
#define N 100100
using namespace std;
struct edge{
	edge(){}
	edge(int _f,int _d):f(_f),d(_d){}
	int f;
	int d;
	bool operator<(const edge &rhs)const{return d<rhs.d;}
};
struct node{
	int sz,v,now;
	node *l,*r;
	void pull(){sz=1+(l?l->sz:0)+(r?r->sz:0);}
}pq[N];
int pa[N],sub[N],stk[N],top;
bool vis[N],instk[N];
vector<edge> rg[N];
void init(int n){
	for(int i=0;i<n;i++){
		pa[i]=i;
		sub[i]=0;
		pq[i].l=pq[i].r=NULL;
		pq[i].sz=1;
		pq[i].v=i;
		pq[i].now=0;
	}
}
int find(int x){
	if(pa[x]==x) return x;
	int y=find(pa[x]);
	if(pa[x]!=y) sub[x]+=sub[pa[x]],pa[x]=y;
	return pa[x];
}
inline int get_sub(int x){
	if(x==find(x)) return sub[x];
	else return sub[x]+sub[pa[x]];
}
inline int get_cost(const node& a){
	return rg[a.v][a.now].d-get_sub(a.v);
}
bool cmp(const node& a,const node& b){
	return get_cost(a)<get_cost(b);
}
node* merge(node *a,node *b){
	if(!a||!b) return a?a:b;
	if(cmp(*b,*a)) swap(a,b);
	a->r=merge(a->r,b);
	if((a->l?a->l->sz:0)<(a->r?a->r->sz:0)) swap(a->l,a->r);
	a.pull();
	return a;
}
int min_cost_arborescence(int r,int n){
	vis[r]=true;
	int res=0;
	for(int i=0;i<n;i++){
		if(!vis[i]){
			top=0;
			int u=i;
			while(!vis[u]){
				
			}
		}
	}
}
int main(){
	int n,m,r,x,y,w;
	scanf("%d%d%d",&n,&m,&r);
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&x,&y,&w);
		rg[y].push_back(edge(x,w));
		sort()
	}
}