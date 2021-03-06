#include <iostream>
#include <vector>
using namespace std;

// KMP
vector<int> getNextArray(string ms) {
    if (ms.size() == 1) {
        return { -1 };
    }
    vector<int> next;
    next[0] = -1;
    next[1] = 0;
    int i = 2;  // next 数组的位置
    int cn = 0; // 拿哪个位置的字符和i-1位置的字符比较
    while (i < next.size()) {
        if (ms[i - 1] == ms[cn]) {
            next[i++] = ++cn;
        }
        else if (cn > 0) {
            cn = next[cn];
        }
        else {
            next[i++] = 0;
        }
    }
    return next;
}
int getIndexOf(string s, string m) {
    if (s.size() < 1 || m.size() < 1 || s.size() < m.size()) {
        return -1;
    }
    int i1 = 0;
    int i2 = 0;
    vector<int> next = getNextArray(m); // O(M)    
    while (i1 < s.size() && i2 < m.size()) { // O(N)
        if (s[i1] == m[i2]) {
            i1++;
            i2++;
        }
        else if (next[i2] == -1) { // i2 == 0
            i1++;
        }
        else {
            i2 = next[i2];
        }
    }
    // i1越界 或者 i2越界
    return i2 == m.size() ? i1 - i2 : -1;
}

// Manacher
string manacherString(string str) {
    string res;
    int size = str.size() * 2 + 1;
    int index = 0;
    for (int i = 0; i < size; i++) {
        char c = (i & 1) == 0 ? '#' : str[index++];
        res.push_back(c);
    }
    return res;
}
int maxLcpsLength(string s) {
    if (s.size() < 1) {
        return 0;
    }
    string str = manacherString(s); // 1221 -> #1#2#2#1#
    vector<int> pArr;   // 回文半径数组
    int C = -1; // 中心
    int R = -1; // 最右回文右边界再往右一个位置
    int m = INTMAX_MIN;
    for (int i = 0; i < str.size(); i++) {
        // i 至少的回文区域 
        int tmp = R > i ? min(pArr[2 * C - i], R - i) : 1;
        pArr.push_back(tmp);
        while (i + pArr[i] < str.size() && i - pArr[i] > -1) {
            // 是否向外扩
            if (str[i + pArr[i]] == str[i - pArr[i]]) {
                pArr[i]++;
            }
            else {
                break;
            }
        }
        if (i + pArr[i] > R) {
            R = i + pArr[i];
            C = i;
        }
        m = max(m, pArr[i]);
    }
    return m - 1;
}

int main()
{
    string s("1221");
    cout << manacherString(s) << endl;
    cout << maxLcpsLength(s) << endl;
    cin.get();
}