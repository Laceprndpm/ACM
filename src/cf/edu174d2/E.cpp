#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    string stringAB;
    cin >> stringAB;
    int       mutexABcnt = 0;
    list<int> domainAB;
    list<int> domainBA;
    int       l = 0, r = 0;
    for (; r < stringAB.length() - 1; r++) {
        if (stringAB[r] == stringAB[r + 1]) {
            if (stringAB[l] == stringAB[r]) {
                mutexABcnt += (r - l) / 2;
            } else {
                if (stringAB[l] == 'A') {
                    domainAB.emplace_back((r - l + 1) / 2);
                } else {
                    domainBA.emplace_back((r - l + 1) / 2);
                }
            }
            l = r + 1;
        }
    }
    if (stringAB[l] == stringAB[r]) {
        mutexABcnt += (r - l) / 2;
    } else {
        if (stringAB[l] == 'A') {
            domainAB.emplace_back((r - l + 1) / 2);
        } else {
            domainBA.emplace_back((r - l + 1) / 2);
        }
    }
    domainAB.sort();
    domainBA.sort();
    int cntA = 0;
    int cntB = 0;
    for (char i : stringAB) {
        if (i == 'A') {
            cntA++;
        } else {
            cntB++;
        }
    }
    int a, b, ab, ba;
    cin >> a >> b >> ab >> ba;
    i64 ABcontri = 0;
    while (!domainAB.empty() && ab > 0) {
        int& cur = domainAB.front();
        if (ab >= cur) {
            ab -= cur;
            domainAB.pop_front();
            ABcontri += cur;
        } else {
            cur -= ab;
            ABcontri += ab;
            ab = 0;
        }
    }

    while (!domainBA.empty() && ba > 0) {
        int& cur = domainBA.front();
        if (ba >= cur) {
            ba -= cur;
            ABcontri += cur;
            domainBA.pop_front();
        } else {
            cur -= ba;
            ABcontri += ba;
            ba = 0;
        }
    }

    int remain = ab + ba;
    int yolo   = mutexABcnt;
    while (!domainAB.empty()) {
        yolo += domainAB.front() - 1;
        domainAB.pop_front();
    }
    while (!domainBA.empty()) {
        yolo += domainBA.front() - 1;
        domainBA.pop_front();
    }
    ABcontri += min(remain, yolo);
    if (a < cntA - ABcontri || b < cntB - ABcontri) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

// 对于AA BB必然有一刀，所以要处理的子段必然是ABABA格式
// ABA格式，假如我固定AB数量，那么BA数量是否已知？
// ABABAB : 1/1;2/0
// BABABA : 1/1
// BABABAB : 1/2
// 穷举ABABA, BABAB, ABABAB, BABABA
// 前面两个单纯互斥 后两个则AB优势与BA优势，即如果全部AB则有n个，否则k个AB与n-1-k个BA