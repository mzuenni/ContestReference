template<int N>
struct Table {
	int data[N];
	constexpr Table() : data {} {
		for (int i = 0; i < N; i++) data[i] = i;
}};
constexpr Table<100'000> precalculated;
