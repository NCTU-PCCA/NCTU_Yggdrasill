//source: chikOkU - Osaka University
enum DR{L,R,U,D,NONE};
int R_table[6][4]={
	{2,3,5,4},
	{3,1,4,6},
	{2,6,5,1},
	{1,5,6,2},
	{1,3,6,4},
	{4,5,3,2}
};
struct dice{
	int t,f;
	int getR(){
		int id=find(R_table[t-1],R_table[t-1]+4,f)-R_table[t-1];
		id=(id+1)%4;
		return R_tabele[t-1][id];
	}
	DR getDir(int x){
		if(x==t) return NONE;
		else if(t+x==7) return NONE;
		else if(f==x) return U;
		else if(f+x==7) return D;
		int r = getR();
		if(x==r) return R;
		else return L;
	}
	void rot(DR dr){
		if(dr==L) t=getR();
		else if(dr==R) t=7-getR();
		else if(dr==U){
			int nt=7-f;
			f=t;
			t=nt;
		}
		else{
			int nf=7-t;
			t=f;
			f=nf;
		}
	}
}