#include<cstdio>
#include<vector>
#include<algorithm>
#define N 50010
using namespace std;
long long dp[N],c[N],sum[N];
int len;
inline long long sq(long long x){
	return x*x;
}
inline long long cost(int a,int b){
	return sq(sum[b]-sum[a]-len);
}
int main(){
	int n,i,j,l,r,m,s;
	vector<int> k,p;
	scanf("%d%d",&n,&len);
	len++;
	for(i=1;i<=n;i++){
		scanf("%lld",&c[i]);
		c[i]++;
		sum[i]=sum[i-1]+c[i];
	}
	p.push_back(1);
	k.push_back(0);
	for(i=1;i<=n;i++){
		j=upper_bound(p.begin(),p.end(),i)-1-p.begin();
		dp[i]=dp[k[j]]+cost(k[j],i);
		r=n+1;
		while(!p.empty()&&p.back()>i){
			if(dp[i]+cost(i,p.back())<=dp[k.back()]+cost(k.back(),p.back())){
				r=p.back();
				p.pop_back();
				k.pop_back();
			}
			else break;
		}
		l=max(p.back()-1,i);
		s=1;
		while(l+s<r) s<<=1;
		while(s){
			while(l+s>=r) s>>=1;
			if(!s) break;
			if(dp[k.back()]+cost(k.back(),l+s)<dp[i]+cost(i,l+s)) l+=s;
			else s>>=1;
		}
			
		if(l+1<=n){
			k.push_back(i);
			p.push_back(l+1);
		}
	}
	printf("%lld\n",dp[n]);
	return 0;
}