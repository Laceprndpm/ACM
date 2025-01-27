#include <map>
#include <cstdio>
#include <algorithm>
int init()
{
	char c = getchar();
	int x = 0, f = 1;
	for (; c < '0' || c > '9'; c = getchar())
		if (c == '-')
			f = -1;
	for (; c >= '0' && c <= '9'; c = getchar())
		x = (x << 1) + (x << 3) + (c & 15);
	return x * f;
}
void print(int x)
{
	if (x < 0)
		x = -x, putchar('-');
	if (x / 10)
		print(x / 10);
	putchar(x % 10 + '0');
}
const int N = (int)1e4 + 5;
struct Tree
{
	int x, y, z;
	friend bool operator<(const Tree &p, const Tree &q)
	{
		if (p.x != q.x)
			return p.x < q.x;
		if (p.y != q.y)
			return p.y < q.y;
		return p.z < q.z;
	}
} s[N];
int x[N], y[N], z[N];
std::map<Tree, int> map;
int lowbit(int x)
{
	return x & -x;
}
void rebuild(int a, int b, int c) // 三维树状数组
{
	for (int i = a; i <= x[0]; i += lowbit(i))
		for (int j = b; j <= y[0]; j += lowbit(j))
			for (int k = c; k <= z[0]; k += lowbit(k))
				map[(Tree){i, j, k}]++;
}
std::map<Tree, int> dp;
/**
 * search() 函数用于在三维树状数组中查询以 (a, b, c) 为右上角的矩形区域
 * （即包含坐标 (a, b, c) 且位于原点 (1, 1, 1) 到 (a, b, c) 之间的区域）
 * 内的所有元素的频率总和。查询是通过树状数组的低位更新规则进行的，遍历所有
 * 从 (a, b, c) 到原点 (1, 1, 1) 的路径。为了加速查询，使用了记忆化（dp）
 * 来缓存查询结果，避免重复计算。
 */
int search(int a, int b, int c)
{
	Tree abc = (Tree){a, b, c};
	if (dp.count(abc))
		return dp[abc]; // 记忆化，进一步减小常数
	int ans = 0;
	for (int i = a; i; i -= lowbit(i))
		for (int j = b; j; j -= lowbit(j))
			for (int k = c; k; k -= lowbit(k))
			{
				Tree node = (Tree){i, j, k};
				if (map.count(node))
					ans += map[node];
				// 注意这个地方，如果直接写作 ans += map[node]，会在 node 不存在时仍然插入结点，导致无用结点变多
			}
	return dp[abc] = ans;
}
int Ans;
int mn(int x, int y)
{
	return x < y ? x : y;
}
int mx(int x, int y)
{
	return x > y ? x : y;
}
signed main(signed argc, char **argv)
{
#ifndef ONLINE_JUDGE
//	freopen(argv[1], "r", stdin);
//	freopen(argv[2], "w", stdout);
#endif
	int n = init();
	for (int i = 1; i <= n; ++i)
	{
		x[i] = init(), y[i] = init(), z[i] = init();
		s[i] = (Tree){x[i], y[i], z[i]};
	}
	std::stable_sort(x + 1, x + 1 + n);
	x[0] = std::unique(x + 1, x + 1 + n) - (x + 1); // 有多少种x坐标
	std::stable_sort(y + 1, y + 1 + n);
	y[0] = std::unique(y + 1, y + 1 + n) - (y + 1);
	std::stable_sort(z + 1, z + 1 + n);
	z[0] = std::unique(z + 1, z + 1 + n) - (z + 1);
	for (int i = 1; i <= n; ++i)
	{
		rebuild(std::upper_bound(x + 1, x + 1 + x[0], s[i].x) - (x + 1), // 离散化
				std::upper_bound(y + 1, y + 1 + y[0], s[i].y) - (y + 1),
				std::upper_bound(z + 1, z + 1 + z[0], s[i].z) - (z + 1));
	}
	Ans = n;
	const int Limit = 60;
	for (int dx1 = 0; dx1 <= Limit; ++dx1)
		for (int dx2 = -1; dx2 <= 1; dx2 += 2)
		{
			if (dx1 == 0 && dx2 == 1)
				continue; // 不重复计算
			int dx = dx1 * dx2;
			int X = x[0] / 2 + dx;
			int B = search(X, y[0], z[0]), D = search(x[0], y[0], z[0]);
			int max1 = mx(B >> 2, D - B >> 2);
			for (int dy1 = 0; dy1 <= Limit && max1 <= Ans; ++dy1)
				for (int dy2 = -1; dy2 <= 1; dy2 += 2)
				{
					if (dy1 == 0 && dy2 == 1)
						continue; // 不重复计算
					int dy = dy1 * dy2;
					int Y = y[0] / 2 + dy;
					int A = search(X, Y, z[0]), C = search(x[0], Y, z[0]);
					int max2 = mx(mx(A >> 1, B - A >> 1), mx(C - A >> 1, D - B - C + A >> 1));
					int L = z[0] / 2 - Limit, R = z[0] / 2 + Limit;
					// 最后一层 dz 用二分求最值
					while (L < R - 2 && max2 <= Ans)
					{
						int mid = L + R >> 1;
						int a = search(X, Y, mid);
						int b = A - a;
						int c = search(X, y[0], mid) - a;
						int d = B - a - b - c;
						int e = search(x[0], Y, mid) - a;
						int f = C - a - b - e;
						int g = search(x[0], y[0], mid) - a - c - e;
						int h = D - a - b - c - d - e - f - g;
						int ac = a > c ? a : c;
						int eg = e > g ? e : g;
						int bd = b > d ? b : d;
						int fh = f > h ? f : h;
						int aceg = ac > eg ? ac : eg;
						int bdfh = bd > fh ? bd : fh;
						if (aceg > bdfh)
							Ans = mn(Ans, aceg), R = mid;
						else
							Ans = mn(Ans, bdfh), L = mid;
					}
					if (max2 <= Ans)
						for (int mid = L; mid <= R; ++mid)
						{
							int a = search(X, Y, mid);
							int b = A - a;
							int c = search(X, y[0], mid) - a;
							int d = B - a - b - c;
							int e = search(x[0], Y, mid) - a;
							int f = C - a - b - e;
							int g = search(x[0], y[0], mid) - a - c - e;
							int h = D - a - b - c - d - e - f - g;
							int ac = a > c ? a : c;
							int eg = e > g ? e : g;
							int bd = b > d ? b : d;
							int fh = f > h ? f : h;
							int aceg = ac > eg ? ac : eg;
							int bdfh = bd > fh ? bd : fh;
							if (aceg > bdfh)
								Ans = mn(Ans, aceg);
							else
								Ans = mn(Ans, bdfh);
						}
				}
		}
	print(Ans), putchar('\n');
}
