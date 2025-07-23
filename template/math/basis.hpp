struct Basis {
    bool flag;  // 可以表示0

    static constexpr int MN = 60;

    u64 basis_arr[MN + 1];
    u64 tmp[MN + 1];

    void init()
    {
        memset(basis_arr, 0, sizeof(basis_arr));
        flag = 0;
    }

    void retreat(int idx)
    {
        basis_arr[idx] = 0;
    }

    int insert(u64 x)
    {
        for (int i = MN; i >= 0; i--)
            if (x & (1ull << i)) {
                if (!basis_arr[i]) {
                    basis_arr[i] = x;
                    return i;
                } else {
                    x ^= basis_arr[i];
                }
            }
        flag = true;
        return -1;
    }

    bool check(u64 x)
    {
        for (int i = MN; i >= 0; i--)
            if (x & (1ull << i)) {
                if (!basis_arr[i])
                    return false;
                else
                    x ^= basis_arr[i];
            }
        return true;
    }

    u64 qmax(u64 res = 0)
    {
        for (int i = MN; i >= 0; i--)
            res = max<u64>(res, res ^ basis_arr[i]);
        return res;
    }

    u64 qmin(u64 res = 0)
    {
        if (flag) return 0;
        for (int i = 0; i <= MN; i++)
            if (basis_arr[i]) return basis_arr[i];
        assert(0);
    }

    // -1ull为无值
    u64 query(u64 k)
    {
        u64 res = 0;
        int cnt = 0;
        k -= flag;
        if (!k) return 0;
        for (int i = 0; i <= MN; i++) {
            for (int j = i - 1; j >= 0; j--)
                if (basis_arr[i] & (1ull << j)) basis_arr[i] ^= basis_arr[j];
            if (basis_arr[i]) tmp[cnt++] = basis_arr[i];
        }
        if (k >= (1ull << cnt)) return -1ull;
        for (int i = 0; i < cnt; i++)
            if (k & (1ull << i)) res ^= tmp[i];
        return res;
    }
};
