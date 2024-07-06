vector<ll> add, mul;

void update(int l, int r, ll val) {
	for (int tl = l + 1; tl < sz(add); tl += tl & -tl)
		add[tl] += val, mul[tl] -= val * l;
	for (int tr = r + 1; tr < sz(add); tr += tr & -tr)
		add[tr] -= val, mul[tr] += val * r;
}

void init(vector<ll>& v) {
	mul.assign(sz(v) + 1,0);
	add.assign(sz(v) + 1,0);
	for(int i = 0; i < sz(v); i++) update(i, i + 1, v[i]);
}

ll prefix_sum (int i) {
	ll res = 0; i++;
	for (int ti = i; ti > 0; ti -= ti & -ti)
		res += add[ti] * i + mul[ti];
	return res;
}
