#include <iostream>
#include <ostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct BigIntTiny {
    int              sign;
    std::vector<int> v;

    BigIntTiny() : sign(1) {}

    BigIntTiny(const std::string &s)
    {
        *this = s;
    }

    BigIntTiny(i64 v)
    {
        char buf[21];
        sprintf(buf, "%lld", v);
        *this = buf;
    }

    /**
     * 数据压缩/解压缩方法
     * @param unzip 模式选择：0=压缩(10进制→10000进制)，1=解压缩(10000进制→10进制)
     */
    void zip(int unzip)
    {
        if (unzip == 0) {
            // 压缩模式：将每4个10进制位合并为1个10000进制位
            for (int i = 0; i < (int)v.size(); i++)
                v[i] = get_pos(i * 4) + get_pos(i * 4 + 1) * 10 + get_pos(i * 4 + 2) * 100 + get_pos(i * 4 + 3) * 1000;
        } else
            // 解压缩模式：将每个10000进制位展开为4个10进制位
            for (int i = (v.resize(v.size() * 4), (int)v.size() - 1), a; i >= 0; i--)
                a = (i % 4 >= 2) ? v[i / 4] / 100 : v[i / 4] % 100, v[i] = (i & 1) ? a / 10 : a % 10;
        setsign(1, 1);
    }

    int get_pos(unsigned pos) const
    {
        return pos >= v.size() ? 0 : v[pos];
    }

    /**
     * 设置符号并规范化数字
     * @param newsign 新符号
     * @param rev 是否反转当前符号
     * @return 返回自身引用
     */
    BigIntTiny &setsign(int newsign, int rev)
    {
        // 移除高位的无效0
        for (int i = (int)v.size() - 1; i > 0 && v[i] == 0; i--)
            v.erase(v.begin() + i);
        // 处理零值的符号
        sign = (v.size() == 0 || (v.size() == 1 && v[0] == 0)) ? 1 : (rev ? newsign * sign : newsign);
        return *this;
    }

    // 转换为字符串表示
    std::string to_str() const
    {
        BigIntTiny  b = *this;
        std::string s;
        for (int i = (b.zip(1), 0); i < (int)b.v.size(); ++i)
            s += char(*(b.v.rbegin() + i) + '0');
        return (sign < 0 ? "-" : "") + (s.empty() ? std::string("0") : s);
    }

    // 绝对值比较：判断当前数绝对值是否小于b
    bool absless(const BigIntTiny &b) const
    {
        if (v.size() != b.v.size()) return v.size() < b.v.size();
        for (int i = (int)v.size() - 1; i >= 0; i--)
            if (v[i] != b.v[i]) return v[i] < b.v[i];
        return false;
    }

    BigIntTiny operator-() const
    {
        BigIntTiny c = *this;
        c.sign       = (v.size() > 1 || v[0]) ? -c.sign : 1;
        return c;
    }

    BigIntTiny &operator=(const std::string &s)
    {
        if (s[0] == '-')
            *this = s.substr(1);
        else {
            for (int i = (v.clear(), 0); i < (int)s.size(); ++i)
                v.push_back(*(s.rbegin() + i) - '0');
            zip(0);
        }
        return setsign(s[0] == '-' ? -1 : 1, sign = 1);
    }

    bool operator<(const BigIntTiny &b) const
    {
        return sign != b.sign ? sign < b.sign : (sign == 1 ? absless(b) : b.absless(*this));
    }

    bool operator==(const BigIntTiny &b) const
    {
        return v == b.v && sign == b.sign;
    }

    BigIntTiny &operator+=(const BigIntTiny &b)
    {
        if (sign != b.sign) return *this = (*this) - -b;
        v.resize(std::max(v.size(), b.v.size()) + 1);
        for (int i = 0, carry = 0; i < (int)b.v.size() || carry; i++) {
            carry += v[i] + b.get_pos(i);
            v[i] = carry % 10000, carry /= 10000;
        }
        return setsign(sign, 0);
    }

    BigIntTiny operator+(const BigIntTiny &b) const
    {
        BigIntTiny c = *this;
        return c += b;
    }

    // 辅助方法：加上b乘以mul的结果
    void add_mul(const BigIntTiny &b, int mul)
    {
        v.resize(std::max(v.size(), b.v.size()) + 2);
        for (int i = 0, carry = 0; i < (int)b.v.size() || carry; i++) {
            carry += v[i] + b.get_pos(i) * mul;
            v[i] = carry % 10000, carry /= 10000;
        }
    }

    // 减法运算符
    BigIntTiny operator-(const BigIntTiny &b) const
    {
        if (b.v.empty() || b.v.size() == 1 && b.v[0] == 0) return *this;
        if (sign != b.sign) return (*this) + -b;
        if (absless(b)) return -(b - *this);
        BigIntTiny c;
        for (int i = 0, borrow = 0; i < (int)v.size(); i++) {
            borrow += v[i] - b.get_pos(i);
            c.v.push_back(borrow);
            c.v.back() -= 10000 * (borrow >>= 31);
        }
        return c.setsign(sign, 0);
    }

    // 乘法运算符（使用加法实现）
    BigIntTiny operator*(const BigIntTiny &b) const
    {
        if (b < *this) return b * *this;
        BigIntTiny c, d = b;
        for (int i = 0; i < (int)v.size(); i++, d.v.insert(d.v.begin(), 0))
            c.add_mul(d, v[i]);
        return c.setsign(sign * b.sign, 0);
    }

    // 除法运算符（使用估商法）
    BigIntTiny operator/(const BigIntTiny &b) const
    {
        BigIntTiny c, d;
        BigIntTiny e = b;
        e.sign       = 1;

        d.v.resize(v.size());
        double db = 1.0
                    / (b.v.back() + (b.get_pos((unsigned)b.v.size() - 2) / 1e4)
                       + (b.get_pos((unsigned)b.v.size() - 3) + 1) / 1e8);
        for (int i = (int)v.size() - 1; i >= 0; i--) {
            c.v.insert(c.v.begin(), v[i]);
            int m = (int)((c.get_pos((int)e.v.size()) * 10000 + c.get_pos((int)e.v.size() - 1)) * db);
            c     = c - e * m, c.setsign(c.sign, 0), d.v[i] += m;
            while (!(c < e))
                c = c - e, d.v[i] += 1;
        }
        return d.setsign(sign * b.sign, 0);
    }

    BigIntTiny operator%(const BigIntTiny &b) const
    {
        return *this - *this / b * b;
    }

    bool operator>(const BigIntTiny &b) const
    {
        return b < *this;
    }

    bool operator<=(const BigIntTiny &b) const
    {
        return !(b < *this);
    }

    bool operator>=(const BigIntTiny &b) const
    {
        return !(*this < b);
    }

    bool operator!=(const BigIntTiny &b) const
    {
        return !(*this == b);
    }

    friend ostream &operator<<(ostream &os, const BigIntTiny &b)
    {
        os << b.to_str();
        return os;
    }
};

void solve()

{
    i64 l, r;
    cin >> l >> r;
    BigIntTiny L(l), R(r);
    cout << (((R + L) * (R - L + 1) / 2) % 9).to_str() << '\n';
}

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}