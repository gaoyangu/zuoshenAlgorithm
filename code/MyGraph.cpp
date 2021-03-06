#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <list>
#include <set>

using namespace std;

class Node{// 点
public:
    Node(int val, int i = 0, int o = 0) : value(val), in(i), out(o) { }

    int value;  // 点上的值
    int in;     // 点的入度
    int out;    // 点的出度
    vector<Node*> nexts;    // 直接邻居
    vector<Edge*> edges;    // 属于点的边
};

class Edge{// 边
public:
    Edge(int w, Node* f, Node* t) : weight(w), from(f), to(t) { }

    int weight;
    Node* from;
    Node* to;
};

class Graph{// 图
public:
    unordered_map<int, Node*> nodes;    // 点集
    unordered_set<Edge*> edges;         // 边集
};


// 结构转化
// [from, to, weight]
Graph creatGraph(vector<vector<int>>& matrix){
    Graph graph;
    for(int i = 0; i < matrix.size(); i++){
        int from = matrix[i][0];
        int to = matrix[i][1];
        int weight = matrix[i][2];
        if(graph.nodes.find(from) == graph.nodes.end()){
            graph.nodes.insert(pair<int, Node*>(from, new Node(from)));
        }
        if(graph.nodes.find(to) == graph.nodes.end()){
            graph.nodes.insert(pair<int, Node*>(to, new Node(to)));
        }
        Node* fromNode = graph.nodes.at(from);
        Node* toNode = graph.nodes.at(to);
        Edge* newEdge = new Edge(weight, fromNode, toNode);
        fromNode->nexts.push_back(toNode);
        fromNode->out++;
        toNode->in++;
        fromNode->edges.push_back(newEdge);
        graph.edges.insert(newEdge);
    }
    return graph;
}


// 图的宽度优先遍历
void bfsGraph(Node* node){
    if(node == nullptr){
        return;
    }
    queue<Node*> q;
    unordered_set<Node*> s; // 保证不要重复进队列
    q.push(node);
    s.insert(node);
    while (!q.empty()){
        Node* cur = q.front();
        q.pop();
        cout << cur->value << " ";
        for(Node* next : cur->nexts){
            if(s.find(next) == s.end()){
                s.insert(next);
                q.push(next);
            }
        }
    }
}


// 图的深度优先遍历
// 入栈时处理
void dfsGraph(Node* node){
    if(node == nullptr){
        return;
    }
    stack<Node*> sT;
    unordered_set<Node*> s;
    sT.push(node);
    s.insert(node);
    cout << node->value << " ";
    while (!sT.empty()){
        Node* cur = sT.top();
        sT.pop();
        for(Node* next : cur->nexts){
            if(s.find(next) == s.end()){
                sT.push(cur);
                sT.push(next);
                s.insert(next); 
                cout << next->value << " ";
                break;
            }
        }
    }
}


// 拓扑排序
list<Node*> sortedTopology(Graph graph){
    // key: 某一个node
    // value: 剩余的入度
    unordered_map<Node*, int> inMap;
    // 入度为0的点，才能进这个队列
    queue<Node*> zeroInQueue;
    for(int i = 0; i < graph.nodes.size(); i++){
        Node* node = graph.nodes.at(i);
        inMap.insert(pair<Node*, int>(node, node->in));
        if(node->in == 0){
            zeroInQueue.push(node);
        }
    }
    // 拓扑排序的结果，依次加入result
    list<Node*> result;
    while (!zeroInQueue.empty()){
        Node* cur = zeroInQueue.front();
        zeroInQueue.pop();
        result.push_back(cur);
        for(Node* next : cur->nexts){
            inMap.insert(pair<Node*, int>(next, inMap.at(next) - 1));
            if(inMap.at(next) == 0){
                zeroInQueue.push(next);
            }
        }
    }
    return result;
}


// 最小生成树
class MySets{
public:
    MySets(list<Node*> nodes){
        // !!! 错误代码，待修正
        for(Node* cur : nodes){
            list<Node*> s;
            s.push_back(cur);
            setMap.insert(pair<Node*, list<Node*>>(cur, s));
        }
    }

    bool isSameSet(Node* from, Node* to){
        list<Node*> fromSet = setMap.at(from);
        list<Node*> toSet = setMap.at(to);
        return fromSet == toSet;
    }

    void unionSet(Node* from, Node* to){
        list<Node*> fromSet = setMap.at(from);
        list<Node*> toSet = setMap.at(to);
        for(Node* toNode : toSet){
            fromSet.push_back(toNode);
            setMap.insert(pair<Node*, list<Node*>>(toNode, fromSet));
        }
    }

    unordered_map<Node*, list<Node*>> setMap;
};
// kruskal算法
class EdgeComparator {
public:
    bool operator()(Edge* e1, Edge* e2) {
        return e1->weight > e2->weight;
    }
};
set<Edge*> kruskalMST(Graph graph) {
    list<Node*> lTmp;
    for (int i = 0; i < graph.nodes.size(); i++) {
        lTmp.push_back(graph.nodes.at(i));
    }
    MySets mysets(lTmp);
    priority_queue<Edge*, vector<Edge*>, EdgeComparator> q;
    for (Edge* edge : graph.edges) {
        q.push(edge);
    }
    set<Edge*> result;
    while (!q.empty()) {
        Edge* e = q.top();
        q.pop();
        if (!mysets.isSameSet(e->from, e->to)) {
            result.insert(e);
            mysets.unionSet(e->from, e->to);
        }
    }
    return result;
}
// prim 算法
set<Edge*> primMST(Graph graph) {
    priority_queue<Edge*, vector<Edge*>, EdgeComparator> q;
    vector<Node*> vNode;
    unordered_set<Node*> s;
    set<Edge*> result;      // 依次挑选的边放在result中
    for (int i = 0; i < graph.nodes.size(); i++) {
        vNode.push_back(graph.nodes.at(i));
    }
    for (Node* node : vNode) {   // 处理森林问题：不是连通图
        // 随便挑一个点
        if (s.find(node) == s.end()) {
            s.insert(node);
            for (Edge* edge : node->edges) {  // 由一个点，解锁所有相连的边
                q.push(edge);
            }
            while (!q.empty()) {
                Edge* edge = q.top();  // 弹出解锁的边中最小的边
                q.pop();
                Node* toNode = edge->to;    // 可能的一个新的点
                if (s.find(toNode) == s.end()) {  // 不包含的时候就是新的点
                    s.insert(toNode);
                    result.insert(edge);
                    for (Edge* newEdge : toNode->edges) {
                        q.push(newEdge);
                    }
                }
            }
        }
    }
    return result;
}


