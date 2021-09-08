#include <iostream>
#include <vector>
using namespace std;

// 机器人运动问题
// 递归方法
// N 固定参数，一共是1~N这么多位置
// E 固定参数，最终目标是E
// 还剩 rest 步需要走
// 当前在 cur 位置
// 返回方法数
int f(int N, int E, int rest, int cur){
    if(rest == 0){
        return cur == E ? 1 : 0;
    }
    if(cur == 1){
        return f(N, E, rest - 1, 2);
    }
    if(cur == N){
        return f(N, E, rest - 1, N - 1);
    }
    return f(N, E, rest - 1, cur - 1) + f(N, E, rest - 1, cur + 1);
}
int walkWays(int N, int E, int S, int K){
    return f(N, E, K, S);
}
// 记忆化搜索
int f2(int N, int E, int rest, int cur, vector<vector<int>>& dp){
    if(dp[rest][cur] == -1){
        return dp[rest][cur];
    }
    // 缓存没命中
    if(rest == 0){
        dp[rest][cur] = cur == E ? 1 : 0;
        return dp[rest][cur];
    }
    // rest > 0, 有路可以走
    if(cur == 1){
        dp[rest][cur] = f2(N, E, rest - 1, 2, dp);
    }
    else if(cur == N){
        dp[rest][cur] = f2(N, E, rest - 1, N - 1, dp);
    }
    else{
        dp[rest][cur] = f2(N, E, rest - 1, cur - 1, dp) + f2(N, E, rest - 1, cur + 1, dp);
    }
    return dp[rest][cur];
}
int walkWay2(int N, int E, int S, int K){
    vector<vector<int>> dp;
    for(int i = 0; i <= K; i++){
        vector<int> tmp;
        for(int j = 0; j <= N; j++){
            tmp.push_back(-1);
        }
        dp.push_back(tmp);
    }
    return f2(N, E, K, S, dp);
}
// 严格表结构
int dpWay(int N, int P, int M, int K){
    vector<vector<int>> dp;
    for(int i = 0; i <= K; i++){
        vector<int> tmp;
        for(int j = 0; j <= N; j++){
            tmp.push_back(0);
        }
        dp.push_back(tmp);
    }
    dp[0][P] = 1;
    for(int rest = 1; rest <= K; rest++){
        for(int cur = 1; cur <= N; cur++){
            if(cur == 1){
                dp[rest][cur] = dp[rest - 1][2];
            }
            else if(cur == N){
                dp[rest][cur] = dp[rest - 1][N - 1];
            }
            else{
                dp[rest][cur] = dp[rest - 1][cur - 1] + dp[rest - 1][cur + 1];
            }
        }
    }
    return dp[M][K];
}

// 硬币
// 递归
int process(vector<int>& arr, int index, int rest){
    if(rest < 0){
        return -1;
    }
    if(rest == 0){
        return 0;
    }
    // rest > 0
    if(index == arr.size()){
        return -1;
    }
    // rest >0 并且有硬币
    int p1 = process(arr, index + 1, rest);
    int p2Next = process(arr, index + 1, rest - arr[index]);
    if(p1 == -1 && p2Next == -1){
        return -1;
    }
    else{
        if(p1 == -1){
            return p2Next + 1;
        }
        if(p2Next == -1){
            return p1;
        }
        return min(p1, p2Next + 1);
    }
}
int minCoins1(vector<int>& arr, int aim){
    return process(arr, 0, aim);
}
// 记忆化搜索
int process2(vector<int>& arr, int index, int rest, vector<vector<int>> dp){
    if(rest < 0){
        return -1;
    }
    if(dp[index][rest] != -2){
        return dp[index][rest];
    }
    if(rest == 0){
        dp[index][rest] = 0;
    }
    else if(index == arr.size()){
        dp[index][rest] = -1;
    }
    else{
        int p1 = process(arr, index + 1, rest);
        int p2Next = process(arr, index + 1, rest - arr[index]);
        if(p1 == -1 && p2Next == -1){
            dp[index][rest] = -1;
        }
        else{
            if(p1 == -1){
                dp[index][rest] = p2Next + 1;
            }
            if(p2Next == -1){
                dp[index][rest] = p1;
            }
            dp[index][rest] = min(p1, p2Next + 1);
        }
    }
    return dp[index][rest];
}
int minCoins2(vector<int>& arr, int aim){
    vector<vector<int>> dp;
    for(int i = 0; i <= arr.size(); i++){
        vector<int> tmp;
        for(int j = 0; j <= aim; j++){
            tmp.push_back(-2);
        }
        dp.push_back(tmp);
    }
    return process2(arr, 0, aim, dp);
}
// 严格表结构
int minCoins3(vector<int>& arr, int aim){
    vector<vector<int>> dp;
    for(int i = 0; i <= arr.size(); i++){
        vector<int> tmp;
        for(int j = 0; j <= aim; j++){
            tmp.push_back(-2);
        }
        dp.push_back(tmp);
    }
    for(int row = 0; row <= arr.size(); row++){
        dp[row][0] = 0;
    }
    for(int col = 1; col <= aim; col++){
        dp[arr.size()][col] = -1;
    }
    for(int index = arr.size() - 1; index >= 0; index--){
        for(int rest = 1; rest <= aim; rest++){
            int p1 = dp[index + 1][rest];
            int p2Next = -1;
            if(rest - arr[index] >= 0){
                p2Next = dp[index + 1][rest - arr[index]];
            } 
            if(p1 == -1 && p2Next == -1){
                dp[index][rest] = -1;
            }
            else{
                if(p1 == -1){
                    dp[index][rest] = p2Next + 1;
                }
                else if(p2Next == -1){
                    dp[index][rest] = p1;
                }
                else{
                    dp[index][rest] = min(p1, p2Next + 1);
                }
            }
        }
    }
    return dp[0][aim];
}










