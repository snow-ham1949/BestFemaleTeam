bool cmp(pdd a, pdd b){
#define is_neg(k) (sign(k.Y) < 0 || (sign(k.Y) == 0 && sign(k.X) < 0))
	int A = is_neg(a), B = is_neg(b);
	if(A!=B){
		return A<B;
	}
	if(sign(cross(A, B))==0){
		return abs2(a) < abs2(b);
	}
	return sign(cross(a, b)) > 0;
}
void rotatingSweepLine(vector<pii> &ps){
	int n = SZ(ps);
	vector<int> id(n), pos(n);
	vectpr<pii> line(n*(n-1));
	int m = 0;
	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			if(i!=j){
				line[m++] = pii(i, j);
			}
		}
	}
	sort(line.begin(), line.end(), [&](pii a, pii b){return cmp(ps[a.Y] - ps[a.X], ps[b.Y] - ps[b.X]);});
	iota(id.begin(), id.end(), 0);
	sort(id.begin(), id.end(), [&](int a, int b){
		if(ps[a].Y !=ps[b].Y)
			return ps[a].Y < ps[b].Y;
		return ps[a] < ps[b];
	});//initial order, since (1, 0) is the smallest
	for(int i=0; i<n; ++i){
		pos[id[i]] = i;
	}
	for(int i=0; i<m; ++i){
		auto l = line[i];
		//do something
		tie(pos[l.X], pos[l.Y], id[pos[l.X]], id[pos[l.Y]]) = make_tuple(pos[l.Y], pos[l.X], l.Y, l.X);
	}
}
