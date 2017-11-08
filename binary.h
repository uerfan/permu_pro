#ifndef _BINARY_H_
#define _BINARY_H_

/*
Generate full permutations of N(length of numbers)
 */
#include <stdlib.h>
#include <stdio.h>

int log_2(int x) { // 求log2(x)的整数部分
	int res = -1;
	while(x != 0) {
		x = x >> 1;
	    res = res + 1;
	}
	return res;
}

int ror_1(int x, int n) { //对x的二进制形式循环右移1位，限定二进制长度为低n位
    int lowest = x & 1;
    x = x >> 1;
    if(lowest == 1) {
    	x = x + (1 << (n-1));
    }
    return x;
}

bool is_last(int *binarys, int N) {
	for(int i = 1; i <= N-1; i++) {
		if(binarys[i] != (1<<i)-1) {
			return 0;
		}
	}
	return 1;
}

void get_right_n_zero_positions(int x, int n, int *zp) { //求x的二进制形式中靠右侧的n个0的位置（相对于最右侧的偏移）
	int i = 1, offset = 0;
    while(i <= n) {
    	if((x & 1) == 0) {
    		zp[n-i] = offset;
    		i = i + 1;
    	}
		
		x = x >> 1;
		offset = offset + 1;
	}
}

void print_permutations(int *binarys, int N) { // 将变换转换成排列并打印
	for(int i = 1; i <= N; i++) {
		int a = N - log_2(binarys[i] - binarys[i-1]);
		printf("%d ", a);
	}
	printf("\n");
}

bool find_the_next_by_binary_dict(int *binarys, int N, int *zp) {
	int i = 0, k = 0, x = 0, y = 0, z = 0;
	k = N - 1;
    while(k >= 1) {
    	x = binarys[k] - binarys[k-1];
    	y = binarys[k] % x;
    	z = y ^ (x - 1);
    	if(z != 0) {
    		break;
    	}
    	k = k - 1;
    }

    if(k == 0) {
    	return 0;
    }

    while((binarys[k] & x) > 0) {
    	x = x >> 1;
    }
    binarys[k] = binarys[k-1] + x;

    if(k == N - 1) {
    	return 1;
    }

    get_right_n_zero_positions(binarys[k], N-k, zp);
    for(i = k + 1; i <= N - 1; i++) {
    	binarys[i] = binarys[i-1] + (1 << zp[i-k-1]);
    }

    return 1;
}

long generate_permutations_by_binary_dict(int N) {
	long count = 0;
	int *binarys = (int *)malloc((N+1) * sizeof(int));
	int *zp = (int *)malloc((N-1) * sizeof(int));
    
	binarys[0] = 0;
	for(int i = 1; i <= N; i++) {
		binarys[i] = (1 << (N-i)) + binarys[i-1];
		//printf("%d %d\n", i, binarys[i]);
	}
    
    while(1) {
    #ifdef _PRINT_
        print_permutations(binarys, N);
    #endif
	    count++;

        if(find_the_next_by_binary_dict(binarys, N, zp) == 0) {
        	break;
        }
    }

    return count;
}

long generate_permutations_by_binary_new(int N) {
	long count = 0;
	int *binarys = (int *)malloc((N+1) * sizeof(int));
	int *zp = (int *)malloc((N-1) * sizeof(int));
    
	binarys[0] = 0;
	for(int i = 1; i <= N; i++) {
		binarys[i] = (1 << (N-i)) + binarys[i-1];
		//printf("%d %d\n", i, binarys[i]);
	}
    
    int i = 0, x = 0;
    while(1) {
    #ifdef _PRINT_
        print_permutations(binarys, N);
    #endif
	    count++;

	    if(is_last(binarys, N)) {
	    	break;
	    }

	    if(binarys[1] != 1) {
	    	binarys[1] = binarys[1] >> 1;
	    	i = 2;
	    	while(i <= N - 1) {
	    		x = binarys[i] | binarys[1];
	    		if(binarys[i] == x) {
	    			break;
	    		}
	    		else {
	    			binarys[i] = binarys[i] - binarys[1];
	    		}
	    		i = i + 1;
	    	}
	    }
	    else {
	    	for(i = 1; i <= N - 1; i++) {
	    		binarys[i] = ror_1(binarys[i], N);
	    	}

	    	if(find_the_next_by_binary_dict(binarys, N, zp) == 0) {
        		break;
        	}
	    }
    }

    return count;
}


#endif