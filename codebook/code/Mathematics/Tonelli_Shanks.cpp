#include<cstdio>
#include<cassert>
#include<cstdlib>
using namespace std;
int pow_mod(int a,int p,int q){ //a^p mod q
	int r=1;
	while(p){
		if(p&1) r=1LL*r*a%q;
		a=1LL*a*a%q;
		p>>=1;
	}
	return r;
}
int Jacobi(int q,int p){ //q/p
	if(p==1) return 1;
	q%=p;
	int c2=0,m2;
	while(!(q&1)){
		q>>=1;
		c2^=1;
	}
	if((p&7)==7||(p&7)==1||!c2) m2=1;
	else m2=-1;
	if((p&2)&&(q&2)) m2*=-1;
	return m2*Jacobi(p,q);
}	
int Tonelli_Shanks(int a,int p){ //p is prime,gcd(a,p)=1
	if(p==2) return 1;
	if(Jacobi(a,p)==-1) return -1;
	int s=0,q=p-1,z=2;
	while(!(q&1)) q>>=1,s++;
	while(Jacobi(z,p)==1) z++;
	z = pow_mod(z, q, p);
	int zp[30]={z};
	for(int i=1;i<s;i++) zp[i]=1LL*zp[i-1]*zp[i-1]%p;
	int r = pow_mod(a,(q+1)>>1, p), t = pow_mod(a, q, p);
	while(t!=1){
		int m=0;
		for(int i=t;i!=1;i=1LL*i*i%p) m++;
		r=1LL*r*zp[s-m-1]%p;
		t=1LL*t*zp[s-m]%p;
	}
	return r;
}
int main(){
	for(int i=0;i<37;i++){
		
	}
	return 0;
}