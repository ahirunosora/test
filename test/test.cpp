// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


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
	T = (char*)malloc(100 * sizeof(char));
	if (T == NULL)exit(1);
	sprintf_s(T,20, "%s", e_list[0]);
	srand((unsigned)time(NULL));
	for (i = 0; i < 5; i++) {
		random=rand()%500;
		sprintf_s(T, 100,"%s%s", T, e_list[random]);
	}
	sprintf_s(T, 100, "%s$", T);
	n = strlen(T);
	printf("%d\n", n);
	T[n] = NULL;
	SA = (int *)malloc((size_t)n * sizeof(int));
	if (SA == NULL)printf("error\n");//exit(EXIT_FAILURE);
	fclose(fp);
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
	char *F = (char *)malloc((size_t)n * sizeof(char) + 1);
	for (i = 0; i < n; i++) {
		F[i] = T[SA[i]];
	}
	F[n] = NULL;
	printf("T  :%s\nSA :", T);
	for (i = 0; i<n; i++) {
		printf("%3d", SA[i]);
	}
	printf("\nBWT:");
	for (i = 0; i<n; i++) {
		printf("%3c", BWT[i]);
	}
	printf("\nF:%s\n",F);
	free(T);
	free(SA);
	free(BWT);
	return 0;
}

