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

void arr_create() {
	capacity *= 2;

	char** copy_name = (char**)malloc(sizeof(char*) * capacity);
	char** copy_number = (char**)malloc(sizeof(char*) * capacity);

	for (int i = 0; i < n; i++) {
		copy_name[i] = names[i];
		copy_number[i] = numbers[i];
	}

	names = copy_name;
	numbers = copy_number;
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

void add(char* name, char* number) {
	int num = n - 1;

	if (n > capacity) {
		arr_create();
	}

	while (1) {
		if (num < 0) {
			break;
		}
		if (strcmp(names[num], name) > 0) {
			names[num + 1] = names[num];
			numbers[num + 1] = numbers[num];
			num--;
		}
	}

	names[num + 1] = _strdup(name);
	numbers[num + 1] = _strdup(number);
	n++;
	printf("%s was added successfully\n", name);
}

void load(char* fileName) {
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];
	int num = 0;

	FILE* in_fp = fopen(fileName, "r");

	while (fscanf(in_fp, "%s", buf1) != EOF) {
		fscanf(in_fp, "%s", buf2);
		names[num] = _strdup(buf1);
		numbers[num] = _strdup(buf2);
		num++;
	}
	n = strlen(buf1);

	fclose(in_fp);
}

void find(char* name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(names[i], name) == 0) {
			printf("%s\n", numbers[i]);
			break;
		}
	}
}

void status() {
	for (int i = 0; i < n; i++) {
		if (names[i] == NULL) {
			break;
		}
		printf("%s %s\n", names[i], numbers[i]);
	}
	printf("Total %d person\n", n);
}

void remove(char* name) {
	int num = 0;
	int count = 1;
	while (1) {
		if (count == 0) {
			break;
		}
		if (strcmp(names[num], name) == 0){
			for (num; num < n; num++) {
				names[num] = names[num + 1];
				numbers[num] = numbers[num + 1];
			}
			count = 0;
		}
		num++;
	}
	n--;
	printf("%s was deleted successfully\n", name);
}

void save(char *fileName) {
	int i = 0;
	FILE* write_fp = fopen(fileName, "w");

	while (1) {
		if (i == n) {
			break;
		}
		fprintf(write_fp, "%s %s\n", names[i], numbers[i]);
		i++;
	}
	fclose(write_fp);
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
		
		read_line(command_line, BUFFER_SIZE);

		command = strtok(command_line, delim);
		if (strcmp(command, "read") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("File name required\n");
				continue;
			}
			else if (argument1 != NULL) {
				load(argument1);
			}
		}

		if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);

			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid arguments\n");
				continue;
			}
			else if (argument1 != NULL && argument2 != NULL) {
				add(argument1, argument2);
			}
		}

		if (strcmp(command, "status") == 0) {
			status();
		}

		if (strcmp(command, "delete") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("Invalid arguments\n");
				continue;
			}
			else if (argument1 != NULL) {
				remove(argument1);
			}
		}

		if (strcmp(command, "save") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);

			if (argument1 == NULL || argument2 == NULL || strcmp(argument1, "as") != 0) {
				printf("Invalid arguments\n");
				continue;
			}
			else if (argument1 != NULL && strcmp(argument1, "as") == 0) {
				save(argument2);
			}
		}

		if (strcmp(command, "exit") == 0) {
			break;
		}
	}
}

int main() {
	init_directory(); // names, numbers 积己
	process_command(); // 疙飞 罐酒 贸府何盒

	return 0;
}