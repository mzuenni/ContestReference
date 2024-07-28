// base and base_digits must be consistent
constexpr ll base = 1'000'000;
constexpr ll base_digits = 6;
struct bigint {
	using vll = vector<ll>;
	vll a; ll sign;

	bigint() : sign(1) {}

	bigint(ll v) {*this = v;}

	bigint(const string &s) {read(s);}

	void operator=(ll v) {
		sign = 1;
		if (v < 0) sign = -1, v = -v;
		a.clear();
		for (; v > 0; v = v / base)
			a.push_back(v % base);
	}

	bigint operator+(const bigint& v) const {
		if (sign == v.sign) {
			bigint res = v;
			for (ll i = 0, carry = 0; i < max(sz(a), sz(v.a)) || carry; ++i) {
				if (i == sz(res.a))
					res.a.push_back(0);
				res.a[i] += carry + (i < sz(a) ? a[i] : 0);
				carry = res.a[i] >= base;
				if (carry)
					res.a[i] -= base;
			}
			return res;
		}
		return *this - (-v);
	}

	bigint operator-(const bigint& v) const {
		if (sign == v.sign) {
			if (abs() >= v.abs()) {
				bigint res = *this;
				for (ll i = 0, carry = 0; i < sz(v.a) || carry; ++i) {
					res.a[i] -= carry + (i < sz(v.a) ? v.a[i] : 0);
					carry = res.a[i] < 0;
					if (carry) res.a[i] += base;
				}
				res.trim();
				return res;
			}
			return -(v - *this);
		}
		return *this + (-v);
	}

	void operator*=(ll v) {
		if (v < 0) sign = -sign, v = -v;
		for (ll i = 0, carry = 0; i < sz(a) || carry; ++i) {
			if (i == sz(a)) a.push_back(0);
			ll cur = a[i] * v + carry;
			carry = cur / base;
			a[i] = cur % base;
		}
		trim();
	}

	bigint operator*(ll v) const {
		bigint res = *this;
		res *= v;
		return res;
	}

	friend pair<bigint, bigint> divmod(const bigint& a1, const bigint& b1) {
		ll norm = base / (b1.a.back() + 1);
		bigint a = a1.abs() * norm;
		bigint b = b1.abs() * norm;
		bigint q, r;
		q.a.resize(sz(a.a));
		for (ll i = sz(a.a) - 1; i >= 0; i--) {
			r *= base;
			r += a.a[i];
			ll s1 = sz(r.a) <= sz(b.a) ? 0 : r.a[sz(b.a)];
			ll s2 = sz(r.a) <= sz(b.a) - 1 ? 0 : r.a[sz(b.a) - 1];
			ll d = (base * s1 + s2) / b.a.back();
			r -= b * d;
			while (r < 0) r += b, --d;
			q.a[i] = d;
		}
		q.sign = a1.sign * b1.sign;
		r.sign = a1.sign;
		q.trim();
		r.trim();
		return make_pair(q, r / norm);
	}

	bigint operator/(const bigint& v) const {
		return divmod(*this, v).first;
	}

	bigint operator%(const bigint& v) const {
		return divmod(*this, v).second;
	}

	void operator/=(ll v) {
		if (v < 0) sign = -sign, v = -v;
		for (ll i = sz(a) - 1, rem = 0; i >= 0; --i) {
			ll cur = a[i] + rem * base;
			a[i] = cur / v;
			rem = cur % v;
		}
		trim();
	}

	bigint operator/(ll v) const {
		bigint res = *this;
		res /= v;
		return res;
	}

	ll operator%(ll v) const {
		if (v < 0) v = -v;
		ll m = 0;
		for (ll i = sz(a) - 1; i >= 0; --i)
			m = (a[i] + m * base) % v;
		return m * sign;
	}

	void operator+=(const bigint& v) {
		*this = *this + v;
	}
	void operator-=(const bigint& v) {
		*this = *this - v;
	}
	void operator*=(const bigint& v) {
		*this = *this * v;
	}
	void operator/=(const bigint& v) {
		*this = *this / v;
	}

	bool operator<(const bigint& v) const {
		if (sign != v.sign) return sign < v.sign;
		if (sz(a) != sz(v.a))
			return sz(a) * sign < sz(v.a) * v.sign;
		for (ll i = sz(a) - 1; i >= 0; i--)
			if (a[i] != v.a[i])
				return a[i] * sign < v.a[i] * sign;
		return false;
	}

