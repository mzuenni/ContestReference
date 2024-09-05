/rope<int> v;/ {
	print "void test() {"
	print "ll num = 5;"
	print "ll start = 2;"
	print "ll length = 4;"
	print "ll offset = 3;"
}
/v.push_back(num);/ {
	print "v.push_back(0);"
	print "v.push_back(1);"
	print "v.push_back(2);"
	print "v.push_back(3);"
	print "v.push_back(4);"
}
/rope<int> sub/ {
	print "v.push_back(6);"
	print "v.push_back(7);"	
}
/for\(auto it/ {
	print "vector<int> got, expected = {0,1,6,2,3,4,5,7};"
}
END {
	print "	got.push_back(*it)"
	print "if (got != expected) cerr << \"error\" << endl;"
	print "}"
}
{ print }
