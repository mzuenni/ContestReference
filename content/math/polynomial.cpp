struct poly {
	vector<ll> data;

	poly(int deg = 0) : data(1 + deg) {}
	poly(initializer_list<ll> _data) : data(_data) {}

	int size() const {return sz(data);}

	void trim() {
		for (ll& x : data) x = (x % mod + mod) % mod;
		while (size() > 1 && data.back() == 0) data.pop_back();
	}

	ll& operator[](int x) {return data[x];}
	const ll& operator[](int x) const {return data[x];}

	ll operator()(int x) const {
		ll res = 0;
		for (int i = size() - 1; i >= 0; i--)
			res = (res * x + data[i]) % mod;
		return res % mod;
	}

	poly& operator+=(const poly& o) {
		if (size() < o.size()) data.resize(o.size());
		for (int i = 0; i < o.size(); i++)
			data[i] = (data[i] + o[i]) % mod;
		return *this;
	}

	poly operator*(const poly& o) const {
		poly res(size() + o.size() - 1);
		for (int i = 0; i < size(); i++) {
			for (int j = 0; j < o.size(); j++) {
				res[i + j] += (data[i] * o[j]) % mod;
		}}
		res.trim();
		return res;
	}

	//return p(x+a)
	poly operator<<(ll a) const {
		poly res(size() - 1);
		for (int i = size() - 1; i >= 0; i--) {
			for (int j = size() - i - 1; j >= 1; j--)
				res[j] = (res[j] * a + res[j - 1]) % mod;
			res[0] = (res[0] * a + data[i]) % mod;
		}
		return res;
	}

	pair<poly, poly> divmod(const poly& d) const {
		int i = size() - d.size();
		if (i <= 0) return {{}, *this};
		poly s(i + 1), r = *this;
		ll inv = multInv(d.data.back(), mod);
		for (; i >= 0; i--) {
			s[i] = (r.data.back() * inv) % mod;
			r.data.pop_back();
			for (int j = 0; i + j < r.size(); j++) {
				r[i + j] = (r.data[i + j] - s[i] * d[j]) % mod;
		}}
		s.trim(); r.trim();
		return {s, r};
	}
};