	bool operator>(const bigint& v) const {
		return v < *this;
	}
	bool operator<=(const bigint& v) const {
		return !(v < *this);
	}
	bool operator>=(const bigint& v) const {
		return !(*this < v);
	}
	bool operator==(const bigint& v) const {
		return !(*this < v) && !(v < *this);
	}
	bool operator!=(const bigint& v) const {
		return *this < v || v < *this;
	}

	void trim() {
		while (!a.empty() && !a.back()) a.pop_back();
		if (a.empty()) sign = 1;
	}

	bool isZero() const {
		return a.empty() || (sz(a) == 1 && a[0] == 0);
	}

	bigint operator-() const {
		bigint res = *this;
		res.sign = -sign;
		return res;
	}

	bigint abs() const {
		bigint res = *this;
		res.sign *= res.sign;
		return res;
	}

	ll longValue() const {
		ll res = 0;
		for (ll i = sz(a) - 1; i >= 0; i--)
			res = res * base + a[i];
		return res * sign;
	}

	void read(const string& s) {
		sign = 1;
		a.clear();
		ll pos = 0;
		while (pos < sz(s) && (s[pos] == '-' || s[pos] == '+')) {
			if (s[pos] == '-') sign = -sign;
			++pos;
		}
		for (ll i = sz(s) - 1; i >= pos; i -= base_digits) {
			ll x = 0;
			for (ll j = max(pos, i - base_digits + 1); j <= i; j++)
				x = x * 10 + s[j] - '0';
			a.push_back(x);
		}
		trim();
	}

	friend istream& operator>>(istream& stream, bigint& v) {
		string s;
		stream >> s;
		v.read(s);
		return stream;
	}

	friend ostream& operator<<(ostream& stream, const bigint& v) {
		if (v.sign == -1) stream << '-';
		stream << (v.a.empty() ? 0 : v.a.back());
		for (ll i = sz(v.a) - 2; i >= 0; --i)
			stream << setw(base_digits) << setfill('0') << v.a[i];
		return stream;
	}

	static vll karatsubaMultiply(const vll& a, const vll& b) {
		ll n = sz(a);
		vll res(n + n);
		if (n <= 32) {
			for (ll i = 0; i < n; i++)
				for (ll j = 0; j < n; j++)
					res[i + j] += a[i] * b[j];
			return res;
		}
		ll k = n >> 1;
		vll a1(a.begin(), a.begin() + k);
		vll a2(a.begin() + k, a.end());
		vll b1(b.begin(), b.begin() + k);
		vll b2(b.begin() + k, b.end());
		vll a1b1 = karatsubaMultiply(a1, b1);
		vll a2b2 = karatsubaMultiply(a2, b2);
		for (ll i = 0; i < k; i++) a2[i] += a1[i];
		for (ll i = 0; i < k; i++) b2[i] += b1[i];
		vll r = karatsubaMultiply(a2, b2);
		for (ll i = 0; i < sz(a1b1); i++) r[i] -= a1b1[i];
		for (ll i = 0; i < sz(a2b2); i++) r[i] -= a2b2[i];
		for (ll i = 0; i < sz(r); i++) res[i + k] += r[i];
		for (ll i = 0; i < sz(a1b1); i++) res[i] += a1b1[i];
		for (ll i = 0; i < sz(a2b2); i++) res[i + n] += a2b2[i];
		return res;
	}

	bigint operator*(const bigint& v) const {
		vll ta(a.begin(), a.end());
		vll va(v.a.begin(), v.a.end());
		while (sz(ta) < sz(va)) ta.push_back(0);
		while (sz(va) < sz(ta)) va.push_back(0);
		while (sz(ta) & (sz(ta) - 1))
			ta.push_back(0), va.push_back(0);
		vll ra = karatsubaMultiply(ta, va);
		bigint res;
		res.sign = sign * v.sign;
		for (ll i = 0, carry = 0; i < sz(ra); i++) {
			ll cur = ra[i] + carry;
			res.a.push_back(cur % base);
			carry = cur / base;
		}
		res.trim();
		return res;
	}
};
