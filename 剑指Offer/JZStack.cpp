#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 剑指 Offer 09. 用两个栈实现队列
class CQueue {
    stack<int> sIn;
    stack<int> sOut;
public:
    CQueue() {
        while(!sIn.empty()){
            sIn.pop();
        }
        while(!sOut.empty()){
            sOut.pop();
        }
    }
    
    void appendTail(int value) {
        sIn.push(value);
    }
    
    int deleteHead() {
        if(sOut.empty()){
            while(!sIn.empty()){
                sOut.push(sIn.top());
                sIn.pop();
            }
        }
        if(sOut.empty()){
            return -1;
        }else{
            int ret = sOut.top();
            sOut.pop();
            return ret;
        }
    }
};


// 剑指 Offer 30. 包含min函数的栈
class Solution30 {
public:
    void push(int value) {
        if(stack1.empty()){
            stack1.push(value);
            stack2.push(value);
        }else{
            stack1.push(value);
            stack2.push(value < stack2.top() ? value : stack2.top());
        }
    }
    void pop() {
        stack1.pop();
        stack2.pop();
    }
    int top() {
        return stack1.top();
    }
    int min() {
        return stack2.top();
    }
private:
    stack<int> stack1;
    stack<int> stack2;
};

// 剑指 Offer 31. 栈的压入、弹出序列
class Solution31 {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        stack<int> s;
        int i = 0;
        for(int num : pushV){
            s.push(num);
            while(!s.empty() && s.top() == popV[i]){
                s.pop();
                i++;
            }
        }
        return s.empty();
    }
};
