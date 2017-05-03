#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10000; 
vector <int> adja[MAXN]; 
int gcnt, top, timeStamp, dfn[MAXN], low[MAXN], depth[MAXN]; 
pair<int, int> stk[MAXN],ans[MAXN]; 
set <int> group[MAXN]; 
bool cut[MAXN]; 
void BCC(int now, int nextv){ 
    int sf, st; 
    group[gcnt].clear(); 
    do{ 
        sf = stk[top-1].first, st = stk[top-1].second; 
        group[gcnt].insert(sf); 
        group[gcnt].insert(st); 
        --top; 
    }while(sf != now || st != nextv); 
    ++gcnt; 
} 
void tarjan(int now, int parent, int d){ 
    int child = 0; 
    dfn[now] = low[now] = ++timeStamp, depth[now] = d; 
    for(int i = 0; i < adja[now].size(); i++){ 
        int nextv = adja[now][i]; 
        if(nextv == parent) continue; 
        if(dfn[nextv] == 0){ 
            stk[top++] = make_pair(now, nextv); 
            tarjan(nextv, now, d+1); 
            low[now] = min(low[now], low[nextv]); 
            ++child; 
            if( (parent != -1 && low[nextv] >= dfn[now]) || (parent == -1 && child >= 2)){ 
                cut[now] = true; 
                if(parent != -1) BCC(now, nextv); 
            } 
            if(parent == -1) BCC(now, nextv); 
        } 
        else if(depth[nextv] < depth[now]-1){ 
            stk[top++] = make_pair(now, nextv); 
            low[now] = min(low[now], dfn[nextv]); 
        } 
    } 
} 
int main(){ 
    int n,m,x,y,cnt=0; 
    while(~scanf("%d",&n)){ 
        cnt=timeStamp=top=gcnt=0; 
        memset(cut, 0, sizeof(cut)); 
        memset(dfn, 0, sizeof(dfn)); 
        for(int i=0;i<n;i++)adja[i].clear(); 
        for(int i=0;i<n;i++){ 
            scanf("%d ",&x); 
            scanf("(%d)",&m); 
            while(m--){ 
                scanf("%d",&y); 
                adja[x].push_back(y); 
            } 
        } 
        for(int i=0;i<n;i++) 
            if(dfn[i]==0)tarjan(i, -1, 1); 
        for(int i=0;i<gcnt;i++){ 
            if(group[i].size()==2){ 
                //critical links
            } 
        } 
    } 
} 
