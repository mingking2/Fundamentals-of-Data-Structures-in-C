#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int key;
}element;

struct Queue {
	element data;
	struct Queue* link;
};

struct Queue* front, * rear;

void addq(element item);
element deleteq();
void print();

int main() {
	front = NULL;
	int num = 0;

	printf("Queue Structure made by Linked List!!\n");
	while (1) {
		printf("1. add   2. delete   3. print\n");
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			element item;
			printf("push: ");
			scanf_s("%d", &item.key);
			addq(item);
			break;
		case 2:
			deleteq();
			break;
		case 3:
			print();
			break;
		default:
			break;
		}

	}
}

void addq(element item) {
	struct Queue* temp = (struct Queue*)malloc(sizeof(struct Queue));
	if (temp == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->data = item;
	temp->link = NULL;
	if (front) rear->link = temp;
	else front = temp;
	rear = temp;
}

element deleteq() {
	struct Queue* temp = front;
	element item;
	if (temp == NULL) {
		fprintf(stderr, "The queue is empty\n");
		exit(1);
	}
	item = temp->data;
	front = temp->link;
	free(temp);
	return item;
}

void print() {
	struct Queue* ptr;
	printf("--------------------------\n");
	for (ptr = front; ptr != NULL; ptr = ptr->link) {
		printf("%d ", ptr->data);
	}
	printf("\n\n");
}