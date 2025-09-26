#include <bits/stdc++.h>

#include <algorithm>
#include <vector>
using namespace std;
using LL     = long long;
namespace fs = filesystem;
mt19937 rd;
using i64 = long long;

i64 rdInt(i64 l, i64 r) { return rd() % (r - l) + l; }

void rdInit(const std::string seedFileName = fs::current_path() / "seed.txt")
{
    // 使用 RAII 来管理文件资源
    std::fstream seedFile(seedFileName, std::ios::in);
    unsigned int seed;
    if (!seedFile) {
        // 如果文件不存在，则创建并写入当前时间作为种子
        seed = static_cast<int>(std::time(0));
        seedFile.close();                            // 关闭输入模式
        seedFile.open(seedFileName, std::ios::out);  // 打开输出模式
        seedFile << seed;
    } else {
        // 如果文件存在，则读取种子
        seedFile >> seed;
    }
    seedFile.close();  // 确保文件被关闭
    // 初始化随机数生成器
    rd.seed(seed);
    // 更新种子文件
    seedFile.open(seedFileName, std::ios::out);
    seedFile << rd();
    seedFile.close();
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    rdInit(argv[1]);
    freopen(argv[2], "w", stdout);
#endif
    // freopen("test.in", "w", stdout);
    int t = 1;
    cout << t << '\n';
    while (t--) {
        int n = rdInt(1, 20);
        cout << n << '\n';
        for (int i = 0; i < n; i++) {
            cout << char(rdInt(0, 2) + 'a');
        }
        cout << '\n';
    }
    cout << endl;
    return 0;
}
