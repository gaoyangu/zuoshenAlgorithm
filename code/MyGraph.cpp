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
Graph creatGraph(vector<vector<int>> & matrix){
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
void bfs(Node* node){
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
void dfs(Node* node){
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
class EdgeComparator{
public:
    bool operator()(Edge* e1, Edge* e2){
        return e1->weight > e2->weight;
    }
};
set<Edge*> kruskalMST(Graph graph){
    list<Node*> ltmp;
    for(int i = 0; i < graph.nodes.size(); i++){
        ltmp.push_back(graph.nodes.at(i));
    }
    MySets mysets(ltmp);
    // vector<Edge*> v;
    priority_queue<Edge*, vector<Edge*>, EdgeComparator()> p;
    for(Edge* edge : graph.edges){
        p.push(edge);
    }
    set<Edge*> result;
    while(!p.empty()){
        Edge* e = p.top();
        p.pop();
        if(!mysets.isSameSet(e->from, e->to)){
            result.insert(e);
            mysets.unionSet(e->from, e->to);
        }
    }
    return result;
}
// prim 算法
set<Edge*> primMST(Graph graph){
    // vector<Edge*> v;
    priority_queue<Edge*, vector<Edge*>, EdgeComparator()> p;
    vector<Node*> vN;
    unordered_set<Node*> s;
    set<Edge*> result;      // 依次挑选的边放在result中
    for(int i = 0; i < graph.nodes.size(); i++){
        vN.push_back(graph.nodes.at(i));
    }
    for(Node* node : vN){   // 随便挑一个点
        if(s.find(node) == s.end()){
            s.insert(node);
            for(Edge* edge : node->edges){  // 由一个点，解锁所有相连的边
                p.push(edge);
            }
            while(!p.empty()){
                Edge* edge = p.top();  // 弹出解锁的边中最小的边
                p.pop();
                Node* toNode = edge->to;    // 可能的一个新的点
                if(s.find(toNode) == s.end()){  // 不包含的时候就是新的点
                    s.insert(toNode);
                    result.insert(edge);
                    for(Edge* newEdge : toNode->edges){
                        p.push(newEdge);
                    }
                }
            }
        }
    }
    return result;
}

// Dijkstra算法
Node* getMinDistanceAndUnselectedNode(
        unordered_map<Node*, int> distaceMap, 
        unordered_set<Node*> touchedNodes){
    Node* minNode;
    int minDistance = INTMAX_MAX;
    for(pair<Node*, int> entry : distaceMap){
        Node* node = entry.first;
        int distance = entry.second;
        if(touchedNodes.find(node) == touchedNodes.end() && distance < minDistance){
            minNode = node;
            minDistance = distance;
        }
    }
    return minNode;
}
unordered_map<Node*, int> dijkstral(Node* head){
    // key: 从head出发到达key
    // value: 从head出发到达key的最小距离
    unordered_map<Node*, int> distanceMap;
    distanceMap.insert(pair<Node*, int>(head, 0));
    // 已经求过距离的节点放在selectedNodes中，以后再也不碰
    unordered_set<Node*> selectedNodes;
    Node* minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);
    while (minNode != nullptr){
        int distance = distanceMap.at(minNode);
        for(Edge* edge : minNode->edges){
            Node* toNode = edge->to;
            if(distanceMap.find(toNode) == distanceMap.end()){
                distanceMap.insert(pair<Node*, int>(toNode, distance + edge->weight));
            }
            distanceMap.insert(pair<Node*, int>(toNode, min(distanceMap.at(toNode), distance + edge->weight)));
        }
        selectedNodes.insert(minNode);
        minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNodes);
    }
    return distanceMap;
}