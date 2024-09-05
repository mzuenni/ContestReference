/for \(int subset/ {
	print "template<typename F>"
	print "void subsets(int bitmask, F&& f) {"
}
/\/\/ Nächste Permutation/ {
	print "	{f(subset);}"
	print "}"
}
{ print }
