#define _CRT_SECURE_NO_WARNINGS
#define BUFFER_SIZE 100
#include <stdio.h>

int read_line(char str[], int n) {
	int ch, i = 0;
	while ((ch = getchar()) != '\n')
		if (i < n)
			str[i++] = ch;
	str[i] = '\0';
	return i;
}

int main() {
	char buffer[BUFFER_SIZE];
	int k;
	while (1) {
		printf("$ ");
		k = read_line(buffer, BUFFER_SIZE);
		printf("%s:%d\n", buffer, k);
	}
	return 0;
}


