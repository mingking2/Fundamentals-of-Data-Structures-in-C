# define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define MAX_SIZE 100000
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))
void sort(int[], int); /*selection sort*/
bool is_sorted(int[], int);
bool binsearch(int list[], int searchnum, int left, int right);
int COMPARE(int x, int y);
int counter;
int main(void)
{
	int i, n;
	int A[MAX_SIZE];
	srand(time(NULL));
	double duration;
	clock_t start,stop;
	printf("Enter the number of numbers to generate: ");
	scanf_s("%d", &n);
	if (n < 1 || n > MAX_SIZE) {
		fprintf(stderr, "Improper value of n\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < n; i++) {/*randomly generate numbers*/
		A[i] = rand() % 100000;
		printf("%d ", A[i]);
	}
	start = clock();
	sort(A, n);
	stop = clock();

	printf("\n Soretd array:\n ");
	for (i = 0; i < n; i++) /* print out sorted numbers */
		printf("%d  ", A[i]);
	printf("\n");

	if (is_sorted(A, n) == true)
		printf("\n올바른 정렬입니다. \n");
	else
		printf("잘못된 정렬입니다. \n");

	printf("실행 시간: %lf\n", (double)(stop - start) / CLOCKS_PER_SEC); // 실행시간 출력
	
	int search = 0;
	while (1) {
		scanf_s("%d", &search);

		if (binsearch(A, search, 0, n - 1)) {
			printf("searchNum을 찾았습니다.\n");
		}
		else
			printf("searchNum을 못 찾았습니다.\n");

		printf("counter = %d\n", counter);
	}
}
void sort(int A[], int n)
{
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (A[j] < A[min])
				min = j;
		SWAP(A[i], A[min], temp);
	}
}

bool is_sorted(int A[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (A[i] > A[i + 1])
			return 0;
	}
	return 1;
}

int COMPARE(int x, int y) {
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1;
}

bool binsearch(int list[], int searchnum, int left, int right)
{
	counter = 0;
	int middle;
	while (left <= right) {
		counter++;
		middle = (left + right) / 2;
		switch (COMPARE(list[middle], searchnum))
		{
		case -1: left = middle + 1;
			break;
		case  0: return 1;
		case  1: right = middle - 1;
		}
	}
	return 0;
}
