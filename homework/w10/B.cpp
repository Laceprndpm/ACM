#include <climits>
#include <iostream>
#include <vector>

using namespace std;

// 1. 定义二叉链表节点结构
struct Node {
    int   data;    // 节点存储的值
    int   id;      // 节点的唯一ID
    Node* lchild;  // 左孩子指针
    Node* rchild;  // 右孩子指针

    Node(int val, int _id) : data(val), id(_id), lchild(nullptr), rchild(nullptr) {}
};

// 判断是否为二叉排序树
bool isBST(Node* root, long long& lastVal)
{
    if (root == nullptr) return true;

    if (!isBST(root->lchild, lastVal)) return false;

    if (root->data <= lastVal) return false;
    lastVal = (long long)root->data;

    return isBST(root->rchild, lastVal);
}

// A.非递归
void iterativeSearch(Node* root, int key)
{
    Node*       p = root;
    vector<int> path;
    bool        found = false;

    while (p != nullptr) {
        path.push_back(p->data);
        if (p->data == key) {
            found = true;
            break;
        }
        p = (key < p->data) ? p->lchild : p->rchild;
    }

    if (found) {
        cout << "非递归查找路径 : ";
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : "->");
        }
        cout << endl;
    } else {
        cout << "未找到该节点" << endl;
    }
}

// B.递归
bool getRecursivePath(Node* root, int key, vector<int>& path)
{
    if (root == nullptr) return false;

    path.push_back(root->data);
    if (root->data == key) return true;

    if (key < root->data) {
        if (getRecursivePath(root->lchild, key, path)) return true;
    } else {
        if (getRecursivePath(root->rchild, key, path)) return true;
    }

    path.pop_back();  // 回溯
    return false;
}

int main()
{
    int n;
    cout << "请输入节点数 n: ";
    cin >> n;

    vector<Node*> nodePtrs(n + 1, nullptr);

    struct InputData {
        int val, leftId, rightId;
    };

    vector<InputData> inputs(n + 1);

    cout << "请按行输入 (值 左儿子ID 右儿子ID):" << endl;
    for (int i = 1; i <= n; ++i) {
        cin >> inputs[i].val >> inputs[i].leftId >> inputs[i].rightId;
        nodePtrs[i] = new Node(inputs[i].val, i);
    }

    for (int i = 1; i <= n; ++i) {
        if (inputs[i].leftId != 0) {
            nodePtrs[i]->lchild = nodePtrs[inputs[i].leftId];
        }
        if (inputs[i].rightId != 0) {
            nodePtrs[i]->rchild = nodePtrs[inputs[i].rightId];
        }
    }

    Node* root = nodePtrs[1];

    // 任务 1: 判断是否为 BST
    long long lastVal = LLONG_MIN;
    if (isBST(root, lastVal)) {
        cout << "\n判定结果:该树是二叉排序树" << endl;
    } else {
        cout << "\n判定结果:该树不是二叉排序树" << endl;
    }

    // 任务 2: 查找关键字
    int searchKey;
    cout << "\n请输入查找结点关键字 : ";
    cin >> searchKey;
    // A
    iterativeSearch(root, searchKey);
    // B
    vector<int> recPath;
    if (getRecursivePath(root, searchKey, recPath)) {
        cout << "递归查找路径   : ";
        for (int i = 0; i < recPath.size(); ++i) {
            cout << recPath[i] << (i == recPath.size() - 1 ? "" : "->");
        }
        cout << endl;
    }

    return 0;
}