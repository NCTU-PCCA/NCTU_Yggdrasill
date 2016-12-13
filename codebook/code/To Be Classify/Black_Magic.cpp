#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
const int MAXN = 50000 + 10;
crope ro,l[MAXN],tmp;
char str[200+10];
main(){
    int T,op,p,c,d=0,cnt=1,v;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&op);
        if(op==1){
            scanf("%d%s",&p,str);
            p-=d;
            ro.insert(p,str);
            l[cnt++]=ro;
        }
        else if(op==2){
            scanf("%d%d",&p,&c);
            p-=d,c-=d;
            ro.erase(p-1,c);
            l[cnt++]=ro;
        }
        else{
            scanf("%d%d%d",&v,&p,&c);
            p-=d,v-=d,c-=d;
            tmp=l[v].substr(p-1,c);
            d+=count(tmp.begin(),tmp.end(),'c');
            cout<<tmp<<endl;
        }
    }
}
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
__gnu_pbds::priority_queue<int> h1,h2;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;

int main(){
    printf("heap:\n");
    for(int i=1;i<=10;i+=2)h1.push(i);
    for(int i=2;i<=10;i+=2)h2.push(i);

    printf("%d\n",h1.top());
    printf("%d\n",h2.top());
    h1.join(h2);
    printf("%d\n",h1.size());
    printf("%d\n",h2.size());
    printf("%d\n",h1.top());

    printf("\ntree:\n");
    set_t s;
    for(int i=0;i<5;i++)s.insert(10*i);
    printf("%d\n",*s.find_by_order(0));
    printf("%d\n",*s.find_by_order(3));
    printf("%d\n",s.find_by_order(5)==s.end());

    printf("%d\n",s.order_of_key(0));
    printf("%d\n",s.order_of_key(30));
    printf("%d\n",s.order_of_key(35));
    printf("%d\n",s.order_of_key(100));
    return 0;
}
