#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <stack>
using namespace std;

// n 层汉诺塔问题
void func(int i, string start, string end, string other) {
    if (i == 1) {   // base case
        cout << "Move 1 from " << start << " to " << end << endl;
    }
    else {
        func(i - 1, start, other, end);
        cout << "Move " << i << " from " << start << " to " << end << endl;
        func(i - 1, other, end, start);
    }
}
void hanoi(int n) {
    if (n > 0) {
        func(n, "左", "右", "中");
    }
}

// 打印一个字符串的全部子序列
void process(string str, int i) {
    if (i == str.size()) {
        cout << str << endl;
        return;
    }
    process(str, i + 1);    //要当前字符
    char tmp = str[i];
    str[i] = 0;
    process(str, i + 1);    // 不要当前字符
    str[i] = tmp;
}

// 打印一个字符串的全排列
void swap(string str, int i, int j) {
    char tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
}
void process1(string str, int i, list<string> res) {
    if (i == str.size()) {
        res.push_back(str);
    }
    vector<bool> visit;
    for (int j = i; j < str.size(); j++) {
        if (!visit[str[j] - 'a']) {
            visit[str[j] - 'a'] = true;
            swap(str, i, j);
            process1(str, i + 1, res);
            swap(str, i, j);
        }
    }
}

// 纸牌游戏
// 先手
int f(vector<int>& arr, int i, int j) {
    if (i == j) {
        return arr[i];
    }
    return max(arr[i] + s(arr, i + 1, j), arr[j] + s(arr, j, j - 1));
}
// 后手
int s(vector<int>& arr, int i, int j) {
    if (i == j) {
        return 0;
    }
    return min(f(arr, i + 1, j), f(arr, i, j - 1));
}
int win1(vector<int>& arr) {
    if (arr.size() < 1) {
        return 0;
    }
    return max(f(arr, 0, arr.size() - 1), s(arr, 0, arr.size() - 1));
}

// 逆序栈
void reverse(stack<int> s) {
    if (s.empty()) {
        return;
    }
    int i = f(s);
    reverse(s);
    s.push(i);
}
int f(stack<int> s) {
    int result = s.top();
    s.pop();
    if (s.empty()) {
        return result;
    }
    else {
        int last = f(s);
        s.push(result);
        return last;
    }
}

// 字符串转化
// i 之前的位置如何转化已经做过决定
// i... 有多少种转化的结果
int process2(string str, int i) {
    if (i == str.size()) {
        return 1;
    }
    if (str[i] == '0') {
        return 0;
    }
    if (str[i] == '1') {
        int res = process2(str, i + 1);     // i 自己作为单独的部分，后续有多少种方法
        if (i + 1 < str.size()) {
            res += process2(str, i + 2);    // i 和 i+1 作为单独的部分
        }
        return res;
    }
    if (str[i] == '2') {
        int res = process2(str, i + 1);
        // i 和 i+1 作为单独的部分且不超过26
        if (i + 1 < str.size() && (str[i + 1] >= '0' && str[i + 1] <= '6')) {
            res += process2(str, i + 2);
        }
        return res;
    }
    // str[i] == '3' ~ '9'
    return process2(str, i + 1);
}

// 装物品
// i... 的货物自由选择，形成的最大价值返回
int process3(vector<int>& weights, vector<int>& values, int i, int alreadyweight, int bag) {
    if (alreadyweight > bag) {
        return 0;
    }
    if (i == weights.size()) {
        return 0;
    }
    return max(process3(weights, values, i + 1, alreadyweight, bag),
        values[i] + process3(weights, values, i + 1, alreadyweight + weights[i], bag));
}

// N皇后问题
bool isVaild(vector<int>& record, int i, int j) {
    for (int k = 0; k < i; k++) {
        if (j == record[k] || abs(record[k] - j) == abs(i - k)) {
            return false;
        }
    }
    return true;
}
// record[0,...,i-1] 的皇后，任何两个皇后一定不共行、不共列、不共斜线
// 目前来到了第 i 行
// record[0,...,i-1] 表示之前的行，放过了哪些皇后
// n 代表整体一共有多少行
// res 表示摆完所有的皇后，合理的摆法有多少种
int process1(int i, vector<int>& record, int n) {
    if (i == n) {   // 终止行：最后一行再下一行的位置
        return 1;
    }
    int res = 0;
    for (int j = 0; j < n; j++) {
        // 当前i行的皇后，放在j列，会不会和之前(0...i-1)的皇后共行、共列或共斜线
        if (isVaild(record, i, j)) {
            record[i] = j;
            res += process1(i + 1, record, n);
        }
    }
    return res;
}
int num1(int n) {
    if (n < 1) {
        return 0;
    }
    vector<int> record; // record[i] -> 第i行的皇后，放在了第几列
    return process1(0, record, n);
}
// 常数时间的优化，使用位运算
// colLim 列的限制，1的位置不能放皇后，0的位置可以
// leftDiaLim 左斜线的限制
// rightDiaLim 右斜线的限制
int process2(int limit, int colLim, int leftDiaLim, int rightDiaLim) {
    if (colLim == limit) {  // base case
        return 1;
    }
    int pos = 0;
    int mostRightOne = 0;
    // 所有候选皇后的位置都在pos上
    pos = limit & (~(colLim | rightDiaLim | leftDiaLim));
    int res = 0;
    while (pos != 0) {
        mostRightOne = pos & (~pos + 1);
        pos = pos - mostRightOne;
        res += process2(limit,
            colLim | mostRightOne,
            (leftDiaLim | mostRightOne) << 1,
            (rightDiaLim | mostRightOne) >> 1);
    }
    return res;
}
// 请不要超过32皇后问题
int num2(int n) {
    if (n < 1 || n > 32) {
        return 0;
    }
    // 生成二进制的数，8皇后问题，后8为是1
    int limit = n == 32 ? -1 : (1 << n) - 1;
    return process2(limit, 0, 0, 0);
}

int main()
{
    hanoi(3);
    return 0;
}