const double eps = 1e-10;
const double INF = 1.0/0.0;
const double SIDE = 10000;
const double PI = acos(-1.0);
const int MAXN = 500000 + 10;
struct PT{
    double x,y;
    PT(){}
    PT(double x,double y):x(x),y(y){}
    PT operator + (const PT& p)const{
        return PT(x+p.x,y+p.y);
    }
    PT operator - (const PT& p)const{
        return PT(x-p.x,y-p.y);
    }
    PT operator * (double c)const{
        return PT(x*c,y*c);
    }
    PT operator / (double c)const{
        return PT(x/c,y/c);
    }
	PT rot(double a)const{return PT(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a));}
    double operator *(const PT& p)const{
        return x*p.x+y*p.y;
    }
    double operator ^(const PT& p)const{
        return x*p.y-y*p.x;
    }
    bool operator ==(const PT& p)const{
        return fabs(x-p.x)<eps&&fabs(y-p.y)<eps;
    }
	double len2()const{return x*x+y*y;}
	double len()const{return sqrt(len2());}
}poi[MAXN],stk[MAXN];
struct LINE{
    PT a,b;
    double angle;
    LINE(){}
    LINE(PT _a,PT _b):a(_a),b(_b),angle(atan2(_b.y-_a.y,_b.x-_a.x)){}
}line[MAXN],deq[MAXN];
int top;
inline int ori(const PT& p1,const PT& p2,const PT& p3){
    double a=(p2-p1)^(p3-p1);
    if(a>-eps&&a<eps)return 0;
    return a>0 ? 1:-1;
}
inline bool btw(const PT& p1,const PT& p2,const PT& p3){
    return (p2-p1)*(p3-p1)<eps;
}
//segment intersection
inline bool intersection(const PT& p1,const PT& p2,const PT& p3,const PT& p4){
    int a123=ori(p1,p2,p3);
    int a124=ori(p1,p2,p4);
    int a341=ori(p3,p4,p1);
    int a342=ori(p3,p4,p2);
    if(a123==0&&a124==0)return btw(p1,p3,p4)||btw(p2,p3,p4)||btw(p3,p1,p2)||btw(p4,p1,p2);
    return a123*a124 <= 0 && a341*a342 <= 0;
}
inline PT intersectionPoint(const PT& p1,const PT& p2,const PT& p3,const PT& p4){
    double a123=(p2-p1)^(p3-p1);
    double a124=(p2-p1)^(p4-p1);
    return (p4*a123-p3*a124)/(a123-a124);
}
//line intersection
inline PT intersectionPoint(const LINE& l1,const LINE& l2){
    PT p1=l1.a,p2=l1.b,p3=l2.a,p4=l2.b;
    double a123=(p2-p1)^(p3-p1);
    double a124=(p2-p1)^(p4-p1);
    return (p4*a123-p3*a124)/(a123-a124);
}
PT foot(const LINE& l,const PT& p){
	PT m(l.b.y-l.a.y,l.a.x-l.b.x);
	return p+m*(l.a-p ^ l.b-p)/((l.b-l.a).len2());
}
PT mirror(const LINE& l,const PT& p){
	PT m(l.b.y-l.a.y,l.a.x-l.b.x);
	return p+m*(l.a-p ^ l.b-p)/((l.b-l.a).len2())*2;
}
//segment-point distance
inline double sp_dis(PT a,PT l1,PT l2){
    if((a-l1)*(l2-l1)<0) return (l1-a).len();
	else if((a-l2)*(l1-l2)<0) return (l2-a).len();
    return fabs(l1-a^l2-a)/((l2-l1).len());
}

struct cir{
    point c;
    double r;
}o[10];
double out_ang(cir a,cir b){    //a.c+(b.c-a.c).unit().rot(ang)*b.r
    return acos((a.r-b.r)/(a.c-b.c).len());
}
double in_ang(cir a,cir b){
    return acos((a.r+b.r)/(a.c-b.c).len());
}
int main(){
	double tmp,sum;
	if(fabs(o[i].r-o[j].r)<(o[j].c-o[i].c).len()){
		tmp = out_ang(o[i],o[j]);
		sum = ang_add(cl,tmp);
		pi=o[i].c+point(o[i].r*cos(sum),o[i].r*sin(sum));
		pj=o[j].c+point(o[j].r*cos(sum),o[j].r*sin(sum));
		sum = ang_add(cl,-tmp);
		pi=o[i].c+point(o[i].r*cos(sum),o[i].r*sin(sum));
		pj=o[j].c+point(o[j].r*cos(sum),o[j].r*sin(sum));
	}
	if(o[i].r+o[j].r<(o[j].c-o[i].c).len()){
		tmp = in_ang(o[i],o[j]);
		sum = ang_add(cl,tmp);
		pi=o[i].c+point(o[i].r*cos(sum),o[i].r*sin(sum));
		pj=o[j].c-point(o[j].r*cos(sum),o[j].r*sin(sum));
		sum = ang_add(cl,-tmp);
		pi=o[i].c+point(o[i].r*cos(sum),o[i].r*sin(sum));
		pj=o[j].c-point(o[j].r*cos(sum),o[j].r*sin(sum));
	}
}