// Dijkstra算法
Node* getMinDistanceAndUnselectedNode(unordered_map<Node*, int> distaceMap, unordered_set<Node*> touchedNodes) {
    Node* minNode = nullptr;
    int minDistance = INTMAX_MAX;
    for (pair<Node*, int> entry : distaceMap) {
        Node* node = entry.first;
        int distance = entry.second;
        if (touchedNodes.find(node) == touchedNodes.end() && distance < minDistance) {
            minNode = node;
            minDistance = distance;
        }
    }
    return minNode;
}
unordered_map<Node*, int> dijkstral(Node* head) {
    // key: 从head出发到达key
    // value: 从head出发到达key的最小距离
    unordered_map<Node*, int> distanceMap;
    distanceMap.insert(pair<Node*, int>(head, 0));
    // 已经求过距离的节点放在selectedNodes中，以后再也不碰
    unordered_set<Node*> selectedNodes;
    Node* minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);
    while (minNode != nullptr) {
        int distance = distanceMap.at(minNode);
        for (Edge* edge : minNode->edges) {
            Node* toNode = edge->to;
            if (distanceMap.find(toNode) == distanceMap.end()) {
                distanceMap.insert(pair<Node*, int>(toNode, distance + edge->weight));
            }
            distanceMap.insert(pair<Node*, int>(toNode, min(distanceMap.at(toNode), distance + edge->weight)));
        }
        selectedNodes.insert(minNode);
        minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);
    }
    return distanceMap;
}
// 使用堆优化 Dijkstra算法
class NodeRecord{
public:
    NodeRecord(Node* n, int dis) : node(n), distance(dis) {}
    Node* node;
    int distance;
};
class NodeHeap{
public:
    NodeHeap(int s) : size(0) {}

    bool isEmpty(){
        return size == 0;
    }
    bool isEntered(Node* node){
        return heapIndexMap.find(node) != heapIndexMap.end();
    }
    bool inHeap(Node* node){
        return isEntered(node) && heapIndexMap.at(node) != -1;
    }
    void swap(int index1, int index2){
        heapIndexMap.at(nodes[index1]) = index2;
        heapIndexMap.at(nodes[index2]) = index1;
        Node* tmp = nodes[index1];
        nodes[index1] = nodes[index2];
        nodes[index2] = tmp;
    }
    void insertHeapify(Node* node, int index){
        while (distanceMap.at(nodes[index]) < distanceMap.at(nodes[(index - 1)/2])){
            swap(index, (index - 1) / 2);
            index = (index - 1) / 2;
        }
    }
    void heapify(int index, int size){
        int left = index * 2 + 1;
        while (left < size){
            int smallest = left + 1 < size && distanceMap.at(nodes[left + 1]) < distanceMap.at(nodes[left]) ? left + 1 : left;
            smallest = distanceMap.at(nodes[smallest]) < distanceMap.at(nodes[index]) ? smallest : index;
            if(smallest == index){
                break;
            }
            swap(smallest, index);
            index = smallest;
            left = index * 2 + 1;
        }
    }
    void addOrUpdateOrIgnore(Node* node, int distance){ 
        if(inHeap(node)){
            distanceMap.at(node) = min(distanceMap.at(node), distance);
            insertHeapify(node, heapIndexMap.at(node));
        }
        if(!isEntered(node)){
            nodes[size] = node;
            heapIndexMap.at(node) = size;
            distanceMap.at(node) = distance;
            insertHeapify(node, size++);
        }
    }
    NodeRecord* pop(){
        NodeRecord* nodeRecord = new NodeRecord(nodes[0], distanceMap.at(nodes[0]));
        swap(0, size - 1);
        heapIndexMap.at(nodes[size - 1]) = -1;
        distanceMap.erase(nodes[size - 1]);
        nodes.erase(nodes.begin() + size - 1);
        heapify(0, --size);
        return nodeRecord;
    }

    vector<Node*> nodes;
    unordered_map<Node*, int> heapIndexMap;
    unordered_map<Node*, int> distanceMap;
    int size;
};
unordered_map<Node*, int> dijkstralwithHeap(Node* head, int size){
    NodeHeap* nodeheap = new NodeHeap(size);
    nodeheap->addOrUpdateOrIgnore(head, 0);
    unordered_map<Node*, int> result;
    while(!nodeheap->isEmpty()){
        NodeRecord* record = nodeheap->pop();
        Node* cur = record->node;
        int distance = record->distance;
        for(Edge* edge : cur->edges){
            nodeheap->addOrUpdateOrIgnore(edge->to, edge->weight + distance);
        }
        result.insert(pair<Node*, int>(cur, distance));
    }
    return result;
}