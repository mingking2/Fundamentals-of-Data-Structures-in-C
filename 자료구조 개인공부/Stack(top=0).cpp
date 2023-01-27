#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct {
	int key;
}element;
element stack[MAX_STACK_SIZE];
int top = 0;	// 전역 변수

bool IsEmpty();
bool IsFull();
void push(element item);
element pop();
void print();

int main() {
	int num = 0;
	int num1 = 0;
	int num2 = 0;

	printf("Stack Structure!!\n");
	while (1) {
		if (num == 3) break;
		printf("1. push   2. pop   3. print\n");
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			if (IsFull()) {
				printf("stack is Full !!\n");
			}
			else {
				printf("push: ");
				scanf_s("%d", &num1);
				element item;
				item.key = num1;
				push(item);
			}
			break;
		case 2:
			if (IsEmpty()) {
				printf("stack is Empty!!\n");
			}
			else {
				pop();
			}
			break;
		case 3:
			print();
			break;
		default:
			break;
		}

	}


}

bool IsEmpty() {	// top=0 에서 시작하면 top=0일때 비엇다
	if (top == 0) return true;
	else return false;
}

bool IsFull() {		// top=0 이면 MAX_STACK_SIZE -1 보다 크다
	if (top > MAX_STACK_SIZE-1) return true;
	else return false;
}

void push(element item) {		// top=0일때 0번째 칸 부터 값을 넣기 때문에 stack에 값을 집어넣은 후 ++해준다.
	stack[top++] = item;
}

element pop() {
	return stack[--top];
}

void print() {
	for (int i = 0; i < top; i++) {
		printf("%d ", stack[i]);
	}
	printf("\n\n");
}