#include "testlib.h"
#define int long long
#define inf inf.readLong()
#define ouf ouf.readLong()
#define ans ans.readLong()
signed main (signed argc, char**argv) {
	registerTestlibCmd(argc, argv);
	int T = inf;
	for (int i = 1; i <= T; ++i) {
		int x = ouf, y = ans;
		if (x != 0 && x != y) quitf(_wa, "WA on Test %lld", i);
	}
	quitf(_ok, "AC!");
}

