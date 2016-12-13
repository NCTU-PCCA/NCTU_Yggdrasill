#include<cstdio>
#include<string>
using namespace std;
struct node{
	node *ch[2],*par;
	long long sum;
	int val,sz,add;
	node(){}
	node(int x):par(NULL),val(x),sum(x),add(0),sz(1){ch[0]=ch[1]=NULL;}
	bool dir(){return !par||par->ch[1]==this;}
	void pull();
	void push();
}pool[100100];
inline long long qsum(node *x){
	return x?1LL*x->add*x->sz+x->sum:0;
}
inline int qsz(node *x){return x?x->sz:0;}
void node::pull(){
	sum=val+qsum(ch[0])+qsum(ch[1]);
	sz=1+qsz(ch[0])+qsz(ch[1]);
}
void node::push(){
	if(add){
		val+=add;
		sum+=add*sz;
		if(ch[0]) ch[0]->add+=add;
		if(ch[1]) ch[1]->add+=add;
		add=0;
	}
}
inline void con(node *p,node *c,bool d){
	p->ch[d]=c;
	if(c) c->par=p;
}
void splay(node *x){
	x->push();
	while(x->par){
		node *p=x->par,*g=p->par;
		bool d=x->dir(),pd=p->dir();;
		con(p,x->ch[d^1],d);
		con(x,p,d^1);
		if(g){
			if(g->par) con(g->par,x,g->dir());
			else x->par=NULL;
			if(d^pd){
				con(g,x->ch[d],pd);
				con(x,g,pd^1);
			}
			else{
				con(g,p->ch[pd^1],pd);
				con(p,g,pd^1);
			}
			g->pull();
		}
		else x->par=NULL;
		p->pull();
		x->pull();
	}
}
void check_tree(node *t,int d){
	if(!t) return;
	check_tree(t->ch[0],d+1);
	for(int i=0;i<d;i++) printf("\t");
	printf("%d\n",t->val);
	check_tree(t->ch[1],d+1);
}
void split(node *t,int k,node *&a,node *&b){
	if(!k){
		a=NULL; b=t; return;
	}
	int rod;
	while( k != (rod=qsz(t->ch[0])+1) ){
		t->push();
		if(k>rod) k-=rod,t=t->ch[1];
		else t=t->ch[0];
	}
	splay(t);
	a=t;
	a->push();
	b=a->ch[1];
	a->ch[1]=NULL;
	a->pull();
	if(b) b->par=NULL;
}
node* merge(node *a,node *b){
	if(!a) return b;
	while(a->ch[1]){
		a->push();
		a=a->ch[1];
	}
	splay(a);
	con(a,b,1);
	a->pull();
	return a;
}
int main(){
	int n,q,x;
	node *root=NULL,*a,*b,*c;
	scanf("%d%d",&n,&q);
	for(int i=0;i<n;i++){
		scanf("%d",&x);
		node *tmp=new (pool+i) node(x);
		root=merge(root,tmp);
	}
	for(int i=0;i<q;i++){
		char tp;
		int x,y,z;
		scanf(" %c%d%d",&tp,&x,&y);
		split(root,x-1,a,b);
		split(b,y-x+1,b,c);
		if(tp=='C'){
			scanf("%d",&z);
			b->add+=z;
		}
		else printf("%lld\n",qsum(b));
		root=merge(a,merge(b,c));
	}
	return 0;
}