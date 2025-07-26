struct SuffixArray {
    int         n;
    int         k;
    string      s;
    vector<int> sa, rk, oldrk, id, cnt, lc;

    // lc[i]:sa[i] 与 sa[i-1] 的 LCP 长度

    SuffixArray(const string &s)
    {
        SuffixArray::s = s;
        n              = s.size() - 1;
        sa.resize(n + 1);
        rk.resize((n << 1) + 1);
        oldrk.resize((n << 1) + 1);
        id.resize(n + 1);
        cnt.resize(max(n + 1, 128));
        getsa(s);
        getlcp(s);
    }

    // chatgpt:构建后缀数组 sa 和排名数组 rk，用倍增 + 基数排序
    void getsa(const string &s)
    {
        int m = 127;
        for (int i = 1; i <= n; i++)
            ++cnt[rk[i] = s[i]];
        for (int i = 1; i <= m; i++)
            cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--)
            sa[cnt[rk[i]]--] = i;
        oldrk = rk;

        for (int p = 0, i = 1; i <= n; ++i) {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]]) {
                rk[sa[i]] = p;
            } else {
                rk[sa[i]] = ++p;
            }
        }

        for (int w = 1; w < n; w <<= 1, m = n) {
            cnt.assign(max(n, m) + 1, 0);
            id = sa;
            for (int i = 1; i <= n; ++i)
                ++cnt[rk[id[i] + w]];
            for (int i = 1; i <= m; ++i)
                cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; --i)
                sa[cnt[rk[id[i] + w]]--] = id[i];

            cnt.assign(max(n, m) + 1, 0);
            id = sa;
            for (int i = 1; i <= n; ++i)
                ++cnt[rk[id[i]]];
            for (int i = 1; i <= m; ++i)
                cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; --i)
                sa[cnt[rk[id[i]]]--] = id[i];

            oldrk = rk;
            for (int p = 0, i = 1; i <= n; ++i) {
                if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
                    rk[sa[i]] = p;
                } else {
                    rk[sa[i]] = ++p;
                }
            }
        }
    }

    // chatgpt:构建 LCP（Height）数组 lc，表示相邻后缀的最长公共前缀
    void getlcp(const string &s)
    {
        lc.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            rk[sa[i]] = i;
        }

        int h = 0;
        lc[1] = 0;

        for (int i = 1; i <= n; i++) {
            int j = sa[rk[i] - 1];
            if (h > 0) h--;
            while (i + h <= n && j + h <= n) {
                if (s[i + h] != s[j + h]) break;
                h++;
            }
            lc[rk[i]] = h;
        }
    }

    // chatgpt:判断字符串 t 是否是 s 的某个子串，用二分查找在 sa 中搜索。
    bool find(const string &t)
    {
        bool ans = 0;
        int  lo = 1, hi = n;

        auto check = [&](int idx, const string &t) {
            int p = 0;
            while (1) {
                if (s[idx] != t[p]) {
                    if (s[idx] < t[p]) return -1;
                    return 1;
                }
                idx++;
                p++;
                if (idx > n || p == t.size()) break;
            }
            if (p == t.size()) return 0;
            return 1;
        };

        while (lo <= hi && !ans) {
            int mid = (lo + hi) >> 1;
            int f   = check(sa[mid], t);
            if (f == 0) {
                ans = 1;
            } else if (f == 1) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        return ans;
    }
};