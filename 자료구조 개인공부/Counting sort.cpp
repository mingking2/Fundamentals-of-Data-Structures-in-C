#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int a[MAX_SIZE];
int row_terms[MAX_SIZE];
int starting_pos[MAX_SIZE];

void fast_transpose(int a[]) {
	for (int i = 0; i < MAX_SIZE; i++) {
		row_terms[i] = 0;
		starting_pos[i] = 0;
	}

	for (int i = 0; i < MAX_SIZE; i++) {
		row_terms[a[i]]++;
	}

	for (int i = 0; i < MAX_SIZE-1; i++) {
		starting_pos[i + 1] = row_terms[i] + starting_pos[i];
	}

	printf("\n* array A *\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		if (i % 10 == 0) printf("\n");
		printf("%3d ", a[i]);
	}

	printf("\n* row_terms *\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		if (i % 10 == 0) printf("\n");
		printf("%d ",row_terms[i]);
	}

	printf("\n* starting_pos *\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		if (i % 10 == 0) printf("\n");
		printf("%3d ", starting_pos[i]);
	}
}

void sort(int a[]) {
	int sorted[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++) {
		sorted[i] = 0;
	}

	for (int i = 0; i < MAX_SIZE; i++) {
		sorted[starting_pos[a[i]]]=a[i];
		starting_pos[a[i]]++;
	}

	printf("\n* sorted *\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		if (i % 10 == 0) printf("\n");
		printf("%3d ", sorted[i]);
	}
}

int main() {
	srand(time(NULL));
	
	for (int i = 0; i < MAX_SIZE; i++) {
		int random = rand() % MAX_SIZE;
		a[i] = random;
	}

	fast_transpose(a);
	printf("\n");
	sort(a);

}