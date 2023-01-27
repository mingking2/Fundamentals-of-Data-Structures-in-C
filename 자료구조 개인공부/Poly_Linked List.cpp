#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) (((x)<(y))? -1: ((x)==(y)) ? 0:1)
struct poly {
	int coef;
	int expon;
	struct poly* link;
};
struct poly* a, * b, * d;
struct poly* padd(struct poly* a, struct poly* b);
void attach(float coefficient, int exponent, struct poly** rear);

int main() {
	int c = 0;
	int e = 0;
	a = (struct poly*)malloc(sizeof(struct poly));
	a = NULL;
	b = (struct poly*)malloc(sizeof(struct poly));
	b = NULL;
	printf("Polynomials made by Linked List!!\n\n");

	printf("Polynomial A\n");
	printf("coef  expon(exit : input(-1) )\n");
	while (1) {
		scanf_s("%d %d", &c, &e);
		if (c == -1&&e==-1) break;

		struct poly* ptr = (struct poly*)malloc(sizeof(struct poly));
		ptr->coef = c;
		ptr->expon = e; 
		ptr->link = NULL;


		if (a == NULL) {
			a = ptr;
		}
		else {
			struct poly* exA = NULL;
			for (exA = a; exA->link != NULL; exA = exA->link);
			exA->link = ptr;
		}

	}
	struct poly* temp;
	printf("Polynomial A\n");
	printf("* coef   expon\n");
	for (temp = a; temp != NULL; temp = temp->link) {
		printf("   %d      %d\n", temp->coef, temp->expon);
	}



	printf("Polynomial B\n");
	printf("coef  expon(exit : input(-1) )\n");
	while (1) {
		scanf_s("%d %d", &c, &e);
		if (c == -1 && e == -1) break;

		struct poly* ptr = (struct poly*)malloc(sizeof(struct poly));
		ptr->coef = c;
		ptr->expon = e;
		ptr->link = NULL;


		if (b == NULL) {
			b = ptr;
		}
		else {
			struct poly* exB = NULL;
			for (exB = b; exB->link != NULL; exB = exB->link);
			exB->link = ptr;
		}

	}
	struct poly* temp2;
	printf("Polynomial B\n");
	printf("* coef   expon\n");
	for (temp2 = b; temp2 != NULL; temp2 = temp2->link) {
		printf("   %d      %d\n", temp2->coef, temp2->expon);
	}

	d = (struct poly*)malloc(sizeof(struct poly));
	d = padd(a, b);

	struct poly* temp3;
	printf("Polynomial D\n");
	printf("* coef   expon\n");
	for (temp3 = d; temp3 != NULL; temp3 = temp3->link) {
		printf("   %d      %d\n", temp3->coef, temp3->expon);
	}

}


struct poly* padd(struct poly* a, struct poly* b) {
	struct poly* front, * rear, * temp;
	int sum;
	
	rear = (struct poly*)malloc(sizeof(struct poly));
	if (rear == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	front = rear;
	while (a && b) {
		switch (COMPARE(a->expon, b->expon)) {
		case -1:
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0:
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expon, &rear);
			a = a->link;
			b = b->link;
			break;
		case 1:
			attach(a->coef, a->expon, &rear);
			a = a->link;
		}
	}
	for (; a; a = a->link) attach(a->coef, a->expon, &rear);
	for (; b; b = b->link) attach(b->coef, b->expon, &rear);
	rear->link = NULL;

	temp = front;
	front = front->link;
	free(temp);

	return front;
}

void attach(float coefficient, int exponent, struct poly** rear) {
	struct poly* temp;
	temp = (struct poly*)malloc(sizeof(struct poly));
	if (temp == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->coef = coefficient;
	temp->expon = exponent;
	(*rear)->link = temp;
	*rear = temp;
}