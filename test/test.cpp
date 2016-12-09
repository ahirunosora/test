// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define n 11

//int compare(const void *arg1, const void *arg2)
//{
	/* Compare all of both strings: */
	//return strcmp(*(char**)arg1, *(char**)arg2);
//}*/

int *GetSA(const char *T, int *SA) {
	char *p;
	char *str = (char *)malloc(2 * n);
	char **suffix = (char **)malloc(n+1);
	int j = 0;
	int k = 0;
	for (int i = 0; i < n; i++)str[k++] = T[i];
	for (int i = 0; i < n; i++)str[k++] = T[i];
	p = str;
	int length = k - 1;
	//*suffix = p;
	while (j < length) {
		*(suffix + j) = p + j;
		j++;
		if (j == n)break;
	}
	char *T2 = str;
	//qsort(*suffix,n,sizeof(char*),compare);
	for (int i = 0; i < n; i++) SA[i] = suffix[i] - T2;
	return SA;
}

int main() {
	char T[] = { "mississippi" };
	int SA[n];
	int *sa;
	int a;
	sa = GetSA(T,SA);
	printf("T:%s\nSA:", T);
	for (int i = 0; i<n; i++) {
		printf("%d", sa[i]);
	}
	return 0;
}

