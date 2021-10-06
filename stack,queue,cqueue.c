#include <stdio.h>
#include <stdlib.h>

int MAX_STACK_SIZE = 10; //스택의 수
int MAX_QUEUE_SIZE = 10; //큐의 수
int MAX_CQUEUE_SIZE = 10; //원형 큐의 수

typedef struct {
	int key;
}element;

element* stack = (element*)malloc(sizeof(int) * MAX_STACK_SIZE); //스택을 동적 할당
element* queue = (element*)malloc(sizeof(int) * MAX_QUEUE_SIZE); //큐를 동적 할당
element* cqueue = (element*)malloc(sizeof(int) * MAX_CQUEUE_SIZE); //원형 큐를 동적 할당

int top = -1; //스택의 top
int front = -1; //큐의 front
int rear = -1; //큐의 rear
int crear = -1; //원형 큐의 rear
int cfront = -1; //원형 큐의 front

void push(element item); //스택의 삽입 함수
element pop(); //스택의 삭제 함수
void stackFull(); //스택이 가득 찼을 때
element stackEmpty(); //스택이 비었을 때
void showstack(); //모든 스택을 출력

void addq(element item); //큐의 삽입 함수
element deleteq(); //큐의 삭제 함수
void queueFull(); //큐가 가득 찼을 때
element queueEmpty(); //큐가 비었을 때
void showqueue(); //모든 큐를 출력

void addcq(element item); //원형 큐의 삽입 함수
element cdelete(); //원형 큐의 삭제 함수
void cqueueFull(); //원형 큐가 가득 찼을 때
element cqueueEmpty(); //원형 큐가 비었을 때 
void printcqueue(); //모든 원형 큐를 출력

void push(element item) {
	if (top >= MAX_STACK_SIZE - 1) {
		stackFull();
	}
	stack[++top]=item;
}

element pop() {
	if (top == -1) {
		return stackEmpty();
	}
	return stack[top--];
}

void stackFull() {
	MAX_STACK_SIZE = MAX_STACK_SIZE * 2;
	stack = (element*)realloc(stack, sizeof(int) * MAX_STACK_SIZE); //realloc으로 동적 할당
 }

element stackEmpty() {
	fprintf(stderr, "스택이 비었습니다. \n");
	exit(EXIT_FAILURE);
}

void showstack() {
	printf("현재 스택\n");
	for (int i = 0; i < top + 1; i++) {
		printf("stack[%d] : %d\n", i, stack[i]);
	}
}

void addq(element item) {
	if (rear == MAX_QUEUE_SIZE) { //큐가 가득 참
		queueFull();
	}
	queue[++rear] = item;
}
element deleteq() {
	if (front == rear) { //큐가 빔
		return queueEmpty(); 
	}
	return queue[++front];
}
void queueFull() {
	MAX_QUEUE_SIZE = MAX_QUEUE_SIZE * 2;
	queue = (element*)realloc(queue, sizeof(int) * MAX_QUEUE_SIZE); //realloc으로 동적 할당
}
element queueEmpty() {
	fprintf(stderr, "큐가 비었습니다. \n");
	exit(EXIT_FAILURE);
}
void showqueue() {
	printf("현재 큐\n");
	int j = 0;
	for (int i = front + 1; i < rear + 1; i++) {
		printf("queue[%d] : %d\n", j, queue[i]);
		j++;
	}
}

void addcq(element item) {
	crear = (crear + 1) % MAX_CQUEUE_SIZE; //원형 큐가 가득참
	if (cfront == crear) {
		cqueueFull();
	}
	cqueue[crear] = item;
}

element cdelete() {
	if (cfront == crear) {
		return cqueueEmpty();
	}
	cfront = (cfront + 1) % MAX_CQUEUE_SIZE;
	return cqueue[cfront];
}

void cqueueFull() {
	fprintf(stderr, "원형 큐가 가득 찼습니다. \n");
	exit(EXIT_FAILURE);
}
element cqueueEmpty() {
	fprintf(stderr, "원형 큐가 비었습니다. \n");
	exit(EXIT_FAILURE);
}
void showcqueue() {
	printf("현재 원형 큐\n");
	for (int i = cfront + 1; i < crear + 1; i++) {
		printf("cqueue : %d\n", cqueue[i]);
	}
}

int main() {
	int number;
	while (1) {
		printf("================================\n");
		printf(" 1. 스택\n");
		printf(" 2. 큐\n");
		printf(" 3. 원형 큐\n");
		printf("================================\n");

		printf("번호를 입력하세요>> ");
		scanf_s("%d", &number);
		switch (number) {
		case 1:
			int n1;
			printf("스택을 몇번 실행할까요? :");
			scanf_s("%d", &n1);
			for (int i = 0; i < n1; i++) {
				int choice;
				printf("1. push\t2. pop\t");
				scanf_s("%d", &choice);
				if (choice == 1) {
					element num;
					printf("push할 숫자를 입력하세요. ");
					scanf_s("%d", &num.key);
					push(num);
				}
				else if (choice == 2) {
					element num = pop();
					printf("pop  :  %d\n", num.key);
				}
				else {
					printf("잘못된 입력입니다. \n");
				}
				showstack();
			}
			break;
		case 2:
			int n2;
			printf("큐를 몇번 실행할까요? :");
			scanf_s("%d", &n2);
			for (int i = 0; i < n2; i++) {
				int choice;
				printf("1. add\t2. delete\t");
				scanf_s("%d", &choice);
				if (choice == 1) {
					element num;
					printf("add할 숫자를 입력하세요. ");
					scanf_s("%d", &num.key);
					addq(num);
				}
				else if (choice == 2) {
					element num = deleteq();
					printf("delete  :  %d\n", num.key);
				}
				else {
					printf("잘못된 입력입니다. \n");
				}
				showqueue();
			}
			break;
		case 3:
			int n3;
			printf("원형큐를 몇번 실행할까요? :");
			scanf_s("%d", &n3);
			for (int i = 0; i < n3; i++) {
				int choice;
				printf("1. add\t2. delete\t");
				scanf_s("%d", &choice);
				if (choice == 1) {
					element num;
					printf("add할 숫자를 입력하세요. ");
					scanf_s("%d", &num.key);
					addcq(num);
				}
				else if (choice == 2) {
					element num = cdelete();
					printf("delete  :  %d\n", num.key);
				}
				else {
					printf("잘못된 입력입니다. \n");
				}
				showcqueue();
			}
			break;
		default:
			return 0;
		}
	}
	
}
