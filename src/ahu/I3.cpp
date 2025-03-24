#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#define REMOVE_ME
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
#define int long long

int V, minLength, NiXuHe_prefix, cnt[27], cntPrefixChar[27];

int getMinLength(int l)
{
    int fullround = l / 26;
    int remain    = l % 26;  // 有round+1个数的组数
    int ans = ((l - (fullround + 1)) * (fullround + 1) * remain + ((26 - remain) * fullround) * (l - fullround)) / 2;
    return ans;
}

// 从前往后枚举，如何知道当前状态是否合法。。。
// 前缀已知，后缀未知
// 后缀对位置是否敏感。。。不敏感，即332211。。。
//

bool check(int x, int lengthUndo)
{
    vector<int> cntSuffixChar(27);
    int         totalNi_Done = 0, suffixMaxNi = 0;
    for (int j = 26; j >= x + 1; j--) {
        totalNi_Done += cntPrefixChar[j];
    }
    totalNi_Done += NiXuHe_prefix;

    cntPrefixChar[x]++;

    for (int i = 1; i <= lengthUndo; i++) {
        int maxNi = -1, place = 0, num = 0;
        for (int j = 26; j >= 1; j--) {
            if (i - 1 - cntSuffixChar[j] + num > maxNi) {
                maxNi = i - 1 - cntSuffixChar[j] + num;
                place = j;
            }
            num += cntPrefixChar[j];
        }
        suffixMaxNi += maxNi;
        cntSuffixChar[place]++;
    }
    if (totalNi_Done + suffixMaxNi >= V) {
        NiXuHe_prefix = totalNi_Done;
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
    string ans = "";
    cin >> V;
    for (int i = 1;; i++) {
        if (getMinLength(i) >= V) {
            minLength = i;
            break;
        }
    }
    for (int i = 1; i <= minLength; i++) {
        for (int j = 1; j <= 26; j++) {
            if (check(j, minLength - i)) {
                ans += (char)(j + 'a' - 1);
                break;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}