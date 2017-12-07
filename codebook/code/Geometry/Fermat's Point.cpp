#define F(n) Fi(i,n)
#define Fi(i,n) Fl(i,0,n)
#define Fl(i,l,n) for(int i=(l);i<(int)(n);++i)
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/priority_queue.hpp>
using namespace std;
// using namespace __gnu_pbds;
const double pi = acos(-1), eps = 1e-9;
const double st = sin(pi/3), ct = cos(pi/3);
struct point {
	point(double x_ = 0, double y_ = 0): x(x_), y(y_) {}
	double x, y;
	inline friend istream& operator>>(istream &is, point &p) {
		is >> p.x >> p.y;
		return is;
	}
	inline friend ostream& operator<<(ostream &os, const point &p) {
		os << p.x << ' ' << p.y;
		return os;
	}
};
struct line {
	line(double a_ = 0, double b_ = 0, double c_ = 0): a(a_), b(b_), c(c_) {}
	double a, b, c;
	inline double calc(point p) {
		return a*p.x+b*p.y;
	}
};
inline double calc(double a, double b, point p) {
	return a*p.x+b*p.y;
}
inline double dist2(point a, point b) {
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
inline point rot(point O, point p) {
	p.x -= O.x, p.y -= O.y;
	return point(O.x+p.x*ct-p.y*st, O.y+p.x*st+p.y*ct);
}
inline line cln(point a, point b) {
	return line(a.y-b.y, b.x-a.x, calc(a.y-b.y, b.x-a.x, a));
}
inline point ntse(line f, line g) {
	double det = f.a*g.b-g.a*f.b, dx = f.c*g.b-g.c*f.b, dy = f.a*g.c-g.a*f.c;
	return point(dx/det, dy/det);
}
inline point fema(point a, point b, point c) {
	double la = dist2(b, c), lb = dist2(a, c), lc = dist2(a, b);
	double sa = sqrt(la), sb = sqrt(lb), sc = sqrt(lc);
	if ((lb+lc-la)/(2.0*sb*sc) < -0.5 + eps)
		return a;
	if ((la+lc-lb)/(2.0*sa*sc) < -0.5 + eps)
		return b;
	if ((la+lb-lc)/(2.0*sa*sb) < -0.5 + eps)
		return c;
	point t1 = rot(a, b), t2 = rot(b, a);
	if (dist2(c, t1) < dist2(c, t2)) swap(t1, t2);
	point s1 = rot(b, c), s2 = rot(c, b);
	if (dist2(a, s1) < dist2(a, s2)) swap(s1, s2);
	return ntse(cln(c, t1), cln(a, s1));
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	point a, b, c;
	cin >> a >> b >> c;
	cout << setprecision(10) << fixed << fema(a, b, c) << '\n';
}