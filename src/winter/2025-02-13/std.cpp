#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#define int long long
std::set<std::string> ans, vis;

bool check(int x1, int y1, int x2, int y2, int R)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= R * R;
}

signed main(signed argc, char** argv)
{
    ans.clear();
    vis.clear();
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int x0, y0, R, N;
    std::cin >> x0 >> y0 >> R >> N;
    int Len = 0;
    while (N--) {
        int         x, y;
        std::string s;
        std::cin >> x >> y >> s;
        if (check(x, y, x0, y0, R)) {
            if (!vis.count(s))
                ans.insert(s), vis.insert(s);
        } else if (ans.count(s))
            ans.erase(s);
    }
    std::cout << ans.size() << std::endl;
    for (std::set<std::string>::iterator it = ans.begin(); it != ans.end(); ++it)
        std::cout << *it << ' ';
}