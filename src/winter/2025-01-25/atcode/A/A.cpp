#include <bits/stdc++.h>
using namespace std;
using LL = long long;

bool check(int arr[]) {
    for (int i = 1; i <= 4; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int arr[6];
    int temp[6];
    for (int i = 1; i <= 5; i++) {
        cin >> arr[i];
    }

    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 5; j++) {
            temp[j] = arr[j];
        }
        swap(temp[i], temp[i + 1]);
        if (check(temp)) {
            cout << "Yes";
            return 0;
        }
    }
    cout << "No";
    return 0;
}