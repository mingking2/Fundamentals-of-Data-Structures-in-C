#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef struct node* tree_pointer;
struct node {
	int data;
	struct node* lchild;
	struct node* rchild;
};

int data1 = 0;
tree_pointer yourmom = NULL;


tree_pointer bsearch(tree_pointer root, int data1) {
	tree_pointer ptr = root;
	
	if (ptr == NULL) {
		return NULL;
	}
	
	while(ptr){

		if (ptr->data = data1) {
			return ptr;
		}
		else if (ptr->data < data1) {
			ptr = ptr->rchild;
		}
		else {
			ptr = ptr->lchild;
		}

		yourmom = ptr;
	}

	
}

tree_pointer insert(tree_pointer root, int data1) {
	tree_pointer ptr;
	tree_pointer newNode = (tree_pointer)malloc(sizeof(node));
	newNode->data = data1;
	newNode->lchild = newNode->rchild = NULL;
	
	if (root == NULL) {
		root = newNode;
		return root;
	}

	ptr = root;

	while (ptr) {
		if (data1 == ptr->data) {
			printf("ERROR 중복된 값입니다.");
			return root;
		}
		else if(data1<ptr->data){
			if (ptr->lchild == NULL) {
				ptr->lchild = newNode;
				return root;
			}
			else {
				ptr = ptr->lchild;
			}
		}
		else {
			if (ptr->rchild == NULL) {
				ptr->rchild = newNode;
				return root;
			}
			else {
				ptr = ptr->rchild;
			}
		}
	}
	

	

}

tree_pointer delete_node(tree_pointer root, int data1) {
	tree_pointer del = NULL;
	tree_pointer parent = NULL;
	tree_pointer successor = NULL;
	tree_pointer predecessor = NULL;
	tree_pointer child = NULL;

	del = root;
	while (del != NULL) {
		if (data1 == del->data) {
			break;
		}
		parent = del;
		if (data1 < del->data) {
			del = del->lchild;
		}
		else {
			del = del->rchild;
		}
	}

	if (del == NULL) {
		printf("ERROR : 존재하지 않는 데이터\n");
		return root;
	}

	if (del->lchild == NULL && del->rchild == NULL) {
		if (parent != NULL) {
			if (parent->lchild == del) {
				parent->lchild = NULL;
			}
			else {
				parent->rchild = NULL;
			}
		}
		else {
			root = NULL;
		}
	}
	else if (del->lchild != NULL && del->rchild != NULL) {
		predecessor = del;
		successor = del->lchild;

		while (successor->rchild != NULL) { // 왼쪽 서브트리에서 가장 큰 값 찾기
			predecessor = successor;
			successor = successor->rchild;
		}

		predecessor->rchild = successor->lchild;	// 중간에 비워서 연결
		successor->lchild = del->lchild;		// successor 노드를 삭제한 노드위치로 이동하여 기존것과 연결
		successor->rchild = del->rchild;		// 위와 같다

		if (parent != NULL) {
			if (parent->lchild == del) {
				parent->lchild = successor;
			}
			else {
				parent->rchild = successor;
			}
		}
		else {
			root = successor;
		}

	}
	else {
		if (del->lchild != NULL) {
			child = del->lchild;
		}
		else {
			child = del->rchild;
		}

		if (parent != NULL) {
			if (parent->lchild == del) {
				parent->lchild = child;
			}
			else {
				parent->rchild = child;
			}
		}
		else {
			root = child;
		}
	}
	
	free(del);
	return root;
}

void inorder(struct node* ptr) {
	if (ptr) {
		inorder(ptr->lchild);
		printf("%d ", ptr->data);
		inorder(ptr->rchild);
	}
};

int top = -1;
tree_pointer stack[MAX_STACK_SIZE];

void push(tree_pointer node) {
	stack[++top] = node;
}

tree_pointer pop() {
	return stack[top--];
}

void iter_inorder(tree_pointer node) {
	for (;;) {
		for (; node; node = node->lchild)
			push(node);
		node = pop();
		if (!node) break;
		printf("%d ", node->data);
		node = node->rchild;
	}
}

void preorder(struct node* ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}

int front = 0, rear = 0;
tree_pointer queue[MAX_QUEUE_SIZE];

void addq(tree_pointer ptr) {
	queue[++rear] = ptr;
}

tree_pointer deleteq() {
	return queue[++front];
}

void level_order(tree_pointer ptr) {
	if (!ptr) return;
	addq(ptr);
	for (;;) {
		ptr = deleteq();
		if (ptr == NULL) break;
		printf("%d ", ptr->data);
		if (ptr->lchild)
			addq(ptr->lchild);
		if (ptr->rchild)
			addq(ptr->rchild);
	}
}

void postorder(struct node* ptr) {
	if (ptr) {
		postorder(ptr->lchild);
		postorder(ptr->rchild);
		printf("%d ", ptr->data);
	}
}


int main() {
	tree_pointer root = NULL;
	tree_pointer ptr = NULL;
	root = insert(root, 7);
	root = insert(root, 3);
	root = insert(root, 8);
	root = insert(root, 1);
	root = insert(root, 5);
	root = insert(root, 4);
	root = insert(root, 10);
	
	//printf("\n 검색결과 : %d \n", bsearch(root, 4)->data);

	printf("\n * inorder * \n");
	inorder(root);
	printf("\n");

	printf("\n * iter_inorder * \n");
	iter_inorder(root);
	printf("\n");


	printf("\n * preorder * \n");
	preorder(root);
	printf("\n");

	printf("\n * level_order * \n");
	level_order(root);
	printf("\n");


	printf("\n * postorder * \n");
	postorder(root);
	printf("\n");

	ptr = bsearch(root, 7);
	printf("%d\n", ptr->data);

	root = delete_node(root, 7);
	ptr = bsearch(root, 7);

	return 0;

}