// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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
	char **suffix = (char **)malloc(n);
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

int main() {
	//char T[] = { "mississippi$" };
	char *T;
	int *SA;
	FILE *fp;
	errno_t err;
	const char *fname = "C:\\Users\\aredayone\\Documents\\sample\\sample.txt";
	long n;
	if ((err = fopen_s(&fp, fname, "r")) != 0)printf("error\n"); //exit(1);
	if (fseek(fp, 0, SEEK_END) == 0) {
		n = ftell(fp);
		rewind(fp);
	}
	T = (char *)malloc((size_t)n * sizeof(char)+1);
	SA = (int *)malloc((size_t)n * sizeof(int));
	if ((T == NULL) || (SA == NULL))printf("error\n");//exit(EXIT_FAILURE);
	fread(T, sizeof(char), (size_t)n, fp);
	T[n] = NULL;
	fclose(fp);
	int i;
	GetSA(T,SA,n);
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
	printf("T  :%s\nSA :", T);
	for (i = 0; i<n; i++) {
		printf("%2d", SA[i]);
	}
	printf("\nBWT:");
	for (i = 0; i<n; i++) {
		printf("%2c", BWT[i]);
	}
	printf("\n");
	free(T);
	free(SA);
	free(BWT);
	return 0;
}

