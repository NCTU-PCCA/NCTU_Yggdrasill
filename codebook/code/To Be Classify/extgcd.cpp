long long extgcd(long long a,long long b,long long &x,long long &y){ 
    long long d=a; 
    if(b!=0){ 
        d=extgcd(b,a%b,y,x); 
        y-=(a/b)*x; 
    } 
    else x=1,y=0; 
    return d; 
} 
int main(){ 
    int T; 
    long long a,b,m,GCD,x,y; 
    while(~scanf("%d",&T)) 
        while(T--){ 
            scanf("%lld%lld%lld",&m,&a,&b); 
            GCD=extgcd(a,m,x,y); 
            if(GCD!=1)printf("No inverse, gcd(a,m)=%lld\n",GCD); 
            else{ 
                b=((-b*x)%m+m)%m; 
                printf("%lld %lld\n",(x%m+m)%m,b); 
            } 
        } 
} 
