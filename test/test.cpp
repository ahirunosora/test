// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

#define MAX_LEN 2000000

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
	int length = k + 1;
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

int FM_count(char *P,int *SSA,int *mark, char *BWT, char *FF, int *C, int m, int n) {
	int b = 0, e = n;
	char c;
	int count1 = 0, count2 = 0, count3 = 0;
	int answer;
	time_t start, end;
	for (int i = m - 1; i >= 0; i--) {
		c = P[i];
		while (FF[count1] != c)count1++;
		for (int j = 0; j < b; j++) {
			if (BWT[j] == c)count2++;
		}
		for (int j = 0; j < e; j++) {
			if (BWT[j] == c)count3++;
		}
		b = C[count1] + count2;
		e = C[count1] + count3;
		count1 = 0;
		count2 = 0;
		count3 = 0;
		if (b == e)break;
	}
	start = clock();
	for (int k = b; k < e; k++) {
		answer=Get_position(SSA, mark, BWT, FF, C, k);
		//printf("S[%d]:T[%d]\n", k, answer);
	}
	end = clock();
	printf("time:%f(s)\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return e - b;
}


int main() {
	char *T;
	int *SA;
	FILE *fp;
	errno_t err;
	int i = 0;
	const char *fname = "e_list1.txt";
	long n;

	
	//make_elist
	if ((err = fopen_s(&fp, fname, "r")) != 0)exit(1);
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
	fclose(fp);
	
	
	
	//Make_T
	T = (char*)malloc(MAX_LEN * sizeof(char));
	if (T == NULL)exit(1);
	sprintf_s(T,20, "%s", e_list[0]);
	//srand((unsigned)time(NULL));
	int random = 0;
	for (i = 0; i < 200000; i++) {
		random=rand()%500;
		sprintf_s(T, MAX_LEN,"%s%s", T, e_list[random]);
	}
	sprintf_s(T, MAX_LEN, "%s$", T);
	n = strlen(T);
	printf("•¶Žš”:%d\n", n);
	T[n] = '\0';

	
	//make_SA
	SA = (int *)malloc((size_t)n * sizeof(int));
	if (SA == NULL)printf("error\n");//exit(EXIT_FAILURE);
	GetSA(T,SA,n);


	/*make_SSA,mark
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
	}*/

	//make_BWT
	char* BWT;
	BWT = (char *)malloc(((size_t)n+1) * sizeof(char));
	for (i = 0; i < n; i++) {
		if (SA[i] != 0) {
			BWT[i] = T[SA[i] - 1];
		}
		else {
			BWT[i] = '$';
		}
	}
	BWT[n] = '\0';

	//Make_F
	char *F = (char *)malloc(((size_t)n+ 1) * sizeof(char) );
	for (i = 0; i < n; i++) {
		F[i] = T[SA[i]];
	}
	F[n] ='\0';
	
	
	//char count
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
	FF[j] = '\0';
	
	//input string
	char P[15];
	int select = 1;
	int occ = 0;
	int len_P = 0;
	int space = 0;
	int slog = 2;
	int *SSA = (int *)malloc(sizeof(int)*n);
	int *mark = (int *)malloc(sizeof(int)*n);
	if (SSA == NULL||mark==NULL)exit(1);

	while (select == 1) {
		printf("input string\n");
		scanf_s("%s", P,15);
		len_P = strlen(P);
		while (slog != 32) {
			space = log((double)n) / log((double)slog);
			printf("space:%d(log%d)\n", space,slog);
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
			occ = FM_count(P, SSA, mark, BWT, FF, C, len_P, n);
			printf("occ:%d\n", occ);
			slog *= 2;
			memset(SSA, 0, sizeof(SSA));
			memset(mark, 0, sizeof(mark));
		}
		slog = 2;
		printf("continue?\n");
		scanf_s("%d", &select);
		memset(P, 0, sizeof(P));
	}

	/*all e_list output
	char *P;
	int len_P = 0;
	int occ = 0;
	int e_count = 0;
	for (int z = 0; z < 500; z++) {
		P = e_list[z];
		len_P = strlen(P);
		occ = FM_count(P, SSA, mark, BWT, FF, C, len_P, n);
		e_count += occ;
		memset(P, 0, sizeof(P));
	}
	printf("e_count:%d\n", e_count);*/

	/*printf("\nBWT:");
	for (i = 0; i<n; i++) {
		printf("%3c", BWT[i]);
	}
	printf("\nF:%s\n",F);
	*/

	/*get_position without search
	clock_t start, end;
	start = clock();
	int answer = 0;
	for (i = 0; i < 200000; i++) {
		answer = Get_position(SSA, mark, BWT, FF, C, 5+i);
	}
	end = clock();
	//printf("time:%f(s)\n", (long double)(end - start) / CLOCKS_PER_SEC);*/
	
	free(T);
	free(SA);
	free(BWT);
	return 0;
}

