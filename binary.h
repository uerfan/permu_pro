#ifndef _BINARY_H_
#define _BINARY_H_

/*
Generate full permutations of N(length of numbers)
 */
#include <stdlib.h>
#include <stdio.h>

int log_2(int x) {
	int res = -1;
	while(x != 0) {
		x = x >> 1;
	    res = res + 1;
	}
	return res;
}

void get_right_n_zero_positions(int x, int n, int *zp) {
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

void print_permutations(int *binarys, int N) {
	for(int i = 1; i <= N; i++) {
		int a = N - log_2(binarys[i] - binarys[i-1]);
		printf("%d ", a);
	}
	printf("\n");
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
    
    int i = 0, k = 0, x = 0, y = 0, z = 0;
    while(1) {
        print_permutations(binarys, N);
	    count++;

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
        	break;
        }

        while((binarys[k] & x) > 0) {
        	x = x >> 1;
        }
        binarys[k] = binarys[k-1] + x;

        if(k == N - 1) {
        	continue;
        }

        get_right_n_zero_positions(binarys[k], N-k, zp);
        for(i = k + 1; i <= N - 1; i++) {
        	binarys[i] = binarys[i-1] + (1 << zp[i-k-1]);
        }
    }

    return count;
}


#endif