#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAPACITY 3
#define BUFFER_SIZE 50

char** names;
char** numbers;

int capacity = INIT_CAPACITY;
int n = 0;

char delin[] = " ";

void init_directory() {
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}

int read_line(char str[], int limit) {
	int ch, i = 0;

	while ((ch = getchar()) != '\n') {
		if (i < limit - 1)
			str[i++] = ch;
	}

	//str[i] = '\n';
	return i;
}

void add(char* argument1, char* argument2) {
	int min;
	char** temp1, **temp2, *temp;

	if (n <= capacity) {
		names[n] = _strdup(argument1);
		numbers[n++] = _strdup(argument2);
	}
	
	else {
		capacity *= 2;
		temp1 = (char**)malloc(sizeof(char*) * capacity);
		temp2 = (char**)malloc(sizeof(char*) * capacity);
		for (int i = 0; i < n; i++) {
			temp1[i] = names[i];
			temp2[i] = names[i];
		}
		names = (char**)malloc(capacity * sizeof(char*));
		numbers = (char**)malloc(capacity * sizeof(char*));
		for (int i = 0; i < n; i++) {
			names[i] = temp1[i];
			numbers[i] = temp2[i];
		}
	}

	//정렬
	for (int i = 0; i < n; i++) {
		for (int j = i;j < n; j++) {
			if (strcmp(names[i], names[j]) > 0) {
				temp = _strdup(names[i]);
				names[i] = _strdup(names[j]);
				names[j] = _strdup(temp);
				temp = _strdup(numbers[i]);
				numbers[i] = _strdup(numbers[j]);
				numbers[j] = _strdup(temp);
			}
		}
	}

	printf("%s was added successfully.\n", argument1);

	return;
}

void find(char* argument1) {


	for (int i = 0; i < n; i++) {
		if (strcmp(names[i], argument1) == 0) {
			printf("%s\n", numbers[i]);
			return;
		}
	}
	printf("No person named '%s' exists.\n", argument1);
	return;
}

void status() {
	for (int i = 0; i < n; i++) {
		printf("%s %s", names[i], numbers[i]);
		printf("\n");
	}
	printf("Total %d persons.\n", n);
}

void remove(char* command1) {
	int index = -1;

	for (int i = 0; i < n; i++) {
		if (strcmp(names[i], command1) == 0) {
			if (i == n - 1) {
				n--;
				printf("%s was deleted successfully.\n", command1);
				return;
			}
			for (int j = i; j < n - 1; j++) {
				names[j] = names[j + 1];
				numbers[j] = numbers[j + 1];
				index = i;
			}
		}
	}

	if (index == -1)
		printf("No person named '%s' exists.\n", command1);

	else {
		n--;
		printf("%s was deleted successfully.\n", command1);
	}
}

void load(char* argument1) {
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];
	printf("[%s]", argument1);
	if (strcmp(argument1, "directory.txt") == 0)
		printf("같습니다.");
	else
		printf("다릅니다.");

	FILE* pFile = fopen(argument1, "r");

	if (pFile == NULL) {
		printf("File name required\n");
		return;
	}

	for (int i = 0; i < 4; i++) {
		fscanf(pFile, "%s", buf1);
		names[n] = _strdup(buf1);

		fscanf(pFile, "%s", buf2);
		numbers[n++] = _strdup(buf2);
	}
	fclose(pFile);
}

void save(char* argument) {
	FILE* file = fopen(argument, "w");

	if (file == NULL)
		printf("File name required");

	for (int i = 0; i < n; i++) {
		fprintf(file, "%s %s\n", names[i], numbers[i]);
	}
	fclose(file);
}

int process_command() {

	while (1) {
		char command_line[BUFFER_SIZE] = { NULL };
		char* command = NULL, * argument1 = NULL, * argument2 = NULL;
		printf("$ ");

		read_line(command_line, BUFFER_SIZE);

		command = strtok(command_line, " ");
		argument1 = strtok(NULL, " ");

		printf("%s\n", command);
		printf("%s\n\n", argument1);

		if (strcmp(command, "read") == 0) {
			load(argument1);	//new
		}
		else if (strcmp(command, "add") == 0) {
			argument2 = strtok(NULL, " ");
			add(argument1, argument2);
		}
		else if (strcmp(command, "find") == 0) {
			find(argument1);
		}
		else if (strcmp(command, "status") == 0)		status();
		else if (strcmp(command, "delete") == 0) {
			remove(argument1);
		}
		else if (strcmp(command, "save") == 0) {
			save(argument1);	//new
		}
		else if (strcmp(command, "exit") == 0)			return 0;
		else printf("명령어를 다시 입력하세요.\n");
	}
}

int main() {
	init_directory();		//names, numbers 생성
	process_command();		//사용자 명령어 입력부
	return 0;
}