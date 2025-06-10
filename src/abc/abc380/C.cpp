#include <iostream>
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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    string sans;
    int    cnt = 0;
    for (int i = 0; i < n; i++) {
        if (cnt < k - 1) {
            if (s[i] == '1') {
                int j = i;
                while (s[j] == '1') {
                    j++;
                }
                i = j - 1;
                cnt++;
            } else {
                int j = i;
                while (s[j] == '0') {
                    j++;
                }
                i = j - 1;
            }
        } else {
            sans  = string(s.begin(), s.begin() + i);
            int j = i;
            while (s[j] == '0') {
                j++;
            }
            string temp(s.begin() + i, s.begin() + j);
            i = j;
            while (j < n && s[j] == '1') {
                j++;
            }
            string temp2(s.begin() + i, s.begin() + j);
            sans += temp2;
            sans += temp;
            sans += string(s.begin() + j, s.end());
            break;
        }
    }
    cout << sans << '\n';
    return 0;
}