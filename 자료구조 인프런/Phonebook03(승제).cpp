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
char buffer[100];

char delim[] = " ";
void process_command();
void read(char * fileName);
void add(char* name, char* number);
void find(char* name);
void status();
void remove(char* name);
void save(char* fileName);
void init_directory();
int read_line(char str[], int limit);

int main()
{
    /*char command[BUFFER_SIZE] = {};*/
    init_directory();
    
    process_command();    
    printf("\n프로그램 종료!!\n");
}

void init_directory() {
    names = (char**)malloc(capacity* sizeof(char*));
    numbers = (char**)malloc(capacity * sizeof(char*));
}

void process_command() {
    char command_line[BUFFER_SIZE];                       //한 라인을 통째로 읽어오기 위한 버퍼
    char* command = {}, * argument1 = {}, * argument2;

    while (1)       //strcmp(command, "exit") != 0
    {
        printf("$ ");
        
        read_line(command_line, BUFFER_SIZE);    //한번에 명령어 받아버리기
        command = strtok(command_line," ");
        argument1 = strtok(NULL," ");
        argument2 = strtok(NULL, " ");
        if (strcmp(command, "read") == 0){
            if (argument1 == NULL)
                printf("File name required\n");
            else
                read(argument1);
        }
        else if (strcmp(command, "add") == 0){
            if (argument1 == NULL || argument2 == NULL)
                printf("Invalid arguments\n");
            else
                add(argument1, argument2);
        }
        else if (strcmp(command, "find") == 0)
            find(argument1);
        else if (strcmp(command, "status") == 0) 
            status();
        else if (strcmp(command, "remove") == 0)
            remove(argument1);
        else if (strcmp(command, "save") == 0){
            if (strcmp(argument1,"as") != 0 || argument2 == NULL)
                printf("Invalid command format.%s %s\n",argument1, argument2);
            else
                save(argument2);
        }
        else if (strcmp(command, "exit") == 0)
            break;
    }
}

int read_line(char str[], int limit) {  //명령어 받기
    int ch, i = 0;

    while ((ch = getchar()) != '\n') {
        if (i < limit - 1)
            str[i++] = ch;
    }
    str[i] = '\0';
    return i;

}

void read(char * fileName) {
    FILE* fp = fopen(fileName, "r");
    /*FILE* fp = fopen("directory.txt", "r");*/
    int i = 0;
    while (fscanf(fp, "%s", buffer) != EOF)
    {
        if (i % 2 == 0)
            names[n] = _strdup(buffer);
        else {
            numbers[n] = _strdup(buffer);
            n++;
        }
        i++;
    }
    fclose(fp);
}
void add(char * name, char *number) {
    int j = n;
    int i = 0;

    for (i = 0; i < n; i++){
        if (strcmp(name, names[i]) < 0){
            while (j > i)
            {
                names[j] = (names[j - 1]);
                numbers[j] = (numbers[j - 1]);
                j--;
            }
            break;
        }
    }
    names[i] = _strdup(name);
    numbers[i] = _strdup(number);
    n++;
}
void find(char * name) {
    
    for (int i = 0; i < n; i++)
    {
        if (strcmp(names[i], name) == 0) {
            printf("%s\n", numbers[i]);
            break;
        }
        else if (strcmp(names[i], name) != 0 && i == n - 1)
            printf("No person named %s exists\n", name);
    }
}
void status() {
    for (int i = 0; i < n; i++)
    {
        printf("%s %s\n", names[i], numbers[i]);
    }
    printf("Total %d persons\n", n);

}
void remove(char * name) {
    int i = 0;
    int j = n;
    for (i = 0; i < n; i++)
    {

        if (strcmp(names[i], name) == 0) {

            while (i < j)
            {
                names[i] = names[i + 1];
                numbers[i] = numbers[i + 1];
                i++;
            }
            n--;
            break;
        }
        else if (strcmp(names[i], name) != 0 && i == n - 1)
            printf("No person named %s exists\n", name);
    }
}
void save(char *fileName)
{
    FILE* out_fp = fopen(fileName, "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(out_fp, "%s ", names[i]);
        fprintf(out_fp, "%s\n", numbers[i]);
    }

    fclose(out_fp);
}