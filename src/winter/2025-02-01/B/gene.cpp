#include <bits/stdc++.h>
using namespace std;
using LL     = long long;
namespace fs = filesystem;
mt19937 rd;

int rdInt(int l = 0, int r = UINT32_MAX)
{
    return rd() % (r - l) + l;
}

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
    // std::filesystem::path workingDirectory = fs::current_path();
    // std::cout << "Current working directory: " << workingDirectory << std::endl;
#ifndef BATCH
    rdInit();
    freopen("test.in", "w", stdout);
#endif
#ifdef BATCH
    rdInit(argv[1]);
    freopen(argv[2], "w", stdout);
#endif
    int rdn   = rdInt(5, 50);
    int hardn = rdInt(110, 120);
    int m     = 1050;
    cout << rdn + hardn << ' ' << m << '\n';
    for (int i = 1; i <= rdn; i++) {
        int lastc = 2000;
        for (int j = 1; j <= 10; j++) {
            lastc = rdInt(lastc + 1, max(INT32_MIN, lastc + 5));
            cout << lastc << ' ';
        }
        cout << '\n';
    }
    int mid = 9;
    for (int i = 1; i <= hardn; i++) {
        int lastc = 0;
        int j     = 1;
        for (; j <= mid; j++) {
            lastc = rdInt(lastc + 1, max(j * j * 2, lastc + 5));
            cout << lastc << ' ';
        }
        for (; j <= 10; j++) {
            lastc = 2000 + rdInt(lastc + 1, max(j * j * 100, lastc + 5));
            cout << lastc << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
    return 0;
}