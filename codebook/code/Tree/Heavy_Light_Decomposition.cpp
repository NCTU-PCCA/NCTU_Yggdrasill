//with set value && query sum, 1-based with n points
//remove vis in DFS, add it back if something weird happen(I don’t think it’s required)
using namespace std;
int sz[N],top[N],up[N],dep[N];
int lightval[N];   //value on light edge
struct node{
	node(){}
	node(int _l,int _r):val(1),l(_l),r(_r),lc(NULL),rc(NULL){}
	int l,r;
	node *lc,*rc;
	int sum;
	int val;
	int qsum(){return val>=0?val*(r-l):sum;}
	void push(){
		if(val>=0){
			sum=val*(r-l);
			lc->val=rc->val=val;
			val=-1;
		}
	}
	void pull(){
		sum=lc->qsum()+rc->qsum();
	}
};
node* tr[N];
node* build(int l,int r){
	node *now=new node(l,r);
	if(r-l>1){
		now->lc=build(l,(l+r)/2);
		now->rc=build((l+r)/2,r);
	}
	return now;
}
//partial
int qry(node* now,int l,int r){
	if(l>=r) return 0;
	if(l==now->l&&r==now->r){
		return now->qsum();
	}
	int m=(now->l+now->r)/2;
	now->push();
	if(l>=m){
		return qry(now->rc,l,r);
	}
	else if(r<=m){
		return qry(now->lc,l,r);
	}
	else return qry(now->lc,l,m)+qry(now->rc,m,r);
}
void set0(node *now,int l,int r){
	if(l>=r) return;
	if(l==now->l&&r==now->r){
		now->val=0;
		return;
	}
	int m=(now->l+now->r)/2;
	now->push();
	if(l>=m){
		set0(now->rc,l,r);
	}
	else if(r<=m){
		set0(now->lc,l,r);
	}
	else{
		set0(now->lc,l,m);
		set0(now->rc,m,r);
	}
	now->pull();
}
vector<int> g[N];
void DFS(int u,int p,int d){
	dep[u]=d;
	sz[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==p) continue;
		DFS(v,u,d+1);
		sz[u]+=sz[v];
}
}
void decom(int u,int p,bool istop){
	bool ed=true;
	if(istop) top[u]=u,up[u]=p,lightval[u]=1;
	else top[u]=top[p],up[u]=up[p];
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==p) continue;
		if(sz[v]>=sz[u]-sz[v]){
			decom(v,u,false);
			ed=false;
		}
		else decom(v,u,true);
	}
	if(ed){
		tr[top[u]]=build(dep[top[u]],dep[u]);
	}
}
//global
int qry(int u,int v){
	int res=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]) swap(u,v);
		res+=qry(tr[top[v]],dep[top[v]],dep[v]);
		res+=lightval[top[v]];
		v=up[top[v]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	res+=qry(tr[top[v]],dep[u],dep[v]);
	return res;
}
void set0(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]) swap(u,v);
		set0(tr[top[v]],dep[top[v]],dep[v]);
		lightval[top[v]]=0;
		v=up[top[v]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	set0(tr[top[v]],dep[u],dep[v]);
}
int main(){
	DFS(1,0,0);
	decom(1,0,true);
}
