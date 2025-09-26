/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <bits/stdc++.h>

struct ListNode {
    int       val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

constexpr int P = 1e9 + 7;
using i64       = long long;

constexpr i64 power(i64 a, i64 b)
{
    i64 res = 1;
    for (; b != 0; b /= 2, a *= a, a %= P) {
        if (b & 1) {
            res *= a;
            res %= P;
        }
    }
    return res;
}

template <int x, int P>
constexpr int CInv = power(x, P - 2);

class Solution {
public:
    bool isPalindrome(ListNode *head)
    {
        int       len  = 0;
        ListNode *cur  = head;
        i64       mod1 = 0, mod2 = 0;
        while (cur != nullptr) {
            mod1 *= 114;
            mod1 %= P;
            mod2 *= CInv<114, P>;
            mod2 %= P;
            mod1 += cur->val;
            mod2 += cur->val;
            cur = cur->next;
            len++;
        }
        return mod1 == mod2 * power(114, len - 1) % P;
    }
};

int main()
{
    ListNode n4(1);
    ListNode n3(2, &n4);
    ListNode n2(2, &n3);
    ListNode n1(1, &n2);
    std::cout << (Solution::isPalindrome(&n1) ? 1 : 0);
}