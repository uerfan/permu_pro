#include "permutation.h"
#include <unistd.h>
#include <time.h>

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
			fprintf(stderr, "            4: binary_dict (n <= 32)\n");
			fprintf(stderr, "            5: binary_new  (n <= 32)\n");
			fprintf(stderr, "  -h        this help message\n");
			return 0;
		}
	}

	long count=0;
	int* old;
	int* new;
	int i,flag;

	#ifdef _TEST_
		clock_t t1,t2;
	#endif
	
	
	switch(algo){
		case 0:
		#ifdef _TEST_
			t1 = clock();
		#endif
		    count = generate_permutations_by_dict(n);
		#ifdef _TEST_
			t2 = clock();
		#endif
		    printf("[+]Dictionary,Permutations(%d)=%ld\n",n,count);
			break;
		case 1:
		#ifdef _TEST_
			t1 = clock();
		#endif
			count=generate_permutations_by_increase(n);
		#ifdef _TEST_
			t2 = clock();
		#endif
			printf("[+]Increase,Permutations(%d)=%ld\n",n,count);
			break;
		case 2:
		#ifdef _TEST_
			t1 = clock();
		#endif
			count=generate_permutations_by_decrease(n);
		#ifdef _TEST_
			t2 = clock();
		#endif
			printf("[+]Decrease,Permutations(%d)=%ld\n",n,count);
			break;
		case 3:
		#ifdef _TEST_
			t1 = clock();
		#endif
			count=generate_permutations_by_neighbor(n);
		#ifdef _TEST_
			t2 = clock();
		#endif
			printf("[+]Neighbor,Permutations(%d)=%ld\n",n,count);
			break;
		case 4:
		#ifdef _TEST_
			t1 = clock();
		#endif
			count=generate_permutations_by_binary_dict(n);
		#ifdef _TEST_
			t2 = clock();
		#endif
			printf("[+]Binary_Dict,Permutations(%d)=%ld\n",n,count);
			break;
		case 5:
		#ifdef _TEST_
			t1 = clock();
		#endif
			count=generate_permutations_by_binary_new(n);
		#ifdef _TEST_
			t2 = clock();
		#endif
			printf("[+]Binary_New,Permutations(%d)=%ld\n",n,count);
			break;
		default:
		#ifdef _TEST_
			t1 = clock();
		#endif
			count = generate_permutations_by_dict(n);
		#ifdef _TEST_
			t2 = clock();
		#endif
		    printf("[+]Default Dictionary,Permutations(%d)=%ld\n",n,count);
			break;
	}
#ifdef _TEST_
	printf("CPU time is %gs\n",(double)(((double)(t2-t1))/CLOCKS_PER_SEC));
#endif

	return 0;

}
