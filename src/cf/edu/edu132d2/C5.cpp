#include <iostream>
#include <string>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int len = s.size();
        int cnt = 0, num = 0;
        s[0] = '(';
        for (int i = 0; i < len; i++) {
            if (s[i] == '(')
                cnt++;
            else if (s[i] == ')') {
                cnt--;
                if (cnt < 0) cnt++, num--;  // 之前一个未确定的问号需要确定为 '('
            } else
                num++;

            if (cnt == 0 && num == 1) cnt = 1, num = 0;  // 类似于括号序列第一个是 '?'， 所以'?' 应该确定为 '('
        }

        cout << (cnt == num ? "YES\n" : "NO\n");
    }
}
