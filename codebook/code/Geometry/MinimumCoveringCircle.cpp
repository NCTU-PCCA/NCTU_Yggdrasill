#define F(n) Fi(i,n)
#define Fi(i,n) Fl(i,0,n)
#define Fl(i,l,n) for(int i=(l);i<(int)(n);++i)
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
#define x first
#define y second
typedef pair<double, double> point;
inline double dq(const point& p1, const point& p2) {
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
inline point oc(const point& pa, const point& pb, const point& pc) {
	double a, b, c, d, e, f, delta, dx, dy;
	// ax + by = c
	// dx + ey = f
	a = pa.x - pb.x;
	b = pa.y - pb.y;
	c = a*(pa.x+pb.x)/2 + b*(pa.y+pb.y)/2;
	d = pa.x - pc.x;
	e = pa.y - pc.y;
	f = d*(pa.x+pc.x)/2 + e*(pa.y+pc.y)/2;
	delta = a*e-b*d;
	dx = c*e-f*b;
	dy = a*f-d*c;
	return point(dx/delta, dy/delta);
}
inline point enc(const vector<point>& tmp) {
	random_shuffle(tmp.begin(), tmp.end());
	point O = tmp[0];
	double r = 0;
	Fl(i, 1, tmp.size()) if (dq(O, tmp[i]) - r > eps) {
		O = tmp[i], r = 0;
		Fi(j, i) if (dq(O, tmp[j]) - r > eps) {
			O = point((tmp[i].x+tmp[j].x)/2, (tmp[i].y+tmp[j].y)/2);
			r = dq(O, tmp[j]);
			Fi(k, j) if (dq(O, tmp[k]) - r > eps)
				O = oc(tmp[i], tmp[j], tmp[k]), r = dq(O, tmp[k]);
		}
	}
	return O;
}
int n;
vector<point> v;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	while (cin >> n) {
		if (!n) break;
		v.clear();
		F(n) {
			point tp;
			cin >> tp.x >> tp.y;
			v.push_back(tp);
		}
		point ct = enc(v);
		cout << setprecision(2) << fixed << ct.x << ' ' << ct.y << ' ' << dq(ct, v[0]) << '\n';
	}
}