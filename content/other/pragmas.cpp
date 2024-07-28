#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,"
									 "popcnt,abm,mmx,avx,tune=native")
#pragma GCC target("fpmath=sse,sse2")	// no excess precision
#pragma GCC target("fpmath=387") 			// force excess precision
