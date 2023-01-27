#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>


typedef struct Sudoku {
	int row;
	int col;
	int value;
}sudoku;

int board[9][9] = { 0 };
int index = 0;

void solve();
bool check(int r, int c, int n);
void show();
bool isfull();
void firstfill();

void solve() {
	int r = -1;
	int c = -1;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] == 0) {
				r = i;
				c = j;
				break;
			}
		}
		if (r != -1 && c != -1) break;
	}

	if (r == -1 && c == -1) show();

	for (int i = 1; i <= 9; i++) {
		if (check(r, c, i)) {
			board[r][c] = i;
			solve();
			board[r][c] = 0;
		}
		if (isfull()) break;

	}

}

void firstfill() {
	int r = -1;
	int c = -1;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {

			int ans[9] = { 1,2,3,4,5,6,7,8,9 };
			int count = 0;

			if (board[i][j] == 0) {
				r = i;
				c = j;
				for (int h = 0; h < 9; h++) {
					for (int g = 0; g < 9; g++) {
						if (board[r][h] == ans[g]) {
							ans[g] = 0;
						}
					}
				}
				for (int m = 0; m < 9; m++) {
					for (int k = 0; k < 9; k++) {
						if (board[m][c] == ans[k]) {
							ans[k] = 0;
						}
					}
				}

				for (int a = (r / 3) * 3; a < (r / 3) * 3 + 3; a++) {
					for (int b = (c / 3) * 3; b < (c / 3) * 3 + 3; b++) {
						for (int d = 0; d < 9; d++) {
							if (board[a][b] == ans[d]) {
								ans[d] = 0;
							}
						}
					}
				}

				for (int q = 0; q < 9; q++) {
					if (ans[q] != 0) count++;
				}
				for (int w = 0; w < 9; w++) {
					if (count == 1 && ans[w] != 0) {
						board[r][c] = ans[w];
						firstfill();
					}
				}

			}
		}
	}

}

bool isfull() {
	int x = -1;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] == 0) {
				x = 1;
			}
		}
	}
	if (x == -1) return true;
	else return false;
}


bool check(int r, int c, int n) {
	for (int i = 0; i < 9; i++) {
		if (board[r][i] == n) return false;
	}

	for (int i = 0; i < 9; i++) {
		if (board[i][c] == n) return false;
	}

	for (int i = (r / 3) * 3; i < (r / 3) * 3 + 3; i++) {
		for (int j = (c / 3) * 3; j < (c / 3) * 3 + 3; j++) {
			if (board[i][j] == n) return false;
		}
	}

	return true;

}

void show() {
	if (isfull()) {
		index += 1;
		printf("해답 %d: \n", index);
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (j != 0 && j % 3 == 0) printf("| ");
			if (board[i][j] == 0) printf("- ");
			else printf("%d ", board[i][j]);

		}

		if (i % 3 == 2 && i != 8) printf("\n======+=======+=======");
		printf("\n");
	}
	printf("\n");
}


int main() {
	FILE* fp;
	int i, n;

	char fname[100];
	printf("파일 이름? ");
	scanf("%s", fname);

	fp = fopen(fname, "r");

	if (fp == NULL) {
		printf("error!\n");
		return 0;
	}
	fscanf(fp, "%d", &n);


	sudoku* arry = (sudoku*)malloc(sizeof(sudoku) * n);
	for (int i = 0; i < n; i++) {
		fscanf(fp, "%d %d %d", &arry[i].row, &arry[i].col, &arry[i].value);
	}

	// txt파일에서 데이터 받아온거 확인
	/*for (int i = 0; i < n; i++) {
		printf("%d %d %d", arry[i].row, arry[i].col, arry[i].value);
		printf("\n");
	}*/


	for (int i = 0; i < n; i++) {
		board[arry[i].row][arry[i].col] = arry[i].value;
	}

	// arry1 배열에 데이터 들어간거 확인
	/*for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d ", arry1[i][j]);
		}
		printf("\n");
	}*/

	printf("Problem:\n");
	show();
	printf("\n");


	printf("후보가 하나인 cell의 값을 할당한 결과 : \n");
	firstfill();
	show();

	printf("\n");
	solve();

	printf("\n해답의 수: %d\n", index);





}
