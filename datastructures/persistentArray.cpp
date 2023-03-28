template<typename T>
struct persistentArray {
	int time;
	vector<persistent<T>> data;
	vector<pair<int, int>> mods;

	persistentArray(int n, T value = {}) 
		: time(0), data(n, {time, value}) {}

	T get(int p, int t) {return data[p].get(t);}

	int set(int p, T value) {
		mods.push_back({p, time});
		return data[p].set(value);
	}

	void reset(int t) {
		while (!mods.empty() && mods.back().second > t) {
			data[mods.back().first].data.pop_back();
			mods.pop_back();
		}
		time = t;
	}
};
