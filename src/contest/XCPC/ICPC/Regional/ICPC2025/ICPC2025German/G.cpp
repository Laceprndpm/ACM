#include <bits/stdc++.h>

#include <ctime>
#include <random>
using namespace std;
mt19937 rd(time(0));
using i64 = long long;
#define all(x) (x).begin(), (x).end()

int main()
{
    int n;
    cin >> n;
    while (n--) {
        char   abc     = rd() % 26 + 'a';
        char   ABC     = rd() % 26 + 'A';
        char   a123    = rd() % 10 + '0';
        char   special = rd() % 15 + '!';
        string str     = {abc, ABC, a123, special};
        for (int i = 0; i < 8; i++) {
            str.push_back(char(rd() % (126 - 33 + 1) + 33));
        }
        shuffle(all(str), rd);
        cout << str << '\n';
    }
}