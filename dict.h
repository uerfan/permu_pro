#ifndef _DICT_H_
#define _DICT_H_

/*
Generate full permutations of N(length of numbers)
 */
#include <stdlib.h>
#include <stdio.h>

void print_array(int *arr, int N) {
	for(int i = 0; i < N; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void swap(int *arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

long generate_permutations_by_dict(int N) {
	long count = 0;
	int *permutations = (int *)malloc(N * sizeof(int));
	for(int i = 0; i < N; i++) {
		permutations[i] = i + 1;
	}

    int i = 0, j = 0, k = 0;
    while(1) {
    #ifdef _PRINT_
        print_array(permutations, N);
    #endif
	    count++;

        for(k = N - 2; k >= 0 && permutations[k] > permutations[k+1]; k--); // 从后往前查找第一个递减
        if(k < 0) break;
        for(j = N - 1; j > k && permutations[j] < permutations[k]; j--);    // 查找第k个之后比它大的最小数

        swap(permutations, k, j);                                           // 交换第k个数和找到的最小数

        for (int i = k + 1, j = N - 1; i < j; i++, j--) {                   // 翻转第k个数之后的序列
            swap(permutations, i, j);  
        }
    }

    return count;
}


#endif