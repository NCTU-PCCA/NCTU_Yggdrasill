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
inline point enc(const point& a, const point& b, const point& c) {
	vector<point> tmp;
	tmp.clear();tmp.push_back(a);tmp.push_back(b);tmp.push_back(c);
	point O = tmp[0];
	double r = 0;
	Fl(i, 1, 3) if (dq(O, tmp[i]) - r > eps) {
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