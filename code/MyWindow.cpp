#include <iostream>
#include <vector>
#include <list>
using namespace std;

class WindowMax{
public:
    WindowMax(vector<int> a){
        arr = a;
        L = -1;
        R = 0;
    }
    void addNumFromRight(){
        if(R == arr.size()){
            return;
        }
        while (!qmax.empty() && arr[qmax.back()] <= arr[R]){
            qmax.pop_back();
        }
        qmax.push_back(R);
        R++;   
    }
    void removeNumFromLeft(){
        if(L >= R - 1){
            return;
        }
        L++;
        if(qmax.front() == L){
            qmax.pop_front();
        }
    }
    int getMax(){
        if(!qmax.empty()){
            return arr[qmax.front()];
        }
        return NULL;
    }
private:
    int L;
    int R;
    vector<int> arr;
    list<int> qmax;
};

vector<int> getMaxWindow(vector<int> arr, int w){
    if(arr.size() == 0 || w < 1 || arr.size() < w){
        return {};
    }
    list<int> qmax;
    vector<int> res;
    for(int i = 0; i < arr.size(); i++){
        while(!qmax.empty() && arr[qmax.back()] <= arr[i]){
            qmax.pop_back();
        }
        qmax.push_back(arr[i]);
        if(qmax.front() == i - w){
            qmax.pop_front();
        }
        if(i >= w - 1){ // 窗口形成
            res.push_back(arr[qmax.front()]);
        }
    }
    return res;
}