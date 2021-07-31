#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

class TireNode{
public:
    TireNode(){
        pass = 0;
        end = 0;
        for(int i = 0; i < 26; i++){
            // next[0] == nullptr   没有走向'a'的路
            // next[0] != nullptr   有走向'a'的路
            // ...
            // next[25] != nullptr   有走向'z'的路
            nexts.push_back(nullptr);
        }
    }

    int pass;
    int end;
    vector<TireNode*> nexts;
};

class Tire{
public:
    Tire(){
        root = new TireNode();
    }

    TireNode* root;

    void insertWord(string word){
        if(word.empty()){
            return;
        }
        TireNode* node = root;
        node->pass++;
        int index = 0;
        for(auto ch : word){
            index = ch - 'a';
            if(node->nexts[index] == nullptr){
                node->nexts[index] = new TireNode();
            }
            node = node->nexts[index];
            node->pass++;
        }
        node->end++;
    }

    // word 这个单词之前加入过了几次
    int searchWord(string word){
        if(word.empty()){
            return 0;
        }
        TireNode* node = root;
        int index = 0;
        for(auto ch : word){
            index = ch - 'a';
            if(node->nexts[index] == nullptr){
                return 0;
            }
            node = node->nexts[index];
        }
        return node->end;
    }

    // 所有加入的字符串中，有几个是以 pre 这个字符串作为前缀的
    int prefixNumber(string pre){
        if(pre.empty()){
            return 0;
        }
        TireNode* node = root;
        int index = 0;
        for(auto ch : pre){
            index = ch - 'a';
            if(node->nexts[index] == nullptr){
                return 0;
            }
            node = node->nexts[index];
        }
        return node->pass;
    }

    void deleteWord(string word){
        if(searchWord(word) != 0){
            TireNode* node = root;
            node->pass--;
            int index = 0;
            for(auto ch : word){
                index = ch - 'a';
                if(--node->nexts[index]->pass == 0){
                    node->nexts[index] = nullptr;   // todo
                    return;
                }
                node = node->nexts[index];
            }
            node->end--;
        }
    }
};

// 贪心算法 - 会议安排
class Program{
public:
    Program(int s, int e) : start(s), end(e) { }

    int start;
    int end;
};
// 谓词
class ProgramComparator{
public:
    bool operator()(Program & p1, Program & p2){
        return p1.end < p2.end;
    }
};
int bestArrange(vector<Program> & programs, int timePoint){
    sort(programs.begin(), programs.end(), ProgramComparator());
    int result = 0;
    for(int i = 0; i < programs.size(); i++){
        if(timePoint <= programs[i].start){
            result++;
            timePoint = programs[i].end;
        }
    }
    return result;
}

// 贪心算法 - 字符串最小字典序
class MyComparator{
public:
    bool operator()(string & p1, string & p2){
        return p1 < p2;
    }
};
string lowestString(vector<string> & strs){
    if(strs.size() < 1){
        return "";
    }
    sort(strs.begin(), strs.end(), MyComparator());
    string res;
    for(int i = 0; i < strs.size(); i++){
        res += strs[i];
    }
    return res;
}

// 分金条
int lessMoney(vector<int>& arr) {
    priority_queue<int, vector<int>, greater<int>> pQ(arr.begin(), arr.end());
    int sum = 0;
    int cur = 0;
    while (pQ.size() > 1) {
        int cur1 = pQ.top();
        pQ.pop();
        cout << cur1 << endl;

        int cur2 = pQ.top();
        pQ.pop();
        cout << cur2 << endl;

        cur = cur1 + cur2;
        sum += cur;
        pQ.push(cur);
    }
    return sum;
}

// 做任务，得利润
class Node {
public:
    Node(int p, int c) : profit(p), cost(c){ }
    int profit;
    int cost;
};
class MinCostComparator {
public:
    bool operator()(Node* o1, Node* o2) {
        return o1->cost > o2->cost;
    }
};
class MinProfitComparator {
public:
    bool operator()(Node* o1, Node* o2) {
        return o1->profit < o2->profit;
    }
};
// k: 最多做k个项目，w: 初始资金
int findMaxCapital(int k, int w, vector<int>& Profits, vector<int>& Capital) {
    priority_queue<Node*, vector<Node*>, MinCostComparator> minCostQ;
    priority_queue<Node*, vector<Node*>, MinProfitComparator> maxProfitQ;
    // 所有项目放在被锁池中，根据 cost 组织的小根堆
    for (int i = 0; i < Profits.size(); i++) {
        minCostQ.push(new Node(Profits[i], Capital[i]));
    }
    for (int i = 0; i < k; i++) {
        // 能力所及的项目，全解锁
        while (!minCostQ.empty() && minCostQ.top()->cost <= w) {
            maxProfitQ.push(minCostQ.top());
            minCostQ.pop();
        }
        if (maxProfitQ.empty()) {
            return w;
        }
        w += maxProfitQ.top()->profit;
        maxProfitQ.pop();
    }
    return w;
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
int process1(int i, vector<int> & record, int n){
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
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    cout << lessMoney(v) << endl;
    return 0;
}
