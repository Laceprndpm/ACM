#define REMOVE_ME
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
    int n;
    cin >> n;
    string binaryS;
    cin >> binaryS;
    int firstOne  = n - 1;
    int firstZero = n - 1;
    // 随机数据，是不是代表第一个前导1后很快就有一个0了？？
    for (int i = 0; i < n; i++) {
        if (binaryS[i] == '1') {
            firstOne = i;
            break;
        }
    }

    for (int i = firstOne; i < n; i++) {
        if (binaryS[i] == '0') {
            firstZero = i;
            break;
        }
    }
    int orLength = n - firstZero;
    // 1110010
    // first1 = 0, first0 = 3
    // 0-6 OR
    // 0-3, 1-4, 2-5, 3-6
    // 如何挑选最大的？第一个|为0的位置最靠后的，精度不够
    int maxOr0       = 0;
    int maxOr02      = 0;
    int maxOrpointer = 0;
    for (int l = firstOne; l < n; l++) {
        if (l + orLength - 1 >= n) {
            break;
        }
        bool findF = false;
        int  cur0  = n;
        int  cur1  = n;
        for (int place = 0; place < n; place++) {
            int pointer1 = place + firstZero;
            int pointer2 = place + l;
            if (!(binaryS[pointer1] - '0') && !(binaryS[pointer2] - '0')) {
                if (!findF) {
                    cur0  = place;
                    findF = true;
                } else {
                    cur1 = place;
                    break;
                }
            }
        }
        if (cur0 > maxOr0) {
            maxOr0       = cur0;
            maxOr02      = cur1;
            maxOrpointer = l;
        } else if (cur0 == maxOr0 && maxOr02 < cur1) {
            maxOr02      = cur1;
            maxOrpointer = l;
        }
    }
    int i;
    for (i = firstOne; i < n - orLength; i++) {
        cout << binaryS[i];
    }
    for (int j = 0; i + j < n; j++) {
        cout << ((binaryS[i + j] - '0') || (binaryS[j + maxOrpointer] - '0') ? 1 : 0);
    }
    return 0;
}