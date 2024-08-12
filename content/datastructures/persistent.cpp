template<typename T>
struct persistent {
	int& time;
	vector<pair<int, T>> data;

	persistent(int& time, T value = {}) 
		: time(time), data(1, {2*time, value}) {}
	
	T get(int t) {
		return prev(upper_bound(all(data),pair{2*t+1, T{}}))->second;
	}
	
	int set(T value) {
		time++;
		data.push_back({2*time, value});
		return time;
	}
};
