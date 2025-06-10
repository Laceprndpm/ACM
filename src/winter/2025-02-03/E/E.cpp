#include <bits/stdc++.h>
using namespace std;
using LL = long long;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> listA(n + 1);
    vector<int> listB(n + 1);
    LL          scoreA = 0;
    LL          scoreB = 0;
    for (int i = 1; i <= n; i++) {
        cin >> listA[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> listB[i];
    }
    sort(listA.begin() + 1, listA.end(), greater<int>());
    sort(listB.begin() + 1, listB.end(), greater<int>());
    int round = 1;
    int i     = 1;
    int j     = 1;
    for (; round <= 2 * n; round++) {
        if (round % 2 == 1) {
            if (i == n + 1) {
                j++;
                continue;
            }
            if (j == n + 1) {
                scoreA += listA[i];
                i++;
                continue;
            }
            if (listA[i] > listB[j]) {
                scoreA += listA[i];
                i++;
            } else {
                j++;
            }
        } else {
            if (i == n + 1) {
                scoreB += listB[j];
                j++;
                continue;
            }
            if (j == n + 1) {
                i++;
                continue;
            }
            if (listA[i] > listB[j]) {
                i++;
            } else {
                scoreB += listB[j];
                j++;
            }
        }
    }
    cout << scoreA - scoreB << '\n';
    return 0;
}