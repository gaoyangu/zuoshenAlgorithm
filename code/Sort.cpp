#include <iostream>
#include <vector>
using namespace std;

void swap(vector<int> & arr, int i, int j)
{
   int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp; 
}

//选择排序
void selectionSort(vector<int> & arr)
{
    if( arr.size() < 2){
        return;
    }
    for (int i = 0; i < arr.size() - 1; i++){
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); j++){
            minIndex = arr[j] < arr[minIndex] ? j : minIndex;
        }
        swap(arr, i ,minIndex);
    }
}

//冒泡排序
void bubbleSort(vector<int> & arr)
{
    if( arr.size() < 2){
        return;
    } 
    for(int i = arr.size() - 1; i > 0; i--){
        for (int j = 0; j < i; j++){
            if(arr[j] > arr[j+1]){
                swap(arr, j, j+1);  
            }    
        }
    }
}

//插入排序
void insertionSor(vector<int> & arr)
{
    if (arr.size() < 2){
        return;
    }
    for(int i = 1; i < arr.size(); i++){ //0~i做到有序
        for(int j = i-1; j >= 0 && arr[j] > arr[j+1]; j--){
            swap(arr, j, j+1);
        }
    }
}

//归并排序
void merge(vector<int>& arr, int L, int M, int R)
{
    vector<int> help;   //！额外空间复杂度
    //int i = 0;
    int p1 = L;
    int p2 = M + 1;
    while (p1 <= M && p2 <= R) {
        //help[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
        help.push_back(arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++]);
    }
    while (p1 <= M) {
        //help[i++] = arr[p1++];
        help.push_back(arr[p1++]);
    }
    while (p2 <= M) {
        //help[i++] = arr[p2++];
        help.push_back(arr[p2++]);
    }
    for (int i = 0; i < help.size(); i++) {
        arr[L + i] = help[i];
    }
}

void process(vector<int>& arr, int L, int R)
{
    if (L == R){
        return;
    }
    int mid = L + ((R - L) >> 1);
    process(arr, L, mid);
    process(arr, mid + 1, R);
    merge(arr, L, mid, R);
}

void mergeSort(vector<int> & arr)
{
    if(arr.size() < 2){
        return;
    }
    process(arr, 0, arr.size() - 1);
}

int main()
{
    vector<int> a;
    a.push_back(3);
    a.push_back(2);
    a.push_back(1);
    a.push_back(5);
    a.push_back(6);
    a.push_back(2);

    process(a, 0, a.size()-1);

    for(int i = 0; i < a.size(); i++)
        cout << a[i] << endl;

    return 0;
}