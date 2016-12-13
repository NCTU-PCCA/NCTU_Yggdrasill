int X,Y ;
int adj[510][510],lx[510], ly[510],mx[510], my[510];
bool vx[510], vy[510];
bool DFS(int x){
    vx[x] = true;
    for (int y=0; y<Y; ++y)
        if (!vy[y])
            if (lx[x] + ly[y] == adj[x][y]){
                vy[y] = true;
                if (my[y] == -1 || DFS(my[y])){
                    mx[x] = y; my[y] = x;
                    return true;
                }
            }
    return false;
}
int Hungarian(){
    memset(ly, 0, sizeof(ly));
    for (int x=0; x<X; ++x)
        for (int y=0; y<Y; ++y)
            if (adj[x][y] != 1e9)
                lx[x] = max(lx[x], adj[x][y]);
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
    for (int x=0; x<X; ++x)
        while (true){
            memset(vx, false, sizeof(vx));
            memset(vy, false, sizeof(vy));
            if (DFS(x)) break;
            int d = 1e9;
            for (int xx=0; xx<X; ++xx) if (vx[xx])
                for (int y=0; y<Y; ++y) if (!vy[y])
                    if (adj[xx][y] != 1e9)
                        d = min(d, lx[xx] + ly[y] - adj[xx][y]);
            if (d == 1e9) return -1e9;
            for (int xx=0; xx<X; ++xx)
                if (vx[xx])
                    lx[xx] -= d;
            for (int y=0; y<Y; ++y)
                if (vy[y])
                    ly[y] += d;
        }
    int weight = 0;
    for (int x=0; x<X; ++x)
        weight += adj[x][mx[x]];
    return weight;
}
int main()
{
    int ans;
    while(~scanf("%d",&X)){
        Y=X;
        for(int q=0;q<X;++q)
            for(int w=0;w<X;++w)
                scanf("%d",&adj[q][w]);
        ans=Hungarian();
        printf("%d",lx[0]);
        for(int q=1;q<X;++q)
            printf(" %d",lx[q]);
        printf("\n%d",ly[0]);
        for(int q=1;q<X;++q)
            printf(" %d",ly[q]);
        printf("\n%d\n",ans);
    }
    return 0;
}