#include <bits/stdc++.h>
using namespace std;

int generateRandomInt(int min, int max)
{
    int tmp;
    tmp = rand() % (max - min);
    tmp += min;
    return tmp;
}

int main(int argc, char *argv[])
{
    // 默认输出文件名
    string outputFile = ".\\input.txt";
    unsigned seed = static_cast<unsigned>(time(0)) * 1000 + (clock() % 1000);
    srand(seed);
    // 检查命令行参数是否指定了输出文件
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-n" && i + 1 < argc) // 检查 -n 参数及其后续的文件名
        {
            outputFile = argv[i + 1];
            break;
        }
    }
    // freopen(outputFile.c_str(), "w", stdout);
    int n = generateRandomInt(2, 10);
    int k = generateRandomInt(1, 10);
    cout << n << '\n';
    for (int i = 0; i < n; i++)
    {
        cout << generateRandomInt(1, 10) << " ";
    }
    cout << '\n';
    cout << k;
    cout << endl;

    return 0;
}
