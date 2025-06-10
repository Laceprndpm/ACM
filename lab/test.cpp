#include <functional>
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

int kmp(const string& pattern)
{
    int m = pattern.size();
    if (m == 0) {
        return 0;
    }
    vector<int> next(m);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        next[i] = j;
    }
    for (int i = 0; i < m; i++) {
        cout << next[i] << ' ';
    }
    return -1;
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    string target;
    string pattern;
    cin >> target >> pattern;
    auto searcher = std::boyer_moore_searcher(  // 也有knuth_morris_pratt_searcher
        pattern.begin(), pattern.end());

    for (auto it = search(target.begin(), target.end(), searcher); it != target.end();
         it      = search(it, target.end(), searcher)) {
        cout << it - target.begin() + 1 << '\n';
        it++;
    }
    kmp(pattern);
    return 0;
}