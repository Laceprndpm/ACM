#include <bits/stdc++.h>

#include <cassert>
#include <vector>
using namespace std;

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

typedef struct LNode  // 定义单链表
{
    int           data = 0;
    struct LNode *next = nullptr;
} LNode, *LinkList;

struct LinkedList {
    LinkList head;
    int      _size;

    LinkedList() : head(nullptr), _size(0) {}

    ~LinkedList()
    {
        while (head != nullptr) {
            del(0);
        }
    }

    LinkedList &operator=(LinkedList &&ot) noexcept
    {
        if (this != &ot) {
            auto p = head;
            while (p) {
                auto nxt = p->next;
                delete p;
                p = nxt;
            }

            head  = ot.head;
            _size = ot._size;

            ot.head  = nullptr;
            ot._size = 0;
        }
        return *this;
    }

    LinkedList(LinkedList &&ot) noexcept : head(ot.head), _size(ot._size)
    {
        ot.head  = nullptr;
        ot._size = 0;
    }

    LinkedList(vector<int> _data, int headins = 1) : LinkedList()
    {
        if (headins) {
            for (int val : _data) {
                this->insert(0, val);
            }
        } else {
            for (int val : _data) {
                this->insert(_size, val);
            }
        }
    }

    int query_idx(int idx)
    {
        auto o = head;
        while (idx--) {
            assert(o != nullptr);
            o = o->next;
        }
        return o->data;
    }

    int query_val(int val)
    {
        auto o   = head;
        int  idx = 0;
        while (o) {
            if (o->data == val) {
                return idx;
            }
            o = o->next;
            idx++;
        }
        return -1;
    }

    int insert(int idx, int val)
    {
        if (idx < 0 || idx > _size) {
            return -1;
        }

        auto node  = new LNode;
        node->data = val;
        node->next = nullptr;

        if (idx == 0) {
            node->next = head;
            head       = node;
        } else {
            auto o = head;
            for (int i = 0; i < idx - 1; ++i) {
                assert(o != nullptr);
                o = o->next;
            }
            node->next = o->next;
            o->next    = node;
        }
        ++_size;
        return 0;
    }

    int del(int idx)
    {
        if (idx < 0 || idx >= _size) {
            return -1;
        }

        LNode *cur = nullptr;
        if (idx == 0) {
            cur  = head;
            head = head->next;
        } else {
            auto o = head;
            for (int i = 0; i < idx - 1; ++i) {
                assert(o != nullptr);
                o = o->next;
            }
            cur     = o->next;
            o->next = cur->next;
        }
        delete cur;
        --_size;
        return 0;
    }

    vector<int> get_data()
    {
        vector<int> tmp;
        auto        o = head;
        while (o != nullptr) {
            tmp.push_back(o->data);
            o = o->next;
        }
        return tmp;
    }

    void merge(LinkedList &&ot)
    {
        if (!ot.head) return;
        if (!head) {
            head     = ot.head;
            _size    = ot._size;
            ot.head  = nullptr;
            ot._size = 0;
            return;
        }

        LNode  dummy;
        LNode *tail = &dummy;
        dummy.next  = nullptr;

        auto p1 = head;
        auto p2 = ot.head;

        while (p1 && p2) {
            if (p1->data <= p2->data) {
                tail->next = p1;
                p1         = p1->next;
            } else {
                tail->next = p2;
                p2         = p2->next;
            }
            tail = tail->next;
        }

        tail->next = p1 ? p1 : p2;

        head = dummy.next;
        _size += ot._size;

        ot.head  = nullptr;
        ot._size = 0;
    }

    int size() { return _size; }
};

int main()
{
    cout << R"(
（1）初始化单链表；

（2）头插法建立单链表；

（3）尾插法建立单链表；

（4）按位置查询，返回元素值；

（5）按元素值查询，返回位置序号；

（6）输出单链表长度；

（7）输出单链表所有元素；

（8）合并两个有序单链表。（参考2-17源码有，或教材P43页）

（9）退出
)";
    LinkedList lst;
    int        cmd;
    while (true) {
        cin >> cmd;
        switch (cmd) {
            case 1: {
                lst = LinkedList();
                cerr << RED << "CLEAR\n" << RESET;
                break;
            }
            case 2: {
                int n;
                cin >> n;
                vector<int> vec(n);
                for (int &i : vec) {
                    cin >> i;
                }
                lst = LinkedList(vec);
                cerr << RED << "头插法\n" << RESET;
                break;
            }
            case 3: {
                int n;
                cin >> n;
                vector<int> vec(n);
                for (int &i : vec) {
                    cin >> i;
                }
                lst = LinkedList(vec, 0);
                cerr << RED << "尾插法\n" << RESET;
                break;
            }
            case 4: {
                int idx;
                cin >> idx;
                cout << lst.query_idx(idx) << '\n';
                cerr << RED << "查下标\n" << RESET;
                break;
            }
            case 5: {
                int val;
                cin >> val;
                cout << lst.query_val(val) << '\n';
                cerr << RED << "查值\n" << RESET;
                break;
            }
            case 6: {

                cout << lst.size() << '\n';
                cerr << RED << "长度\n" << RESET;
                break;
            }
            case 7: {
                auto res = lst.get_data();
                for (int i : res) {
                    cout << i << ' ';
                }
                cerr << RED << "打印\n" << RESET;
                break;
            }
            case 8: {
                int m;
                cin >> m;
                vector<int> vec(m);
                for (int &i : vec) {
                    cin >> i;
                }
                LinkedList mamawoyaodawa(vec);
                lst.merge(std::move(mamawoyaodawa));
                cerr << RED << "归并\n" << RESET;
                break;
            }
            case 9: {
                cerr << RED << "退出\n" << RESET;
                return 0;
            }
        }
    }
}