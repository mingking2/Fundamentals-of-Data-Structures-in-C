#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 100
#define BUFFER_LENGTH 100
//왜 마지막이 # 일까

typedef struct person {
    char* name;
    char* number;
    char* email;
    char* group;
} Person;

Person directory[CAPACITY];
int n = 0;

int read_line(FILE* fp, char str[], int n) {
    int ch, i = 0;
    while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
        if (i < n) {
            str[i++] = ch;
        }
    }
    str[i] = '\0';
    return i;
}

void add(char* name, char* number, char* email, char* group) {
    directory[n].name = _strdup(name);
    directory[n].number = _strdup(number);
    directory[n].email = _strdup(email);
    directory[n].group = _strdup(group);
    n++;
}

void load(char* fileName) {
    char buffer[BUFFER_LENGTH];
    char* name, * number, * email, * group;
    int num = 0;
    FILE* in_fp = fopen(fileName, "r");

    while (1) {
        read_line(in_fp, buffer, BUFFER_LENGTH);
        name = strtok(buffer, "#");
        if (name == NULL) {
            break;
        }
        number = strtok(NULL, "#");
        email = strtok(NULL, "#");
        group = strtok(NULL, "#");
        add(name, number, email, group);
        num++;
    }
    fclose(in_fp);
}

int compose_name(char str[], int limit) {
    char* name;
    char* name_length;
    int length = 0;
    name = strtok(NULL, " ");
    name_length = _strdup(name);
    while (1) {
        name = strtok(NULL, " ");
        if (name == NULL) {
            break;
        }
        name_length = strcat(name_length, " ");
        name_length = strcat(name_length, name);
    }
    str = strcpy(str, name_length);
    length = strlen(str);
    return length;
}

void handle_add(char* name) {
    char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
    char empty[] = " ";
    printf("Phone : ");
    gets_s(number);
    printf("Email : ");
    gets_s(email);
    printf("Group : ");
    gets_s(group);

    int num = n - 1;
    int count = n;
    while (1) {
        if (num <= 0) {
            break;
        }
        if (strcmp(directory[num].name, name) > 0) {
            directory[num + 1].name = directory[num].name;
            directory[num + 1].number = directory[num].number;
            directory[num + 1].email = directory[num].email;
            directory[num + 1].group = directory[num].group;
            count--;
        }
        num--;
    }
    directory[count].name = _strdup(name);
    if (strcmp(number, empty) == 0) {
        directory[num + 1].number = _strdup(" ");
    }
    else {
        directory[count].number = _strdup(number);
    }
    if (strcmp(email, empty) == 0) {
        directory[count].email = _strdup(" ");
    }
    else {
        directory[count].email = _strdup(email);
    }
    if (strcmp(group, empty) == 0) {
        directory[count].group = _strdup(" ");
    }
    else {
        directory[count].group = _strdup(group);
    }
    n++;
}

void save(char* fileName) {
    int i = 0;
    FILE* write_fp = fopen(fileName, "w");

    while (1) {
        if (i == n) {
            break;
        }
        fprintf(write_fp, "%s#%s#%s#%s#\n", directory[i].name, directory[i].number, directory[i].email, directory[i].group);
        i++;
    }
    fclose(write_fp);
}

void print_person(Person P) {
    printf("%s\n", P.name);
    printf("   Phone : %s\n", P.number);
    printf("   Email : %s\n", P.email);
    printf("   Group : %s\n", P.group);
}

void status() {
    for (int i = 0; i < n; i++) {
        print_person(directory[i]);
    }
    printf("Total %d person\n", n);
}

int search(char* name) {
    int i;

    for (i = 0; i < n; i++) {
        if (strcmp(name, directory[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

void find(char* name) {
    int i = search(name);
    print_person(directory[i]);
}

void remove(char* name) {
    int num = 0;
    int count = 1;
    while (1) {
        if (count == 0) {
            break;
        }
        if (strcmp(directory[num].name, name) == 0) {
            for (num; num < n; num++) {
                directory[num].name = directory[num + 1].name;
                directory[num].number = directory[num + 1].number;
                directory[num].email = directory[num + 1].email;
                directory[num].group = directory[num + 1].group;
            }
            count = 0;
        }
        num++;
    }
    n--;
    printf("%s was deleted successfully\n", name);
}

int main() {
    char command_line[BUFFER_LENGTH];
    char* command, * argument;
    char name_str[BUFFER_LENGTH];


    while (1) {
        printf("$ ");
        if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0) {
            continue;
        }
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
                printf("INvalid arguments.\n");
                continue;
            }
            argument = strtok(NULL, " ");
            if (argument == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            save(argument);
        }
        else if (strcmp(command, "exit") == 0) {
            break;
        }
    }
    return 0;
}