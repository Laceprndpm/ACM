#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

// std::vector<int> ans;

// int tot = 0;
int query(const std::vector<int> &p)
{
    // tot++;
    // int cnt = 0;
    // for (int i = 0; i < ans.size(); i++) {
    //     cnt += (p[i] == ans[i]);
    // }
    // return cnt;
    std::cout << 0;
    for (auto x : p) {
        std::cout << " " << x + 1;
    }
    std::cout << std::endl;
    int res;
    std::cin >> res;
    return res;
}

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    // ans.resize(n);
    // std::iota(ans.begin(), ans.end(), 0);
    // std::shuffle(ans.begin(), ans.end(), rng);

    std::vector<int> p(n);
    auto             work = [&](auto &self, int l, int r, std::vector<int> a) -> void {
        if (r - l == 1) {
            p[l] = a[0];
            return;
        }
        int m = (l + r) / 2;

        std::shuffle(a.begin(), a.end(), rng);
        std::vector<int> v;

        std::vector<int> al, ar;
        for (auto x : a) {
            if (v.empty()) {
                v.push_back(x);
            } else {
                std::vector b(n, x);
                for (int i = l; i < m; i++) {
                    b[i] = v[0];
                }
                int res = query(b);
                if (res == 0) {
                    for (auto y : v) {
                        ar.push_back(y);
                    }
                    al.push_back(x);
                    v.clear();
                } else if (res == 1) {
                    v.push_back(x);
                } else {
                    for (auto y : v) {
                        al.push_back(y);
                    }
                    ar.push_back(x);
                    v.clear();
                }
            }
        }
        if (!v.empty()) {
            if (al.empty()) {
                al = v;
            } else if (ar.empty()) {
                ar = v;
            } else {
                std::vector b(n, al[0]);
                for (int i = m; i < r; i++) {
                    b[i] = v[0];
                }
                if (query(b) == 2) {
                    std::copy(v.begin(), v.end(), std::back_inserter(ar));
                } else {
                    std::copy(v.begin(), v.end(), std::back_inserter(al));
                }
            }
        }
        self(self, l, m, al);
        self(self, m, r, ar);
    };
    std::vector<int> a(n);
    std::iota(a.begin(), a.end(), 0);
    work(work, 0, n, a);

    // assert(p == ans);
    // std::cerr << "tot : " << tot << "\n";

    std::cout << 1;
    for (int i = 0; i < n; i++) {
        std::cout << " " << p[i] + 1;
    }
    std::cout << std::endl;

    return 0;
}
