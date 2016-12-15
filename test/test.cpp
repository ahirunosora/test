// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>


int compare(const void *arg1, const void *arg2)
{
	/* Compare all of both strings: */
	const char* left_char = *(const char **)arg1;
	const char* right_char = *(const char **)arg2;
	return strcmp(left_char, right_char);
}

void GetSA(const char *T, int *SA,long n) {
	char *p;
	char *str = (char *)malloc(2 * (size_t)n * sizeof(char));
	char **suffix = (char **)malloc((size_t)n*sizeof(char *));
	//char *suffix[n];
	int j = 0;
	int k = 0;
	for (int i = 0; i < n; i++)str[k++] = T[i];
	for (int i = 0; i < n; i++)str[k++] = T[i];
	p = str;
	int length = k - 1;
	while (j < length) {
		suffix[j] = p + j;
		j++;
		if (j == n)break;
	}
	char *T2 = str;
	qsort(suffix,n,sizeof(*suffix),compare);
	for (int i = 0; i < n; i++) SA[i] = suffix[i] - T2;
}


int Get_position(int *SSA, int *mark,char *BWT,char *FF,int *C,int rank) {
	int b_count = 0;
	char c;
	int i = 0;
	int count = 0;
	int j = 0;
	while (mark[rank] != 1){
		c = BWT[rank];
		while (FF[i] != c) {
			i++;
		}
		for (j = 0; j < rank; j++) {
			if (BWT[j] == c)count++;
		}
		rank = C[i] + count;
		i = 0;
		count = 0;
		b_count++;
	}
	count = 0;
	for (j= 0; j < rank; j++) {
		if (mark[j] == 1) {
			count++;
		}
	}
	//printf("b_count:%d\n",b_count);
	return SSA[count] + b_count;
}

int main() {
	//char T[] = { "mississippi$" };
	char *T;
	int *SA;
	FILE *fp;
	errno_t err;
	int i = 0;
	const char *fname = "C:\\Users\\aredayone\\Desktop\\Œ¤‹†\\e_list1.txt";
	long n;
	if ((err = fopen_s(&fp, fname, "r")) != 0)exit(1);
	/*if (fseek(fp, 0, SEEK_END) == 0) {
		n = ftell(fp);
		rewind(fp);
	}*/
	char e_list[550][20];
	char *lfcp;
	char s[20];
	int j;
	while (fgets(s, 256, fp) != NULL) {
		lfcp = strchr(s, '\n');
		if (lfcp != NULL)*lfcp = '\0';
		for(j=0;j<strlen(s)+1;j++){
			e_list[i][j] = s[j];
		}
		i++;
	}
	int random = 0;
	T = (char*)malloc(5000000 * sizeof(char));
	if (T == NULL)exit(1);
	sprintf_s(T,20, "%s", e_list[0]);
	//srand((unsigned)time(NULL));
	for (i = 0; i < 200000; i++) {
		random=rand()%500;
		sprintf_s(T, 5000000,"%s%s", T, e_list[random]);
	}
	sprintf_s(T, 5000000, "%s$", T);
	n = strlen(T);
	printf("•¶Žš”:%d\n", n);
	T[n] = NULL;
	SA = (int *)malloc((size_t)n * sizeof(int));
	if (SA == NULL)printf("error\n");//exit(EXIT_FAILURE);
	fclose(fp);
	GetSA(T,SA,n);
	/*printf("T  :%s\nSA :", T);
	for (i = 0; i<n; i++) {
		printf("%3d", SA[i]);
	}*/
	//make_SSA,mark
	int space =  log((double)n) / log(32.0);
	printf("space:%d\n", space);
	int *SSA = (int *)malloc(sizeof(int)*n);
	int *mark = (int *)malloc(sizeof(int)*n);
	if (SSA == NULL)exit(1);
	j = 0;
	for (i = 0; i < n; i++) {
		if (SA[i] % space == 0) {
			SSA[j] = SA[i];
			mark[i] = 1;
			j++;
		}
		else {
			mark[i] = 0;
		}
	}
	char* BWT;
	BWT = (char *)malloc((size_t)n * sizeof(char)+1);
	for (i = 0; i < n; i++) {
		if (SA[i] != 0) {
			BWT[i] = T[SA[i] - 1];
		}
		else {
			BWT[i] = '$';
		}
	}
	BWT[n] = NULL;
	char *F = (char *)malloc((size_t)n * sizeof(char) + 1);
	for (i = 0; i < n; i++) {
		F[i] = T[SA[i]];
	}
	F[n] = NULL;
	//char *FF = (char *)malloc((size_t)n * sizeof(char) + 1);
	//int *C = (int *)malloc((size_t)n * sizeof(int) + 1);
	char FF[256];
	int C[256];
	memset(C, 0, sizeof(C));
	j = 1;
	int count=0;
	FF[0] = F[0];
	C[0] = 0;
	for (i = 1; i < n; i++) {
			count++;
			if (F[i] != F[i - 1]) {
				FF[j] = F[i];
				C[j] = count;
				j++;
			}
	}
	FF[j] = NULL;
	/*printf("\nBWT:");
	for (i = 0; i<n; i++) {
		printf("%3c", BWT[i]);
	}
	printf("\nF:%s\n",F);
	*/
	clock_t start, end;
	start = clock();
	int answer = 0;
	for (i = 0; i < 2000; i++) {
		answer = Get_position(SSA, mark, BWT, FF, C, 5+i);
	}
	end = clock();
	//printf("time:%f(s)\nanswer:%d\n",(long double)(end-start) / CLOCKS_PER_SEC,answer);
	printf("time:%f(s)\n", (long double)(end - start) / CLOCKS_PER_SEC);
	free(T);
	free(SA);
	free(BWT);
	return 0;
}

