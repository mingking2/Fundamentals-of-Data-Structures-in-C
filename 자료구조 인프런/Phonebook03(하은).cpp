#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 3
#define BUFFER_SIZE 50

char** names;
char** numbers;

int capacity = INIT_CAPACITY;
int n = 0;

char delim[] = " ";

void add(char* name, char *number) {
	if (n >= capacity) {
		capacity *= 2;
		char** tmp1 = (char**)malloc(capacity * sizeof(char*));
		char** tmp2 = (char**)malloc(capacity * sizeof(char*));

		for (int i = 0; i < n; i++) {
			tmp1[i] = names[i];
			tmp2[i] = numbers[i];
		}

		free(names);
		free(numbers);

		names = tmp1;  // 포인터 바꾸기
		numbers = tmp2;  // 포인터 바꾸기
	}

	int i = n - 1;	
	while (i >= 0 && strcmp(names[i], name) > 0){												
		names[i + 1] = names[i];	
		numbers[i + 1] = numbers[i];
		i--;
	}

	names[i + 1] = _strdup(name);
	numbers[i + 1] = _strdup(number);
	n++;
}

void find(char *name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(names[i], name) == 0) printf("%s\n", numbers[i]);
		return;
	}
	printf("No person named '%s' exists.\n", name);
}

void status() {
	for (int i = 0; i < n; i++) {
		printf("%s %s\n", names[i], numbers[i]);
	}
	printf("Total %d person.\n", n);
}

void remove(char *name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(names[i], name) == 0) {
			for (int j = i; j < n - 1; j++) {
				names[j] = names[j + 1];
				numbers[j] = numbers[j + 1];
			}
			n--;
			printf("'%s' was deleted successfully. \n", name);
			return;
		}
	}
	printf("NO person named '%s' exists\n", name);
}

void load(char *fileName) {
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("fail\n");
		return;
	}

	while (fscanf(fp, "%s", buf1) != EOF) {
		fscanf(fp, "%s", buf2);
		names[n] = _strdup(buf1);
		numbers[n] = _strdup(buf2);
		n++;
	}

	fclose(fp);
}

void save(char *fileName) {
	int i;
	char tmp[BUFFER_SIZE];

	FILE* fp = fopen(fileName, "w");

	for (i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}

	fclose(fp);
}

int read_line(char str[], int limit) {
	int ch, i = 0;

	while ((ch = getchar()) != '\n') {
		if (i < limit - 1) str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

void init_directory() {
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}

void process_command() {
	char command_line[BUFFER_SIZE];
	char* command, * argument1, * argument2;

	while (1) {
		printf("$ ");

		if (read_line(command_line, BUFFER_SIZE) <= 0) continue;

		command = strtok(command_line, " ");
		if (command == NULL) continue;

		if (strcmp(command, "read") == 0) {
			argument1 = strtok(NULL, " ");

			if (argument1 == NULL) {
				printf("File name required\n");
				continue;
			}
			load(argument1);
		}
		else if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, " ");
			argument2 = strtok(NULL, " ");

			if (argument1 == NULL || argument2 == NULL) {
				printf("Invlid arguments\n");
				continue;
			}
			add(argument1, argument2);
			printf("%s was added successfully\n", argument1);
		}
		else if (strcmp(command, "find") == 0) {
			argument1 = strtok(NULL, " ");
			if (argument1 == NULL) {
				printf("Invlid arguments\n");
				continue;
			}
			find(argument1);
		}
		else if (strcmp(command, "status") == 0) status();
		else if (strcmp(command, "remove") == 0) {
			argument1 = strtok(NULL, " ");
			if (argument1 == NULL) {
				printf("Invlid arguments\n");
				continue;
			}
			remove(argument1);
		}
		else if (strcmp(command, "save") == 0) {
			argument1 = strtok(NULL, " ");
			argument2 = strtok(NULL, " ");
			if (strcmp("as", argument1) != 0) {
				printf("Invalid command format\n");
				continue;
			}
			save(argument2);
		}
		else if (strcmp(command, "exit") == 0) break;
	}
}

int main() {
	init_directory();
	process_command();
	return 0;
}