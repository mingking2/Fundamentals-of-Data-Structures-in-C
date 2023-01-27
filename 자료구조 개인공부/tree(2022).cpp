#define _CRT_SECURE_NO_WARNINGS
#define MAX_LENGTH 1000
#include <stdio.h>
#include <stdlib.h>

struct element {
	//int arrivetime;
	//int worktime;
	int priority;
	int num;
};

struct node {
	element heap[MAX_LENGTH];
	int size;
	//int num=0;

	int arrivetime;
	int worktime;
	int priority;
};


int flength =0;
int end;
double ave_run=0, ave_wait=0;

void insert_max_heap(node* h, element item) {
	int i;
	i = ++(h->size);	// ������ ������ ��ġ

	while ((i != 1) && (item.priority > h->heap[i / 2].priority)) {
		/*if (item.priority == h->heap[i / 2].priority) {

		}*/
		h->heap[i] = h->heap[i / 2];    // �ڽ� ���� �θ��� ��ȯ 
		i /= 2;    // �� ���� ���� �ö� 
	}

	item.num++;
	h->heap[i] = item;    // ���ο� ��� ����



}

//element max_heap_delete(node* h) {
//	int parent, child;
//	element item, temp;
//
//	item = h->heap[1];
//	temp = h->heap[(h->size)--];
//	parent = 1;
//	child = 2;
//
//	while (child <= h->size) {
//		if ((child < h->size) && ((h->heap[child].priority) < h->heap[child + 1].priority)) {
//			child++;    // ������ �ڽ� ��� ����
//		}
//
//		/* ������ ��尡 �ڽ� ��庸�� ũ�� ���� */
//		if (temp.priority >= h->heap[child].priority) {
//			break;
//		}
//
//		/* �θ���� �ڽĳ�� ��ȯ */
//		h->heap[parent] = h->heap[child];
//
//		/* �� ���� �Ʒ��� �̵� */
//		parent = child;
//		child *= 2;
//	}
//
//	h->heap[parent] = temp;
//	return item;
//}

int main() {

	struct node n[1000];
	FILE* fp = NULL;
	char fname[20] = "";
	char buffer[MAX_LENGTH];
	
	printf("���� �̸�? ");
	scanf_s("%s", fname,20);

	fp = fopen(fname,"rt");
	 
	if (fp == NULL) {
		printf("error!\n");
		return 0;
	}

	
	fscanf(fp, "%d", &flength);
	printf("���� �� ���� :%d\n", flength);

	for (int i = 0; i < flength; i++) {
		fscanf(fp, "%d %d %d", &n[i].arrivetime, &n[i].worktime, &n[i].priority);
	}

	// ���� ������ ����ü�� �̵� �ߵ̳� Ȯ��
	/*for (int i = 0; i < flength; i++) {
		printf("%d %d %d\n", n[i].arrivetime, n[i].worktime, n[i].priority);
	}*/
	

	//FIFO �����ٸ�
	int* end_time = (int*)malloc(sizeof(int) * flength);
	int* run_time = (int*)malloc(sizeof(int) * flength);
	int* wait_time = (int*)malloc(sizeof(int) * flength);

	for (int i = 0; i < flength; i++) {
		if (i == 0)	end_time[i] = n[i].arrivetime + n[i].worktime;
		else {
			end_time[i] = end_time[i - 1] + n[i].worktime;
		}
	}

	for (int j = 0; j < flength; j++) {
		run_time[j] = end_time[j] - n[j].arrivetime;
	}

	for (int k = 0; k < flength; k++) {
		wait_time[k] = run_time[k] - n[k].worktime;
	}

	end = end_time[flength - 1];
	for (int i = 0; i < flength; i++) {
		ave_run += run_time[i];
		ave_wait += wait_time[i];
	}
	ave_run /= flength;
	ave_wait /= flength;

	printf("FIFO Scheduling�� ���� ���:\n");
	printf("	�۾��� = %d, ����ð� = %d, ��� ����ð� = %.2lf, ��� ���ð� = %.2lf\n", flength, end, ave_run, ave_wait);

	free(end_time);
	free(run_time);
	free(wait_time);
	
	// �켱���� �����ٸ�
	node max_heap;
	element* item= (element*)malloc(sizeof(element) * flength);
	
	for (int i = 0; i < flength; i++) {
		item[i].priority = n[i].priority;
		//item[i].arrivetime = n[i].arrivetime;
		//item[i].worktime = n[i].worktime;
		item[i].num = 0;
	}
	max_heap.size = flength;
	
	for(int j = 0; j < flength; j++){
		insert_max_heap(&max_heap, item[j]);
	}
	
	printf("\nPriority Scheduling�� ���� ���:\n");
	printf("	�۾��� = %d, ����ð� = %d, ��� ����ð� = %d\n\n", flength,flength,flength);

	for (int i = 1; i <= flength; i++) {
		printf("	�켱���� %d: �۾��� = %d\n", max_heap.heap[i], max_heap.heap[i].num);
	}



}

