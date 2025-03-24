#include <bits/stdc++.h>

using namespace std;
using LL = long long;

constexpr int N = 1e3 + 5;

int input[N][N];
int maxBoard[N][N];
int minBoard[N][N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int a, b, n;
    cin >> a >> b >> n;
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            cin >> input[i][j];
        }
    }

    for (int i = 1; i <= a; i++) {
        deque<int> monoQue;
        for (int j = 1; j < n; j++) {
            while (!monoQue.empty() && input[i][monoQue.back()] <= input[i][j]) {
                monoQue.pop_back();
            }
            monoQue.push_back(j);
        }
        for (int j = n; j <= b; j++) {
            while (!monoQue.empty() && monoQue.front() <= j - n) {
                monoQue.pop_front();
            }
            while (!monoQue.empty() && input[i][monoQue.back()] <= input[i][j]) {
                monoQue.pop_back();
            }
            monoQue.push_back(j);
            maxBoard[i][j - n + 1] = input[i][monoQue.front()];
        }
    }
    for (int j = 1; j <= b - n + 1; j++) {
        deque<int> monoQue;
        for (int i = 1; i < n; i++) {
            while (!monoQue.empty() && maxBoard[monoQue.back()][j] <= maxBoard[i][j]) {
                monoQue.pop_back();
            }
            monoQue.push_back(i);
        }
        for (int i = n; i <= a; i++) {
            while (!monoQue.empty() && monoQue.front() <= i - n) {
                monoQue.pop_front();
            }
            while (!monoQue.empty() && maxBoard[monoQue.back()][j] <= maxBoard[i][j]) {
                monoQue.pop_back();
            }
            monoQue.push_back(i);
            maxBoard[i - n + 1][j] = maxBoard[monoQue.front()][j];
        }
    }

    for (int i = 1; i <= a; i++) {
        deque<int> monoQue;
        for (int j = 1; j < n; j++) {
            while (!monoQue.empty() && input[i][monoQue.back()] >= input[i][j]) {
                monoQue.pop_back();
            }
            monoQue.push_back(j);
        }
        for (int j = n; j <= b; j++) {
            while (!monoQue.empty() && monoQue.front() <= j - n) {
                monoQue.pop_front();
            }
            while (!monoQue.empty() && input[i][monoQue.back()] >= input[i][j]) {
                monoQue.pop_back();
            }
            monoQue.push_back(j);
            minBoard[i][j - n + 1] = input[i][monoQue.front()];
        }
    }
    for (int j = 1; j <= b - n + 1; j++) {
        deque<int> monoQue;
        for (int i = 1; i < n; i++) {
            while (!monoQue.empty() && minBoard[monoQue.back()][j] >= minBoard[i][j]) {
                monoQue.pop_back();
            }
            monoQue.push_back(i);
        }
        for (int i = n; i <= a; i++) {
            while (!monoQue.empty() && monoQue.front() <= i - n) {
                monoQue.pop_front();
            }
            while (!monoQue.empty() && minBoard[monoQue.back()][j] >= minBoard[i][j]) {
                monoQue.pop_back();
            }
            monoQue.push_back(i);
            minBoard[i - n + 1][j] = minBoard[monoQue.front()][j];
        }
    }

    int ans = INT32_MAX;
    for (int i = 1; i <= a - n + 1; i++) {
        for (int j = 1; j <= b - n + 1; j++) {
            ans = min(ans, maxBoard[i][j] - minBoard[i][j]);
        }
    }
    cout << ans;
    return 0;
}