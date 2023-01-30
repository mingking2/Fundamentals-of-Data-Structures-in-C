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
char* value[1];

char delim[] = " ";


void add(char* name, char* number);
void load(char* name);
void find(char* name);
void status();
void remove(char* name);
void save(char* fileName);
void init_directory();
void process_command();

int main() {
	init_directory(); 
	process_command(); //사용자의 명령을 받아 처리하는 부분
	return 0;
}

void init_directory() {//이 함수에서 배열 names와 numbers를 생성
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));

}

int read_line(char str[], int limit) {
	int ch, i = 0;
	while ((ch = getchar()) != '\n') {
		if (i < limit - 1) {
			str[i++] = ch;
		}
	}
	str[i] = '\0';
	return i;
}


void process_command() {
	char command_line[BUFFER_SIZE];
	char* command, * argument1, * argument2;

	while (1) {
		printf("$ ");
		
		if (read_line(command_line, BUFFER_SIZE) <= 0)
			printf("입력된 값이 없습니다.");

		command = strtok(command_line, " ");

		if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, " ");
			argument2 = strtok(NULL, " ");
			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid arguments");
			}
			else
				add(argument1, argument2);
		}

		if (strcmp(command, "read") == 0) {
			argument1 = strtok(NULL, " ");
			if (argument1 == NULL) {
				printf("File name required");
			}
			else
				load(argument1);
		}

		else if (strcmp(command, "find") == 0) {
			argument1 = strtok(NULL, " ");
			find(argument1);
		}

		else if (strcmp(command, "status") == 0)
			status();

		else if (strcmp(command, "delete") == 0) {
			argument1 = strtok(NULL, " ");
			remove(argument1);
		}

		else if (strcmp(command, "save") == 0) {
			argument1 = strtok(NULL, " ");
			argument2 = strtok(NULL, " ");
			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid arguments");
			}
			else
				save(argument2);
		}

		else if (strcmp(command, "exit") == 0)
			break;
	}
}



void add(char *name, char *number) {

	if (n >= INIT_CAPACITY) {
		capacity *= 2;
		char** names1 = (char**)malloc(capacity * sizeof(char*));
		char** numbers2 = (char**)malloc(capacity * sizeof(char*));

		for (int i = 0; i < n; i++) {
			names1[i] = names[i];
			numbers2[i] = numbers[i];
		}
		
		free(names);
		free(numbers);
		names = names1;
		names = numbers2;
	}

	names[n] = _strdup(name);
	numbers[n] = _strdup(number);
	n++;
	
	int i = 0;
	for (i = n-1; i > 0; i--) {
		if (strcmp(names[n], names[i]) < 0) {
			break;
		}
	}

	for (int j = n; j > i; j--) {
		names[j + 1] = names[j];
		numbers[j + 1] = numbers[j];
	}
	names[i] = _strdup(name);
	numbers[i] = _strdup(number);

	printf("%s was added succesfully.\n", names[n - 1]);
}

void find(char *name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0) {
			printf("find %s.\n", names[i]);
			printf("%s\n", numbers[i]);
			return;
		}
	}
	printf("그런 사람 없어요\n");
}

void status() {

	int i = 0;
	for (i = 0; i < n; i++) {
		printf("%s %s\n", names[i], numbers[i]);
	}
	printf("total %d persons\n", i);
}

void remove(char *name) {

	for (int i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0) {
			names[i] = names[n - 1];
			numbers[i] = numbers[n - 1];
			n--;
			return;
		}
	}

}

void load(char * fileName) { //파일 읽어오기
	char buf1[BUFFER_SIZE];
	int i = 2;
	int L = 0;
	int R = 0;
	FILE* in_fp = fopen(fileName, "r");
	while (fscanf(in_fp, "%s", buf1) != EOF) {
		if (i % 2 == 0) {
			names[L] = _strdup(buf1);
			L++;
		}
		else {
			numbers[R] = _strdup(buf1);
			R++;
		}
		i++;
	}
	n = R;

	fclose(in_fp);
}


void save(char *fileName) {//현재 buffer 파일로 저장하기
	int i;
	char tmp[BUFFER_SIZE];
	FILE* out_fp = fopen(fileName, "w");
	for (int i = 0; i < n; i++) {
		fprintf(out_fp, "%s %s\n", names[i], numbers[i]);
	}

	fclose(out_fp);
}

