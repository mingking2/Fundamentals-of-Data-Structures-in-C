#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define BUFFER_LENGTH 100

typedef struct person {
	char* name;
	char* number;
	char* email;
	char* group;
}Person;

Person directory[CAPACITY];
int n = 0;

int read_line(FILE* fp, char str[], int n) { // o
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		if (i < n)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

void add(char* name, char* number, char* email, char* group) { // o
	int i = n - 1;
	while (i >= 0 && strcmp(directory[i].name, name) > 0) {
		directory[i + 1] = directory[i];
		i--;
	}

	directory[i + 1].name = _strdup(name);
	directory[i + 1].number = _strdup(number);
	directory[i + 1].email = _strdup(email);
	directory[i + 1].group = _strdup(group);
	n++;
}

void load(char* fileName) { // o
	char buffer[BUFFER_LENGTH];
	char* name, * number, * email, * group;

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("fail\n");
		return;
	}
	
	while (1) {
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)
			break;
		name = strtok(buffer, "#");
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group = strtok(NULL, "#");
		add(name, number, email, group);
	}
	fclose(fp);
}

int compose_name(char str[], int limit) {
	char* ddd;
	int length = 0;

	ddd = strtok(NULL, " "); 
	if (ddd == NULL) return 0;
	strcpy(str, ddd);	
	length += strlen(ddd);	

	while ((ddd = strtok(NULL, " ")) != NULL) {
		if (strcmp(ddd, " ") != 0) {
			str[length] = ' ';
			str[++length] = '\0';
			strcat(str, ddd);
			length += strlen(ddd);
		}
	}

	return length;
}

void handle_add(char* name) {  // $ add ÇßÀ» ¶§
	char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
	char empty[] = " ";

	printf(" Phone: ");
	read_line(stdin, number, BUFFER_LENGTH);

	printf(" Email: ");
	read_line(stdin, email, BUFFER_LENGTH);

	printf(" Group: ");
	read_line(stdin, group, BUFFER_LENGTH);

	add(name, number, email, group);

	printf("%s was added successfully.\n", name);
}

void save(char* fileName) { // o
	FILE* fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("fail\n");
		return;
	}
	for (int i = 0; i < n; i++)	{
		fprintf(fp, "%s#%s#%s#%s#\n", directory[i].name, directory[i].number, directory[i].email, directory[i].group);
	}
	fclose(fp);
}

int search(char* name) { // o
	int i;
	for (int i = 0; i < n; i++) {
		if (strcmp(name, directory[i].name) == 0)
			return i;
	}
	return -1;
}

void print_person(Person P) { // o
	printf("%s.\n", P.name);
	printf("    Phone : %s\n", P.number);
	printf("    Email : %s\n", P.email);
	printf("    Group : %s\n", P.group);
}

void remove(char* name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(directory[i].name, name) == 0) {
			for (int j = i; j < n - 1; j++)	directory[j] = directory[j + 1];
			n--;
			printf("'%s' was deleted successfully. \n", name);
			return;
		}
	}
	printf("NO person named '%s' exists\n", name);
}

void find(char* name) {
	if (search(name) == -1) printf("No person named '%s' exists.\n", name);
	else print_person(directory[search(name)]);
}

void status() { // o
	for (int i = 0; i < n; i++) {
		print_person(directory[i]);
	}
	printf("Total %d person.\n", n);
}

int main() {
	char command_line[BUFFER_LENGTH];
	char* command, * argument;
	char name_str[BUFFER_LENGTH];

	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
			continue;

		command = strtok(command_line, " ");

		if (strcmp(command, "read") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invaild arguments.\n");
				continue;
			}
			load(argument);
		}
		else if (strcmp(command, "add") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}
			handle_add(name_str);
		}
		else if (strcmp(command, "find") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}
			find(name_str);
		}
		else if (strcmp(command, "status") == 0) {
			status();
		}
		else if (strcmp(command, "delete") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Invalid arguments.\n");
				continue;
			}
			remove(name_str);
		}
		else if (strcmp(command, "save") == 0) {
			argument = strtok(NULL, " ");
			if (strcmp(argument, "as") != 0) {
				printf("Invalid arguments.\n");
				continue;
			}
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invaild arguments.\n");
				continue;
			}
			save(argument);
		}
		else if (strcmp(command, "exit") == 0)
			break;
	}
	return 0;
}