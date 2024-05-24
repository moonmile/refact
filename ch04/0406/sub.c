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
    if (size <= 0) {
        return -1;
    }
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}

/**
 * 配列の最大値と最小値を求める関数
 */
int max_min(int array[], int size, int *max, int *min) {
    if (size <= 0) {
        return -1;
    }
    *max = array[0];
    *min = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > *max) {
            *max = array[i];
        }
        if (array[i] < *min) {
            *min = array[i];
        }
    }
    return 0;
}

