template<typename T>
struct persistent {
	int& time;
	vector<pair<int, T>> data;

	persistent(int& time, T value = {}) 
		: time(time), data(1, {time, value}) {}
	
	T get(int t) {
		return prev(upper_bound(all(data), {t+1, {}}))->second;
	}
	
	int set(T value) {
		time += 2;
		data.push_back({time, value});
		return time;
	}
};
