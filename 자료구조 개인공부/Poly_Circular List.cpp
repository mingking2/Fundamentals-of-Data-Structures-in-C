#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) (((x)<(y))? -1: ((x)==(y)) ? 0:1)

struct poly {
	int coef;
	int expon;
	struct poly* link;
};

struct poly* avail;

struct poly* get_node(void);
void ret_node(struct poly* ptr);
void cerase(struct poly** ptr);
struct poly* cpadd(struct poly* a, struct poly* b);
void attach(float coefficient, int exponent, struct poly** rear);

int main() {

}

struct poly* get_node(void) {
	struct poly* node;
	if (avail != NULL) {
		node = avail;
		avail = avail->link;
	}
	else {
		node = (struct poly*)malloc(sizeof(struct poly));
		if (IS_FULL(node)) {
			fprintf(stderr, "The memory is full \n");
			exit(1);
		}
	}
	return node;
}

void ret_node(struct poly* ptr) {
	ptr->link = avail;
	avail = ptr;
}

void cerase(struct poly** ptr) {
	struct poly* temp;
	if (*ptr) {
		temp = (*ptr)->link;
		(*ptr)->link = avail;
		avail = temp;
		*ptr = NULL;
	}
}

struct poly* cpadd(struct poly* a, struct poly* b) {
	struct poly* starta, * d, * lastd;
	int sum, done = false;
	starta = a;
	a = a->link; b = b->link;
	d = get_node();
	d->expon = -1; lastd = d;
	do {
		switch (COMPARE(a->expon, b->expon)) {
		case -1:
			attach(b->coef, b->expon, &lastd);
			b = b->link;
			break;
		case 0:
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expon, &lastd);
			a = a->link;
			b = b->link;
			break;
		case 1:
			attach(a->coef, a->expon, &lastd);
			a = a->link;

		}
	} while (!done);
	lastd->link = d;
	return d;
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