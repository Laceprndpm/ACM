#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    int    id;
    string name;
    int    age;
    int    score;
    int    rank;
};

void printStudent(const Student& s)
{
    cout << "Name:" << s.name << endl;
    cout << "Age :" << s.age << endl;
    cout << "Score:" << s.score << endl;
    cout << "Rank:" << s.rank << endl;
}

int sequentialSearch(const vector<Student>& data, int targetID)
{
    for (int i = 0; i < data.size(); i++) {
        if (data[i].id == targetID) {
            return i;  // 返回索引
        }
    }
    return -1;  // 未找到
}

// 3. 折半查找实现 (要求数组必须是有序的)
int binarySearch(const vector<Student>& data, int targetID)
{
    int low  = 0;
    int high = data.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (data[mid].id == targetID) {
            return mid;
        } else if (data[mid].id < targetID) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// 辅助函数：用于排序
bool compareByID(const Student& a, const Student& b) { return a.id < b.id; }

int main()
{
    // 初始化原始数据
    vector<Student> students = {{25, "Tom", 19, 100, 1}, {38, "Jack", 18, 92, 2},   {92, "Rose", 20, 89, 3},
                                {64, "Lisa", 18, 72, 6}, {57, "Mike", 21, 85, 4},   {21, "Alice", 20, 65, 7},
                                {39, "Bob", 18, 89, 3},  {45, "Clark", 17, 100, 1}, {82, "Kate", 19, 78, 5},
                                {77, "Lily", 18, 64, 8}, {65, "Prince", 18, 100, 1}};

    int searchID;
    cout << "请输入ID号:";
    cin >> searchID;

    // --- 顺序查找演示 ---
    cout << "\n--- 顺序查找结果 ---" << endl;
    int seqIdx = sequentialSearch(students, searchID);
    if (seqIdx != -1) {
        printStudent(students[seqIdx]);
    } else {
        cout << "未找到该ID的学生信息。" << endl;
    }

    // --- 折半查找演示 ---
    vector<Student> sortedStudents = students;
    sort(sortedStudents.begin(), sortedStudents.end(), compareByID);

    cout << "\n--- 折半查找结果 ---" << endl;
    int binIdx = binarySearch(sortedStudents, searchID);
    if (binIdx != -1) {
        printStudent(sortedStudents[binIdx]);
    } else {
        cout << "未找到该ID的学生信息。" << endl;
    }

    return 0;
}