// #include <bits/stdc++.h>
// using namespace std;

// struct Node
// {
//     int val;
//     Node *pre;
//     Node *next;
//     Node(int v, Node *pre = nullptr, Node *nxt = nullptr) : val(v), pre(pre), next(nxt) {}
// };

// // 从尾部开始插入节点
// void insertSortedFromTail(Node *tail, Node *newNode)
// {
//     Node *current = tail;

//     // 寻找插入位置
//     while (current != nullptr && current->val > newNode->val)
//     {
//         current = current->pre;
//     }

//     // 如果 current == nullptr，说明新节点的值最小，插入到头部
//     if (current == nullptr)
//     {
//         newNode->next = tail;
//         tail->pre = newNode;
//         newNode->pre = nullptr; // 新节点的前驱是 nullptr
//     }
//     else
//     {
//         // 将 newNode 插入到 current 和 current->next 之间
//         newNode->next = current->next;
//         if (current->next != nullptr)
//         {
//             current->next->pre = newNode;
//         }
//         current->next = newNode;
//         newNode->pre = current;
//     }
// }

// int n, m, k;
// signed main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     cout.tie(0);
//     cin >> n >> m >> k;
//     vector<int> temp(n);
//     for (int i = 0; i < n; i++)
//     {
//         cin >> temp[i];
//     }

//     Node *head = new Node(0); // 头节点的值为 0，指向空的前后节点
//     Node *pre = head;         // 预先指向头节点

//     Node kth(0, nullptr, nullptr); // 存储第 k 个节点
//     Node *cnt;
//     for (int i = 0; i < n; i++)
//     {
//         cnt = new Node(temp[i], nullptr, pre); // 创建新节点，prev 指向前一个节点
//         pre->next = cnt;                       // 前一个节点的 next 指向当前节点
//         pre = cnt;                             // 移动到当前节点

//         // 如果是第 k 个节点，保存该节点
//         if (i + 1 == k)
//         {
//             kth = *cnt;
//         }
//     }
//     Node *tail = cnt;
//     while (m--)
//     {
//         int commmand, l;
//         cin >> commmand >> l;
//         switch (commmand)
//         {
//         case 1:
//         {
//             for (; k <= l; k++)
//             {
//                 kth = *(kth.next);
//             }
//             break;
//         }
//         case 2:
//         {
//             if (l < kth.val) // 如果小于目前k的值
//             {
//                 kth = *(kth.next);
//             }
//             else // 大于等于k节点的值
//             {
//                 insertSortedFromTail(tail, new Node(l)); // 插入
//             }
//             break;
//         }
//         default:
//             break;
//         }
//         cout << kth.val << '\n';
//     }
// }

#include <bits/stdc++.h>
using namespace std;

int n, m, k;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> k;
    priority_queue<int> pq1;
    priority_queue<int, vector<int>, greater<int>> pq2;
    vector<int> temp(n);
    for (int i = 0; i < n; i++)
    {
        cin >> temp[i];
    }
    sort(temp.begin(), temp.end());
    for (int i = 0; i < k - 1; i++)
    {
        pq1.push(temp[i]);
    }
    for (int i = k - 1; i < n; i++)
    {
        pq2.push(temp[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        int commmand, l;
        cin >> commmand >> l;
        if (commmand == 1)
        {
            for (; k < l; k++)
            {
                pq1.push(pq2.top());
                pq2.pop();
            }
            cout << pq2.top() << '\n';
        }
        else
        {
            if (l < pq2.top())
            {
                pq1.push(l);
                pq2.push(pq1.top());
                pq1.pop();
            }
            else
            {
                pq2.push(l);
            }
            cout << pq2.top() << '\n';
        }
    }
    return 0;
}