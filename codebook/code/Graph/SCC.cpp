#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#define N 300002
using namespace std;
vector<int>go[N],back[N],tree[N];
int hu[N],ST[N],st=0,scc[N],scCo[N],scmx[N];
bool wed[N];
int DFS_go(int now){
    //cout<<now<<" DFS ";
    wed[now]=true;
    for(int i=0;i<go[now].size();i++){
        if(!wed[go[now][i]])
            DFS_go(go[now][i]);
    }
    ST[st++]=now;
    return 0;
}
int DFS_back(int now,int id){
    wed[now]=true;
    scc[now]=id;
    int sum=1;
    if(now==0)sum=0;
    for(int i=0;i<back[now].size();i++){
        if(!wed[back[now][i]])
            sum+=DFS_back(back[now][i],id);
    }
    return sum;
}
int DFS_tree(int now)
{
    if(scmx[now]!=0)return scmx[now];
    int mx=0,tmp;
    for(int i=0;i<tree[now].size();i++){
        tmp=DFS_tree(tree[now][i]);
        mx=(mx>tmp)? mx:tmp;
    }
    scmx[now]=mx+scCo[now];
    return mx+scCo[now];
}
int main(int argc,char *argv[])
{
    ios_base::sync_with_stdio(false);
    int n,k;
    char c;
    cin>>n>>k>>hu[1];
    go[0].push_back(1);
    back[1].push_back(0);
    for(int i=2;i<=n;i++){
        cin>>hu[i];
        if(hu[i]>=hu[i-1]){
            go[i].push_back(i-1);
            back[i-1].push_back(i);
        }
        if(hu[i-1]>=hu[i]){
            go[i-1].push_back(i);
            back[i].push_back(i-1);
        }
        go[0].push_back(i);
        back[i].push_back(0);
    }
    for(int i=1;i<=n;i++){
        cin>>c;
        if(c=='T'){
            go[i].push_back(0);
            back[0].push_back(i);
        }
    }
    for(int i=0;i<=n;i++)
        if(!wed[i])DFS_go(i);
    //cout<<endl;
    fill((bool*)wed,(bool*)wed+N,false);
    int tsc=0;
    // for(int i=0;i<st;i++)cout<<ST[i]<<" HH ";
    // cout<<endl;
    while(st!=0)
        if(!wed[ST[--st]]){
            scCo[tsc]=DFS_back(ST[st],tsc);
            tsc++;
        }
    // for(int i=0;i<N;i++)
    //     while(!back[i].empty())back[i].pop_back();
    for(int i=0;i<=n;i++)
        for(int j=0;j<go[i].size();j++){
            if(scc[i]!=scc[go[i][j]]){
                tree[scc[i]].push_back(scc[go[i][j]]);
            }
        }
    // for(int i=0;i<=n;i++)cout<<scc[i]<<" BB ";
    // cout<<endl;
    // for(int i=0;i<tsc;i++)cout<<scCo[i]<<" GG ";
    cout<<DFS_tree(scc[k])<<endl;
    //system("pause");
    return 0;
}