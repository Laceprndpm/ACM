#include <cstdlib>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#define REMOVE_ME
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

template <typename T>
class CustomAllocator {
public:
    using value_type = T;

    CustomAllocator(void* buffer, size_t size) : buffer_(static_cast<T*>(buffer)), size_(size), offset_(0) {}

    T* allocate(size_t n)
    {
        if (offset_ + n > size_) {
            throw std::bad_alloc();
        }
        T* result = buffer_ + offset_;
        offset_ += n;
        return result;
    }

    void deallocate(T* p, size_t n) noexcept
    {
        // 自定义释放逻辑（如果需要）
    }

private:
    T*     buffer_;
    size_t size_;
    size_t offset_;
};

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 1; i <= m; i++) {
        int X, Y, Z;
        cin >> X >> Y >> Z;
        graph[X].emplace_back(Y, Z);
        graph[Y].emplace_back(X, Z);
    }
    char*                 bufferVis   = new char[n + 1 + 50];
    int*                  bufferlabel = new int[(int)(n + 1 + 50)];
    CustomAllocator<char> allocatorVis(bufferVis, n + 1);
    CustomAllocator<int>  allocatorLabel(bufferlabel, n + 1);

    vector<int>                         ans(n + 1);
    vector<char, CustomAllocator<char>> vis(allocatorVis);
    vector<int, CustomAllocator<int>>   label(allocatorLabel);
    vector<int>                         needupdate;
    int                                 cnt1;
    int                                 cntn1;
    int                                 mirrorj;
    function<void(int)>                 DFS = [&](int root) {
        if (vis[root]) return;
        needupdate.push_back(root);
        vis[root] = true;
        for (auto adj : graph[root]) {
            int idx      = adj.first;
            int xorLabel = adj.second >> mirrorj & 1;
            if (label[idx] == 0) {
                if (xorLabel) {
                    label[idx] = -label[root];
                } else {
                    label[idx] = label[root];
                }
                if (label[idx] == 1) {
                    cnt1++;
                } else {
                    cntn1++;
                }
            } else if (label[idx] != label[root] * (xorLabel ? -1 : 1)) {
                cout << -1 << '\n';
                exit(0);
            }
            DFS(idx);
        }
    };
    for (int j = 0; j < 31; j++) {  // 枚举位
        vis.assign(n + 1, 0);
        label.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            needupdate.clear();
            if (vis[i]) continue;
            cnt1     = 1;
            cntn1    = 0;
            label[i] = 1;
            mirrorj  = j;
            DFS(i);
            if (cnt1 < cntn1) {
                for (int k : needupdate) {
                    ans[k] += (label[k] == 1) << j;
                }
            } else {
                for (int k : needupdate) {
                    ans[k] += (label[k] == -1) << j;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    return 0;
}