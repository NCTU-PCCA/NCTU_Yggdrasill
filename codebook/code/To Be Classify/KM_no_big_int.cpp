#include<cstdio>
#include<utility>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1010;
long long inf=1LL<<60;
long long cost[MAXN][MAXN]; 
long long lx[MAXN], ly[MAXN], slack[MAXN];
int mat[MAXN];
bool sx[MAXN], sy[MAXN]; 
bool cant[MAXN][MAXN];
int N; 
bool extend(int now) 
{ 
    sx[now] = true; 
    long long temp; 
    for(int i = 0; i < N; i++){
        if(!sy[i]){ 
            temp = -(cost[now][i]-lx[now]-ly[i]); 
            if(temp==0){ 
                sy[i] = true; 
                if(mat[i]==-1 || extend(mat[i])) { 
                    mat[i] = now; 
                    return true; 
                } 
            } 
            else if(temp < slack[i]) 
                slack[i] = temp; 
        } 
	}
    return false; 
} 
  
pair<long long,bool> KM() //finding the maximum value of perfect matching 
{ 
    long long ret = 0; 
    memset(mat, -1, sizeof(mat)); 
    //matching precalculation 
    for(int i = 0; i < N; i++) 
    { 
        lx[i] = -inf; 
        for(int j = 0; j < N; j++) 
            lx[i] = max(lx[i], cost[i][j]); 
		ly[i] = 0;
    } 
    //KM 
    for(int i = 0; i < N; i++) 
    { 
        for(int j = 0; j < N; j++) 
            slack[j] = inf; 
  
        while(true) 
        { 
            memset(sx, false, sizeof(sx)); 
            memset(sy, false, sizeof(sy)); 
  
            if(extend(i)) break; 
            long long themin = inf+1; 
  
            for(int j = 0; j < N; j++) 
                if(!sy[j] && slack[j] < themin) 
                    themin = slack[j]; 
			
            for(int j = 0; j < N; j++) 
            { 
                if(sx[j]) lx[j] = lx[j] - themin; 
                if(sy[j]) ly[j] = ly[j] + themin; 
                else slack[j] = slack[j] - themin; 
            } 
        } 
    } 
  
    for(int i = 0; i < N; i++){
		if(cant[mat[i]][i]) return make_pair(0LL,false);
        ret = ret + cost[mat[i]][i]; 
	}
    return make_pair(ret,true); 
} 
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		memset(cant,0,sizeof(cant));
		int k,x,y;
		long long L,U;
		long long xv[MAXN],yv[MAXN];
		scanf("%d%lld%lld%d",&N,&L,&U,&k);
		U-=L;
		while(k--){
			scanf("%d%d",&x,&y);
			cant[x-1][y-1]=true;
		}
		for(int i=0;i<N;i++) scanf("%lld",&xv[i]);
		for(int i=0;i<N;i++) scanf("%lld",&yv[i]);
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(cant[i][j]) cost[i][j]=-inf;
				else cost[i][j]=-min(max(0LL,xv[i]+yv[j]-L),U);
			}
		}
		pair<long long,bool> ans=KM();
		if(ans.second) printf("%lld\n",-ans.first);
		else puts("no");
	}
	return 0;
}