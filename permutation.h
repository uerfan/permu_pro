#ifndef _PERMUTATION_H_
#define _PERMUTATION_H_

/*
Generate full permutations of N(length of numbers)
 */
#include <stdlib.h>
#include <stdio.h>

void print_array_line(int* permutations,int N){
	int i;
	for(i=0;i<N;i++)
		printf("%d ",permutations[i]);
	printf("\n");
}

void print_array_line_inverse(int* permutations,int N){
	int i;
	for(i=N-1;i>=0;i--)
		printf("%d ",permutations[i]);
	printf("\n");
	
}

int * get_medium_of_increase(){

}

int rank_plus(int *rank,int len){
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

void transform_rank_to_permutation(int *rank,int* permutations,int N){
	int i,j;
	memset(permutations,0,N*sizeof(int));
	int count,number;
	for(i=N-2;i>=0;i--){
		count=0;
		number=i+2;
		//printf("number=%d,rank[i]=%d\n",number,rank[i]);
		for(j=N-1;j>=0;j--){

			if(rank[i]==count && permutations[j]==0){
				permutations[j]=number;
				break;
			}

			if(permutations[j]<number)
				count++;

		}
	}
	for(i=0;i<N;i++){
		if(permutations[i]==0)
			permutations[i]=1;
	}
}

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
	while(rank_plus(rank,N-1)==1){
		transform_rank_to_permutation(rank,permutations,N);
		print_array_line(permutations,N);
		count++;
	}

	return count;
}

int* get_permutation_by_rank_increase(int N,int r){
	int* rank=(int*)malloc((N)*sizeof(int));
	int* permutations=(int*)malloc((N)*sizeof(int));
	int i;
	long count;
	for(i=0;i<N;i++){
		rank[i]=0;
		permutations[i]=i+1;
	}
	count=0;
	while(rank_plus(rank,N-1)==1 && count<r){
		transform_rank_to_permutation(rank,permutations,N);
		count++;
	}
	free(rank);
	return permutations;
}



#endif