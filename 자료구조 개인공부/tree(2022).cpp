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
	i = ++(h->size);	// 마지막 원소의 위치

	while ((i != 1) && (item.priority > h->heap[i / 2].priority)) {
		/*if (item.priority == h->heap[i / 2].priority) {

		}*/
		h->heap[i] = h->heap[i / 2];    // 자식 노드와 부모노드 교환 
		i /= 2;    // 한 레벨 위로 올라감 
	}

	item.num++;
	h->heap[i] = item;    // 새로운 노드 삽입



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
//			child++;    // 오른쪽 자식 노드 선택
//		}
//
//		/* 마지막 노드가 자식 노드보다 크면 종료 */
//		if (temp.priority >= h->heap[child].priority) {
//			break;
//		}
//
//		/* 부모노드와 자식노드 교환 */
//		h->heap[parent] = h->heap[child];
//
//		/* 한 레벨 아래로 이동 */
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
	
	printf("파일 이름? ");
	scanf_s("%s", fname,20);

	fp = fopen(fname,"rt");
	 
	if (fp == NULL) {
		printf("error!\n");
		return 0;
	}

	
	fscanf(fp, "%d", &flength);
	printf("파일 행 개수 :%d\n", flength);

	for (int i = 0; i < flength; i++) {
		fscanf(fp, "%d %d %d", &n[i].arrivetime, &n[i].worktime, &n[i].priority);
	}

	// 파일 데이터 구조체로 이동 잘됫나 확인
	/*for (int i = 0; i < flength; i++) {
		printf("%d %d %d\n", n[i].arrivetime, n[i].worktime, n[i].priority);
	}*/
	

	//FIFO 스케줄링
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

	printf("FIFO Scheduling의 실행 결과:\n");
	printf("	작업수 = %d, 종료시간 = %d, 평균 실행시간 = %.2lf, 평균 대기시간 = %.2lf\n", flength, end, ave_run, ave_wait);

	free(end_time);
	free(run_time);
	free(wait_time);
	
	// 우선순위 스케줄링
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
	
	printf("\nPriority Scheduling의 실행 결과:\n");
	printf("	작업수 = %d, 종료시간 = %d, 평균 실행시간 = %d\n\n", flength,flength,flength);

	for (int i = 1; i <= flength; i++) {
		printf("	우선순위 %d: 작업수 = %d\n", max_heap.heap[i], max_heap.heap[i].num);
	}



}

