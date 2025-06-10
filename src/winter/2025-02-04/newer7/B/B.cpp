#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define int long long
int  n;
int  R[105];
int  C[105];
char inputFloor[105][105][105];
int  dist[105][105][105];

struct Point3d {
    int x, y, z;
};

deque<Point3d> dequeBFS;

vector<list<Point3d>> doorsPlace(60);
vector<bool>          activated(60, false);

void tryActivate(Point3d gate)
{
    char x = inputFloor[gate.x][gate.y][gate.z];
    assert(isalpha(x));
    if ('a' <= x && x <= 'z') {
        x = x - 'a' + 1;
    } else {
        x = x - 'A' + 27;
    }
    if (activated[x]) {
        return;
    }

    for (Point3d iter : doorsPlace[x]) {
        dequeBFS.emplace_front(iter);
        dist[iter.x][iter.y][iter.z] = dist[gate.x][gate.y][gate.z];
    }
    activated[x] = true;
}

void addDoor(Point3d p3d)
{
    char x = inputFloor[p3d.x][p3d.y][p3d.z];
    assert(isalpha(x));
    if ('a' <= x && x <= 'z') {
        x = x - 'a' + 1;
    } else {
        x = x - 'A' + 27;
    }
    doorsPlace[x].emplace_back(p3d);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> R[i] >> C[i];
        for (int r = 1; r <= R[i]; r++) {
            for (int c = 1; c <= C[i]; c++) {
                cin >> inputFloor[i][r][c];
                if (isalpha(inputFloor[i][r][c])) {
                    addDoor(Point3d({i, r, c}));
                }
            }
        }
    }
    for (int x = 0; x <= 104; x++) {
        for (int y = 0; y <= 104; y++) {
            for (int z = 0; z <= 104; z++) {
                dist[x][y][z] = INT32_MAX;
            }
        }
    }
    for (int r = 1; r <= R[1]; r++) {
        for (int c = 1; c <= C[1]; c++) {
            dequeBFS.emplace_front(Point3d{1, r, c});
            dist[1][r][c] = 0;
        }
    }
    int movement[4][2]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    while (!dequeBFS.empty()) {
        Point3d cur = dequeBFS.front();
        dequeBFS.pop_front();
        if (isalpha(inputFloor[cur.x][cur.y][cur.z])) {
            tryActivate(cur);
        }
        for (int i = 0; i < 4; i++) {
            Point3d adj{cur.x, cur.y + movement[i][0], cur.z + movement[i][1]};
            if ((1 <= adj.y && adj.y <= R[adj.x]) && (1 <= adj.z && adj.z <= C[adj.x])
                && dist[adj.x][adj.y][adj.z] == INT32_MAX) {
                if (inputFloor[adj.x][adj.y][adj.z] == '#') {
                    dist[adj.x][adj.y][adj.z] = dist[cur.x][cur.y][cur.z] + 1;
                    dequeBFS.emplace_back(adj);
                } else {
                    dist[adj.x][adj.y][adj.z] = dist[cur.x][cur.y][cur.z];
                    dequeBFS.emplace_front(adj);
                }
            }
        }
    }
    int ans = INT32_MAX;
    for (int r = 1; r <= R[n]; r++) {
        for (int c = 1; c <= C[n]; c++) {
            ans = min(ans, dist[n][r][c]);
        }
    }
    if (ans == INT32_MAX) {
        cout << "No Solution";
    } else {
        cout << ans;
    }
    return 0;
}