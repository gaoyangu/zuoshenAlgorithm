#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
using namespace std;

// 岛问题
int countIslands(vector<vector<int>>& m){
    if(m.size() < 1 || m[0].size() < 1){
        return 0;
    }
    int N = m.size();
    int M = m[0].size();
    int res = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(m[i][j] == 1){
                res++;
                infect(m, i, j, N, M);
            }
        }
    }
}
void infect(vector<vector<int>>& m, int i, int j, int N, int M){
    if(i < 0 || i >= N || j < 0 || j > M || m[i][j] == 1){
        return;
    }
    m[i][j] = 2;
    infect(m, i + 1, j, N, M);
    infect(m, i - 1, j, N, M);
    infect(m, i, j + 1, N, M);
    infect(m, i, j - 1, N, M);
}

// 并查集
template <typename V>
class Element {
public:
    Element(V v) : value(v) {}
    V value;
};

template <typename V>
class UnionFindSet {
public:
    UnionFindSet(list<V> l) {
        for (V value : l) {
            Element<V> element = new Element<V>(value);
            elementMap.insert(value, element);
            fatherMap.insert(element, element);
            sizeMap.insert(element, 1);
        }
    }

    // 给定一个ele，往上一直找，把代表元素返回
    Element<V> findHead(Element<V> element) {
        stack<Element<V>> path;
        while (element != fatherMap.at(element)){
            path.push(element);
            element = fatherMap.at(element);
        }
        while (!path.empty()) {
            fatherMap.insert(path.top(), element);
            path.pop();
        }
        return element;
    }

    bool isSameSet(V a, V b) {
        if (elementMap.find(a) != elementMap.end() && elementMap.find(b) != elementMap.end()) {
            return findHead(elementMap.at(a)) == findHead(elementMap.at(b));
        }
        return false;
    }

    void unionSet(V a, V b) {
        if (elementMap.find(a) != elementMap.end() && elementMap.find(b) != elementMap.end()) {
            Element<V> aF = findHead(elementMap.at(a));
            Element<V> bF = findHead(elementMap.at(b));
            if (aF != bF) {
                Element<V> big = sizeMap.at(aF) >= sizeMap.at(bF) ? aF : bF;
                Element<V> small = big == aF ? bF : aF;
                fatherMap.insert(small, big);
                sizeMap.insert(big, sizeMap.at(aF) + sizeMap.at(bF));
                sizeMap.erase(small);
            }
        }
    }

    unordered_map<V, Element<V>> elementMap;
    // key: 某个元素，value: 该元素的父
    unordered_map<Element<V>, Element<V>> fatherMap;
    // key: 某个集合的代表元素，value: 该集合的大小
    unordered_map<Element<V>, int> sizeMap;
};








