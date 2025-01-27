#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
char arr[3][N];
struct node
{
    int row, col;
    bool operator<(node &other)
    {
        return row + col < other.row + other.col;
    }
};

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> arr[1][i];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> arr[2][i];
        }
        priority_queue<node> pq;
        while (!pq.empty())
        {
            node cnt = pq.top();
            pq.pop();
            if (cnt.col + 1 <= n)
            {
                if (arr[cnt.row][cnt.col + 1] == '>')
                {
                    pq.push({cnt.row, cnt.col + 2});
                }
            }

            if (cnt.row == 1)
            {
                if (arr[2][cnt.col] == '>')
                {
                    pq.push({2, cnt.col + 1});
                }
            }
            else
            {
            }
        }
    }
}