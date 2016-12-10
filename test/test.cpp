// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define n 12

int compare(const void *arg1, const void *arg2)
{
	/* Compare all of both strings: */
	const char* left_char = *(const char **)arg1;
	const char* right_char = *(const char **)arg2;
	return strcmp(left_char, right_char);
}

void GetSA(const char *T, int *SA) {
	char *p;
	char *str = (char *)malloc(2 * n);
	//char **suffix = (char **)malloc(n+1);
	char *suffix[n];
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
	char T[] = { "mississippi$" };
	int SA[n];
	int i;
	GetSA(T,SA);
	char BWT[n];
	for (i = 0; i < n; i++) {
		if (SA[i] != 0) {
			BWT[i] = T[SA[i] - 1];
		}
		else {
			BWT[i] = '$';
		}
	}
	
	/*printf("T  :%s\nSA :", T);
	for (i = 0; i<n; i++) {
		printf("%2d", SA[i]);
	}
	printf("\nBWT:");
	for (i = 0; i<n; i++) {
		printf("%2c", BWT[i]);
	}
	printf("\n");*/

	return 0;
}