inline double dist(const PT& p1,const PT& p2){
    return sqrt((p2-p1)*(p2-p1));
}
inline double tri(const PT& p1,const PT& p2,const PT& p3){
    return fabs((p2-p1)^(p3-p1));
}
inline double getPerimeter(){
    double res=0.0;
    poi[top++]=poi[0];
    for(int i=0;i<top-1;i++)res+=dist(poi[i],poi[i+1]);
    return res;
}
inline double getarea(){
    double res=0.0;
    for(int i=1;i<top-1;i++)res+=tri(poi[0],poi[i],poi[i+1]);
    return 0.5*res;
}

//convex hull
inline bool cmp_convex(const PT &a,const PT &b){
    if(a.x!=b.x)return a.x<b.x;
    return a.y<b.y;
}
inline void convex_hull(PT a[],int &n){
    top=0;
    sort(a,a+n,cmp_convex);
    for(int i=0;i<n;i++){
        while(top>=2&&ori(stk[top-2],stk[top-1],a[i])>=0)top--;
        stk[top++]=a[i];
    }
    for(int i=n-2,t=top+1;i>=0; i--){
        while(top>=t&&ori(stk[top-2],stk[top-1],a[i])>=0)top--;
        stk[top++]=a[i];
    }
    top--;
    for(int i=0;i<top;i++)poi[i]=stk[i];
}
//half plane intersection
inline bool cmp_half_plane(const LINE &a,const LINE &b){
    if(fabs(a.angle-b.angle)<eps)return ori(a.a,a.b,b.a)<0;
    return a.angle > b.angle;
}
inline void half_plane_intersection(LINE a[],int &n){
    int m=1,front=0,rear=1;
    sort(a,a+n,cmp_half_plane);
    for(int i=1;i<n;i++){
        if(fabs(a[i].angle-a[m-1].angle)>eps)a[m++]=a[i];
    }
    deq[0]=a[0],deq[1]=a[1];
    for(int i=2;i<m;i++){
        while(front<rear&&ori(a[i].a,a[i].b,intersectionPoint(deq[rear],deq[rear-1]))<0)rear--;
        while(front<rear&&ori(a[i].a,a[i].b,intersectionPoint(deq[front],deq[front+1]))<0)front++;
        deq[++rear]=a[i];
    }
	while(front<rear&&ori(deq[front].a,deq[front].b,intersectionPoint(deq[rear],deq[rear-1]))<0)rear--;
    while(front<rear&&ori(deq[rear].a,deq[rear].b,intersectionPoint(deq[front],deq[front+1]))<0)front++;
    if(front==rear)return;

    top=0;
    for(int i=front;i<rear;i++)poi[top++]=intersectionPoint(deq[i],deq[i+1]);
    if(rear>front+1)poi[top++]=intersectionPoint(deq[front],deq[rear]);
}




//smallest cover rectangle
double ans1,ans2;
void rotating_calipers(){
    ans1=ans2=INF;
    int j=1,k=1,l=1;
    poi[top]=poi[0];
    for(int i=0;i<top;i++){
        while(tri(poi[i],poi[i+1],poi[j])<tri(poi[i],poi[i+1],poi[j+1])) j=(j+1)%top; 
        while(((poi[i+1]-poi[i])*(poi[k+1]-poi[k]))>eps)k=(k+1)%top;
        if(i==0)l=(k+1)%top;
        while(((poi[i+1]-poi[i])*(poi[l+1]-poi[l]))<-eps)l=(l+1)%top;
        double tmp1 = tri(poi[i],poi[i+1],poi[j])/dist(poi[i],poi[i+1]);
        double tmp2 = (((poi[k]-poi[i])*(poi[i+1]-poi[i]))-((poi[l]-poi[i])*(poi[i+1]-poi[i])))/dist(poi[i],poi[i+1]);
        if((tmp1+tmp2)*2.0<ans1)ans1=(tmp1+tmp2)*2.0;
        if(tmp1*tmp2<ans2)ans2=tmp1*tmp2;
    }
}
int main(){
    int n,m;
    while(~scanf("%d",&n)&&n){
        for(int i=0;i<n;i++)scanf("%lf%lf",&poi[i].x,&poi[i].y);
        convex_hull(poi,n);
        rotating_calipers();
        printf("%.2f %.2f\n",ans2,ans1);
    }
}

inline bool online(const LINE &L,const PT &p){
    return ori(p,L.a,L.b)==0&&btw(p,L.a,L.b);
}
inline bool on_convex(const PT& p){
    for(int i=0;i<top;i++)
        if(p==poi[i])return 1;
    poi[top]=poi[0];
    for(int i=0;i<top;i++){
        line[i].a=poi[i];
        line[i].b=poi[i+1];
    }
    for(int i=0;i<top;i++)
        if(online(line[i],p))return 1;
    return 0;
}
//originally in long long, should be modified
bool in_simple_polygon(PT b[],int k){
	bool flag=false;
	for(int j=0;j<k;j++){		
		if(((p-b[j])^(p-b[(j+1)%k]))==0&&(p-b[j])*(p-b[(j+1)%k])<=0){
			flag=true;
			break;
		}
		if((b[j].y<p.y)^(b[(j+1)%k].y<p.y)){
			long long xss=(b[j]-p)^(b[(j+1)%k]-p);
			if((xss<0)^(b[j].y<b[(j+1)%k].y)){
				flag^=1;
			}
		}
	}
	return flag;
}
