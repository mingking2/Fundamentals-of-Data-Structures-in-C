#include <stdio.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void perm(char* list, int i, int n);

int main() {
	char A[4][10] = { "GO","BOY","GIRL","GIRLS" };
	for (int i = 0; i < 4; i++) {
		int count = 0;
		int j = 0;
		while (A[i][j] != '\0') {
			count++;
			j++;
		}//count에 글자개수를 입력

		perm(A[i], 0, count - 1);
		printf("\n");
		printf("\n");
	}
	return 0;

}

void perm(char* list, int i, int n)
{
	int j, temp;
	if (i == n) {
		for (j = 0; j <= n; j++)
			printf("%c", list[j]);
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
