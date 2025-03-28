#include <bits/stdc++.h>

#include <vector>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

const int AL = 26;

vector<int> prefix_function(const string &s)
{
    int         n = s.size();
    vector<int> p(n);
    for (int i = 1; i < n; ++i) {
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k])  // 失配
            k = p[k - 1];
        k += (s[i] == s[k]);  //  [k == 0]
        p[i] = k;
    }
    return p;
}

int main()
{
    cin.tie(0);
    iostream::sync_with_stdio(false);
    string s;
    cin >> s;
    int                 n = s.size();
    vector<int>         p = prefix_function(s);
    vector<vector<int>> A(n, vector<int>(AL));
    forn(i, n)
    {
        forn(j, AL)
        {
            if (i > 0 && j != s[i] - 'a') {
                A[i][j] = A[p[i - 1]][j];
                // 神秘代码
                // 如果不匹配，就往前找一位，为什么可以？
                // 正常的failing会导致大量重复，如aaaaaaaa，而此时可以直接用b数组跳过，唯一的缺点是初始化时多了AL的成本

            } else {
                A[i][j] = i + (j == s[i] - 'a');
                // 正常的构造自动机
            }
        }
    }
    int q;
    cin >> q;
    vector<vector<int>> ans(q);
    forn(z, q)
    {
        string t;
        cin >> t;
        int m = t.size();
        s += t;
        for (int i = n; i < n + m; ++i) {
            A.push_back(vector<int>(AL));
            forn(j, AL)
            {
                if (j != s[i] - 'a')
                    A[i][j] = A[p[i - 1]][j];
                else
                    A[i][j] = i + (j == s[i] - 'a');
            }
            p.push_back(A[p[i - 1]][s[i] - 'a']);
            ans[z].push_back(p[i]);
        }
        forn(_, m)
        {
            p.pop_back();
            s.pop_back();
            A.pop_back();
        }
    }
    for (auto &it : ans) {
        for (int x : it)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}