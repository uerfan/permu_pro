#include "permutation.h"
#include "similar.h"
#include <unistd.h>

#define PARAM_MESSAGE "./main -h to get help message\n"

int main(int argc, char** argv){

	if(argc<2){
		printf("%s\n",PARAM_MESSAGE);
		return 1;
	}

	int c,n,algo = -1;
	
	while ((c = getopt(argc, argv, "n:a:h")) >= 0) {
		if (c == 'n') n = atoi(optarg);
		else if (c == 'a') algo = atoi(optarg);
		else if (c == 'h') {
			fprintf(stderr, "Usage: ./main [options]\n");
			fprintf(stderr, "Options:\n");
			fprintf(stderr, "  -n INT    size of the full permutations\n");
			fprintf(stderr, "  -a INT    type of algorithm to generate permutations\n");
			fprintf(stderr, "            0: dict\n");
			fprintf(stderr, "            1: increase\n");
			fprintf(stderr, "            2: decrease\n");
			fprintf(stderr, "            3: neighbor\n");
			fprintf(stderr, "  -h        this help message\n");
			return 0;
		}
	}

	long count=0;
	int* old;
	int* new;
	int i,flag;
	switch(algo){
		case 0:
		    count = generate_permutations_by_dict(n);
		    printf("[+]Dictionary,Permutations(%d)=%ld\n",n,count);
			break;
		case 1:
			count=generate_permutations_by_increase(n);
			printf("[+]Increase,Permutations(%d)=%ld\n",n,count);
			break;
		case 2:
			count=generate_permutations_by_decrease(n);
			printf("[+]Decrease,Permutations(%d)=%ld\n",n,count);
			break;
		case 3:
			count=generate_permutations_by_neighbor(n);
			printf("[+]Neighbor,Permutations(%d)=%ld\n",n,count);
			break;
		default:
			old = (int*)malloc(n*sizeof(int));
			new = (int*)malloc(n*sizeof(int));
			for(i=0;i<n;i++) 
				old[i]=i+1;
			print_array_line(old,n);
			count=1;
			while(get_next_permutation_by_increase(old,new,n)==1){
				print_array_line(new,n);
				//scanf("%d",&flag);
				//printf("Edit_distance=%d\n",edit_distance(old,new,n,n));
				memcpy(old,new,n*sizeof(int));
				count++;
			}
			printf("[+] Default increase one by one,Permutations(%d)=%ld\n",n,count);
			break;
	}

	//int r=2;
	//print_array_line(get_rth_permutation_by_increase(n,0),n);
	//print_array_line(get_rth_permutation_by_increase(n,r),n);

	return 0;

}
