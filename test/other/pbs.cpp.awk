BEGIN { print "vector<int> pbs(int Q, int MAX_OPERATIONS) {" }
{ 
    sub(/\/\* requirement already fulfilled \*\//, "test(i)")
    sub(/\/\/ simulation step/, "do_step(step);")
    sub(/\/\/ reset simulation/, "reset();")
}
{ print }
END { print "return high; }" }
