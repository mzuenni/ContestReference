//https://gcc.gnu.org/bugzilla/show_bug.cgi?id=68203
struct A {
	pair<int, int> values[1000000];
};
