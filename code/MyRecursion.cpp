#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <stack>
using namespace std;

// n 层汉诺塔问题
// leetcode
void hanota(vector<int>& A, vector<int>& B, vector<int>& C) {
    int n = A.size();
    process(n, A, C, B);
}
void process(int n, vector<int>& from, vector<int>& to, vector<int>& other){
    if(n == 1){
        to.push_back(from.back());
        from.pop_back();
        return;
    }
    process(n - 1, from, other, to);
    to.push_back(from.back());
    from.pop_back();
    process(n - 1, other, to, from);
}
// 打印方式
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
void swap(string& s, int i, int j) {
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
}
vector<string> permutation(string s) {
    vector<string> res;
    process(s, 0, res);
    return res;
}
// str[i...]范围上，所有的字符，都可以在i位置上，后续都去尝试
// str[0...i-1]范围上，是之前做的选择
// res: 所有的结果
void process(string s, int i, vector<string>& res) {
    if (i == s.size()) {
        res.push_back(s);
        return;
    }
    vector<bool> visit;
    for(int k = 0; k < 26; k++){
        visit.push_back(false);
    }
    for (int j = i; j < s.size(); j++) {
        if(!visit[s[j] - 'a']){ // 分支限界，指标上没有优化，常数项有优化
            visit[s[j] - 'a'] = true;
            swap(s, i, j);
            process(s, i + 1, res);
            swap(s, i, j);
        }  
    }
}


// 纸牌游戏
// 先手
int f(vector<int>& arr, int i, int j) {
    if (i == j) {
        return arr[i];
    }
    return max(arr[i] + s(arr, i + 1, j), arr[j] + s(arr, i, j - 1));
}
// 后手
int s(vector<int>& arr, int i, int j) {
    if (i == j) {
        return 0;
    }
    return min(f(arr, i + 1, j), f(arr, i, j - 1));
}
int win(vector<int>& arr) {
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
int translateNum(int num) {
    string str = to_string(num);
    return process(str, 0);
}
int process(string str, int i){
    if(i == str.size() ){
        return 1;
    }
    if(str[i] == '1'){
        int res = process(str, i+1);    // i 自己作为单独的部分，后续有多少种方法
        if(i+1 < str.size()){
            res += process(str, i+2);   // i 和 i+1 作为单独的部分
        }
        return res;
    }
    if(str[i] == '2'){
        int res = process(str, i+1);
        // i 和 i+1 作为单独的部分且不超过25
        if(i+1 < str.size() && (str[i+1] >= '0' && str[i+1] < '6')){
            res += process(str, i+2);
        }
        return res;
    }
    //str[i] == '0' || '3' ~ '9'
    return process(str, i+1);
}


// 装物品
// i... 的货物自由选择，形成的最大价值返回
int process(vector<int>& weights, vector<int>& values, int i, int alreadyweight, int bag) {
    if (alreadyweight > bag) {
        return 0;
    }
    if (i == weights.size()) {
        return 0;
    }
    return max(process(weights, values, i + 1, alreadyweight, bag),
        values[i] + process(weights, values, i + 1, alreadyweight + weights[i], bag));
}


// N皇后问题
int totalNQueens(int n) {
    vector<int> record; // record[i] -> 第i行的皇后，放在了第几列
    for(int i = 0; i < n; i++){
        record.push_back(-1);
    }
    return process(record, 0, n);
}
// record[0,...,i-1] 的皇后，任何两个皇后一定不共行、不共列、不共斜线
// 目前来到了第 i 行
// record[0,...,i-1] 表示之前的行，放过了哪些皇后
// n 代表整体一共有多少行
// res 表示摆完所有的皇后，合理的摆法有多少种
int process(vector<int>& record, int i, int n){
    if(i == n){ // 终止行：最后一行再下一行的位置
        return 1;
    }
    int res = 0;
    for(int j = 0; j < n; j++){
        if(isVaild(record, i, j)){
            record[i] = j;
            res += process(record, i+1, n);
        }
    }
    return res;
}
// 当前i行的皇后，放在j列，会不会和之前(0...i-1)的皇后共行、共列或共斜线
bool isVaild(vector<int>& record, int i, int j){
    for(int k = 0; k < i; k++){
        if(j == record[k] || abs(record[k] - j) == abs(i - k)){
            return false;
        }
    }
    return true;
}

// 常数时间的优化，使用位运算
// colLim 列的限制，1的位置不能放皇后，0的位置可以
// leftDiaLim 左斜线的限制
// rightDiaLim 右斜线的限制
int process(int limit, int colLim, int leftDiaLim, int rightDiaLim) {
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
        res += process(limit,
            colLim | mostRightOne,
            (leftDiaLim | mostRightOne) << 1,
            (rightDiaLim | mostRightOne) >> 1);
    }
    return res;
}
// 请不要超过32皇后问题
int totalNQueens(int n) {
    if (n < 1 || n > 32) {
        return 0;
    }
    // 生成二进制的数，8皇后问题，后8为是1
    int limit = n == 32 ? -1 : (1 << n) - 1;
    return process(limit, 0, 0, 0);
}

int main()
{
    hanoi(3);
    return 0;
}