#include <cstdio>
#include <cstring>
#include <iostream>
#define REMOVE_ME
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
int           v;
int           NiXuHe_prefix, cnt[27], cntPrefixChar[27];
int           minLength;

int getMinLength(int len)
{
    return ((len - (len / 26 + 1)) * (len / 26 + 1) * (len % 26) + (26 - len % 26) * (len / 26) * (len - len / 26)) / 2;
}

// 从前往后枚举，如何知道当前状态是否合法。。。
// 前缀已知，后缀未知
// 后缀对位置是否敏感。。。不敏感，即332211。。。
//

bool check(char x, int idx)
{
    int add1 = 0, add2 = 0;
    for (int j = 26; j >= x + 1; j--)
        add1 += cntPrefixChar[j];  // 1~pos-1里边比当前插入字符大的字符数量
    cntPrefixChar[x]++;            // 当前字符数量增加1
    for (int L = 1; L <= idx; L++) {
        int ma = -1, pos = 0, num = 0;
        for (int j = 26; j >= 1; j--) {
            if (L - 1 - cnt[j] + num > ma) {
                ma  = L - 1 - cnt[j] + num;
                pos = j;
            }
            num += cntPrefixChar[j];
        }
        add2 += ma, cnt[pos]++;
    }
    if (NiXuHe_prefix + add1 + add2 >= v) {
        NiXuHe_prefix += add1;
        return true;
    } else {
        cntPrefixChar[x]--;
        return false;
    }
}

signed main(signed argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    cin >> v;
    string ans = "";
    for (int i = 1;; i++) {
        if (getMinLength(i) >= v) {  // 最短要minLength
            minLength = i;
            break;
        }
    }
    for (int i = 1; i <= minLength; i++) {  // 考虑这一位
        for (char j = 'a'; j <= 'z'; j++) {
            if (!check(j, i)) {
                ans += j - (char)1;
                cntPrefixChar[j - 'a' - 1]++;
            } else if (j == 'z') {
                ans += j;
                cntPrefixChar[j - 'a']++;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}