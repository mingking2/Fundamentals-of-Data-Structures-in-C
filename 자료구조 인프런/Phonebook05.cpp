#define _CRT_SECURE_NO_WARNINGS
#define INIT_CAPACITY 100
#define BUFFER_LENGTH 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char* name;
	char* number;
	char* email;
	char* group;
}Person;

Person** directory;
int capacity;
int n;

void init();
int read_line(FILE* fp, char str[], int n);
void reallocate();
void load(char* fileName);
void add(char* name, char* number, char* email, char* group);
int compose_name(char str[], int limit);
void handle_add(char* name);
void save(char* fileName);
int search(char* name);
void print_person(Person* p);
void remove(char* name);
void find(char* name);


int main() {
	char command_line[BUFFER_LENGTH];
	char* command, * argument;
	char name_str[BUFFER_LENGTH];
	
	init();

	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
			continue;

		command = strtok(command_line, " ");

		if (strcmp(command, "read") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invalid arguments.\n");
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
			printf("%s was added successfully.\n", name_str);
		}
		else if (strcmp(command, "find") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}
			find(name_str);
		}
		else if (strcmp(command, "status") == 0) {
			for (int i = 0; i < n; i++)
				print_person(directory[i]);
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
				printf("Invalid arguments.\n");
				continue;
			}
			save(argument);
		}
		else if (strcmp(command, "exit") == 0)
			break;
	}
	return 0;
}


void init() {
	directory = (Person**)malloc(INIT_CAPACITY * sizeof(Person*));
	capacity = INIT_CAPACITY;
	n = 0;
}

int read_line(FILE* fp, char str[], int n) {
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
		if (i < n)
			str[i++] = ch;
	str[i] = '\0';
	return i;
}

void load(char* fileName) {
	char buffer[BUFFER_LENGTH];
	char* name, * number, * email, * group;
	char* token;

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	while (1) {
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)
			break;
		name = strtok(buffer, "#");
		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			number = NULL;
		else
			number = _strdup(token);

		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			email = NULL;
		else
			email = _strdup(token);

		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			group = NULL;
		else
			group = _strdup(token);
		add(_strdup(name), number, email, group);
	}
	fclose(fp);
}

void add(char* name, char* number, char* email, char* group) {
	if (n >= capacity)
		reallocate();

	int i = n - 1;
	while (i >= 0 && strcmp(directory[i]->name, name) > 0) {
		directory[i + 1] = directory[i];
		i--;
	}

	directory[i + 1] = (Person*)malloc(sizeof(Person));

	directory[i + 1]->name = name;
	directory[i + 1]->number = number;
	directory[i + 1]->email = email;
	directory[i + 1]->group = group;

	n++;

}

void reallocate() {
	capacity *= 2;
	Person** tmp = NULL;
	tmp = (Person**)malloc(capacity * sizeof(Person*));
	for (int i = 0; i < n; i++)
		tmp[i] = directory[i];
	free(directory);
	directory = tmp;
}

int compose_name(char str[], int limit) {
	char* ptr;
	int length = 0;

	ptr = strtok(NULL, " ");
	if (ptr == NULL)
		return 0;
	strcpy(str, ptr);
	length += strlen(str);

	while ((ptr = strtok(NULL, " ")) != NULL) {
		if (length + strlen(ptr) + 1 < limit) {
			str[length++] = ' ';
			str[length] = '\0';
			strcat(str, ptr);
			length += strlen(ptr);
		}
	}

	return length;
}

void handle_add(char* name) {
	char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];

	printf("Phone : ");
	read_line(stdin, number, BUFFER_LENGTH);

	printf("Email : ");
	read_line(stdin, email, BUFFER_LENGTH);

	printf("Group : ");
	read_line(stdin, group, BUFFER_LENGTH);

	add(name, (char*)(strlen(number) > 0 ? _strdup(number) : NULL),
		(strlen(email) > 0 ? _strdup(email) : NULL),
		(strlen(group) > 0 ? _strdup(group) : NULL));


}

void save(char* fileName) {
	int i;

	FILE* fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	for (i = 0; i < n; i++) {
		fprintf(fp, "%s#", directory[i]->name);
		fprintf(fp, "%s#", directory[i]->number);
		fprintf(fp, "%s#", directory[i]->email);
		fprintf(fp, "%s#\n", directory[i]->group);
	}
	fclose(fp);

}

int search(char* name) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(name, directory[i]->name) == 0) {
			return i;
		}
	}
	return -1;
}

void print_person(Person* p) {
	printf("%s.\n", p->name);
	printf("	Phone : %s\n", p->number);
	printf("	Email : %s\n", p->email);
	printf("	Group : %s\n", p->group);

}

void find(char* buf1) {
	int index = search(buf1);
	if (index == -1)
		printf("No person named '%s' exists.\n", buf1);
	else {
		printf("%s : \n", directory[index]->name);
		printf("	Phone : %s\n", directory[index]->number);
		printf("	Email : %s\n", directory[index]->email);
		printf("	Group : %s\n", directory[index]->group);
	}

}


void remove(char* name) {
	int index = search(name);
	if (index == -1) {
		printf("No person named '%s' exists.\n", name);
		return;
	}
	
	Person* p = directory[index];
	for (int j = index; j < n - 1; j++) {
		directory[j] = directory[j + 1];
	}
	n--;

	free(p);
	printf("'%s' was deleted successfully.\n", name);

}

