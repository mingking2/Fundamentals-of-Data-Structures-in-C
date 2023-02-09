#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 100
#define BUFFER_LENGTH 100
typedef struct person {
	char* names;
	char* numbers;
	char* email;
	char* group;
}Person;
Person directory[CAPACITY];
void load(char* fileName);
void add(char* name, char* number, char* email, char* group);
int read_line(FILE* fp, char str[], int n);
int compose_name(char str[], int limit);
void handle_add(char* name);
void save(char* fileName);
int search(char* name);
void remove(char* name);
void print_person(Person P[]);
void find(char* name);
int n = 0;
int main() { //메인함수
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
		}
		else if (strcmp(command, "find") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}
			find(name_str);
		}
		else if (strcmp(command, "status") == 0) {
			print_person(directory);
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
void find(char* name) {
	int i = search(name);
	printf("%s.\n", directory[i].names);
	printf("    Phone : %s\n", directory[i].numbers);
	printf("    Email : %s\n", directory[i].email);
	printf("    Group : %s\n", directory[i].group);
}
int read_line(FILE* fp, char str[], int n) { //command_line을 읽어주는 함수
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
	FILE* fp = fopen("directory.txt", "r");

	while (fgets(buffer, BUFFER_LENGTH, fp) != NULL) {
		name = strtok(buffer, "#");
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group = strtok(NULL, "#");
		printf("%s,%s,%s,%s\n", name, number, email, group);
		add(name, number, email, group);
	}
	fclose(fp);
}
void add(char* name, char* number, char* email, char* group) {
	directory[n].names = _strdup(name);
	directory[n].numbers = _strdup(number);
	directory[n].email = _strdup(email);
	directory[n].group = _strdup(group);
	/*print_person(directory[n]);*/
	n++;
}
int compose_name(char str[], int limit) { //strcat 써야함
	int length = 0;
	char* ptr;
	ptr = strtok(NULL, " ");
	strcpy(str, ptr);
	length += strlen(str);

	//str[length] = NULL;

	while ((ptr = strtok(NULL, " ")) != NULL) {

		str[length++] = ' ';
		str[length] = '\0';
		strcat(str, ptr);

		length += strlen(ptr);
	}
	return length;
}
void handle_add(char* name) {
	char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
	char empty[] = " ";

	printf("number : ");
	gets_s(number);
	printf("email : ");
	gets_s(email);
	printf("group : ");
	gets_s(group);
	int j = n, i;
	for (i = 0; i < n; i++) {
		if (strcmp(directory[i].names, name) > 0) {     //문자열 크기에 따른 정렬
			while (j > i) {
				directory[j] = directory[j - 1];

				j--;
			}
			break;
		}
	}
	directory[i].names = _strdup(name);
	directory[i].numbers = _strdup(number);
	directory[i].email = _strdup(email);
	directory[i].group = _strdup(group);
	n++;


	printf("%s was added successfulluy.\n", name);
}
void save(char* fileName) {
	FILE* out_fp = fopen(fileName, "w");
	for (int i = 0; i < n; i++) {
		fprintf(out_fp, "%s#", directory[i].names);
		if (strcmp(directory[i].numbers, "") == 0)
			fprintf(out_fp, " #");
		else
			fprintf(out_fp, "%s#", directory[i].numbers);
		if (strcmp(directory[i].email, "") == 0)
			fprintf(out_fp, " #");
		else
			fprintf(out_fp, "%s#", directory[i].email);
		if (strcmp(directory[i].numbers, "") == 0)
			fprintf(out_fp, " #\n");
		else
			fprintf(out_fp, "%s#\n", directory[i].group);
	}
	fclose(out_fp);
	printf("saved successfully\n");

}
int search(char* name) {//index값 찾는ㄴ거
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(name, directory[i].names) == 0) {
			return i;
		}
	}
	return -1;
}
void print_person(Person P[]) {
	for (int i = 0; i < n; i++) {
		printf("%s.\n", P[i].names);
		printf("    Phone : %s\n", P[i].numbers);
		printf("    Email : %s\n", P[i].email);
		printf("    Group : %s\n", P[i].group);
	}
}

void remove(char* name) {
	int i = 0, j = n;
	for (i = 0; i < n; i++) {
		if (strcmp(directory[i].names, name) == 0) {
			while (i < j) {
				directory[i] = directory[i + 1];
				i++;
			}
			n--;
			printf("%s cut!\n", name);
			break;
		}
		else if (strcmp(directory[i].names, name) != 0 && i == n - 1)
			printf("No person named %s exists\n", name);
	}
}