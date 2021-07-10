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
    if( arr.size() < 2)
        return;
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
    if( arr.size() < 2)
        return;
    for(int i = arr.size() - 1; i > 0; i--){
        for (int j = 0; j < i; j++){
            if(arr[j] > arr[j+1])
                swap(arr, j, j+1);
        }
    }
}