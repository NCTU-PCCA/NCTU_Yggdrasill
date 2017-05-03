void Zalg(char *s, int *z, int n) {
	z[0]=n;
	for(int L=0, R=0, i=1; i<n; i++) {
		if(i<=R && z[i-L]<=R-i) z[i]=z[i-L];
		else {
			L=i;
			if(i>R) R=i;
			while(R<n && s[R-L]==s[R]) R++;
			z[i]=(R--)-L;
		}
	}
}
