struct Treap{
	Treap *l,*r;
	int pri,sz,val,add;
	Treap(int _val):pri(rand()),sz(1),val(_val),add(0),l(NULL),r(NULL){}
};

int size(Treap *t){
	return t?t->sz:0;
}
void pull(Treap *t){
	t->sz=size(t->l)+size(t->r)+1;
}
void push(Treap *t){
	t->val+=t->add;
	if(t->l) t->l->add+=t->add;
	if(t->r) t->r->add+=t->add;
	t->add=0;
}
Treap* merge(Treap *a,Treap *b){
	if(!a||!b) return a?a:b;
	if(a->pri > b->pri){
		push(a);
		a->r = merge(a->r,b);
		pull(a);
		return a;
	}
	else{
		push(b);
		b->l = merge(a,b->l);
		pull(b);
		return b;
	}
}
void split(Treap *t,int k,Treap *&a,Treap *&b){
	if(!t) a=b=NULL;
	else{
		push(t);
		if(size(t->l) < k){
			a=t;
			split(t->r,k-size(t->l)-1,a->r,b);
			pull(a);
		}
		else{
			b=t;
			split(t->l,k,a,b->l);
			pull(b);
		}
	}
}
