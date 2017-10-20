#define F(n) Fi(i,n)
#define Fi(i,n) Fl(i,0,n)
#define Fl(i,l,n) for(int i=(l);i<(int)(n);++i)
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/priority_queue.hpp>
using namespace std;
// using namespace __gnu_pbds;
typedef long long ll;
struct point {
	point(ll x_ = 0, ll y_ = 0): x(x_), y(y_) {}	ll x, y;
	inline bool operator<(const point &e_) const {
		return (x != e_.x ? x < e_.x : y < e_.y);
	}
	inline friend istream& operator>>(istream &is_, point& e_) {
		is_ >> e_.x >> e_.y;
		return is_;
	}
};
int k;
priority_queue<ll> PQ;
inline ll dist2(const point &e1, const point &e2) {
	ll res = (e1.x-e2.x)*(e1.x-e2.x)+(e1.y-e2.y)*(e1.y-e2.y);
	PQ.push(res);
	if (PQ.size() > k) {
		PQ.pop();
	}
	return res;
}
#define N 500005
point p[N];
queue<point> Q;
ll closet_point(int l, int m, int r, ll delta2) {
	ll xmid = p[m-1].x;
	while (!Q.empty()) {
		Q.pop();
	}
	for (int i = l, j = m ; i < m ; ++i) {
		if ((p[i].x-xmid)*(p[i].x-xmid) >= delta2) {
			continue;
		}
		while (j < r && p[j].y < p[i].y && (p[j].y-p[i].y)*(p[j].y-p[i].y) < delta2) {
			if ((p[j].x-xmid)*(p[j].x-xmid) < delta2) {
				Q.push(p[j]);
			}
			++j;
		}
		while (!Q.empty() && Q.front().y < p[i].y && (Q.front().y-p[i].y)*(Q.front().y-p[i].y) > delta2) {
			Q.pop();
		}
		while (!Q.empty()) {
			delta2 = min(delta2, dist2(p[i], Q.front()));
			Q.pop();
		}
	}
	return delta2;
}
ll find_distance(int l, int r) {
	if (r - l <= 3000) {
		ll ans = 0x3f3f3f3f3f3f3f3f;
		for (int i = l ; i < r ; ++i)
			for (int j = i+1 ; j < r ; ++j)
				ans = min(ans, dist2(p[i], p[j]));
		return ans;
	}
	int m = (l+r)/2;
	ll delta2 = min(find_distance(l, m), find_distance(m, r));
	return min(delta2, closet_point(l, m, r, delta2));
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n >> k;
	F(n) cin >> p[i];
	sort(p, p+n);
	find_distance(0, n);
	cout << PQ.top() << '\n';
}