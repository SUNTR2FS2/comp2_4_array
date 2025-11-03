#define WIN32_LEAN_AND_MEAN
#include "Windows.h"

#include <stdlib.h>     // malloc, free
#include <stdbool.h>    // bool

#include "../include/lib_func.h"

// my_array を要素数nで初期化する
void initialize(my_array* ar, int n)
{
    if (ar == NULL) return;

    if (n <= 0) {
        ar->num = 0;
        ar->addr = NULL;
        return;
    }

    ar->addr = (int*)malloc(sizeof(int) * n);
    if (ar->addr == NULL) {
        ar->num = 0;
    }
    else {
        ar->num = n;
        for (int i = 0; i < n; i++) {
            ar->addr[i] = 0;
        }
    }
}

// my_array を解放する
void release(my_array* ar)
{
    if (ar == NULL) return;
    free(ar->addr);
    ar->addr = NULL;
    ar->num = 0;
}

// my_array の要素数を取得する
int size(const my_array* ar)
{
    if (ar == NULL || ar->addr == NULL || ar->num <= 0) return 0;
    return ar->num;
}

// my_array のindex番目の要素にvalを設定する
bool set(my_array* ar, int index, int val)
{
    if (ar == NULL || ar->addr == NULL || index < 0 || index >= ar->num) return false;
    ar->addr[index] = val;
    return true;
}

// my_array のindex番目の要素を取得する
int get(const my_array* ar, int index)
{
    if (ar == NULL || ar->addr == NULL || index < 0 || index >= ar->num) return 0;
    return ar->addr[index];
}

// my_array の要素数を変更する（以前の値は同じ範囲で保持）
void resize(my_array* ar, int n)
{
    if (ar == NULL || n <= 0) return;

    int* new_addr = (int*)malloc(sizeof(int) * n);
    if (new_addr == NULL) return;

    int min = (ar->num < n) ? ar->num : n;
    for (int i = 0; i < min; i++) {
        new_addr[i] = ar->addr[i];
    }
    for (int i = min; i < n; i++) {
        new_addr[i] = 0;
    }

    free(ar->addr);
    ar->addr = new_addr;
    ar->num = n;
}