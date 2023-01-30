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

void add(char*,char*);
void find(char*);
void status();
void remove(char*);
void load(char*);
void save(char*);
void reallocate();

int read_line(char str[], int limit);

void init_directory();
void process_command();

int main() {
	init_directory();
	process_command();

	return 0;
}

void init_directory() {
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}

int read_line(char str[], int limit) {
	int ch, i = 0;

	while ((ch = getchar()) != '\n')
		if (i < limit - 1)
			str[i++] = ch;

	str[i] = '\0';
	return i;
}

void process_command() {
	char command_line[BUFFER_SIZE];
	char* command, * argument1, * argument2;

	while (1) {
		printf("$ ");
		
		if (read_line(command_line, BUFFER_SIZE) <= 0)
			continue;

		command = strtok(command_line, delim);
	
		if (command == NULL) continue;

		if (strcmp(command_line, "read") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("File name required.\n");
				continue;
			}
			load(argument1);
		}
		else if (strcmp(command_line, "add") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);
			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			add(argument1, argument2);

			printf("%s was added successfully.\n", argument1);
		}
		else if (strcmp(command_line, "status") == 0) {
			status();
		}
		else if (strcmp(command_line, "find") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			find(argument1);
		}
		else if (strcmp(command_line, "delete") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			remove(argument1);
		}
		else if (strcmp(command_line, "save") == 0) {
			argument1 = strtok(NULL, delim);
			if (strcmp(argument1, "as") == 0) {
				argument1 = strtok(NULL, delim);
				save(argument1);
			}
			else {
				printf("Invalid command format.\n");
				continue;
			}
		}
		else if(strcmp(command_line, "exit") == 0){
			break;
		}
		
	}

}

void load(char* command) {	
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	FILE* fp = fopen(command, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		add(buf1, buf2);
	}
	fclose(fp);

}


void save(char* name) {
	int i;

	FILE* fp = fopen(name, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	for (i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp);
}


void add(char*buf1,char*buf2) {
	if (n >= capacity) {
		reallocate();
	}

	int i = n - 1;
	while (i >= 0 && strcmp(names[i], buf1) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i + 1] = _strdup(buf1);
	numbers[i + 1] = _strdup(buf2);

	n++;
	
}


int search(char* name) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0) {
			return i;
		}
	}
	return -1;
}


void find(char* buf1) {


	int index = search(buf1);
	if (index == -1)
		printf("No person named '%s' exists.\n", buf1);
	else
		printf("%s\n", numbers[index]);
}


void status() {
	int i;
	for (i = 0; i < n; i++)
		printf("%s	%s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);
}


void remove(char* name) {
	
	int index = search(name);
	if (index == -1) {
		printf("No person named '%s' exists.\n", name);
		return;
	}

	int j = index;
	for (; j < n - 1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}

	n--;
	printf("'%s' was deleted successfully.\n", name);
}

void reallocate() {
	int i;
	capacity *= 2;
	char** tmp1 = (char**)malloc(capacity * sizeof(char*));
	char** tmp2 = (char**)malloc(capacity * sizeof(char*));

	for (i = 0; i < n; i++) {
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}
	free(names);
	free(numbers);

	names = tmp1;
	numbers = tmp2;
}