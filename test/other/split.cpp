#include "../util.h"
#include <other/split.cpp>

vector<string> split2(string_view s, string_view delim) {
	vector<string> res;
	while (!s.empty()) {
		auto end = s.find_first_of(delim);
		if (end != 0) res.emplace_back(s.substr(0, end));
		if (end == string_view::npos) break;
		s.remove_prefix(end + 1);
	}
	return res;
}

int main() {
	auto in = "+" + Random::string(100, "abcdef+-*") + "-";
	
	auto expected = split2(in, "+-*");
	auto got = split(in, "+-*");

	if (got != expected) cerr << "error" << FAIL;
	cerr << "done" << endl;
}

