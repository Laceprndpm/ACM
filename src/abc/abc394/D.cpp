#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

bool isPaired(char x, char y)
{
    if ((x == '(' && y == ')') || (x == '[' && y == ']') || (x == '{' && y == '}') || (x == '<' && y == '>')) {
        return true;
    } else {
        return false;
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> s;
    int        n = s.size();
    list<char> ans;
    for (int i = 0; i < n; i++) {
        if (isPaired(ans.back(), s[i])) {
            ans.pop_back();
        } else {
            ans.push_back(s[i]);
        }
    }
    if (ans.empty()) {
        cout << "Yes" << '\n';
    } else {
        cout << "No" << '\n';
    }
    return 0;
}