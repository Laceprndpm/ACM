#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 首先，如果原先字符串是o，那么周围两个必然可以填充.，随后我就获得了一个以.为开头或结尾的可能为奇可能为偶的子段，如果为偶则只计数，如果为奇，那么就要看看是不是全部都要最大化
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == '?') {
            if ((i && s[i - 1] == 'o') || (i + 1 < n && s[i + 1] == 'o')) {
                s[i] = '.';
            }
        }
    }
    int         cnt = 0;
    vector<int> need;
    for (int i = 0; i < n; i++) {
        if (s[i] == '?') {
            int j = i;
            while (j < n && s[j] == '?') {
                j++;
            }
            if ((j - i) % 2) {
                need.push_back(i);
            }
            cnt += (j - i + 1) / 2;
            i = j - 1;
            continue;
        }
        if (s[i] == 'o') {
            cnt++;
        }
    }
    if (cnt == k) {
        for (int i : need) {
            for (int j = i, cnt = 0; j < n; j++, cnt++) {
                if (s[j] != '?') break;
                s[j] = "o."[cnt % 2];
            }
        }
    }
    int onum = count(s.begin(), s.end(), 'o');
    if (onum == k) {
        for (char& c : s) {
            if (c == '?') c = '.';
        }
    }
    cout << s << '\n';
    return 0;
}