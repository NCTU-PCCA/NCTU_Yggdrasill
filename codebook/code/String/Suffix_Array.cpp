//should initialize s and n first 
#define N 301000
using namespace std;
char s[N]; //string=s,suffix array=sar,longest common prefix=lcp
int rk[2][N],id[2][N];
int n,p;
int cnt[N];
int len[N],od[N],sar[N];
inline int sr(int i,int t){ //rank of shifted position
	return i+t<n?rk[p][i+t]:-1;
}
inline bool check_same(int i,int j,int t){
	return rk[p][i]==rk[p][j]&&sr(i,t)==sr(j,t);
}
bool cmp(int i,int j){
	return s[i]<s[j];
}
void sa(){ //length of array s
	int i,t,now,pre;
	memset(cnt,0,sizeof(cnt));
	for(i=0;i<n;i++){
		id[p][i]=i;
		rk[p][i]=s[i];
		cnt[s[i]]++;
	}
	for(i=1;i<128;i++) cnt[i]+=cnt[i-1];
	sort(id[p],id[p]+n,cmp);
	for(t=1;t<n;t<<=1){
        //least significant bit is already sorted
		for(i=n-1;i>=0;i--){
            now=id[p][i]-t;
			if(now>=0) id[p^1][--cnt[rk[p][now]]]=now;
		}
		for(i=n-t;i<n;i++){
            id[p^1][--cnt[rk[p][i]]]=i;
		}
		memset(cnt,0,sizeof(cnt));
		now=id[p^1][0];
		rk[p^1][now]=0;
		cnt[0]++;
		for(i=1;i<n;i++){
			pre=now;
			now=id[p^1][i];
			if(check_same(pre,now,t)){
				rk[p^1][now]=rk[p^1][pre];
			}
			else{
				rk[p^1][now]=rk[p^1][pre]+1;
			}
			cnt[rk[p^1][now]]++;
		}
		p^=1;
		if(rk[p][now]==n-1) break;
		for(i=1;i<n;i++) cnt[i]+=cnt[i-1];
	}
	memcpy(sar,id[p],sizeof(sar));
}
void lcp(){
    int i,l,pre;
    for(i=0;i<n;i++) od[sar[i]]=i;
    for(i=0;i<n;i++){
        if(i) l=len[od[i-1]]?len[od[i-1]]-1:0;
        else l=0;
        if(od[i]){
            pre=sar[od[i]-1];
            while(pre+l<n&&i+l<n&&s[pre+l]==s[i+l]) l++;
            len[od[i]]=l;
        }
        else len[0]=0;
    }
}
