#include <bits/stdc++.h>
using namespace std;

struct Point {
    int q, r, s;
};

int64_t calc_total_distance(const vector<Point>& dragons, int64_t X, int64_t Y)
{
    int64_t S   = -X - Y;
    int64_t sum = 0;
    for (const auto& p : dragons) {
        int64_t dq = abs(p.q - X);
        int64_t dr = abs(p.r - Y);
        int64_t ds = abs(p.s - S);
        sum += max({dq, dr, ds});
    }
    return sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> dragons(n);
    int64_t       max_coord = 0;

    for (int i = 0; i < n; i++) {
        cin >> dragons[i].q >> dragons[i].r >> dragons[i].s;
        max_coord =
            max({max_coord, (int64_t)abs(dragons[i].q), (int64_t)abs(dragons[i].r), (int64_t)abs(dragons[i].s)});
    }

    int64_t low = 0, high = max_coord * 3;

    while (low < high) {
        int64_t mid = (low + high) / 2;

        int64_t Lx = INT64_MIN, Rx = INT64_MAX;
        int64_t Ly = INT64_MIN, Ry = INT64_MAX;
        int64_t Ls = INT64_MIN, Rs = INT64_MAX;

        for (auto& p : dragons) {
            Lx = max(Lx, (int64_t)p.q - mid);
            Rx = min(Rx, (int64_t)p.q + mid);
            Ly = max(Ly, (int64_t)p.r - mid);
            Ry = min(Ry, (int64_t)p.r + mid);
            Ls = max(Ls, (int64_t)(p.q + p.r) - mid);
            Rs = min(Rs, (int64_t)(p.q + p.r) + mid);
        }

        bool feasible = false;
        if (Lx <= Rx && Ly <= Ry) {
            int64_t sum_min = Lx + Ly;
            int64_t sum_max = Rx + Ry;
            if (sum_min <= Rs && sum_max >= Ls) feasible = true;
        }

        if (feasible)
            high = mid;
        else
            low = mid + 1;
    }

    // 找满足条件的点
    int64_t Lx = INT64_MIN, Rx = INT64_MAX;
    int64_t Ly = INT64_MIN, Ry = INT64_MAX;
    int64_t Ls = INT64_MIN, Rs = INT64_MAX;

    for (auto& p : dragons) {
        Lx = max(Lx, (int64_t)p.q - low);
        Rx = min(Rx, (int64_t)p.q + low);
        Ly = max(Ly, (int64_t)p.r - low);
        Ry = min(Ry, (int64_t)p.r + low);
        Ls = max(Ls, (int64_t)(p.q + p.r) - low);
        Rs = min(Rs, (int64_t)(p.q + p.r) + low);
    }

    int64_t X     = Lx;
    int64_t Y_min = max(Ly, Ls - X);
    int64_t Y_max = min(Ry, Rs - X);
    int64_t Y     = (Y_min <= Y_max) ? Y_min : Ly;

    int64_t total_dist = calc_total_distance(dragons, X, Y);

    cout << total_dist << "\n";

    return 0;
}
