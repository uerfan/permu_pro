#ifndef _SIMILAR_H_
#define _SIMILAR_H_


int min(int a,int b){
	return (a<=b)?a:b;
}

int min_of_three(int a,int b,int c){
	return min(min(a,b),c);
}

int edit_distance(int *a, int *b,int lena,int lenb)
{
    int* d=(int*)malloc((lenb+1)*sizeof(int));
    int i, j, old, temp;

    for (j = 0; j <= lenb; j++) {
        d[j] = j;
    }

    for (i = 1; i <= lena; i++) {
        old = i - 1;
        d[0] = i;
        for (j = 1; j <= lenb; j++) {
            temp = d[j];
            if (a[i-1] == b[j-1]) {
                d[j] = old;
            } else {
                d[j] = min_of_three(d[j] + 1, d[j-1] + 1, old + 1);
            }
            old = temp;
        }
    }
    int ret=d[lenb];
    free(d);
    return ret;
}

#endif