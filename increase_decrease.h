#ifndef _INCREASE_DECREASE_H_
#define _INCREASE_DECREASE_H_

/*
使用递增进位和递减进位生成长度为N的全排列
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
顺序打印长度为N的数组
 */
void print_array_line(int* permutations,int N){
	int i;
	for(i=0;i<N;i++)
		printf("%d ",permutations[i]);
	printf("\n");
}

/*
逆序打印长度为N的数组
 */
void print_array_line_inverse(int* permutations,int N){
	int i;
	for(i=N-1;i>=0;i--)
		printf("%d ",permutations[i]);
	printf("\n");
	
}

/*
递减进位制数算法，中介数加1
若还未到达最大值返回0，否则返回1
 */
int rank_decrease_plus(int *rank,int len){
	int i;
	for(i = 0; i <len; i++){
		rank[i] += 1;
		if(rank[i]<=len-i) 
			break;
		else{
			rank[i]=rank[i]-len+i-1;
			if(i==len-1) {
				rank[len]=1;
				return 0;
			}
		}
	}
	return 1;
}


/*
递增进位制数算法，中介数加1
若还未到达最大值返回0，否则返回1
 */
int rank_increase_plus(int *rank,int len){
	int i;
	for(i = 0; i <len; i++){
		rank[i] += 1;
		if(rank[i]<=i+1) 
			break;
		else{
			rank[i]=rank[i]-i-2;
			if(i==len-1) {
				rank[len]=1;
				return 0;
			}
		}
	}
	return 1;
}

/*
递增进位制算法，中介数转化为排列
 */
void transform_rank_to_permutation_increase(int *rank,int* permutation,int N){
	int i,j;
	memset(permutation,0,N*sizeof(int));
	int count,number;
	for(i=N-2;i>=0;i--){
		count=0;
		number=i+2;
		//printf("number=%d,rank[i]=%d\n",number,rank[i]);
		for(j=N-1;j>=0;j--){

			if(rank[i]==count && permutation[j]==0){
				permutation[j]=number;
				break;
			}

			if(permutation[j]<number)
				count++;

		}
	}
	for(i=0;i<N;i++){
		if(permutation[i]==0)
			permutation[i]=1;
	}
}

/*
递减进位制算法，中介数转化为排列
 */
void transform_rank_to_permutation_decrease(int *rank,int* permutation,int N){
	int i,j;
	memset(permutation,0,N*sizeof(int));
	int count,number;
	for(i=0;i<N-1;i++){
		count=0;
		number=N-i;
		//printf("number=%d,rank[i]=%d\n",number,rank[i]);
		for(j=N-1;j>=0;j--){

			if(rank[i]==count && permutation[j]==0){
				permutation[j]=number;
				break;
			}

			if(permutation[j]<number)
				count++;
		}
	}
	for(i=0;i<N;i++){
		if(permutation[i]==0)
			permutation[i]=1;
	}
}

/*
递增进位制全排列生成，输入N，打印全排列，输出全排列数量
 */
long generate_permutations_by_increase(int N){
	int* rank=(int*)malloc((N)*sizeof(int));
	int* permutations=(int*)malloc((N)*sizeof(int));
	int i;
	long count;
	for(i=0;i<N;i++){
		rank[i]=0;
		permutations[i]=i+1;
	}

	print_array_line(permutations,N);
	count=1;
	while(rank_increase_plus(rank,N-1)==1){
		transform_rank_to_permutation_increase(rank,permutations,N);
		print_array_line(permutations,N);
		count++;
	}

	return count;
}

/*
递增进位制生成第r位排列
 */
int* get_rth_permutation_by_increase(int N,int r){
	int* rank=(int*)malloc((N)*sizeof(int));
	int* permutations=(int*)malloc((N)*sizeof(int));
	int i;
	long count;
	for(i=0;i<N;i++){
		rank[i]=0;
		permutations[i]=i+1;
	}
	count=0;
	while(rank_increase_plus(rank,N-1)==1 && count<r){
		transform_rank_to_permutation_increase(rank,permutations,N);
		count++;
	}
	free(rank);
	return permutations;
}

/*
递减进位制全排列生成，输入N，打印全排列，输出全排列数量
 */
long generate_permutations_by_decrease(int N){
	int* rank=(int*)malloc((N)*sizeof(int));
	int* permutations=(int*)malloc((N)*sizeof(int));
	int i;
	long count;
	for(i=0;i<N;i++){
		rank[i]=0;
		permutations[i]=i+1;
	}

	print_array_line(permutations,N);
	count=1;
	while(rank_decrease_plus(rank,N-1)==1){
		transform_rank_to_permutation_decrease(rank,permutations,N);
		print_array_line(permutations,N);
		count++;
	}

	return count;
}

/*
递增进位制生成第r位排列
 */
int* get_rth_permutation_by_decrease(int N,int r){
	int* rank=(int*)malloc((N)*sizeof(int));
	int* permutations=(int*)malloc((N)*sizeof(int));
	int i;
	long count;
	for(i=0;i<N;i++){
		rank[i]=0;
		permutations[i]=i+1;
	}
	count=0;
	while(rank_decrease_plus(rank,N-1)==1 && count<r){
		transform_rank_to_permutation_decrease(rank,permutations,N);
		count++;
	}
	free(rank);
	return permutations;
}

/*
递增进位制 排列转化为中介数
 */
void permutation_to_rank_increase(int* permutation,int* rank,int N)
{
	memset(rank,0,N*sizeof(int));
	for(int i=0;i<N;i++){
		int idx = permutation[i]-2;
		if(idx<0) continue;
		for(int j=i+1;j<N;j++){
			if(permutation[j]<permutation[i]){
				rank[idx]++;
			}
		}
	}
}

/*
递增进位制得到当前排列的下一个排列
 */
int get_next_permutation_by_increase(int* old,int* new,int N){
	int* rank=(int*)malloc(N*sizeof(int));
	permutation_to_rank_increase(old,rank,N);
	//print_array_line(rank,N);
	if(rank_increase_plus(rank,N-1)==1){
		//print_array_line(rank,N);
		transform_rank_to_permutation_increase(rank,new,N);
		free(rank);
		return 1;
	}
	else{
		free(rank);
		return 0;
	}
}


#endif