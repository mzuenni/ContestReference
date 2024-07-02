#include <cfloat>

int main() {
	cout << "Mode: " << FLT_EVAL_METHOD << endl;
	double a = atof("1.2345678");
	double b = a*a;
	cout << b - 1.52415765279683990130 << '\n';
}
