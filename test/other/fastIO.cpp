#include "../util.h"
#include <other/fastIO.cpp>

int main() {
	if (freopen("other/fastIO.in", "r", stdin) == nullptr) cerr << "fastIO.in not found" << FAIL;
	vector<int> got(5);
	vector<int> expected = {4, 7, 3, 6, 9};
	for (int& x : got) fastscan(x);
	if (got != expected) cerr << "failed fastscan" << FAIL;

	if (freopen("other/fastIO.out", "w", stdout) == nullptr) cerr << "fastIO.out not writebale" << FAIL;
	fastprint(0);
	putchar('\n');
	fastprint(-1);
	putchar(' ');
	fastprint(-8321648);
	putchar(' ');
	fastprint(1);
	putchar(' ');
	fastprint(42387);
	putchar('\n');
	fclose(stdout);

	stringstream buffer;
	{
		ifstream tmp("other/fastIO.out");
		buffer << tmp.rdbuf();
	}
	if (buffer.str() != "0\n-1 -8321648 1 42387\n") cerr << "failed fastprint" << FAIL;
	cerr << "done" << endl;
}

