#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

int kmp(const vector<int>& s, const vector<int>& subs)
{
    int         len = subs.size();
    vector<int> nxt(subs.size());
    {
        int j = 0;
        for (int i = 1; i < len; i++) {
            while (j && subs[i] != subs[j]) {
                j = nxt[j];
            }
            nxt[i] = (subs[j] == subs[i] ? j : 0);
            j++;
        }
    }
    int pt   = 0;
    int lenS = s.size();
    for (int i = 0; i < lenS; i++) {
        while (pt && s[i] != subs[pt]) {
            pt = nxt[pt];
        }
        if (s[i] == subs[pt]) pt++;
        if (pt == len) {
            return i - pt + 1;
        }
    }
    return -1;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> l_main(n);
    for (int i = 0; i < n; i++) {
        cin >> l_main[i];
    }
    while (m--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int len_l1;
            cin >> len_l1;
            vector<int> l1(len_l1);
            for (int i = 0; i < len_l1; i++) {
                cin >> l1[i];
            }
            int idx = kmp(l_main, l1);
            if (idx == -1) {
                int len_l2;
                cin >> len_l2;
                int _;
                for (int i = 0; i < len_l2; i++) {
                    cin >> _;
                }
                continue;
            }
            l_main.erase(l_main.begin() + idx, l_main.begin() + idx + len_l1);
            int len_l2;
            cin >> len_l2;
            vector<int> l2(len_l2);
            for (int i = 0; i < len_l2; i++) {
                cin >> l2[i];
            }
            l_main.insert(l_main.begin() + idx, std::move(l2).begin(), std::move(l2).end());
        }
        if (cmd == 2) {
            int         curlen = l_main.size();
            vector<int> temp;
            for (int i = 0; i < curlen; i++) {
                temp.emplace_back(l_main[i]);
                if (i + 1 < curlen && (l_main[i] + l_main[i + 1]) % 2 == 0) {
                    temp.emplace_back((l_main[i] + l_main[i + 1]) / 2);
                }
            }
            l_main = temp;
        }
        if (cmd == 3) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            reverse(l_main.begin() + l, l_main.begin() + r + 1);
        }
    }
    int finalLen = l_main.size();
    for (int i = 0; i < finalLen; i++) {
        cout << l_main[i] << " \0"[i == finalLen - 1];
    }
    return 0;
}

// 14 9 8 7 6 5 4 3 2 1 5 9 8 19 20 21 2 5 4 9 14 5 8 17 26 1 14 5 4 5 13 21 10 9 15 21 8 21 2 9 10 11 12 13 14 1 2
// 14 9 8 7 6 5 4 3 2 1 5 9 8 19 20 21 2 5 4 9 14 5 8 17 26 1 14 5 4 5 13 21 10 9 15 21 8 21 2 9 10 11 12 13 14 1 2