#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

LL merge_sort(vector<int> &arr, int l, int r)
{
    if (l == r) {
        return 0;
    }
    int mid    = (r - l) / 2 + l;
    LL  ansCnt = 0;
    ansCnt += merge_sort(arr, l, mid);
    ansCnt += merge_sort(arr, mid + 1, r);
    int         lPtr = l;
    int         rPtr = mid + 1;
    vector<int> ansArr(r - l + 2);
    for (int ansPtr = 1; ansPtr <= r - l + 1; ansPtr++) {
        if (lPtr == mid + 1) {
            ansArr[ansPtr] = arr[rPtr++];
        } else if (rPtr == r + 1) {
            ansArr[ansPtr] = arr[lPtr++];
            ansCnt += (r - mid);
        } else if (arr[lPtr] > arr[rPtr]) {  // arr[lPtr]与所有arr[mid+1]~arr[rPtr]构成逆序对
            ansArr[ansPtr] = arr[rPtr++];
        } else {
            ansArr[ansPtr] = arr[lPtr++];
            ansCnt += (rPtr - mid - 1);
        }
    }
    for (int i = l; i <= r; i++) {
        arr[i] = ansArr[i - l + 1];
    }
    return ansCnt;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> ai(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ai[i];
    }
    cout << merge_sort(ai, 1, n);
    // cout << '\n';
    // for (int i = 1; i <= n; i++) {
    //     cout << ai[i] << ' ';
    // }
    return 0;
}