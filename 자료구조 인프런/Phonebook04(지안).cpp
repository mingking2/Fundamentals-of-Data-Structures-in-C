#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_LENGTH 100

//read directory1.txt

typedef struct person {
    char* name;
    char* number;
    char* email;
    char* group;
}Person;

Person directory[CAPACITY];
int n = 0;

int read_line(FILE* fp, char str[], int n) {
    int ch, i = 0;
    while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
        if (i < n)
            str[i++] = ch;
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

int compose_name(char str[], int limit) {
    char* s = strtok(NULL, " ");
    str = strcpy(str, s);

    while (1)
    {
        s = strtok(NULL, " ");
        if (s == NULL)  break;
        str = strcat(str, " ");
        str = strcat(str, s);
    }
    
    int length = strlen(str);
    //printf("str %s %x\n", str, &str);
    return length;
}

void handle_add(char* name) {
    char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
    char empty[] = " ";

    int i = n - 1;

    printf("phone: ");
    read_line(stdin, number, BUFFER_LENGTH);
    if (strlen(number) == 0) strcpy(number, empty);

    printf("email: ");
    read_line(stdin, email, BUFFER_LENGTH);
    if (strlen(email) == 0) strcpy(email, empty);

    printf("group: ");
    read_line(stdin, group, BUFFER_LENGTH);
    if (strlen(group) == 0) strcpy(group, empty);

    n++;
    //bubble
    while (i >= 0 && strcmp(directory[i].name, name) > 0) {
        directory[i + 1] = directory[i];
        i--;
    }
    
    directory[++i].name = _strdup(name);
    directory[i].number = _strdup(number);
    directory[i].email = _strdup(email);
    directory[i].group = _strdup(group);

    printf("%s was added successfully.\n", name);

    return;
}

void save(char* fileName) {
    FILE* file = fopen(fileName, "w");
    char* name, number, email, group;

    if (file == NULL)
        printf("File name required");

    //fprintf(file, "%s#%s#%s#%s#", directory[0].name, directory[0].number, directory[0].email, directory[0].group);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s#", directory[i].name);
        fprintf(file, "%s#", directory[i].number);
        fprintf(file, "%s#", directory[i].email);
        fprintf(file, "%s#\n", directory[i].group);
    }
    n = 0;
    fclose(file);
}

int search(char* name) {
    int i;
    for (i = 0;i < n;i++) {
        if (strcmp(name, directory[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

void print_person(Person P) {
    printf("%s.\n", P.name);
    printf("    Phone : %s\n", P.number);
    printf("    Email : %s\n", P.email);
    printf("    Group : %s\n", P.group);
}

void find(char* name_str) {
    print_person(directory[search(name_str)]);
}

void load(char* fileName) {
    char buffer[BUFFER_LENGTH];
    char* name, * number, * email, * group;

    FILE* pFile = fopen(fileName, "r");

    if (pFile == NULL) {
        printf("File name required\n");
        return;
    }
 
    while (1) {
        if(read_line(pFile, buffer, BUFFER_LENGTH)<=0) return;
        name = strtok(buffer, "#");
        number = strtok(NULL, "#");
        email = strtok(NULL, "#");
        group = strtok(NULL, "#");
        add(name, number, email, group);
    }
}

void remove(char* name) {
    int index = -1;

    for (int i = 0; i < n; i++) {
        if (strcmp(directory[i].name, name) == 0) {
            if (i == n - 1) {
                n--;
                printf("%s was deleted successfully.\n", name);
                return;
            }
            for (int j = i; j < n - 1; j++) {
                directory[j] = directory[j + 1];
                directory[j] = directory[j + 1];
                index = i;
            }
        }
    }

    if (index == -1)
        printf("No person named '%s' exists.\n", name);

    else {
        n--;
        printf("%s was deleted successfully.\n", name);
    }
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
            //printf("\nafter %s %x\n", name_str, &name_str);
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
            for (int i = 0; i < n; i++) {
                print_person(directory[i]);
            }
            printf("total %d people\n", n);
        }
        else if (strcmp(command, "delete") == 0) {
            //read_line(stdin, name_str, BUFFER_LENGTH);
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
        else printf("명령어를 다시 입력하세요.\n");
    }
    return 0;
}