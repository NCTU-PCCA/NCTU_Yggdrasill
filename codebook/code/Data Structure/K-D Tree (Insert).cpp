#ifndef SUNMOON_DYNEMIC_KD_TREE
#define SUNMOON_DYNEMIC_KD_TREE
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
template<typename T,size_t kd>//kd表示有幾個維度 
class kd_tree{
	public:
		struct point{
			T d[kd];
			inline T dist(const point &x)const{
				T ret=0;
				for(size_t i=0;i<kd;++i)ret+=std::abs(d[i]-x.d[i]);
				return ret;
			}
			inline bool operator<(const point &b)const{
				return d[0]<b.d[0];
			}
		};
	private:
		struct node{
			node *l,*r;
			point pid;
			int s;
			node(const point &p):l(0),r(0),pid(p),s(1){}
			inline void up(){
				s=(l?l->s:0)+1+(r?r->s:0);
			}
		}*root;
		const double alpha,loga;
		const T INF;//記得要給INF，表示極大值 
		std::vector<node*> A;
		int qM;
		std::priority_queue<std::pair<T,point > >pQ;
		struct __cmp{
			int sort_id;
			inline bool operator()(const node*x,const node*y)const{
				return x->pid.d[sort_id]<y->pid.d[sort_id];
			}
		}cmp;
		void clear(node *o){
			if(!o)return;
			clear(o->l);
			clear(o->r);
			delete o;
		}
		inline int size(node *o){
			return o?o->s:0;
		}
		node* build(int k,int l,int r){
			if(l>r)return 0;
			if(k==kd)k=0;
			int mid=(l+r)/2;
			cmp.sort_id=k;
			std::nth_element(A.begin()+l,A.begin()+mid,A.begin()+r+1,cmp);
			node *ret=A[mid];
			ret->l=build(k+1,l,mid-1);
			ret->r=build(k+1,mid+1,r);
			ret->up();
			return ret;
		}
		inline bool isbad(node*o){
			return size(o->l)>alpha*o->s||size(o->r)>alpha*o->s;
		}
		void flatten(node *u,typename std::vector<node*>::iterator &it){
			if(!u)return;
			flatten(u->l,it);
			*it=u;
			flatten(u->r,++it);
		}
		bool insert(node*&u,int k,const point &x,int dep){
			if(!u){
				u=new node(x);
				return dep<=0;
			}
			++u->s;
			if(insert(x.d[k]<u->pid.d[k]?u->l:u->r,(k+1)%kd,x,dep-1)){
				if(!isbad(u))return 1;
				if((int)A.size()<u->s)A.resize(u->s);
				typename std::vector<node*>::iterator it=A.begin();
				flatten(u,it);
				u=build(k,0,u->s-1);
			}
			return 0;
		}
		inline T heuristic(const T h[])const{
			T ret=0;
			for(size_t i=0;i<kd;++i)ret+=h[i];
			return ret;
		}
		void nearest(node *u,int k,const point &x,T *h,T &mndist){
			if(u==0||heuristic(h)>=mndist)return;
			T dist=u->pid.dist(x),old=h[k];
			/*mndist=std::min(mndist,dist);*/
			if(dist<mndist){
				pQ.push(std::make_pair(dist,u->pid));
				if((int)pQ.size()==qM+1){
					mndist=pQ.top().first,pQ.pop();
				}
			}
			if(x.d[k]<u->pid.d[k]){
				nearest(u->l,(k+1)%kd,x,h,mndist);
				h[k]=std::abs(x.d[k]-u->pid.d[k]);
				nearest(u->r,(k+1)%kd,x,h,mndist);
			}else{
				nearest(u->r,(k+1)%kd,x,h,mndist);
				h[k]=std::abs(x.d[k]-u->pid.d[k]);
				nearest(u->l,(k+1)%kd,x,h,mndist);
			}
			h[k]=old;
		}
	public:
		kd_tree(const T &INF,double a=0.75):root(0),alpha(a),loga(log2(1.0/a)),INF(INF){}
		inline void clear(){
			clear(root),root=0;
		}
		inline void build(int n,const point *p){
			clear(root),A.resize(n);
			for(int i=0;i<n;++i)A[i]=new node(p[i]);
			root=build(0,0,n-1);
		}
		inline void insert(const point &x){
			insert(root,0,x,std::__lg(size(root))/loga);
		}
		inline T nearest(const point &x,int k){
			qM=k;
			T mndist=INF,h[kd]={};
			nearest(root,0,x,h,mndist);
			mndist=pQ.top().first;
			pQ=std::priority_queue<std::pair<T,point > >();
			return mndist;/*回傳離x第k近的點的距離*/ 
		}
		inline int size(){return root?root->s:0;}
};
#endif