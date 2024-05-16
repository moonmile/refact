#include "sub.h"

/**
 * 加算する関数
 */
int add(int a, int b) {
    return a + b;
}

/**
 * 乗算する関数
 */
int mul(int a, int b) {
    return a * b;
}

/**
 * 配列の平均値を求める関数
 */
int average(int array[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}
