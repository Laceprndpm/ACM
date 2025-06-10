#include <cctype>
#include <iostream>
#include <stack>
#include <utility>
using namespace std;
using i64 = long long;

int main()
{
    string s;
    cin >> s;
    stack<pair<string, bool>> val;
    stack<char>               op;
    int                       len     = s.length();
    bool                      haslast = 0;
    for (int i = 0; i < len; i++) {
        char cur = s[i];
        if (cur == '(') {
            continue;
        } else if (isdigit(cur)) {
            if (haslast) {
                string top = val.top().first;
                top += cur;
                val.top().first = top;
            } else {
                string s;
                s += cur;
                val.push({s, true});
                haslast = true;
            }
        } else if (cur == ')') {
            haslast       = false;
            string val2   = val.top().first;
            bool   is2Raw = val.top().second;
            val.pop();
            string val1   = val.top().first;
            int    is1Raw = val.top().second;
            val.pop();
            char oper = op.top();
            op.pop();
            string newval = "";
            // if (oper == '+') {
            //     newval = "";
            // }
            // if (oper == '-') {
            //     newval = val1 - val2;
            // }
            // if (oper == '*') {
            //     newval = val1 * val2;
            // }
            // if (oper == '/') {
            //     newval = val1 / val2;
            // }
            if (is1Raw) {
                cout << val1;
            }
            cout << oper;
            if (is2Raw) {
                cout << val2;
            }
            cout << '\n';
            val.push({newval, false});
        } else {
            haslast = false;
            op.push(cur);
        }
    }
    return 0;
}