#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

using namespace std;

// 设计RandomPool结构
template <typename T>
class Pool {
public:
    Pool() {
        this->size = 0;
    }

    void insertKey(T key) {
        if (KeyIndexMap.find(key) == KeyIndexMap.end()) {
            this->KeyIndexMap.insert(key, this->size);
            this->indexKeyMap.insert(this->size++, key);
        }
    }

    void deleteKey(T key) {
        if (KeyIndexMap.find(key) != KeyIndexMap.end()) {
            int deleteIndex = this->KeyIndexMap[key];
            int lastIndex = --this->size;
            T lastKey = this->indexKeyMap[lastIndex];
            this->KeyIndexMap[lastIndex] = deleteIndex;
            this->indexKeyMap[deleteIndex] = lastKey;
            this->KeyIndexMap.erase(key);
            this->indexKeyMap.erase(lastIndex);
        }
    }

    T getRandom() {
        if (this->size == 0) {
            return NULL;
        }
        srand(time(NULL));
        int randomIndex = rand() % this->size();
        return this->indexKeyMap[randomIndex];
    }

private:
    unordered_map<T, int> KeyIndexMap;
    unordered_map<int, T> indexKeyMap;
    int size;
};