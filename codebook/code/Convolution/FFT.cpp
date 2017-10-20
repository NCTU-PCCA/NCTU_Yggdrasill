#include <cstdio>
#include <cstring>
#include <cmath>
const double PI=acos(-1.0);
typedef  struct {
    double  real;
    double  im;
} COMPLEX;
COMPLEX X[66000],Y[66000],A[66000];
COMPLEX EE(COMPLEX a,COMPLEX b)
{
    COMPLEX c;
    c.real=a.real*b.real-a.im*b.im;
    c.im=a.real*b.im+a.im*b.real;
    return c;
}
/* 1 FFT , -1 IFFT */
void fft(COMPLEX x[],int nfft,int isign)
{
    int i,j=0,k;
    COMPLEX t;
    for(i=1, j = nfft / 2;i<nfft-1;i++)
    {
        if(i<j)
        {
            t=x[j];
            x[j]=x[i];
            x[i]=t;
        }
        k=nfft/2;
        while(k<=j)
        {
            j-=k;
            k/=2;
        }
        if (j < k)
            j+=k;
    }
    int le,lei,ip;
    COMPLEX u,w, v;
    for(le=2;le<=nfft;le *= 2)
    {
        lei=le/2;
        w.real=cos(2.0*PI*isign/le);
        w.im=sin(2.0*PI*isign/le);
        for(i=0;i<nfft;i+=le)
        {
            u.real=1.0;
            u.im=0.0;
            for(j = i ; j < i + lei ; ++j)
            {
                ip=j+lei;
                v = x[j];
                t=EE(u, x[ip]);
                x[j].real=v.real+t.real;
                x[j].im=v.im+t.im;
                x[ip].real=v.real-t.real;
                x[ip].im=v.im-t.im;
                u=EE(u,w);
            }
        }
    }
}
void FFT(COMPLEX x[], int nfft)
{
    fft(x,nfft,1);   
}
void IFFT(COMPLEX x[],int nfft)
{
    int i;
    fft(x,nfft,-1);
    
    for(i=0;i<nfft;i++)
    {
        x[i].real /= nfft;
        x[i].im /= nfft;
    }
}
int main() {
    int t_num;
    int i,ii,iii;
    int p_num;
    int Nx;
    int NFFT;
    int temp;
    scanf("%d",&t_num);
    for(i=0;i<t_num;i++){
        scanf("%d",&p_num);
        Nx=p_num*2-1;
        NFFT = 2 << (int)log2(Nx);
        for(ii=0;ii<p_num;++ii){
            scanf("%d",&temp);
            X[ii].real=(double)temp;
            X[ii].im=0.0;
        }
        for(iii=0;iii<p_num;++iii){
            
            scanf("%d",&temp);
            Y[iii].real=(double)temp;
            Y[iii].im=0.0;
        }
        for(ii=p_num;ii<NFFT;ii++)
        {
            X[ii].real=0.0;
            X[ii].im=0.0;
            Y[ii].real=0.0;
            Y[ii].im=0.0;
        }
        FFT(X,NFFT);
        FFT(Y,NFFT);
        for(ii=0;ii<NFFT;ii++){
            A[ii] = EE(X[ii], Y[ii]);
        }
        IFFT(A,NFFT);
        for(ii=0;ii<Nx;ii++){
            printf("%d ", (int)round(A[ii].real));
        }
        printf("\n");
    }
    return 0;
}
