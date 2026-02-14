#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int not_in(int x, int arr[],int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x)
            return 0; // está no array
    }
    return 1; // NÃO está no array
}


