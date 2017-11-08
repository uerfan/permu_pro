#ifndef _NEIGHBOR_H_
#define _NEIGHBOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void neighbor_swap(int *per, bool* arr, int pos) {

	if (arr[pos]) 
	{
		int  temp = per[pos]; 
		per[pos] = per[pos+1]; 
		per[pos+1] = temp;

		bool flag = arr[pos]; 
		arr[pos] = arr[pos+1]; 
		arr[pos+1] = flag;
	}
	else
	{
		int  temp = per[pos]; 
		per[pos] = per[pos-1]; 
		per[pos-1] = temp;

		bool flag = arr[pos]; 
		arr[pos] = arr[pos-1]; 
		arr[pos-1] = flag;
	}
	
}

bool neighbor_permutations(int *permutations, bool * arrow, int N) {
	
	int mov = 1;
	int pos = -1;

	for(int i = 0; i < N; i++) {
		if(permutations[i] < mov)
			continue;

		if ((arrow[i] && (i < (N - 1)) && (permutations[i] > permutations[i+1])) || 
			(!arrow[i] && (i > 0) && (permutations[i] > permutations[i-1])))
		{
			mov = permutations[i];
			pos = i;
		}
	}
	
	if (pos == -1)
		return false;

	neighbor_swap(permutations, arrow, pos);

	for (int i = 0; i < N; i++)    
	{
		if (permutations[i] > mov)
			arrow[i] = !arrow[i];
	}

	return true;
	
}



long generate_permutations_by_neighbor(int N)
{
	long count = 0;
	int *permutations = (int *)malloc(N * sizeof(int));
	bool *arrow = (bool *)malloc(N * sizeof(bool));

	for(int i = 0; i < N; i++) {
		permutations[i] = i + 1;
		arrow[i] = false;
	}
	
	while(true) {
		print_array(permutations, N);
		count++;

		if (permutations[N - 1] == N)
		{
			for(int i = N - 1; i > 0; i--) {
				neighbor_swap(permutations, arrow, i);
				print_array(permutations, N);
				count++;
			}
		} else {

			for(int i = 0; i < N - 1; i++) {
				neighbor_swap(permutations, arrow, i);
				print_array(permutations, N);
				count++;
			}
		}

		if (!neighbor_permutations(permutations, arrow, N))
			break;

	}

	free(permutations);
	free(arrow);

	return count;
}

#endif