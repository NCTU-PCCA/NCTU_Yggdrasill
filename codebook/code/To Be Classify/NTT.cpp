//prime for 1<<20 :    998244353, 1051721729, 1053818881
long long pow_mod(long long a,long long p,long long q){
	int r=1;
	while(p){
		if(p&1) r=r*a%q;
		p>>=1;
		a=a*a%q;
	}
	return r;
}
bool prime_test(long long p){
	long long q=p-1,s=0;
	while(!(q&1)){
		q>>=1;
		s++;
	}
	for(int i=0;i<20;i++){
		long long a=rand()%(p-1)+1,x=pow_mod(a,q,p);
		if(x==1) continue;
		bool flag=false;
		for(int j=0;j<s;j++){
			if(x==p-1){
				flag=true;
				break;
			}
			x=x*x%p;
		}
		if(!flag) return false;
	}
	return true;
}
void build(){
	int num=0;
	for(long long i=1000;num<2;i++){
		long long p=i<<20|1;
		if(prime_test(p)){
			prm[num]=p;
			bool flag=true;
			for(long long g=2;flag;g++){
				flag=false;
				long long tmp=pow_mod(g,i,p);
				for(int j=0;j<20;j++){
					rt[num][20-j]=tmp;
					if(tmp==1){
						flag=true;
						break;
					}
					tmp=tmp*tmp%p;
				}
			}
			num++;
		}
	}
}
void FFT(long long x[], bool pos, int u){
    for (int i=1, j=0; i<N; ++i){
        for (int k=N>>1; !((j^=k)&k); k>>=1) ;
        if (i>j) swap(x[i], x[j]);
    }
    for (int k=2; k<=N; k<<=1){
        long long om = pos?rt[u][__lg(k)]:pow_mod(rt[u][__lg(k)],prm[u]-2,prm[u]);
        for (int j=0; j<N; j+=k){
            long long mul = 1;
            for (int i=j; i<j+k/2; i++){
				long long a = x[i], b = x[i+k/2]*mul%prm[u];
                x[i]     = (a + b)%prm[u];
                x[i+k/2] = (a + prm[u] - b)%prm[u];
                mul = mul*om%prm[u];
            }
        }
    }
}
//double 
const double π = 2.0 * acos(0);
const int N = 8;
complex<double> x[N];
void FFT(){
    // reverse bit and replace
    for (int i=1, j=0; i<N; ++i){
        for (int k=N>>1; !((j^=k)&k); k>>=1) ;
        if (i>j) swap(x[i], x[j]);
    }
    for (int k=2; k<=N; k<<=1){
        double ω = -2.0 * π / k;
        complex<double> dθ(cos(ω), sin(ω));
        // 每k個做一次FFT
        for (int j=0; j<N; j+=k){
            complex<double> θ(1, 0);
            for (int i=j; i<j+k/2; i++){
                complex<double> a = x[i];
                complex<double> b = x[i + k/2] * θ;
                x[i]       = a + b;
                x[i + k/2] = a - b;
                θ *= dθ;
            }
        }
    }
}
