#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int a[MAX_SIZE];
int min = 0;
int ch = 0;

void sort(int a[]) {
	for (int i = 0; i < MAX_SIZE; i++) {
		min = a[i]; 
		for (int j = i+1; j < MAX_SIZE; j++) {
			if (min > a[j]) {
				min = a[j];
				ch = j;
			}
		}
		a[ch] = a[i];
		a[i] = min;
	}

	printf("\n* selection_sort *\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		if (i % 10 == 0) printf("\n");
		printf("%3d ", a[i]);
	}
}

int main() {
	srand((unsigned)time(NULL));

	for (int i = 0; i < MAX_SIZE; i++) {
		a[i] = (rand() % MAX_SIZE) +1;
		for (int j = 0; j < i; j++) {
			if (a[i] == a[j]) i--;
		}
	}

	printf("\n* array a *\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		if (i % 10 == 0) printf("\n");
		printf("%3d ", a[i]);
	}
	printf("\n");

	sort(a);
}