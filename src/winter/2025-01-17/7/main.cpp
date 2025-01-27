#include <bits/stdc++.h>
using namespace std;
string input;
int n;
struct cont
{
    vector<int> cnt_c;
    vector<int> max_c;
    int total = 0;
    bool inter;
    cont() : cnt_c(5, 0), max_c(5, 0) {}
    void add(int x)
    {
        cnt_c[x]++;
        for (int i = 1; i <= 4; i++)
        {
            max_c[i] = max(max_c[i], cnt_c[i]);
            if (i != x && !inter)
            {
                cnt_c[i] = 0;
            }
        }
        if (!inter)
        {
            total++;
        }
    }
    void is_inter(bool x)
    {
        if (x)
        {
            total++;
        }
        inter = x;
    }
} conti;

signed main()
{
    cin >> input >> n;
    int i = 0;

    while (i <= input.size())
    {
        switch (input[i])
        {
        case 'L':
        {
            if (input[i + 1] == '\'')
            {
                conti.add(2);
            }
            else
            {
                conti.add(1);
            }
            break;
        }
        case 'R':
        {
            if (input[i + 1] == '\'')
            {
                conti.add(4);
            }
            else
            {
                conti.add(3);
            }
            break;
        }
        case '(':
        {
            conti.is_inter(true);
            break;
        }
        case ')':
        {
            conti.is_inter(false);
            break;
        }
        default:
            break;
        }
        i++;
    }
    cout << conti.total << '\n';
    if (n == 1)
        cout << conti.max_c[1] << ' ' << conti.max_c[2] << ' ' << conti.max_c[3] << ' ' << conti.max_c[4] << endl;
    return 0;
}