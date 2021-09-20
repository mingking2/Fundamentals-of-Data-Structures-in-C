#include <stdio.h>
#include <time.h>
#include<stdlib.h>
#include<math.h>
#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void perm(int* list, int i, int n);

int main() {
	int n;
	scanf_s("%d", &n);
	int list[100];
	for (int i = 0; i < n; i++) {
		list[i] = i + 1;
	}// list에 1~n 까지의 숫자를 입력
	clock_t start = clock();
	perm(list, 0, n - 1);
	clock_t end = clock();
	printf("\n\n실행시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);


}

void perm(int* list, int i, int n)
{
	int j, temp;
	if (i == n) {
		for (j = 0; j <= n; j++)
			printf("%d", list[j]);
		printf(" ");
	}
	else {
		for (j = i; j <= n; j++) {
			SWAP(list[i], list[j], temp);
			perm(list, i + 1, n);
			SWAP(list[i], list[j], temp);
		}
	}
}//순열함수
