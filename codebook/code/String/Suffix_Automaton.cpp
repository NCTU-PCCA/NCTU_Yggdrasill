#include<bits/stdc++.h>
#define C 96
#define N 200100
using namespace std;
struct SAM{
	struct node{
		node *nxt[C],*pre;
		int len;
		vector<int> pos;
	};
	node mem[N*2],*root,*ed;
	int top;
	SAM(){
		top = 0;
		root = new_node(0);
		ed = root;
	}
	node *new_node(int l){
		for(int i=0;i<C;i++) mem[top].nxt[i]=NULL;
		mem[top].pre=NULL;
		mem[top].len=l;
		mem[top].pos.clear();
		return mem+(top++);
	}
	node *split_node(int l,node *p){
		for(int i=0;i<C;i++) mem[top].nxt[i]=p->nxt[i];
		mem[top].pre = p->pre;
		mem[top].len = l;
		mem[top].pos.assign()
		p->pre = mem+top;
		return mem+(top++);
	}
	void push(char c){
		node *nw = new_node(ed->len+1),*ptr=ed->pre;
		ed->nxt[c] = nw;
		nw->pos.push_back(ed->len);
		for(;ptr;ptr=ptr->pre){
			if(ptr->nxt[c]){
				if(ptr->nxt[c]->len==ptr->len+1){
					nw->pre = ptr->nxt[c];
				}
				else{
					node *tmp=ptr->nxt[c];
					nw->pre = split_node(ptr->len+1,tmp);
					while(ptr && ptr->nxt[c]==tmp){
						ptr->nxt[c] = nw->pre;
						ptr = ptr->pre;
					}
				}
				break;
			}
			else{
				ptr->nxt[c] = nw;
			}
		}
		if(!nw->pre) nw->pre = root;
		ed = ed->nxt[c];
	}
	void init(){
		while(top){
			mem[--top].pos.clear();
		}
		root = new_node(0);
		ed = root;
	}
	void push(char *s){
		for(int i=0;s[i];i++) push(s[i]-32);
	}
	long long count(){
		long long ans=0;
		for(int i=1;i<top;i++){
			ans+=mem[i].len-mem[i].pre->len;
		}
		return ans;
	}
}sam;
char S[N];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%s",S);
		sam.build(S);
		printf("%lld\n",sam.count());
	}
	return 0;
}