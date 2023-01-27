#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int key;
} element;

struct stack {
	element data;
	struct stack* link;
};

struct stack* top;

void push(element item);
element pop();
void print();

int main() {
	top = NULL;
	int num = 0;
	
	printf("Stack Structure made by Linked List!!\n");
	while (1) {
		printf("1. push   2. pop   3. print\n");
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			element item;
			printf("push: ");
			scanf_s("%d", &item.key);
			push(item);
			break;
		case 2:
			pop();
			break;
		case 3:
			print();
			break;
		default:
			break;
		}

	}

}

void push(element item) {
	struct stack* temp = (struct stack*)malloc(sizeof(struct stack));
	if (temp == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->data = item;
	temp->link = top;
	top = temp;
}

element pop() {
	struct stack* temp = top;
	element item;
	if (temp == NULL) {
		fprintf(stderr, "The stack is empty\n");
		exit(1);
	}
	item = temp->data;
	top = temp->link;
	free(temp);
	return item;
}

void print() {
	struct stack* ptr;
	printf("--------------------------\n");
	for (ptr = top; ptr != NULL; ptr = ptr->link) {
		printf("%d ", ptr->data);
	}
	printf("\n\n");
}