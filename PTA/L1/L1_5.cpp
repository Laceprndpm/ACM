#include <iostream>
#include <vector>
using namespace std;

int main()
{
    string s;
    cin >> s;
    vector<int> cnt(26);
    for (char c : s) {
        cnt[c - 'a']++;
    }
    int ans = 0;
    for (int i = 0; i < 26; i++) {
        int cur;
        cin >> cur;
        int temp = cnt[i] * cur;
        cout << cnt[i] << " \n"[i == 25];
        ans += temp;
    }
    cout << ans;
    return 0;
}