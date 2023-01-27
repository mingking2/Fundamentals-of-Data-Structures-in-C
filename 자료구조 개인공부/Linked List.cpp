#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *link;
};
struct node *ptr= (struct node*)malloc(sizeof(struct node));

void insert(struct node** start, struct node* before, int input_data);
void delete_(struct node** start, struct node* before, struct node* A);
void print();

int main() {
	int num = 0;
	int num1 = 0;
	int num2 = 0;
	int ch = 0;
	int checknum = 0;

	ptr = NULL;
	printf("Linked List !!\n");
	while (1) {
		int checknum = 0;
		printf("1. insert   2. delete   3. print\n");
		scanf_s("%d", &num);
		switch (num)
		{
		case 1:
			if (ptr == NULL) {
				struct node* before = NULL;
				printf("insert: ");
				scanf_s("%d", &num1);
				insert(&ptr, before, num1);
			}
			else {
				print();
				struct node* ch;
				for (ch = ptr; ch != NULL; ch = ch->link) {
					checknum++;
				}
				printf("\ninsert location : ");
				for (int i = 0; i <= checknum; i++) printf("%d ", i);
				printf("\nlocation: ");
				scanf_s("%d", &num1);
				struct node* before = ptr;
				if (num1 != 0) {
					for (int i = 0; i < num1 - 1; i++) {
						before = before->link;
					}
					printf("insert: ");
					scanf_s("%d", &num2);
					insert(&ptr, before, num2);
				}
				else {
					struct node* first = (struct node*)malloc(sizeof(struct node));
					printf("insert: ");
					scanf_s("%d", &num2);
					first->data = num2;
					first->link = ptr;
					ptr = first;
				}
			}
			break;
		case 2:
			ch = -1;
			checknum = 0;
			if (ptr != NULL) {
				printf("choose data: ");
				scanf_s("%d", &num1);
				struct node* del;
				for (del = ptr; del != NULL; del = del->link) {
					if (del->data == num1) {
						ch = 0;
						break;
					}
					checknum++;
				}
				if (ch == 0) {
					struct node* before = ptr;
					if (checknum != 0) {
						for (int i = 0; i < checknum - 1; i++) {
							before = before->link;
						}
						delete_(&ptr, before, before->link);
					}
					else {
						ptr = ptr->link;
					}
				}
				else {
					printf("\nWrong Data in Linked List!\n");
				}
			}
			else {
				printf("\nNo Data in Linked List!\n");
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

void insert(struct node** start, struct node* before, int input_data) {
	struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->data = input_data;
	if (*start != NULL) {
		temp->link = before->link;
		before->link = temp;
	}
	else {
		temp->link = NULL;
		*start = temp;
	}

}

void delete_(struct node** start, struct node* before, struct node* A) {
	if (before != NULL) before->link = A->link;
	else *start = (*start)->link;
	free(A);
}

void print() {
	printf("Linked List -> ");
	struct node* ptr1;
	for (ptr1 = ptr; ptr1 != NULL; ptr1 = ptr1->link)
	{
		printf("%d ", ptr1->data);
	}
	printf("\n\n");
}