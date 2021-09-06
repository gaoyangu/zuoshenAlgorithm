#include <iostream>

using namespace std;

// 请保证参数 n 不是 1 就是 0
// 1 -> 0
// 0 -> 1 
int flip(int n){
    return n ^ 1;
}
// n 是非负数，返回 1
// n 是负数， 返回 0
int sign(int n){
    return flip( (n >> 31) & 1 );
}
// bug: a - b 可能溢出
int getMax1(int a, int b){
    int c = a - b;
    int scA = sign(c);      // a - b 为非负，scA为 1；a - b 为负，scA为 0
    int scB = flip(scA);    // scA为0，scB为1；scA为1，scB为0
    return a * scA + b * scB;
}
int getMax2(int a, int b){
    int c = a - b;
    int sa = sign(a);
    int sb = sign(b);
    int sc = sign(c);
    int difSab = sa ^ sb;       // a 和 b 的符号不一样为1，一样为0
    int sameSab = flip(difSab); // a 和 b 的符号不一样为0，一样为1
    int returnA = difSab * sa + sameSab * sc;
    int returnB = flip(returnA);
    return a * returnA + b * returnB;
}


// 判断一个32位正数是不是2的幂、4的幂
bool is2Power(int n){
    return (n & (n - 1)) == 0;
}
bool is4Power(int n){
    return (n & (n - 1)) == 0 && (n & 0x55555555) != 0;
}


// 加减乘除
// 加法
int myAdd(int a, int b){
    int sum = a;
    while (b != 0){
        sum = a ^ b;        // 无进位相加
        b = (a & b) << 1;   // 进位信息
        a = sum;
    }
    return sum;
}
// 相反数
int negNum(int n){  
    return myAdd(~n, 1);
}
// 减法
int MyMinus(int a, int b){
    return myAdd(a, negNum(b));
}
// 乘法
int MyMulti(int a, int b){
    int res = 0;
    while(b != 0){
        if((b & 1) != 0){
            res = myAdd(res, a);
        }
        a <<= 1;
        b >>= 1;    // 需要无符号右移
    }
    return res;
}
// 除法
bool isNeg(int n){
    return n < 0;
}
int myDiv(int a, int b){
    int x = isNeg(a) ? negNum(a) : a;
    int y = isNeg(b) ? negNum(b) : b;
    int res = 0;
    for(int i = 31; i > -1; i = MyMinus(i, 1)){
        if((x >> i) >= y){  // 右移更安全
            res |= (1 << i);
            x = MyMinus(x, y << i);
        }
    }
    return isNeg(a) ^ isNeg(b) ? negNum(res) : res;
}

