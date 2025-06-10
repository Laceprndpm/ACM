#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void change(int l, int r, string& s)
{
    s[l] = 'A';
    for (int i = l + 1; i <= r; i++) {
        s[i] = 'C';
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string input;
    cin >> input;
    int l = 0, r = 0;
    int n = input.size();
    for (int i = 0; i < n; i++) {
        if (input[i] == 'W') {
            l = i;
            while (i < n && input[i] == 'W') {
                i++;
            }
            if (i < n && input[i] == 'A') {
                change(l, i, input);
            }
        }
    }
    cout << input;
    return 0;
}