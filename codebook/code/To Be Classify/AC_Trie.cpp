#include<bits/stdc++.h>
using namespace std;
const int MAXS = 1000100, MAXN = 10010, MAXP = 51; 
char str[MAXS], pattern[MAXN][MAXP]; 
struct actrie 
{ 
    actrie *flink, *nxt[26]; //failure link, trie structure 
    int pcnt; 
    actrie() 
    { 
        flink = NULL, pcnt = 0; 
        memset(nxt, 0, sizeof(nxt)); 
    } 
};   
actrie *root, *que[MAXN*MAXP];   
void addPattern(char *P) 
{ 
    actrie *now = root; 
    for(int i = 0; P[i]; i++) 
    { 
        if(now->nxt[ P[i] - 'a' ] == NULL) now->nxt[ P[i] - 'a' ] = new actrie(); 
        now = now->nxt[ P[i] - 'a' ]; 
    } 
      
    ++now->pcnt; 
} 
void build() 
{ 
    int front = 0, rear = 1; 
    que[0] = root; 
    while(front < rear) 
    { 
        actrie *now = que[front], *fnode; 
        for(int i = 0; i < 26; i++) 
            if(now->nxt[i]) 
            { 
                fnode = now->flink; 
                while(fnode && fnode->nxt[i] == NULL) fnode = fnode->flink; 
                  
                if(fnode) now->nxt[i]->flink = fnode->nxt[i]; 
                else now->nxt[i]->flink = root; 
                que[rear++] = now->nxt[i]; 
            } 
        ++front; 
    } 
}   
int match(char * S) 
{ 
    int ret = 0; 
    actrie *now = root; 
    for(int i = 0; S[i]; i++) 
    { 
        while(now && now->nxt[ S[i]-'a' ] == NULL) now = now->flink; 
        if(now) 
        {            
            now = now->nxt[ S[i]-'a' ]; 
            actrie *temp = now; 
            while(temp && temp->pcnt != -1) 
            { 
                ret += temp->pcnt; 
                temp->pcnt = -1; 
                temp = temp->flink; 
            }            
        } 
        else now = root; 
    } 
    return ret; 
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		root = new actrie();
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%s",pattern[i]);
			addPattern(pattern[i]);
		}
		build();
		scanf("%s",str);
		printf("%d\n",match(str));
	}
	return 0;
}
