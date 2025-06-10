#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct coder {
    string             raw;
    int                fen = 0;
    static vector<int> rating;

    coder(string x) : raw(x)
    {

        for (const char& i : x) {
            if (i != '\0') fen += rating[i - 'A'];
        }
    }

    bool operator<(coder& t)
    {
        if (fen != t.fen) return fen > t.fen;
        return raw < t.raw;
    }
};

vector<int> coder::rating;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;
    coder::rating = {a, b, c, d, e};
    vector<coder> cd;
    string        chars = "ABCDE";
    for (int i = 1; i <= 31; i++) {
        string cur;
        for (int j = 0; j < 5; j++) {
            if (i >> j & 1) {
                cur += 'A' + j;
            }
        }
        cd.push_back(coder{cur});
    }
    sort(cd.begin(), cd.end());
    for (auto i : cd) {
        cout << i.raw << '\n';
    }
    return 0;
}