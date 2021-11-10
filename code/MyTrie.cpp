#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

class TrieNode{
public:
    TrieNode(){
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

    int pass;   //节点通过了多少次
    int end;    //是多少个字符串的结尾节点
    vector<TrieNode*> nexts;
    // 字符类型很多时
    //unordered_map<char, TrieNode*> nexts; 
    //map<char, TrieNode*> nexts;
};

class Trie{
public:
    TrieNode* root;

    Trie(){
        root = new TrieNode();
    }

    void insertWord(string word){
        if(word.size() < 1){
            return;
        }
        TrieNode* node = root;
        node->pass++;
        int index = 0;
        for(auto ch : word){
            index = ch - 'a';
            if(node->nexts[index] == nullptr){
                node->nexts[index] = new TrieNode();
            }
            node = node->nexts[index];
            node->pass++;
        }
        node->end++;
    }

    // word 这个单词之前加入过了几次
    int searchWord(string word){
        if(word.size() < 1){
            return;
        }
        TrieNode* node = root;
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
        if(pre.size() < 1){
            return 0;
        }
        TrieNode* node = root;
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
            TrieNode* node = root;
            node->pass--;
            int index = 0;
            for(auto ch : word){
                index = ch - 'a';
                if(--node->nexts[index]->pass == 0){
                    node->nexts[index] = nullptr;   
                    // todo: 内存管理
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
    bool operator()(Program& p1, Program& p2){
        return p1.end < p2.end;
    }
};
int bestArrange(vector<Program*>& programs, int timePoint){
    sort(programs.begin(), programs.end(), ProgramComparator());
    int result = 0;
    // 从左往右依次遍历所有的会议
    for(int i = 0; i < programs.size(); i++){
        if(timePoint <= programs[i]->start){
            result++;
            timePoint = programs[i]->end;
        }
    }
    return result;
}

// 贪心算法 - 字符串最小字典序
class MyComparator{
public:
    bool operator()(string& p1, string& p2){
        return p1 + p2 <= p2 + p1;
    }
};
string lowestString(vector<string>& strs){
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

int main()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    cout << lessMoney(v) << endl;
    return 0;
}
