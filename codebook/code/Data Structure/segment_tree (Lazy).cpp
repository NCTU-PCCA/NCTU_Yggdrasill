/* 區間求和 */
void push_up(int rt) {
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}

/* 區間求最大值 */
void push_up(int rt) {
    tree[rt] = max(tree[rt << 1], tree[rt << 1 | 1]);
}

void push_down(int rt, int len) {
    tree[rt << 1] += lazy[rt] * (len - (len >> 1));
    lazy[rt << 1] += lazy[rt];
    tree[rt << 1 | 1] += lazy[rt] * (len >> 1);
    lazy[rt << 1 | 1] += lazy[rt];
    lazy[rt] = 0;
}

#define lchild rt << 1, l, m
#define rchild rt << 1 | 1, m + 1, r
void build(int rt = 1, int l = 1, int r = N) {
    if (l == r) { std::cin >> tree[rt]; return; }
    int m = (l + r) >> 1;
    build(lchild); build(rchild);
    push_up(rt);
}

#define lchild rt << 1, l, m
#define rchild rt << 1 | 1, m + 1, r
void update(int L, int R, int delta, int rt = 1, int l = 1, int r = N) {
    if (L <= l && r <= R) {
        tree[rt] += delta * (r - l + 1);
        lazy[rt] += delta;
        return;
    }
    if (lazy[rt]) push_down(rt, r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, delta, lchild);
    if (R > m)  update(L, R, delta, rchild);
    push_up(rt);
}

#define lchild rt << 1, l, m
#define rchild rt << 1 | 1, m + 1, r
int query(int L, int R, int rt = 1, int l = 1, int r = N) {
    if (L <= l && r <= R) return tree[rt];
    if (lazy[rt]) push_down(rt, r - l + 1);
    int m = (l + r) >> 1, ret = 0;
    if (L <= m) ret += query(L, R, lchild);
    if (R > m)  ret += query(L, R, rchild);
    return ret;
}