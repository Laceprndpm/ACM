#include <bits/stdc++.h>
using namespace std;
signed main()
{
    int j = 1;
    unordered_map<int, int> umap;
    for (int i = 99; i >= 1; i -= 2)
    {
        umap[i] = j;
        j++;
    }
    for (int i = 0; i <= 98; i += 2)
    {
        umap[i] = j;
        j++;
    }
    int a, b;
    cin >> a >> b;
    cout << abs(umap[a] - umap[b]) - 1;
    return 0;
}