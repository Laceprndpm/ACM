#include <bits/stdc++.h>

#include "testlib.h"
#define MAXN 55
#define INF  1000000000
#define F    first
#define S    second

using namespace std;
typedef pair<int, int> P;

int    n, m, k, sx, sy, tx, ty;
string str[MAXN];
char   mp[MAXN][MAXN];
bool   edge[MAXN][MAXN];

int readAndCheckAnswer(InStream& in)
{
    vector<int> ret;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) mp[i][j] = str[i - 1][j - 1];
    int l = in.readInt(-1, 100000, "length");
    // printf("l=%d\n",l);
    if (l == -1) return -1;
    vector<P> vv;
    for (int i = 0; i < l; i++) {
        int x = in.readInt(1, n, "x");
        in.readSpace();
        int y = in.readInt(1, m, "y");
        in.readSpace();
        string str = in.readString();
        // cout<<str<<endl;
        if (str.size() != 1) in.quitf(_wa, "not a single character");
        if (str[0] != 'U' && str[0] != 'D' && str[0] != 'L' && str[0] != 'R') in.quitf(_wa, "not a valid character");
        if (mp[x][y] != '@' && mp[x][y] != '!') in.quitf(_wa, "no box on the required position");
        int nx = x, ny = y;
        if (str[0] == 'U')
            nx--;
        else if (str[0] == 'D')
            nx++;
        else if (str[0] == 'L')
            ny--;
        else
            ny++;
        if (nx <= 0 || nx > n || ny <= 0 || ny > m) in.quitf(_wa, "movement out of border");
        if (mp[nx][ny] == '#') in.quitf(_wa, "movement onto a wall");
        if (mp[nx][ny] == '!') {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << mp[i][j] << ' ';
                }
                cout << '\n';
            }
            cout << nx << ' ' << ny << '\n';
            in.quitf(_wa, "movement onto a !");
        }
        if (mp[nx][ny] == '@') in.quitf(_wa, "movement onto a @");

        if (mp[x][y] == '@')
            mp[x][y] = '.';
        else
            mp[x][y] = '*';
        if (mp[nx][ny] == '.')
            mp[nx][ny] = '@';
        else
            mp[nx][ny] = '!';
    }
    if (!in.eof()) {
        string t = in.readString();
        if (!in.eof()) in.quitf(_wa, "excess output");
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] == '@' || mp[i][j] == '*') in.quitf(_wa, "exists box not on target position");
        }
    return l;
}

int main(int argc, char* argv[])
{
    registerTestlibCmd(argc, argv);
    n = inf.readInt();
    m = inf.readInt();
    inf.readEoln();
    for (int i = 0; i < n; i++) {
        str[i] = inf.readString();
    }
    int ja = readAndCheckAnswer(ans);
    int pa = readAndCheckAnswer(ouf);
    if (ja != -1 && pa == -1) quitf(_wa, "Jury has the answer but participant has not");
    if (ja == -1 && pa != -1) quitf(_fail, "Participant has the answer but jury has not");
    quitf(_ok, "n=%d, m=%d", n, m);
}
