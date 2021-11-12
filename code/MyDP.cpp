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
    if(dp[rest][cur] != -1){
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
            // 根据递归函数改写
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
    return -1;
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
        int p1 = process(arr, index + 1, res, dp);
        int p2Next = process(arr, index + 1, rest - arr[index], dp);
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
            // 根据递归函数改写
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


// 纸牌游戏
int dp(vector<int>& arr){
    int N = arr.size();
    if(N < 1){
        return 0;
    }
    vector<vector<int>> f;
    vector<vector<int>> s;
    for(int i = 0; i < N; i++){
        vector<int> tmp;
        for(int j = 0; j < N; j++){
            tmp.push_back(0);
        }
        f.push_back(tmp);
        s.push_back(tmp);
    }

    for(int i = 0; i < N; i++){
        f[i][i] = arr[i];
    }
    int row = 0;
    int col = 1;
    // 对角线位置开始 row 行 col 列
    while(col < N){
        int i = row;
        int j = col;
        while(i < N && j < N){
            f[i][j] = max(arr[i] + s[i + 1][j], arr[j] + s[i][j - 1]);
            s[i][j] = min(f[i + 1][j], f[i][j - 1]);
            i++;
            j++;
        }
        col++;
    }
    return max(f[0][N - 1], s[0][N - 1]);
}


// 三维动态规划（象棋）
// 递归
int process(int x, int y, int step){
    if(x < 0 || x > 8 || y < 0 || y > 8){
        return 0;
    }
    if(step == 0){
        return (x == 0 && y == 0) ? 1 : 0;
    }
    return process(x - 1, y + 2, step - 1)
            + process(x - 2, y + 1, step - 1)
            + process(x - 2, y - 1, step - 1)
            + process(x - 1, y - 2, step - 1)
            + process(x + 1, y - 2, step - 1)
            + process(x + 2, y - 1, step - 1)
            + process(x + 2, y + 1, step - 1)
            + process(x + 1, y + 2, step - 1);
}
int getWays(int x, int y, int k){
    return process(x, y, k);
}
// 动态规划
int getValue(vector<vector<vector<int>>>& dp, int row, int col, int step){
    if(row < 0 || row > 8 || col < 0 || col > 9){
        return 0;
    }
    return dp[row][col][step];
}
int dpWays(int x, int y, int step){
    if(x < 0 || x > 8 || y < 0 || y > 8){
        return 0;
    }
    vector<vector<vector<int>>> dp;
    for(int i = 0; i <= 8; i++){
        vector<vector<int>> tmp;
        for(int j = 0; j <= 9; j++){
            vector<int> tmp1;
            for(int k = 0; k <= step; k++){
                tmp1.push_back(0);
            }
            tmp.push_back(tmp1);
        }
        dp.push_back(tmp);
    }
    dp[0][0][0] = 1;
    for(int h = 1; h <= step; h++){
        for(int r = 0; r <= 8; r++){
            for(int c = 0; c <= 9; c++){
                dp[r][c][h] += getValue(x - 1, y + 2, step - 1);
                dp[r][c][h] += getValue(x - 2, y + 1, step - 1);
                dp[r][c][h] += getValue(x - 2, y - 1, step - 1);
                dp[r][c][h] += getValue(x - 1, y - 2, step - 1);
                dp[r][c][h] += getValue(x + 1, y - 2, step - 1);
                dp[r][c][h] += getValue(x + 2, y - 1, step - 1);
                dp[r][c][h] += getValue(x + 2, y + 1, step - 1);
                dp[r][c][h] += getValue(x + 1, y + 2, step - 1);
            }
        }
    }
    return dp[x][y][step];
}


// 三维动态规划（生存概率）
long processBob(int N, int M, int row, int col, int rest){
    if(row < 0 || row == N || col < 0 || col == M){
        return 0;
    }
    // row, col 没越界
    if(rest == 0){
        return 1;
    }
    // 还没走完，row，col也没越界
    long live = processBob(N, M, row - 1, col, rest - 1);
    live += processBob(N, M, row + 1, col, rest - 1);
    live += processBob(N, M, row, col - 1, rest - 1);
    live += processBob(N, M, row, col + 1, rest - 1);
    return live;
}


// 枚举行为
// 递归
// 需要搞定的钱数 rest
int processWay(vector<int>& arr, int index, int rest){
    if(index == arr.size() - 1){
        return rest == 0 ? 1 : 0;
    }
    int ways = 0;
    for(int zhang = 0; arr[index] * zhang <= rest; zhang++){
        ways += processWay(arr, index + 1, rest - arr[index] * zhang);
    }
    return ways;
}
// arr里都是正数，没有重复值，每个值代表一种货币，每种货币可以使用无限张
// 最终要找的零钱数是 aim
// 找零方法数返回
int way1(vector<int>& arr, int aim){
    return processWay(arr, 0, aim);
}
// 严格表结构（不优化枚举行为）
int way2(vector<int>& arr, int aim){
    if(arr.size() < 1){
        return 0;
    }
    int N = arr.size();
    vector<vector<int>> dp;
    for(int i = 0; i <= N; i++){
        vector<int> tmp;
        for(int j = 0; j <= aim; j++){
            tmp.push_back(0);
        }
        dp.push_back(tmp);
    }
    dp[N][0] = 1;
    for(int index = N - 1; index >= 0; index--){
        for(int rest = 0; rest <= aim; rest++){
            int ways = 0;
            for(int zhang = 0; arr[index] * zhang <= rest; zhang++){
                ways += dp[index + 1][rest - arr[index] * zhang];
            }
            dp[index][rest] = ways;
        }
    }
    return dp[0][aim];
}
// 严格表结构（优化枚举行为）
int way3(vector<int>& arr, int aim){
    if(arr.size() < 1){
        return 0;
    }
    int N = arr.size();
    vector<vector<int>> dp;
    for(int i = 0; i <= N; i++){
        vector<int> tmp;
        for(int j = 0; j <= aim; j++){
            tmp.push_back(0);
        }
        dp.push_back(tmp);
    }
    dp[N][0] = 1;
    for(int index = N - 1; index >= 0; index--){
        for(int rest = 0; rest <= aim; rest++){
            dp[index][rest] = dp[index + 1][rest];
            if(rest - arr[index] >= 0){
                dp[index][rest] += dp[index][rest - arr[index]];
            }
        }
    }
    return dp[0][aim];
}

